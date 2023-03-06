#include "Transform.h"

yeram_client::Transform::Transform():Component(EComponentType::Transform)
,mPos(Vector2::Zero)
,mScale(Vector2::One)
{
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
}

void yeram_client::Transform::Release()
{
}
