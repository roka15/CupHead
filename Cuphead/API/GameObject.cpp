#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
extern yeram_client::Application application;
namespace yeram_client
{
	
	void GameObject::Initialize()
	{
		//mComponents.resize((UINT)EComponentType::MAX);
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Update();
		}
	}
	void GameObject::Render(HDC hdc)
	{ 
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Render(hdc);
		}
		
	}
	void GameObject::Release()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Release();
		}
	}



	GameObject::GameObject()
	{
		mComponents.resize((UINT)EComponentType::MAX - 1);
		AddComponent<Transform>();
	}
	
	GameObject::~GameObject()
	{
	}

}