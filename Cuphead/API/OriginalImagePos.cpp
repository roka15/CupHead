#include "OriginalImagePos.h"
#include "GameObject.h"
#include "Time.h"

namespace yeram_client
{
	OriginalImagePos::OriginalImagePos() :Script()
	{
		SetName(L"OriginalImagePos");
	}
	OriginalImagePos::~OriginalImagePos()
	{
	}
	void OriginalImagePos::Initialize()
	{
		mAni = mOwner->GetComponent<Animator>();
		mTf = mOwner->GetComponent<Transform>();
		mSpriteSize = mAni->GetSpriteSize();
		mOffset = mTf->GetOffset();
	}
	void OriginalImagePos::Update()
	{
		int index = mAni->GetAniIndex();
		Vector2 first = mAni->GetImageSize(0);
		Vector2 cur = mAni->GetImageSize();
		if (first.y <cur.y)
		{
			Vector2 offset = mOffset;
			float diff = cur.y - first.y;

			offset.y += diff;
			mTf->SetOffset(offset);
		}
		else
		{
			mTf->SetOffset(mOffset);
		}
	}
	void OriginalImagePos::Render(HDC hdc)
	{
	}
	void OriginalImagePos::Release()
	{
	}
	void OriginalImagePos::OnCollisionEnter(Collider* other)
	{
	}
	void OriginalImagePos::OnCollisionStay(Collider* other)
	{
	}
	void OriginalImagePos::OnCollisionExit(Collider* other)
	{
	}
}