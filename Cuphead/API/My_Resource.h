#pragma once
#include "CommonInclude.h"
namespace yeram_client
{
	template <typename T, typename = decltype(std::declval<T>().GetTime()) >
	struct Resource_Greater
	{
		bool operator()(T _obj1, T _obj2)
		{
			return _obj1.GetTime() > _obj2.GetTime();
		}
		bool operator()(T* _obj1, T* _obj2)
		{
			return _obj1->GetTime() > _obj2->GetTime();
		}
	};

	template <typename T, typename = decltype(std::declval<T>().GetTime()) >
	struct Resource_Less
	{
		bool operator()(T _obj1, T _obj2)
		{
			return _obj1.GetTime() < _obj2.GetTime();
		}
		bool operator()(T* _obj1, T* _obj2)
		{
			return _obj1->GetTime() < _obj2->GetTime();
		}
	};
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
		void SetTime(double _time) { mUseTime = _time; }
		double GetTime() { return mUseTime; }
	private:
		std::wstring mKey;
		std::wstring mPath;
		double mUseTime;
	};

	/*class Image : public My_Resource
	{

	};
	class Sound : public My_Resource
	{

	};*/
}

