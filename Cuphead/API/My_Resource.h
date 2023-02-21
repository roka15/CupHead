#pragma once
#include "CommonInclude.h"
namespace yeram_client
{
	class My_Resource
	{
	public:
		My_Resource();
		virtual ~My_Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;
		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		void SetKey(std::wstring _key) { mKey = _key; }
		void SetPath(std::wstring _path) { mPath = _path; }
	private:
		std::wstring mKey;
		std::wstring mPath;
	};

	/*class Image : public My_Resource
	{

	};
	class Sound : public My_Resource
	{

	};*/
}

