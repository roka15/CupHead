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

		struct CreateAniInfo
		{
			CreateAniInfo()
				:mImageKey(L""),mPath(L""), mLeftTop(Vector2::Zero), mCol(0), mRow(0), mSize(0), mOffset(Vector2::Zero), mDuration(0.0f), mSizes(), mAlpha(false)
			{

			}
			CreateAniInfo(std::wstring _key,std::wstring _path,Vector2 _ltop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration, std::vector<Vector2> _sizes, bool _alpha)
				:mImageKey(_key), mPath(_path),mLeftTop(_ltop),mCol(_col),mRow(_row),mSize(_size),mOffset(_offset),mDuration(_duration),mSizes(_sizes),mAlpha(_alpha)
			{

			}
			CreateAniInfo(const CreateAniInfo& _ref)
				:mImageKey(_ref.mImageKey), mPath(_ref.mPath),mLeftTop(_ref.mLeftTop),mCol(_ref.mCol),mRow(_ref.mRow),mSize(_ref.mSize),mOffset(_ref.mOffset),mDuration(_ref.mDuration),mSizes(_ref.mSizes),mAlpha(_ref.mAlpha)
			{

			}
			const std::wstring mImageKey;
			const std::wstring mPath;
			const Vector2 mLeftTop;
			const UINT mCol;
			const UINT mRow;
			const UINT mSize;
			const Vector2 mOffset;
			const float mDuration;
			const std::vector<Vector2> mSizes;
			const bool mAlpha;
		};
		Animator();
		~Animator();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		
		void CreateAnimation(const std::wstring& _name, const std::wstring& _path, const std::wstring& _image_key, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration, const std::vector<Vector2> _origin_size=std::vector<Vector2>(), bool _alpha = false);// 이미지 하나에 스프라이트들이 있는 경우
		void CreateAnimation(const std::wstring& _name);
		std::wstring CreateAnimations(const std::wstring& _path, Vector2 _offset, float _duration,bool _alpha=false);// 이미지를 별개로 불러와서 사용해야 할 경우


		Animation* FindAnimation(const std::wstring& _name);
		bool FindPubAnimation(const std::wstring& _name);
		CreateAniInfo GetPubAnimation(const std::wstring& _name);
		void ActiveReset() { mActiveAnimation->Reset(); }
		void Play(const std::wstring& _name, bool _loop, bool _use_fsm = true);
		void Play(const std::wstring& _name, bool _loop, double _time, bool _use_fsm = true);
		void Stop();
		void FSMStop();
		bool UseAnimation() { return mActiveAnimation != nullptr; }
		bool Complete() { return mActiveAnimation->IsComplete(); }
		void SetCurAniIndex(UINT _index) { mActiveAnimation->SetSpriteIndex(_index); }
		const std::wstring& GetCurAniName();
		const int& GetComEventPlayCnt() { return mComEventCnt; }
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

		const std::wstring& GetImageKey() { return mActiveAnimation->GetImageKey(); }
		const std::wstring& GetImagePath() { return mPublicAniInfo[mActiveAnimation->GetName()].mPath; }

		static void PublicInfoRelease();
	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map <std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		bool mbLoop;
		bool mbUseFsm;
		double mLimitTime;
		double mCurTime;
		int mComEventCnt;
		static std::map<std::wstring, CreateAniInfo> mPublicAniInfo;
	};
}


