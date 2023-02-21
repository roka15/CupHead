#include "MemoryPool.h"

namespace core
{
	std::map<size_t, MemoryPool::memory_pool_info> MemoryPool::m_memory_pools;
	MemoryPool::memory_pool_info::memory_pool_info(size_t _size)
	{
		int size = MEMORY_BYTE / _size;
		

	}
	MemoryPool::memory_pool_info::~memory_pool_info()
	{
		
	}
	void* MemoryPool::operator new(size_t _size)
	{
		int size = AssignSize(_size);
		if (m_memory_pools.find(size)==m_memory_pools.end())
		{
			//m_memory_pools[size] = 
		}
		return nullptr;
	}
	void MemoryPool::operator delete(void* memory)
	{
	}

	int MemoryPool::AssignSize(size_t _size)
	{
		return 0;
	}
	
}