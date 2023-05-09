#include "Camera.h"
#include "Application.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Input.h"
#include "Animator.h"
#include "Resources.h"
extern yeram_client::Application application;
namespace yeram_client
{

	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2  Camera::mLookPosition = Vector2::Zero;
	Vector2  Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;
	bool Camera::mbHorizonMove = false;
	bool Camera::mbVerticalMove = false;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 5.0f;
	float Camera::mCuttonAlpha = 1.0f;
	class Image* Camera::mCutton = nullptr;
	Camera::ECameraEffectType Camera::mType = Camera::ECameraEffectType::NONE;
	Vector2 Camera::mAlphaStartPos = Vector2::Zero;
	Vector2 Camera::mAlphaEndPos = Vector2::Zero;
	float Camera::mAlphaSpeed = 1.0f;
	void Camera::Initialize()
	{
		mDistance = Vector2::Zero;
		mResolution = application.GetWindowSize();
		//operator ±¸Çö
		mLookPosition = (mResolution / 2.0f);

		mCutton = Image::Create(L"Cutton", mResolution.x, mResolution.y, RGB(0, 0, 0));
		mAlphaEndPos = mResolution;
		mAlphaSpeed = 1.0f;
		mCuttonAlpha = 0.0f;
	}

	void Camera::Update()
	{
		if (mTarget != nullptr)
		{
			const Vector2& target_pos = mTarget->GetComponent<Transform>()->GetPos();
			if (mbHorizonMove == true)
			{
				mLookPosition.x = target_pos.x;
			}
			if (mbVerticalMove == true)
			{
				mLookPosition.y = target_pos.y;
			}
		}
		else
		{

			/*if (core::Input::GetKey(core::EKeyCode::Left))
			{
				mLookPosition.x -= 100.0f * Time::DeltaTime();
			}
			if (core::Input::GetKey(core::EKeyCode::Right))
			{
				mLookPosition.x += 100.0f * Time::DeltaTime();
			}
			if (core::Input::GetKey(core::EKeyCode::Up))
			{
				mLookPosition.y -= 100.0f * Time::DeltaTime();
			}
			if (core::Input::GetKey(core::EKeyCode::Down))
			{
				mLookPosition.y += 100.0f * Time::DeltaTime();
			}*/

		}

		if (mAlphaTime < mEndTime && mType != ECameraEffectType::NONE)
		{
			mAlphaTime += Time::DeltaTime();
			float ratio = 0.0f;

			ratio = (mAlphaTime / mEndTime) * mAlphaSpeed;


			if (mType == ECameraEffectType::FADE_IN)
			{
				mCuttonAlpha = 1.0f - ratio;
				if (mCuttonAlpha <= 0.0)
					mCuttonAlpha = 0.0f;
			}
			else if (mType == ECameraEffectType::FADE_OUT)
			{
				mCuttonAlpha = ratio;
				if (mCuttonAlpha >= 1.0f)
					mCuttonAlpha = 1.0f;
			}

		}
		else if (mAlphaTime >= mEndTime)
		{
			if (mType == ECameraEffectType::FADE_IN)
				InitFadeInfo();
			else
				mCuttonAlpha = 1.0f;
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC _hdc)
	{
		if (mAlphaTime < mEndTime
			&& (mType == ECameraEffectType::FADE_IN || mType == ECameraEffectType::FADE_OUT))
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			if (mCutton->GetKey().compare(L"Cutton") == 0)
			{
				func.AlphaFormat = AC_SRC_OVER;
			}
			else
			{
				func.AlphaFormat = AC_SRC_ALPHA;
			}

			func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

			AlphaBlend(_hdc, mAlphaStartPos.x, mAlphaStartPos.y
				, mAlphaEndPos.x, mAlphaEndPos.y
				, mCutton->GetHDC()
				, 0, 0
				, mCutton->GetWidth(), mCutton->GetHeight()
				, func);
		}
		else if (mType == ECameraEffectType::FADE_OUT && mCuttonAlpha == 1.0f)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			if (mCutton->GetKey().compare(L"Cutton") == 0)
			{
				func.AlphaFormat = AC_SRC_OVER;
			}
			else
			{
				func.AlphaFormat = AC_SRC_ALPHA;
			}

			func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

			AlphaBlend(_hdc, mAlphaStartPos.x, mAlphaStartPos.y
				, mAlphaEndPos.x, mAlphaEndPos.y
				, mCutton->GetHDC()
				, 0, 0
				, mCutton->GetWidth(), mCutton->GetHeight()
				, func);
		}
	}

	void Camera::Release()
	{

	}

	void Camera::SetTarget(GameObject* _target)
	{
		mLookPosition = (mResolution / 2.0f);
		mTarget = _target;
	}

	void Camera::SetCameraDistance(float _distance)
	{
		Transform* tf = mTarget->GetComponent<Transform>();
		Vector2 pos = tf->GetScale();
		SceneManager::ChangeScaleGameObjects(pos * _distance);
		//mDistance = mDistance * _distance;
	}

	void Camera::FadeIn()
	{
		InitFadeInfo();
		mType = ECameraEffectType::FADE_IN;
	}
	void Camera::FadeOut()
	{
		InitFadeInfo();
		mType = ECameraEffectType::FADE_OUT;
	}


	void Camera::InitFadeInfo()
	{
		if (mCutton == nullptr)
		{
			mCutton = Resources::Find<Image>(L"Cutton");

			mEndTime = 5.0f;
			mAlphaEndPos = application.GetWindowSize();
			mAlphaStartPos = Vector2::Zero;
		}
		mType = ECameraEffectType::NONE;
		mAlphaTime = 0.0f;
		mCuttonAlpha = 0.0f;
	}

	void Camera::Clear()
	{
		mResolution = application.GetWindowSize();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}




}

