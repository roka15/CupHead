#pragma once
#include "My_Resource.h"
namespace yeram_client
{

	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& _key)
		{
			std::map<std::wstring, My_Resource*>::iterator itr = mResources.find(_key);
			if (itr != mResources.end())
			{
				return dynamic_cast<T*>(itr->second);
			}

			return nullptr;
		}
		template <typename T>
		static T* Load(const std::wstring& _key, const std::wstring& _path)
		{
			T* resource = Find<T>(_key);
			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(_path)))
			{
				assert(false);
				return nullptr;
			}
			resource->SetKey(_key);
			resource->SetPath(_path);

			mResources.insert(std::make_pair(_key, resource));

			return dynamic_cast<T*>(resource);
		}

		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
			mResources.clear();
		}
	private:
		static std::map<std::wstring, My_Resource*> mResources;
	};

}


