#pragma once
#include "Scene.h"
namespace yeram_client
{
	class SaltBakeryShopScene :public Scene
	{
	public:
		SaltBakeryShopScene();
		SaltBakeryShopScene(std::wstring _name);
		virtual ~SaltBakeryShopScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();
	private:
		void ActiveScene1();
	private:
		std::shared_ptr<GameObject> mPlayer;
		Vector2 mStartPos;
		Vector2 mWindowPos;
		int mCurSceneNum;
	};

}

