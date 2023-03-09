#include "UI.h"
#include "SpriteRenderer.h"
namespace yeram_client
{
	UI::UI()
	{
		AddComponent<SpriteRenderer>();
	}
	void UI::SetImage(const std::wstring& _filename, const std::wstring& _path)
	{
		SpriteRenderer* render = GetComponent<SpriteRenderer>();
		render->SetImage(_filename, _path);
	}
}

