#pragma once
#include "Script.h"
namespace yeram_client
{
	class Boss :public Script
	{
	public:
		enum class EAttackType
		{
			Type1,
			Type2,
			Type3,
			Type4,
			Type5
		};
		struct PatternInfo
		{
			EAttackType m_attackType;
			EShotBulletType m_shotType;
			std::map<std::wstring, std::wstring> m_anis;
			Vector2 m_speed;
			Vector2 m_dir;
			Vector2 m_distance;
			bool m_rendom_flag;
			bool m_parry_flag;
		};
		enum class  EParts
		{
			NONE,
			ARM,
			ACC,//¾Ç¼¼¼­¸®
			MAX
		};
		enum class EPhaseType
		{
			NONE,
			PHASE1,
			PHASE2,
			PHASE3,
			MAX
		};
	
		Boss();
		virtual ~Boss();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		std::shared_ptr<GameObject> GetParts(EParts _parts_type) { return mParts[_parts_type]; }
		void SetPhase(EPhaseType _type) { mPhaseType = _type; }
		void TakeDamage(); 
	protected:
		 virtual void Phase1();
		 virtual void Phase2();
		 virtual void Phase3();
	protected:
		class Transform* mTransform;
		class MoveObject* mMoveObject;
		class Animator* mAni;
		class Collider* mCol;
		double mTime;
		EPhaseType mPhaseType;
		std::map<EPhaseType, std::vector<PatternInfo>> mPatterns;
		std::map <EParts, std::shared_ptr<GameObject>> mParts;
		int mHP;
		int mMaxHP;
		bool mbChagePhase;
	};
}


