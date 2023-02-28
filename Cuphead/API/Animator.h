#pragma once
#include "Component.h"
#include "Animation.h"
#include "Image.h"
namespace yeram_client
{
	class Animation;
	class Animator :public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};
		Animator(EComponentType _type);
		~Animator();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		
		void CreateAnimation(std::wstring& _name,Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration);// 이미지 하나에 스프라이트들이 있는 경우
		void CreateAnimations();// 이미지를 별개로 불러와서 사용해야 할 경우

		Animation* FindAnimation(const std::wstring& _name);
		void Play(const std::wstring& _name, bool _loop);

		Events* FindEvents(const std::wstring& _name);
	/*	std::function<void()>& GetStartEvent(const std::wstring& _name);
		std::function<void()>& GetCompleteEvent(const std::wstring& _name);
		std::function<void()>& GetEndEvent(const std::wstring& _name);*/
	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map <std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
	};
}


