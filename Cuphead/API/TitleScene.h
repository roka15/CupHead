#pragma once
#include "Scene.h"
namespace yeram_client
{
	class TitleScene:public Scene
	{
	public:
		TitleScene();
		TitleScene(std::wstring _name);
		~TitleScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	};
}


