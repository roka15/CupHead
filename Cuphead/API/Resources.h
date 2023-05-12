#pragma once
#include "ResourceDeleterThread.h"
namespace yeram_client
{

	class Resources
	{
	public:
		static void Update();
		
		template <typename T>
		static T* Find(const std::wstring& _key)
		{
			std::map<std::wstring, My_Resource*>::iterator itr = mResources.find(_key);
			if (itr != mResources.end())
			{
				itr->second->SetTime(mTime);
				//sort Ω√≈∞±‚.
				core::ResourceDeleterThread::DeleterQueueSort();
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
			resource->SetTime(mTime);
		
			return dynamic_cast<T*>(resource);
		}
		template<typename T>
		static void Insert(const std::wstring& _key, T* _resource)
		{
			mResources.insert(std::make_pair(_key, _resource));
		}
		
		static void Remove(const std::wstring& _key)
		{
			mResources.erase(mResources.find(_key));
		}
		static void Release()
		{
			/*for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
			mResources.clear();*/
		}
		static double GetTime() { return mTime; }
	private:
		static std::map<std::wstring, My_Resource*> mResources;
		static double mTime;
		//static std::priority_queue<pq_time, std::map<std::wstring,My_Resource*>> mLRUQueue;
	};

}


