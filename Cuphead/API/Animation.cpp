#include "Animation.h"
#include "Animator.h"
#include "Image.h"
#include "Time.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
namespace yeram_client
{
	Animation::Animation()
		:mAnimator(nullptr),
		mSheet(nullptr),
		mTime(0.0f),
		mbComplete(false),
		mSpriteIndex(0)
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
		Vector2 scale = tf->GetScale();

		// 이미지가 그려질 좌표는 오브젝트 좌표의 위쪽 중간에 그려진다.
	   // 캐릭터의 발을 기준으로 포지션을 계산
		Vector2 pos = tf->GetPos();
		pos = Camera::CaluatePos(pos);
		pos += mSpriteSheet[mSpriteIndex].offset;
		pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
		pos.y -= mSpriteSheet[mSpriteIndex].size.y;

		//camera 더하기
		// operator 구현해야함.
		TransparentBlt(_hdc, pos.x, pos.y,
			mSpriteSheet[mSpriteIndex].size.x * scale.x,
			mSpriteSheet[mSpriteIndex].size.y * scale.y,
			mSheet->GetHDC(), mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
			, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
			(RGB(255, 0, 255)));
	}

	void Animation::Create(Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration)
	{
		mSheet = _sheet;
		Vector2 size = Vector2::One;
		size.x = mSheet->GetWidth() / (float)_col;
		size.y = mSheet->GetHeight() / (float)_row;

		for (size_t i = 0; i < _size; i++)
		{
			Sprite sprite_info;
			sprite_info.leftTop.x = _leftTop.x + (size.x * i);
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
