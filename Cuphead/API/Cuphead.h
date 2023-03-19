#pragma once
#include "Character.h"

namespace yeram_client
{
	class Cuphead :public Character
	{
	public:
		Cuphead();
		~Cuphead();
		void Initialize()override;
		void Update()override;
		void Render(HDC hdc)override;
		void Release()override;

		void Create(ESceneType _type)override;

	private:
		void move()override;
		void idle()override;
		void shoot()override;
		void death()override;
		void duck()override;
		bool jump_check(ECharacterState _befor_state)override;

		void idleCompleteEvent()override;
		void moveStartEvent() override;
		void moveCompleteEvent()override;
	};
}


