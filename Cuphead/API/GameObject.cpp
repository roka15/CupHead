#include "GameObject.h"
#include "Transform.h"
namespace yeram_client
{
    void GameObject::Initalize()
    {
		//mComponents.resize((UINT)EComponentType::MAX);
		mComponents[(UINT)EComponentType::Transform] = new Transform();
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
		mComponents.resize((UINT)EComponentType::MAX - 1);
	}
	GameObject::~GameObject()
	{
	}
	
}