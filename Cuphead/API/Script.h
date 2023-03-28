#pragma once
#include "Component.h"
namespace yeram_client
{
	class Script :public Component
	{
	public:
		Script();
		~Script();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void RegisterScript(std::string _key, Script* _script);
		Script* FindScript(std::wstring _key);
	private:
		std::map<std::wstring, Script*> mScripts;
	};
}


