#pragma once
#include "Scene.h"
namespace yeram_client
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		TutorialScene(std::wstring _name);
		virtual ~TutorialScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	private:
		GameObject* mPlayer;
		Vector2 mStartPos;
		Vector2 mMapLimit;
		bool mFirstUpdate;
	};
}


