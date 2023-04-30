#pragma once
#include "Monster.h"
namespace yeram_client
{
	class Pepper :public Monster
	{
	public:
		struct SpawnInfo
		{
			bool mbSpawn;
			Vector2 mPos;
		};
		Pepper();
		virtual ~Pepper();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		virtual void Death(Collider* _other)override;
		virtual void Attack()override;
		virtual void Intro()override;
		void SetSpawnPos();
		static const int mSpawnMax;
	private:
		
		static bool mbSpawnInit;
		static std::vector<SpawnInfo> mSpawners;
	};
}


