#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
extern yeram_client::Application application;
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
		Transform* transform = GetComponent<Transform>();
		Vector2 pos = transform->GetPos();
		Vector2 size = transform->GetSize();
		if (mImage != nullptr)
		{
			switch (mRenderType)
			{
			case ERenderType::BitBlt:
				BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHDC(), 0, 0, SRCCOPY);
				break;
			case ERenderType::TransParentBlt:
			{   
				HDC tempDc = CreateCompatibleDC(application.GetHDC());
				
				TransparentBlt(hdc, pos.x, pos.y, size.x, size.y, mImage->GetHDC(), 0,0, mImage->GetWidth(), mImage->GetHeight(),(RGB(234, 2, 255)));
				break;
			}
			case ERenderType::StretchBlt:
				StretchBlt(hdc, pos.x, pos.y, size.x, size.y, mImage->GetHDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
				break;
			}
		}



	}
	void GameObject::Release()
	{
	}



	GameObject::GameObject()
	{
		mComponents.resize((UINT)EComponentType::MAX - 1);
		AddComponent<Transform>();
	}
	GameObject::GameObject(ERenderType _type) :GameObject()
	{
		mRenderType = _type;
	}
	GameObject::~GameObject()
	{
	}

}