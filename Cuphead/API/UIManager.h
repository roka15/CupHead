#pragma once
#include "Engine.h"
namespace yeram_client
{
	class UI;
	class UIManager
	{
	public:
		static void AddUI();
		static void FindUI(std::wstring _key);

	private:
		UIManager();
		~UIManager();
	private:
		static std::map<std::wstring, UI*> mUIs;
	};

}


