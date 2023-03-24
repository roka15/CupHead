#pragma once
#include "Scene.h"
#include <string>
namespace yeram_client
{
	class MainMenuScene:public Scene
	{
	public:
		MainMenuScene();
		~MainMenuScene();
		MainMenuScene(std::wstring _name);
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	private:

	};

}

