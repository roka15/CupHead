#pragma once
#include "Character.h"
namespace yeram_client
{
	class MugMan :public Character
	{
	public:
		MugMan();
		~MugMan();
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

		
		void idleCompleteEvent()override;
		void moveStartEvent() override;
		void moveCompleteEvent()override;
	};
}


