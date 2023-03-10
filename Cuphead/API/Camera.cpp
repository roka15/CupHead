#include "Camera.h"
#include "Application.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Input.h"
extern yeram_client::Application application;
namespace yeram_client
{
	
	Vector2 Camera::mResolution;
	Vector2  Camera::mLookPosition;
	Vector2  Camera::mDistance;
	GameObject* Camera::mTarget = nullptr;
	void Camera::Initialize()
	{
		mResolution = application.GetWindowSize();
		//operator ±¸Çö
		mLookPosition = (mResolution / 2.0f);
	}

	void Camera::Update()
	{
		/*if (core::Input::GetKey(core::EKeyCode::A))
		{
			mLookPosition.x -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::D))
		{
			mLookPosition.x += 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::W))
		{
			mLookPosition.y -= 100.0f * Time::DeltaTime();
		}
		if (core::Input::GetKey(core::EKeyCode::S))
		{
			mLookPosition.y += 100.0f * Time::DeltaTime();
		}*/

		if (mTarget != nullptr)
		{
			mLookPosition = mTarget->GetComponent<Transform>()->GetPos();
		}
		//mDistance = 
	}
	void Camera::Clear()
	{
	}
}

