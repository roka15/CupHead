#include "Image.h"
#include "Application.h"
#include "Resources.h"
extern yeram_client::Application application;
namespace yeram_client
{
	Image* Image::Create(const std::wstring& _key, UINT _width, UINT _height, COLORREF rgb)
	{
		if (_width == 0 || _height == 0)
			return nullptr;

		Image* image = Resources::Find<Image>(_key);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC MainHDC = application.GetHDC();

		image->mBitmap = CreateCompatibleBitmap(MainHDC, _width, _height);
		image->mHdc = CreateCompatibleDC(MainHDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);
		image->mWidth = _width;
		image->mHeight = _height;

		image->SetKey(_key);
		Resources::Insert(_key, image);

		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->mHdc, myBrush);

		Rectangle(image->mHdc, -1, -1, _width + 1, _height + 1);

		DeleteObject(SelectObject(image->mHdc, oldBrush));
		
		return image;
	}

	Image::Image()
		:mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{

	}
	Image::~Image()
	{

	}
	HRESULT Image::Load(const std::wstring& _path)
	{
		//null,이미지경로,어떻게 이미지를 불러올것인가,얼마나 가져올것인가(다 가져올거라 0 0 ) , 로드 방식 
		mBitmap = (HBITMAP)LoadImageW(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}
		//mBitmap 에 불러와진 image 정보 불러와서 bitinfo에 넣음.
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHDC();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);
		return S_OK;
	}

}
