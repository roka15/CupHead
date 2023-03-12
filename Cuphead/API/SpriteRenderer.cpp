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
		, mRenderType(ERenderType::StretchBlt)
		, mImage(nullptr)
	{
		SetName(L"SpriteRenderer");
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
		if (mbActive == false)
			return;
		Transform* transform = mOwner->GetComponent<Transform>();
		Vector2 pos = transform->GetPos();
		Vector2 obj_size = transform->GetSize();
		Vector2 scale = transform->GetScale();
		Vector2 size;
		size.x = obj_size.x == 0 ? mImage->GetWidth() : obj_size.x;
		size.y = obj_size.y == 0 ? mImage->GetHeight() : obj_size.y;

		if (mImage != nullptr)
		{
			switch (mRenderType)
			{
			case ERenderType::BitBlt:
				BitBlt(hdc, pos.x, pos.y, size.x * scale.x, size.y * scale.y, mImage->GetHDC(), 0, 0, SRCCOPY);
				break;
			case ERenderType::TransParentBlt:
				TransparentBlt(hdc, pos.x, pos.y, size.x*scale.x, size.y*scale.y, mImage->GetHDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), (RGB(255, 0, 255)));
				break;
			case ERenderType::StretchBlt:
				StretchBlt(hdc, pos.x, pos.y, size.x * scale.x, size.y * scale.y, mImage->GetHDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
				break;
			}
		}
	}

	void SpriteRenderer::Release()
	{
	}

	void SpriteRenderer::SetImage(const std::wstring& _filename, const std::wstring& _path)
	{
		mImage = Resources::Load<Image>(_filename.c_str(), _path.c_str());
		Transform* tf = mOwner->GetComponent<Transform>();
		Vector2 pos = tf->GetPos();
		pos.x -= mImage->GetWidth();
		pos.y -= mImage->GetHeight();
	}

	const float& SpriteRenderer::GetWidth()
	{
		return mImage->GetWidth();
	}

	const float& SpriteRenderer::GetHeight()
	{
		return mImage->GetHeight();
	}

}
