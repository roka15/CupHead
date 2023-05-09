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
		size.x = obj_size.x == 0 ?mImageSize.x : obj_size.x;
		size.y = obj_size.y == 0 ? mImageSize.y : obj_size.y;

		if (mImageKey.size() != 0)
		{
			Image* findImage = Resources::Find<Image>(mImageKey);
			if (findImage == nullptr)
			{
				findImage = Resources::Load<Image>(mImageKey, mPath);
			}	
			switch (mRenderType)
			{
			case ERenderType::BitBlt:
				BitBlt(hdc, pos.x, pos.y, size.x * scale.x, size.y * scale.y, findImage->GetHDC(), 0, 0, SRCCOPY);
				break;
			case ERenderType::TransParentBlt:
				TransparentBlt(hdc, pos.x, pos.y, size.x*scale.x, size.y*scale.y, findImage->GetHDC(), 0, 0, mImageSize.x, mImageSize.y, (RGB(255, 0, 255)));
				break;
			case ERenderType::StretchBlt:
				StretchBlt(hdc, pos.x, pos.y, size.x * scale.x, size.y * scale.y, findImage->GetHDC(), 0, 0, mImageSize.x, mImageSize.y, SRCCOPY);
				break;
			}
		}
	}

	void SpriteRenderer::Release()
	{
		/*const std::wstring name = mImage->GetKey();
		Resources::Remove(name);*/
	}

	void SpriteRenderer::SetImage(const std::wstring& _filename, const std::wstring& _path)
	{
		Image* image = Resources::Load<Image>(_filename.c_str(), _path.c_str());
		mImageKey = image->GetKey();
		mPath = _path;
		Transform* tf = mOwner->GetComponent<Transform>();
		Vector2 pos = tf->GetPos();
		mImageSize = Vector2{(int)image->GetWidth(),(int)image->GetHeight()};
		pos.x -= mImageSize.x;
		pos.y -= mImageSize.y;
	}

	const float& SpriteRenderer::GetWidth()
	{
		return mImageSize.x;
	}

	const float& SpriteRenderer::GetHeight()
	{
		return mImageSize.y;
	}

}
