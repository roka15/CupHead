#pragma once
#include "Scene.h"
namespace yeram_client
{
	class PlayScene:public Scene
	{public:
		PlayScene();
		~PlayScene();
		virtual void Initalize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
	};
}


