#pragma once
#include "Scene.h"

namespace yeram_client
{
	class SceneManager
	{
	public:
		enum class ELoadingState
		{
			NONE,
			FADE_OUT,
		    LOADING,
			FADE_IN,
		};
		static void Initalize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void LoadScene(ESceneType _type);
		static Scene* GetActiveScene();
		static std::shared_ptr<GameObject> FindObject(std::wstring _name);
		static void RemoveObject(GameObject* _obj);
		static void ChagePosGameObjects(const Vector2& _offset);
		static void ChangeScaleGameObjects(const Vector2& _scale);

		static void OpenLodingScreen();
		static void CloseLodingScreen();
		static void LoadingComplete() { mbCompleteLoad = true; }
		static void SetActivScene();
		static void SetLoadSceneMessage(std::function<void()> _func_event) { mLoadMessageEvent = _func_event; };
		static void UseUI(bool _flag) { mbUseUI = _flag; }
		static bool UseUI() { return  mbUseUI; }

		static void RemoveObjectRequest(GameObject* _obj) { mRemoveRequestObjs.push(_obj); }
		static void RemoveObjectRequestRelease();
	private:
		SceneManager()=delete;
		~SceneManager();
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;

		static GameObject* mLoadingScreen;
		static bool mbLoadScreenFlag;
		static HANDLE mHThread;
		static ESceneType mLoadSceneType;
		static ELoadingState mLoadState;
		static bool mbCompleteLoad;
		static std::function<void()> mLoadMessageEvent;
		static bool mbUseUI;
		static std::queue<GameObject*> mRemoveRequestObjs;
	};
}

