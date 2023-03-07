#include "Rectangle.h"

namespace yeram_client
{
	Rectangle::Rectangle()
	{
	}
	Rectangle::~Rectangle()
	{
	}
	void Rectangle::Initialize()
	{
		GameObject::Initialize();
	}
	void Rectangle::Update()
	{
		GameObject::Update();
	}
	void Rectangle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Rectangle::Release()
	{
		GameObject::Release();
	}
}