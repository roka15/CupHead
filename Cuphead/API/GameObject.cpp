#include "GameObject.h"
namespace yeram_client
{
    void GameObject::Initalize()
    {
		//mComponents.resize((UINT)EComponentType::MAX);
    }
    void GameObject::Update()
    {
    }
    void GameObject::Render(HDC hdc)
    {
    }
    void GameObject::Release()
    {
    }
	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::AddComponent(Component* _component)
	{
	}
	void GameObject::DeleteComponent(Component* _component)
	{
	}
}