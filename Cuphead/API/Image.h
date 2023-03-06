#pragma once
#include "My_Resource.h"
namespace yeram_client
{
	class Image:public My_Resource
	{
	public:
		static Image* Create(const std::wstring& _key,UINT _width,UINT _height);

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& _path) override;
		HDC GetHDC() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
	private:
		HBITMAP mBitmap;
		HDC mHdc;
		int mWidth;
		int mHeight;
	};

}


