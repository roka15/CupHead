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

		void Create()override;

	private:
		void move(const PushInfo& _push_info)override;
		void idle(const PushInfo& _push_info)override;
		void shoot(const PushInfo& _push_info)override;
		void death(const PushInfo& _push_info)override;
		void duck(const PushInfo& _push_info)override;

		bool jump_check(ECharacterState _befor_state)override;

		virtual void air_move()override;
		virtual void air_idle()override;
		virtual void air_shoot()override;
		virtual void air_death()override;

		void idleCompleteEvent()override;
		void moveStartEvent() override;
		void moveCompleteEvent()override;
	};
}


