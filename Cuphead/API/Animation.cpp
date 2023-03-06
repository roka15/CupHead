#include "Animation.h"
#include "Animator.h"
#include "Image.h"
#include "Time.h"
#include "Transform.h"
#include "GameObject.h"
namespace yeram_client
{
	Animation::Animation()
		:mAnimator(nullptr),
		mSheet(nullptr),
		mTime(0.0f),
		mbComplete(false),
		mSpriteIndex(-1)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Initialize()
	{
	}

	void Animation::Update()
	{
		if (mbComplete == true)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mSpriteSheet.size() <= (mSpriteIndex + 1))
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex++;
			}
		}
	}

	void Animation::Render(HDC _hdc)
	{
		Transform* tf = mAnimator->GetOwner()->GetComponent<Transform>();

		TransparentBlt(_hdc, tf->GetPos().x + mSpriteSheet[mSpriteIndex].offset.x,
			tf->GetPos().y + mSpriteSheet[mSpriteIndex].offset.y,
			mSpriteSheet[mSpriteIndex].size.x*tf->GetScale().x,
			mSpriteSheet[mSpriteIndex].size.y * tf->GetScale().y,
			mSheet->GetHDC(),mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
			,mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
			(RGB(234, 2, 255)));

	}

	void Animation::Create(Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row,UINT _size, Vector2 _offset, float _duration)
	{
		mSheet = _sheet;
		Vector2 size = Vector2::One;
		size.x = mSheet->GetWidth() / _col;
		size.y = mSheet->GetHeight() / _row;

		for (size_t i = 0; i < _size; i++)
		{
			Sprite sprite_info;
			sprite_info.leftTop.x = _leftTop.x + (size.x+i);
			sprite_info.leftTop.y = _leftTop.y;
			sprite_info.size = size;
			sprite_info.offset = _offset;
			sprite_info.duration = _duration;

			mSpriteSheet.push_back(sprite_info);
		}

	}

	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}

}
