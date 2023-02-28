#include "Animator.h"

namespace yeram_client
{
	Animator::Animator(EComponentType _type)
		: Component(_type)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{

	}

	Animator::~Animator()
	{
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

	void Animator::CreateAnimation(std::wstring& _name, Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration)
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

	void Animator::CreateAnimations()
	{
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
