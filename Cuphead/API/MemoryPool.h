#pragma once
#include "CommonInclude.h"
namespace core
{
    #define MEMORY_BYTE 32768 
	
	class MemoryPool
	{
	public:
		struct memory_pool_info
		{
			memory_pool_info(size_t _size);
			~memory_pool_info();

			byte* current;
			std::vector<byte*> memorys;
		};

		static void* operator new(size_t _size);
		static void operator delete(void* _memory);
		static int AssignSize(size_t _size);
	private:
		static std::map<size_t,memory_pool_info> m_memory_pools;
	};
}

