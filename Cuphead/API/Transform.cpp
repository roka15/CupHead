#include "Transform.h"
#include "GameObject.h"
yeram_client::Transform::Transform() :Component(EComponentType::Transform)
, mPos(Vector2::Zero)
, mScale(Vector2::One)
, mSize(Vector2::Zero)
{
	SetName(L"Transform");
}

yeram_client::Transform::~Transform()
{
}

void yeram_client::Transform::Initialize()
{
}

void yeram_client::Transform::Update()
{

}

void yeram_client::Transform::Render(HDC hdc)
{
	if (mbActive == false)
		return;
}

void yeram_client::Transform::Release()
{
}

void yeram_client::Transform::CaluatePos(const Vector2& _offset)
{
	int size = mOwner->GetChildCount();
	for (int i = 0; i < size; i++)
	{
		mOwner->FindChild(i)->GetComponent<Transform>()->CaluatePos(_offset);
	}
	mPos -= _offset;
}
