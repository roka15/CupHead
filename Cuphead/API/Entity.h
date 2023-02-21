#pragma once
#include "Engine.h"
namespace yeram_client
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		
		void SetName(std::wstring& name) { mName = name; }
		std::wstring& getName() { return mName; }
	private:
		std::wstring mName;
	};
}
