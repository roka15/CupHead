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
		void Input();//message queue test

		void move(const PushInfo& _push_info)override;
		void idle(const PushInfo& _push_info)override;
		void shoot(const PushInfo& _push_info)override;
		void shoot_start(const PushInfo& _push_info);
		void death(const PushInfo& _push_info)override;
		void duck(const PushInfo& _push_info)override;
		bool duck_start(const PushInfo& _push_info);
		void dash(const PushInfo& _push_info);
		void dash_start(const PushInfo& _push_info);
		void jump(const PushInfo& _push_info);
		void fix(const PushInfo& _push_info)override;
		void fix_start(const PushInfo& _push_info);
		void Parrying()override;

		void PositionUpdate()override;


		virtual void air_move()override;
		virtual void air_idle()override;
		virtual void air_shoot()override;
		virtual void air_death()override;

		void AirMove();
		void AirShoot();

		
		
		void idleCompleteEvent()override;
		void moveStartEvent() override;
		void moveCompleteEvent()override;
		void RegisterShooterSpawnPos();
		
	private:
		float mFirstJumpTime;
	};
}
