#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class UIManager
	{
	public:
		static void Add(std::wstring _group_key, GameObject* _group);
		static void Remove(std::wstring _group_key);
		static GameObject* FindUIGroup(std::wstring _group_key);
		static void Execute(UINT _ui_state, std::wstring _key);
		static void ActiveWindow(std::wstring _group_key);
	private:
		UIManager();
		~UIManager();
	private:
		static std::map<std::wstring,GameObject*> mRegisterWindows;
		static std::stack<GameObject*> mActiveWindow;
	};

}


