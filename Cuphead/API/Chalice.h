#pragma once
#include "Character.h"
namespace yeram_client
{
	class Chalice:public Character
	{
	public:
		Chalice();
		~Chalice();
		void Initialize()override;
		void Update()override;
		void Render(HDC hdc)override;
		void Release()override;

       void Create()override;

	private:
		void move()override;
		void idle()override;
		void shoot()override;
		void death()override;
		void duck()override;
		bool jump_check(ECharacterState _befor_state)override;
		bool duck_check();
		EStateType dash_check();

		virtual void air_move()override;
		virtual void air_idle()override;
		virtual void air_shoot()override;
		virtual void air_death()override;

		bool execute_dash(EStateType _type);
		void PositionUpdate()override;
		void DashPositionUpdate(EStateType _type)override;
		

		void AirMove();
		void AirShoot();

		void idleCompleteEvent()override;
		void moveStartEvent() override;
		void moveCompleteEvent()override;
	
	};
}
