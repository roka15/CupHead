#pragma once
#include "GameObject.h"
#include "Image.h"
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
		
	private:
		Image* mImage;
	};
}


