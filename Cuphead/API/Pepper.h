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
		virtual void Idle()override;
		void Init();
		void SetSpawnPos();
		static bool IsSpawn();
		virtual void TakeDamage(Collider* other)override; 
		static const int mSpawnMax;
	private:
		static bool mbSpawnInit;
		static std::vector<SpawnInfo> mSpawners;
		static bool mbAttackActive;
		SkillInfo mSkill;
		double mDeSpawnStartTime;
		double mReSpawnTime;
		bool mbReSpawn;
	};
}


