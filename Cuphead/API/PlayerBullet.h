#pragma once
#include "Bullet.h"
namespace yeram_client
{
	class PlayerBullet :public Bullet
	{
	public:
		PlayerBullet();
		virtual ~PlayerBullet();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void Shoot()override;
		void Shoot(std::wstring _dirstr);
		virtual void Death(Collider* _other)override;
		void CreateInfo(const Vector2& _startpos, const Vector2 _dir);
		void SetDiagonalColInfo(EDirType _vertical_dir, std::wstring _ani_name);
	private:
		Vector2 mSpeed;
		EDirType mDirType;
	};
}


