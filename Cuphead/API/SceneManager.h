#pragma once
#include "Scene.h"

namespace yeram_client
{
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
	private:
		SceneManager()=delete;
		~SceneManager();
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}

