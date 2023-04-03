#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
extern yeram_client::Application application;
namespace yeram_client
{
	
	void GameObject::Initialize()
	{
		//mComponents.resize((UINT)EComponentType::MAX);
		
		for (int i = (int)EComponentType::NONE + 1; i < (int)EComponentType::MAX; i++)
		{
			EComponentType type = (EComponentType)i;
			for (Component* com : mComponents[type])
			{
				if (com == nullptr)
					continue;
				if (com->GetActive() == false)
					continue;
				com->Initialize();
			}
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
		for (int i = (int)EComponentType::NONE + 1; i < (int)EComponentType::MAX; i++)
		{
			EComponentType type = (EComponentType)i;
			for (Component* com : mComponents[type])
			{
				if (com == nullptr)
					continue;
				if (com->GetActive() == false)
					continue;
				com->Update();
			}
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
		for (int i = (int)EComponentType::NONE + 1; i < (int)EComponentType::MAX; i++)
		{
			EComponentType type = (EComponentType)i;
			for (Component* com : mComponents[type])
			{
				if (com == nullptr)
					continue;
				if (com->GetActive() == false)
					continue;
				com->Render(hdc);
			}
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
		for (int i = (int)EComponentType::NONE + 1; i < (int)EComponentType::MAX; i++)
		{
			EComponentType type = (EComponentType)i;
			if (mComponents.find(type) != mComponents.end())
			{
				for (Component* com : mComponents[type])
				{
					if (com == nullptr)
						continue;
					com->Release();
					delete com;
					com = nullptr;
				}
				mComponents[type].clear();
				mComponents[type].~vector();
			}
		}
		
		mComponents.clear();
	

		for (std::shared_ptr<GameObject> child : mChilds)
		{
			if (child == nullptr)
				continue;
			child.reset();
		}
		mChilds.clear();
		mChilds.~vector();
	}

	void GameObject::SetParent(GameObject* _obj)
	{
		if (_obj == nullptr)
			return;
		mParent = _obj;
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
		Transform* tf = GetComponent<Transform>();
		_child->SetParent(this);
		_child->GetComponent<Transform>()->SetPos(tf->GetPos());
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

	void GameObject::RemoveChilds()
	{
		for (std::shared_ptr<GameObject> child : mChilds)
		{
			if (child == nullptr)
				continue;
			child.reset();
		}
		mChilds.clear();
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{
		for (auto script_comp : mComponents[EComponentType::Script])
		{
			Script* script = dynamic_cast<Script*>(script_comp);
			if (script == nullptr)
				continue;
			script->OnCollisionEnter(other);
		}
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
		for (auto script_comp : mComponents[EComponentType::Script])
		{
			Script* script = dynamic_cast<Script*>(script_comp);
			if (script == nullptr)
				continue;
			script->OnCollisionStay(other);
		}
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
		for (auto script_comp : mComponents[EComponentType::Script])
		{
			Script* script = dynamic_cast<Script*>(script_comp);
			if (script == nullptr)
				continue;
			script->OnCollisionExit(other);
		}
	}

	void GameObject::MoveObjectSetting(float _speed, EDirType _dir_type)
	{
	}



	GameObject::GameObject():mParent(nullptr)
	{
		mbActive = true;
		AddComponent<Transform>();
	}
	
	GameObject::~GameObject()
	{
	}

}