#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Resources.h"
namespace yeram_client
{
	extern Application application;

	SpriteRenderer::SpriteRenderer()
		:Component(EComponentType::SpriteRenderer)
		,mRenderType(ERenderType::StretchBlt)
		,mImage(nullptr)
	{
	}
	
	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2 pos = transform->GetPos();
		Vector2 size = transform->GetScale();
		if (mImage != nullptr)
		{
			switch (mRenderType)
			{
			case ERenderType::BitBlt:
				BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHDC(), 0, 0, SRCCOPY);
				break;
			case ERenderType::TransParentBlt:
				TransparentBlt(hdc, pos.x, pos.y, size.x, size.y, mImage->GetHDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), (RGB(234, 2, 255)));
				break;
			case ERenderType::StretchBlt:
				StretchBlt(hdc, pos.x, pos.y, size.x, size.y, mImage->GetHDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
				break;
			}
		}
	}

	void SpriteRenderer::Release()
	{
	}

	void SpriteRenderer::SetImage(const std::wstring& _filename,const std::wstring& _path)
	{
		mImage = Resources::Load<Image>(_filename.c_str(), _path.c_str());
	}

}
