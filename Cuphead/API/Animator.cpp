#include "Animator.h"
#include "Resources.h"
namespace yeram_client
{
	Animator::Animator()
		:Component(EComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{
	}
	

	Animator::~Animator()
	{
		for (auto ani : mAnimations)
		{
			delete ani.second;
			ani.second = nullptr;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation != nullptr)
		{
			mActiveAnimation->Update();
			if (mbLoop == true 
				&& mActiveAnimation->IsComplete()==true)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation != nullptr)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void Animator::Release()
	{
	}

	void Animator::CreateAnimation(const std::wstring& _name, Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration)
	{
		Animation* ani = FindAnimation(_name);
		if (ani != nullptr)
		{
			return;
		}
		ani = new Animation();
		ani->Create(_sheet, _leftTop, _col, _row,_size, _offset, _duration);
		ani->SetName(_name);
		ani->SetAnimator(this);

		mAnimations.insert(std::make_pair(_name, ani));
	}

	void Animator::CreateAnimations(const std::wstring& _path, Vector2 _offset, float _duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;
		std::filesystem::path fs(_path);
		std::vector<Image*> images = {};
		for (auto& itr : std::filesystem::recursive_directory_iterator(_path))
		{
			const std::wstring ext = itr.path().extension();
			if (ext != L".bmp")
				continue;
			std::wstring fileName = itr.path().filename();
			std::wstring fullName = _path + L"\\" + fileName;
			Image* image = Resources::Load<Image>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}
			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}
			fileCount++;
		}
		
		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
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

		CreateAnimation(key, mSpriteSheet, Vector2::Zero, index, 1, index, _offset, _duration);

	}

	Animation* Animator::FindAnimation(const std::wstring& _name)
	{
		auto itr = mAnimations.find(_name);
		if (itr == mAnimations.end())
			return nullptr;
		return itr->second;
	}

	void Animator::Play(const std::wstring& _name, bool _loop)
	{
		mActiveAnimation = FindAnimation(_name);
		mbLoop = _loop;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& _name)
	{
		return nullptr;
	}

	//std::function<void()>& Animator::GetStartEvent(const std::wstring& _name)
	//{
	//	// TODO: 여기에 return 문을 삽입합니다.
	//}

	//std::function<void()>& Animator::GetCompleteEvent(const std::wstring& _name)
	//{
	//	// TODO: 여기에 return 문을 삽입합니다.
	//}

	//std::function<void()>& Animator::GetEndEvent(const std::wstring& _name)
	//{
	//	// TODO: 여기에 return 문을 삽입합니다.
	//}

}
