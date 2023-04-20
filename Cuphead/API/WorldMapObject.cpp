#include "WorldMapObject.h"
#include "GameObject.h"
yeram_client::WorldMapObject::WorldMapObject():Script()
{
	SetName(L"WorldMapObject");
}

yeram_client::WorldMapObject::~WorldMapObject()
{
}

void yeram_client::WorldMapObject::Initialize()
{
	mCollider = mOwner->AddComponent<Collider>();
	mAni = mOwner->AddComponent<Animator>();

	mCollider->Initialize();
	mAni->Initialize();
	Script::Initialize();
}

void yeram_client::WorldMapObject::Update()
{
}

void yeram_client::WorldMapObject::Render(HDC hdc)
{
}

void yeram_client::WorldMapObject::Release()
{
	Script::Release();
}

void yeram_client::WorldMapObject::OnCollisionEnter(Collider* other)
{
}

void yeram_client::WorldMapObject::OnCollisionStay(Collider* other)
{
}

void yeram_client::WorldMapObject::OnCollisionExit(Collider* other)
{
}

void yeram_client::WorldMapObject::SetColliderInfo()
{
	const Vector2 size = mAni->GetSpriteSize();
	mCollider->SetCenter(Vector2{ -(size.x / 2),-size.y });
	mCollider->SetSize(size);
}
