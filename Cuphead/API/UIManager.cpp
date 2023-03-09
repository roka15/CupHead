#include "UIManager.h"
#include "UI.h"
namespace yeram_client
{
	std::map<std::wstring, GameObject*> UIManager::mRegisterWindows;
	std::stack<GameObject*> UIManager::mActiveWindow;

	void UIManager::Add(std::wstring _group_key, GameObject* _group)
	{
		GameObject* window = FindUIGroup(_group_key);
		if (window != nullptr)
			return;
		mRegisterWindows.insert(std::make_pair(_group_key, _group));
	}

	void UIManager::Remove(std::wstring _key)
	{
		mRegisterWindows.erase(_key);
	}

	GameObject* UIManager::FindUIGroup(std::wstring _group_key)
	{
		auto itr = mRegisterWindows.find(_group_key);
		if (itr == mRegisterWindows.end())
			return nullptr;
		else
			return itr->second;
	}
	void UIManager::Execute(UINT _ui_state, std::wstring _key)
	{
		GameObject* active_window = mActiveWindow.top();
		//null 예외처리 안한 이유는 일부러 터트리려고.

		GameObject* find_obj = active_window->FindChild(_key);
		GameObject* execute_ui = dynamic_cast<UI*>(find_obj);
		
		/*if (execute_ui == nullptr)
			return;*/

		reinterpret_cast<UI*>(execute_ui)->execute(static_cast<UI::EUIState>(_ui_state));
	}
	void UIManager::ActiveWindow(std::wstring _group_key)
	{
		GameObject* window = FindUIGroup(_group_key);
		if (window != nullptr)
		{
			mActiveWindow.push(window);
		}
	}
	UIManager::UIManager()
	{
	}
	UIManager::~UIManager()
	{
	}
}

