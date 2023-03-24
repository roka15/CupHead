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

		for (std::shared_ptr<GameObject> child : mChilds)
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
		if (mbActive == false)
			return;
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			if (com->GetActive() == false)
				continue;
			com->Update();
		}

		for (std::shared_ptr<GameObject> child : mChilds)
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
		if (mbActive == false)
			return;
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			if (com->GetActive() == false)
				continue;
			com->Render(hdc);
		}
		
		for (std::shared_ptr<GameObject> child : mChilds)
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
		int i = 0;
		for (Component* com : mComponents)
		{
			if (com == nullptr)
				continue;
			com->Release();
			delete com;
			com = nullptr;
		}
		mComponents.clear();
		mComponents.~vector();

		for (std::shared_ptr<GameObject> child : mChilds)
		{
			if (child == nullptr)
				continue;
			child.reset();
		}
		mChilds.clear();
		mChilds.~vector();
	}

	void GameObject::InitComponent()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] == nullptr)
				continue;
			if (dynamic_cast<Transform*>(mComponents[i]) != nullptr)
				continue;
			mComponents[i]->Release();
			delete mComponents[i];
			mComponents[i] = nullptr;
		}
	}


	std::shared_ptr<GameObject> GameObject::FindChild(std::wstring _name)
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

	std::shared_ptr<GameObject> GameObject::FindChild(UINT _index)
	{
		UINT max = GetChildCount();
		if (max <= _index || 0 > _index)
			return nullptr;
		return mChilds[_index];
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> _child)
	{
		mChilds.push_back(_child);
	}

	void GameObject::RemoveChild(std::shared_ptr<GameObject> _child)
	{
		int i = 0;
		for (std::vector<std::shared_ptr<GameObject>>::iterator i = mChilds.begin();
			i!=mChilds.end();)
		{
			std::shared_ptr<GameObject> obj = (*i);
			if (obj->GetName() == _child->GetName())
			{
				obj.reset();
				mChilds.erase(i);
				return;
			}
			i++;
		}
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{

	}

	void GameObject::OnCollisionStay(Collider* other)
	{

	}

	void GameObject::OnCollisionExit(Collider* other)
	{

	}

	void GameObject::MoveObjectSetting(float _speed, EDirType _dir_type)
	{
	}



	GameObject::GameObject()
	{
		mbActive = true;
		mComponents.resize((UINT)EComponentType::MAX);
		AddComponent<Transform>();
	}
	
	GameObject::~GameObject()
	{
	}

}