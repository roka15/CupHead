#include "Image.h"
#include "Application.h"
extern yeram_client::Application application;
namespace yeram_client
{
	Image::Image()
		:mBitmap(NULL)
		,mHdc(NULL)
		,mWidth(0)
		,mHeight(0)
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
