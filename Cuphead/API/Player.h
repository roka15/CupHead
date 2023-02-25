#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class Player :public GameObject
	{
	public:
		Player();
		Player(ERenderType _type);
		virtual ~Player();
		virtual void Initalize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
	private:
		float mTime;
		int midx;
	};
}


