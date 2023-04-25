#pragma once
#include "Script.h"
namespace yeram_client
{
	class Boss :public Script
	{
	public:
		struct PatternInfo
		{
			std::wstring m_aniname;
		};
		enum class EParts
		{
			NONE,
			ARM,
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

		std::shared_ptr<GameObject> GetParts(EParts _parts_type) { return mParts[EParts::ARM]; }
	protected:
		 void Phase1();
		 void Phase2();
		 void Phase3();
	protected:
		class Transform* mTransform;
		class MoveObject* mMoveObject;
		class Animator* mAni;
		class Collider* mCol;

		EPhaseType mPhaseType;
		std::map<EPhaseType, std::vector<PatternInfo>> mPatterns;
		std::map <EParts, std::shared_ptr<GameObject>> mParts;
	};
}


