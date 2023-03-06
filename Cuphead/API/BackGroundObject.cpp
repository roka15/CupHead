#include "BackGroundObject.h"
#include "Transform.h"
#include "Resources.h"
namespace yeram_client
{
    BackGroundObject::BackGroundObject():GameObject()
    {
    }
    BackGroundObject::BackGroundObject(const std::wstring& _obj_name, const std::wstring& _image_path, ERenderType _type, Vector2 _pos, Vector2 _size):GameObject()
    {
        SetImage(Resources::Load<Image>(_obj_name.c_str(), _image_path.c_str()));
        
        SetTransform(_pos, _size);
    }
    BackGroundObject::~BackGroundObject()
    {
    }
    void BackGroundObject::Initialize()
    {
        GameObject::Initialize();
    }
    void BackGroundObject::Update()
    {
        GameObject::Update();
    }
    void BackGroundObject::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }
    void BackGroundObject::Release()
    {
        GameObject::Release();
    }
    void yeram_client::BackGroundObject::SetTransform(Vector2 _pos, Vector2 _size)
    {
        Transform* tf = GetComponent<Transform>();
        if (tf == nullptr)
            return;
        tf->SetPos(_pos);
        tf->SetSize(_size);
    }

}
