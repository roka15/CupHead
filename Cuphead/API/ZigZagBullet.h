#pragma once
#include "Script.h"
#include "Bullet.h"
namespace yeram_client
{
	class ZigZagBullet :public Bullet
	{
	public:
		enum class EVertical
		{
			UP,
			DOWN,
		};
		ZigZagBullet();
		ZigZagBullet(const ZigZagBullet& _other);
		virtual ~ZigZagBullet();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void Reset();

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		virtual void Shoot()override;
		virtual void Death(Collider* _other)override;
		
		void RegisterAniKey(const std::wstring& _up, const std::wstring& _down,const std::wstring& _death);
		virtual void CreateInfo(const Vector2& _speed, const Vector2& _distance, const Vector2& _start_dir);
		const Vector2 GetEndPos();
		virtual void NextInfoSetting();
		virtual void SetColInfo(std::wstring _ani_name)override;
	protected: 
		std::function<void()>& GetCompleteEvent(std::wstring _name); 
	protected:
		std::wstring mUpAnimation;
		std::wstring mDownAnimation;
		std::wstring mDeathAnimation;
		Vector2 mDir;
		Vector2 mDistance;
		Vector2 mSpeed;
		Vector2 mStartpos;
	};
}


