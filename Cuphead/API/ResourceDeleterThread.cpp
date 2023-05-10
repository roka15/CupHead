#include "ResourceDeleterThread.h"
#include "Resources.h"
namespace core
{
	LRU_Queue<ResourceDeleterThread::myResource*, ResourceDeleterThread::resource_greater> ResourceDeleterThread::mLRUQueue(MAX_RESOURCE);

	void ResourceDeleterThread::RegisterResourceInfo(myResource* _resource)
	{
		// �� �Լ��� main thread���� �����ϴϱ� ����ȭ �����൵ �ɵ�?
		myResource* outData;
		bool is_delete = mLRUQueue.Push(_resource, outData);
		if (is_delete == true)
		{
			////������
			double time = outData->GetTime();
			////����볡
			std::wstring key = outData->GetKey();
			Resources::Remove(key);
			delete outData;
			outData = nullptr;
		}
	}

	DWORD __stdcall ResourceDeleterThread::DeleterThread(PVOID _param)
	{
		while (mLRUQueue.Empty() == false)
		{
			int a = 0;
		}
		return 0;
	}

	void ResourceDeleterThread::SetResourceQueueCapacity(size_t _capacity)
	{
		mLRUQueue.Capacity(_capacity);
	}

}
