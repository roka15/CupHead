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
		//null,�̹������,��� �̹����� �ҷ��ð��ΰ�,�󸶳� �����ð��ΰ�(�� �����ðŶ� 0 0 ) , �ε� ��� 
		mBitmap = (HBITMAP)LoadImageW(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}
		//mBitmap �� �ҷ����� image ���� �ҷ��ͼ� bitinfo�� ����.
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
