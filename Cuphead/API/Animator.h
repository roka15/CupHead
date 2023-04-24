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
		Animator();
		~Animator();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		
		void CreateAnimation(const std::wstring& _name, Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration, const std::vector<Vector2> _origin_size=std::vector<Vector2>(), bool _alpha = false);// 이미지 하나에 스프라이트들이 있는 경우
		std::wstring CreateAnimations(const std::wstring& _path, Vector2 _offset, float _duration,bool _alpha=false);// 이미지를 별개로 불러와서 사용해야 할 경우


		Animation* FindAnimation(const std::wstring& _name);
		void ActiveReset() { mActiveAnimation->Reset(); }
		void Play(const std::wstring& _name, bool _loop, bool _use_fsm = true);
		void Play(const std::wstring& _name, bool _loop, double _time, bool _use_fsm = true);
		void Stop();
		void FSMStop();
		bool UseAnimation() { return mActiveAnimation != nullptr; }
		bool Complete() { return mActiveAnimation->IsComplete(); }
		const std::wstring& GetCurAniName();
		const Vector2& GetSpriteSize();
		const Vector2& GetSpriteSize(const std::wstring& _key);
		const Vector2& GetImageSize();
		const Vector2& GetImageSize(int _index);
		const UINT& GetAniIndex();
		Events* FindEvents(const std::wstring& _name);
		std::function<void()>& GetStartEvent(const std::wstring& _name);
		std::function<void()>& GetCompleteEvent(const std::wstring& _name);
		std::function<void()>& GetEndEvent(const std::wstring& _name);

		std::wstring GetDirAniKey(const std::wstring& _name, EDirType _type);
		std::wstring GetDirAniKey(const std::wstring& _name, EDirType _horizontal, EDirType _vertical);
		void GetDirAniKey(EDirType& _horizontal,EDirType& _vertical,const std::wstring& _dir);
	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map <std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
		bool mbUseFsm;
		double mLimitTime;
		double mCurTime;
	};
}


