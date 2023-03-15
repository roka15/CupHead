#pragma once
#include "Component.h"
namespace yeram_client
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void SetMass(float _mass) { mMass = _mass; }
		void AddForce(Vector2 _force);
		void SetGround(bool _ground) { mbGround = _ground; }
	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;

		/*
		float mStaticFriction;
		float mKineticFriction;
		float mCoefficientFriction;

		float mNormalForce;
		*/
	};

}

