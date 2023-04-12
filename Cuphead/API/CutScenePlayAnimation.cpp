#include "CutScenePlayAnimation.h"
#include "GameObject.h"
namespace yeram_client
{
    CutScenePlayAnimation::CutScenePlayAnimation() :Script()
	{
		SetName(L"CutScenePlayAnimation");
	}

	CutScenePlayAnimation::~CutScenePlayAnimation()
	{
	}

	void CutScenePlayAnimation::Initialize()
	{
		mAni = mOwner->AddComponent<Animator>();

	}

	void CutScenePlayAnimation::Update()
	{
		if (mAni->GetActive() == false)
			return;
		if (mAniQueue.empty() == false)
		{
			if (mPrevAniName.size()==0||mAni->Complete() == true)
			{
				std::pair<std::wstring, double> p = mAniQueue.front();
				mAniQueue.pop();
				if (p.second == 0)
				{
					mAni->Play(p.first, false);
				}
				else
				{
					mAni->Play(p.first, true, p.second,false);
				}
				mPrevAniName = p.first;
			}
		}
		else
		{
			mPrevAniName.clear();
		}

	}

	void CutScenePlayAnimation::Render(HDC hdc)
	{
	}

	void CutScenePlayAnimation::Release()
	{
	}
	void CutScenePlayAnimation::SetAnimation(std::wstring _ani_name, double _time)
	{
		mAniQueue.push(std::make_pair(_ani_name,_time));
	}

}

