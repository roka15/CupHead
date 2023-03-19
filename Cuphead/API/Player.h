#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class Animator;
	class Character;
	class Player :public GameObject
	{
	public:
		

		Player();
		virtual ~Player();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void CreateCharacter(ESceneType _scenetype,EPlayerType _type);
		void ChangeCharacter(EPlayerType _type);
		void SetSceneType_Ch(ESceneType _scenetype);
		Character* GetActiveCharacter() { return mCharacter; }

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
	private:
		Animator* mAnimator;
		Character* mCharacter;
		std::map<EPlayerType, Character*> mCharacters;
		/*float mTime;
		int midx;*/
	};
}


