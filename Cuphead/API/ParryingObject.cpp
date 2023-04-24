#include "ParryingObject.h"
#include "GameObject.h"
#include "Player.h"
yeram_client::ParryingObject::ParryingObject():Script()
{
	SetName(L"ParryingObject");
}

yeram_client::ParryingObject::~ParryingObject()
{
}

void yeram_client::ParryingObject::Initialize()
{
	GameObject* owner = GetOwner();
}

void yeram_client::ParryingObject::Update()
{
}

void yeram_client::ParryingObject::Render(HDC hdc)
{
}

void yeram_client::ParryingObject::Release()
{
}

void yeram_client::ParryingObject::OnCollisionEnter(Collider* other)
{
	
}

void yeram_client::ParryingObject::OnCollisionStay(Collider* other)
{
	GameObject* other_obj = other->GetOwner();
	Player* player = other_obj->GetComponent<Player>();
	if (player == nullptr)
		return;
	player->Parry_Check();
}

void yeram_client::ParryingObject::OnCollisionExit(Collider* other)
{
}
