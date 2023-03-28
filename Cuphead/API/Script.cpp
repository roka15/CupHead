#include "Script.h"

namespace yeram_client
{
	Script::Script():Component(EComponentType::Animator)
	{
	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}

	void Script::Update()
	{

	}

	void Script::Render(HDC hdc)
	{
		Component::Render(hdc);
	}

	void Script::Release()
	{

	}
	void Script::RegisterScript(std::string _key, Script* _script)
	{
		/*static std::locale loc("");
		auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
		std::wstring key =  std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(_key);
		mScripts.insert(std::make_pair(key, _script));*/
	}
	Script* Script::FindScript(std::wstring _key)
	{
		std::map<std::wstring, Script*>::iterator itr = mScripts.find(_key);
		if (itr == mScripts.end())
			return nullptr;
		else
			return itr->second;
	}
}
