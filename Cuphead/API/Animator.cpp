#include "Animator.h"
#include "Resources.h"
#include "GameObject.h"
#include "Time.h"
namespace yeram_client
{
	Animator::Animator()
		:Component(EComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{
		SetName(L"Animator");
	}


	Animator::~Animator()
	{

	}

	void Animator::Initialize()
	{
		//Play(mOwner->GetName(), true);
	}

	void Animator::Update()
	{
		if (mActiveAnimation != nullptr)
		{
			mActiveAnimation->Update();


			if (mLimitTime != 0)
			{
				mCurTime += Time::DeltaTime();
				if (mbLoop == true
					&& mActiveAnimation->IsComplete() == true)
				{
					mActiveAnimation->Reset();
				}
				if (mLimitTime <= mCurTime)
				{
					Stop();
				}
				return;
			}
			if (mbUseFsm == false)
			{
				if (mbLoop == true
					&& mActiveAnimation->IsComplete() == true)
				{
					mActiveAnimation->Reset();
				}
			}
			else // 일반 play 
			{
				if (mActiveAnimation->IsComplete() == true)
				{
					std::wstring str = mActiveAnimation->GetName();
					Events* event = FindEvents(str);
					if (event != nullptr)
					{
						event->mCompleteEvent();
						mComEventCnt++;
					}
					if (mbLoop == true)
					{
						mActiveAnimation->Reset();
					}
					
					//else if (mbLoop == false)
					//{
					//	/*	Animator::Events* events
					//			= FindEvents(mActiveAnimation->GetName());
					//		if (events != nullptr)
					//			events->mEndEvent();*/
					//}
				}
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mbActive == false)
			return;
		if (mActiveAnimation != nullptr)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void Animator::Release()
	{
		for (auto ani : mAnimations)
		{
			delete ani.second;
			ani.second = nullptr;
		}
		mAnimations.clear();
		for (auto event : mEvents)
		{
			delete event.second;
			event.second = nullptr;
		}
		mEvents.clear();
	}

	void Animator::CreateAnimation(const std::wstring& _name, Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration, const std::vector<Vector2> _origin_size, bool _alpha)
	{
		Animation* ani = FindAnimation(_name);
		if (ani != nullptr)
		{
			return;
		}
		ani = new Animation();
		mSpriteSheet = _sheet;
		ani->Create(_sheet, _leftTop, _col, _row, _size, _offset, _duration, _origin_size, _alpha);
		ani->SetName(_name);
		ani->SetAnimator(this);
		Events* event = new Events();
		mAnimations.insert(std::make_pair(_name, ani));
		mEvents.insert(std::make_pair(_name, event));
	}

	std::wstring Animator::CreateAnimations(const std::wstring& _path, Vector2 _offset, float _duration, bool _alpha)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(_path);
		std::vector<Image*> images = {};
		std::vector<Vector2> sizes = {};
		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
		if (FindAnimation(key) != nullptr)
			return key;

		for (auto& itr : std::filesystem::recursive_directory_iterator(_path))
		{
			const std::wstring ext = itr.path().extension();
			if (ext != L".bmp")
				continue;
			std::wstring fileName = itr.path().filename();
			std::wstring fullName = _path + L"\\" + fileName;
			Image* image = Resources::Load<Image>(fileName, fullName);
			images.push_back(image);

			Vector2 size = Vector2{ (float)image->GetWidth(),(float)image->GetHeight() };
			sizes.push_back(size);
			if (width < size.x)
			{
				width = size.x;
			}
			if (height < size.y)
			{
				height = size.y;
			}
			fileCount++;
		}

		mSpriteSheet = Image::Create(key, width * fileCount, height);

		int index = 0;
		for (Image* image : images)
		{
			int centerX = (width - image->GetWidth()) / 2;
			int centerY = (height - image->GetHeight());

			BitBlt(mSpriteSheet->GetHDC()
				, width * index + centerX
				, 0 + centerY
				, image->GetWidth(), image->GetHeight()
				, image->GetHDC(), 0, 0, SRCCOPY);


			index++;

		}

		CreateAnimation(key, mSpriteSheet, Vector2::Zero, index, 1, index, _offset, _duration, sizes, _alpha);
		return key;
	}

	Animation* Animator::FindAnimation(const std::wstring& _name)
	{
		auto itr = mAnimations.find(_name);
		if (itr == mAnimations.end())
			return nullptr;
		return itr->second;
	}

	void Animator::Play(const std::wstring& _name, bool _loop, bool _use_fsm)
	{
		mComEventCnt = 0;
		mbUseFsm = _use_fsm;
		Animator::Events* prev_events = nullptr;
		if (mActiveAnimation != nullptr)
		{
			if (mActiveAnimation->GetName().compare(_name) == 0)
			{
				if (_loop == false)
				{
					mActiveAnimation->Reset();
				}
				return;
			}
			prev_events
				= FindEvents(mActiveAnimation->GetName());
		}

		mActiveAnimation = FindAnimation(_name);

		if (prev_events != nullptr)
			prev_events->mEndEvent();


		mActiveAnimation->Reset();
		mbLoop = _loop;

		Animator::Events* events
			= FindEvents(mActiveAnimation->GetName());
		if (events != nullptr)
			events->mStartEvent();
		mLimitTime = 0;
	}

	void Animator::Play(const std::wstring& _name, bool _loop, double _time, bool _use_fsm)
	{
		mComEventCnt = 0;
		mbUseFsm = _use_fsm;
		Animator::Events* prev_events = nullptr;
		if (mActiveAnimation != nullptr)
		{
			if (mActiveAnimation->GetName().compare(_name) == 0)
				return;

			prev_events
				= FindEvents(mActiveAnimation->GetName());
		}

		mActiveAnimation = FindAnimation(_name);

		if (prev_events != nullptr)
			prev_events->mEndEvent();


		mActiveAnimation->Reset();
		mbLoop = _loop;

		Animator::Events* events
			= FindEvents(mActiveAnimation->GetName());
		if (events != nullptr)
			events->mStartEvent();
		mLimitTime = _time;
	}

	void Animator::Stop()
	{
		mLimitTime = 0;
		mCurTime = 0;
		if (mbUseFsm == true)
		{
			FSMStop();
			return;
		}
		if (mActiveAnimation != nullptr)
		{
			mActiveAnimation->Stop();

			Animator::Events* events
				= FindEvents(mActiveAnimation->GetName());
			if (events != nullptr)
				events->mEndEvent();
		}
	}

	void Animator::FSMStop()
	{
		mLimitTime = 0;
		mCurTime = 0;
		if (mActiveAnimation != nullptr)
		{
			Animator::Events* events
				= FindEvents(mActiveAnimation->GetName());
			mActiveAnimation = nullptr;
			if (events != nullptr)
				events->mEndEvent();
		}
	}

	const std::wstring& Animator::GetCurAniName()
	{
		return mActiveAnimation->GetName();
	}

	const Vector2& Animator::GetSpriteSize()
	{
		return mActiveAnimation->GetSpriteSize();
	}

	const Vector2& Animator::GetSpriteSize(const std::wstring& _key)
	{
		Animation* ani = FindAnimation(_key);
		return ani->GetSpriteSize();
	}

	const Vector2& Animator::GetImageSize()
	{
		return mActiveAnimation->GetImageSize();
	}

	const Vector2& Animator::GetImageSize(int _index)
	{
		return mActiveAnimation->GetImageSize(_index);
	}

	const UINT& Animator::GetAniIndex()
	{
		return mActiveAnimation->GetSpriteIndex();
	}


	Animator::Events* Animator::FindEvents(const std::wstring& _name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(_name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& _name)
	{
		Animation* ani = FindAnimation(_name);
		Animator::Events* events
			= FindEvents(ani->GetName());
		if (events != nullptr)
			return events->mStartEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& _name)
	{
		Animation* ani = FindAnimation(_name);
		Animator::Events* events
			= FindEvents(ani->GetName());
		if (events != nullptr)
			return events->mCompleteEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& _name)
	{
		Animation* ani = FindAnimation(_name);
		Animator::Events* events
			= FindEvents(ani->GetName());
		if (events != nullptr)
			return events->mEndEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	std::wstring Animator::GetDirAniKey(const std::wstring& _name, EDirType _type)
	{
		std::wstring temp(_name);
		switch (_type)
		{
		case EDirType::LEFT:
			temp += L"Left";
			break;
		case EDirType::RIGHT:
			temp += L"Right";
			break;
		}

		return temp;
	}
	std::wstring Animator::GetDirAniKey(const std::wstring& _name, EDirType _horizontal, EDirType _vertical)
	{
		std::wstring temp(_name);
		switch (_vertical)
		{
		case EDirType::UP:
			temp += L"Up";
			break;
		case EDirType::DOWN:
			temp += L"Down";
			break;
		}
		switch (_horizontal)
		{
		case EDirType::LEFT:
			temp += L"Left";
			break;
		case EDirType::RIGHT:
			temp += L"Right";
			break;
		}
		return temp;
	}
	void Animator::GetDirAniKey(EDirType& _horizontal, EDirType& _vertical, const std::wstring& _dir)
	{
		size_t cursor = _dir.find(L"Up");
		if (std::wstring::npos != cursor)
			_vertical = EDirType::UP;
		cursor = _dir.find(L"Down");
		if (std::wstring::npos != cursor)
			_vertical = EDirType::DOWN;


		cursor = _dir.find(L"Left");
		if (std::wstring::npos != cursor)
			_horizontal = EDirType::LEFT;
		cursor = _dir.find(L"Right");
		if (std::wstring::npos != cursor)
			_horizontal = EDirType::RIGHT;
	}
}
