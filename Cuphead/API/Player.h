#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class Player :public GameObject
	{
	public:
		Player();
		virtual ~Player();
		virtual void Initalize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void SetPos(Vector2 _pos) { mPos = _pos; };
	private:
	};
}


