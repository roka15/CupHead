#pragma once
#include "Scene.h"
namespace yeram_client
{
	class WorldMoveIntroScene :public Scene
	{
	public:
		WorldMoveIntroScene();
		WorldMoveIntroScene(std::wstring _name);
		virtual ~WorldMoveIntroScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	private:
		double mTime;
	};

}

