#pragma once
#include "Scene.h"

namespace yeram_client
{
	class Rectangle;
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void LoadScene(ESceneType _type);
		static Scene* GetActiveScene();
		static GameObject* FindObject(std::wstring _name);
		static void ChagePosGameObjects(const Vector2& _offset);
		static void ChangeScaleGameObjects(const Vector2& _scale);

		static void OpenLodingScreen();
		static void CloseLodingScreen();
	private:
		SceneManager()=delete;
		~SceneManager();
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;

		static GameObject* mLoadingScreen;
		static bool mbLoadScreenFlag;
	};
}

