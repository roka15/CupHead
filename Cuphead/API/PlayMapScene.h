#pragma once
#include "Scene.h"
namespace yeram_client
{
	class PlayMapScene:public Scene
	{public:
		PlayMapScene();
		~PlayMapScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	};
}


