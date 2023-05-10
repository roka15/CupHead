#pragma once
#include "CommonInclude.h"
#include "LRU_Queue.h"
#include "My_Resource.h"
#define MAX_RESOURCE 2400
namespace yeram_client
{
	class Resources;
}
namespace core
{
	class ResourceDeleterThread
	{
	protected:
		typedef yeram_client::My_Resource myResource;
		typedef yeram_client::Resource_Greater<myResource> resource_greater;
		typedef yeram_client::Resource_Less<myResource> resource_less;
		typedef yeram_client::Resources Resources;
	public:
		static void RegisterResourceInfo(myResource* _resource);
		static DWORD __stdcall DeleterThread(PVOID _param);
		static void SetResourceQueueCapacity(size_t _capacity);
	private:
		static LRU_Queue<myResource*, resource_greater> mLRUQueue;
	};
}


