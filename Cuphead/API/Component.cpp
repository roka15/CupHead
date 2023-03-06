#include "Component.h"
namespace yeram_client
{
	Component::Component(EComponentType _type)
        :mType(_type)
        , mOwner(nullptr)
	{
	}
    Component::~Component()
    {
    }
    void Component::Initialize()
    {
    }
    void Component::Update()
    {
    }
    void Component::Render(HDC hdc)
    {
    }
    void Component::Release()
    {
    }
}