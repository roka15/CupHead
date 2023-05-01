#pragma once
#include "Boss.h"


namespace yeram_client
{
	class SaltBaker :public Boss
	{
	public:
		struct SpawnInfo
		{
			bool mActive;
			double mCoolTime;
			int mCount;
			int mCurCount;
			double mSpawnTime;
			std::function<void()> mSpawnEvent;
			~SpawnInfo() {}
		};
		
		SaltBaker();
		virtual ~SaltBaker();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	private:
		virtual void Phase1()override;
		virtual void Phase2()override;
		virtual void Phase3()override;
		void RegisterPattern1();
		void RegisterPattern2();
		void RegisterPattern3();

		void P1AttackType1();
		void P1AttackType2();
		void P1AttackType4();
		void P1AttackType5();

		void P2AttackType1();
		void P2AttackAni();
	private:
		EGameObjectType mobjType;
		std::map<EPhaseType, std::map<EAttackType, std::vector<std::wstring>>> mPhaseInfo;
		std::vector<std::wstring> mActiveAttack;
		std::map<EPhaseType, std::map<EAttackType, std::shared_ptr<SpawnInfo>>> mAttackCheck;

		bool mbSkillUseCheck;
		bool mbPepperSpawnCheck;
		SkillInfo mP2BossSkill;
	};
}


