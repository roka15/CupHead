#include "Camera.h"
#include "Application.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Input.h"
#include "Animator.h"
extern yeram_client::Application application;
namespace yeram_client
{

	Vector2 Camera::mResolution;
	Vector2  Camera::mLookPosition;
	Vector2  Camera::mDistance;
	GameObject* Camera::mTarget = nullptr;
	
	

	void Camera::Initialize()
	{
		mDistance = Vector2::Zero;
		mResolution = application.GetWindowSize();
		//operator ±¸Çö
		mLookPosition = (mResolution / 2.0f);

		
	}

	void Camera::Update()
	{
		if (CheckActive() == false)
			return;
		if (mTarget != nullptr)
		{
			mLookPosition = mTarget->GetComponent<Transform>()->GetPos();
		}
		else
		{
			if (core::Input::GetKey(core::EKeyCode::Left))
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
			}
		}

		
		
		mDistance = mLookPosition - (mResolution / 2.0f);

	}

	void Camera::Render(HDC _hdc)
	{
		
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
		SceneManager::ChangeScaleGameObjects(pos*_distance);
		//mDistance = mDistance * _distance;
	}

	

	void Camera::Clear()
	{
		mResolution = application.GetWindowSize();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}

	
	
	bool Camera::CheckActive()
	{
		ESceneType cur_scene = SceneManager::GetActiveScene()->GetSceneType();
		switch (cur_scene)
		{
		case ESceneType::Title:
		case ESceneType::MainMenu:
			return false;
		}
		return true;
	}
}

