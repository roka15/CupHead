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
			if (com->GetActive() == false)
				continue;
			com->Initialize();
		}

		for (GameObject* child : mChilds)
		{
			if (child == nullptr)
				continue;
			if (child->GetActive() == false)
				continue;
			child->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			if (com->GetActive() == false)
				continue;
			com->Update();
		}

		for (GameObject* child : mChilds)
		{
			if (child == nullptr)
				continue;
			if (child->GetActive() == false)
				continue;
			child->Update();
		}
	}
	void GameObject::Render(HDC hdc)
	{ 
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			if (com->GetActive() == false)
				continue;
			com->Render(hdc);
		}
		
		for (GameObject* child : mChilds)
		{
			if (child == nullptr)
				continue;
			if (child->GetActive() == false)
				continue;
			child->Render(hdc);
		}
	}
	void GameObject::Release()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Release();
			delete com;
			com = nullptr;
		}

		for (GameObject* child : mChilds)
		{
			if (child == nullptr)
				continue;
			child->Release();
			delete child;
			child = nullptr;
		}

	}

	GameObject* GameObject::FindChild(std::wstring _name)
	{
		for (auto child : mChilds)
		{
			if (child == nullptr)
				continue;
			if (child->GetName() == _name)
				return child;

			FindChild(_name);
		}
		return nullptr;
	}

	void GameObject::AddChild(GameObject* _child)
	{
		mChilds.push_back(_child);
	}

	void GameObject::RemoveChild(GameObject* _child)
	{
		int i = 0;
		for (std::vector<GameObject*>::iterator i = mChilds.begin();
			i!=mChilds.end();)
		{
			GameObject* obj = (*i);
			if (obj->GetName() == _child->GetName())
			{
				obj->Release();
				delete obj;
				obj = nullptr;
				mChilds.erase(i);
				return;
			}
			i++;
		}
	}



	GameObject::GameObject()
	{
		mbActive = true;
		mComponents.resize((UINT)EComponentType::MAX - 1);
		AddComponent<Transform>();
	}
	
	GameObject::~GameObject()
	{
	}

}