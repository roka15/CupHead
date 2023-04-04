#include "Script.h"

namespace yeram_client
{
	Script::Script(EScriptType _type) :Component(EComponentType::Script)
	{
		mScriptType = _type;
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
	

	void Script::OnCollisionEnter(Collider* other)
	{
	}
	void Script::OnCollisionStay(Collider* other)
	{
	}
	void Script::OnCollisionExit(Collider* other)
	{
	}
}
