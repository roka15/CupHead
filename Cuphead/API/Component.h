#pragma once
#include "Entity.h"
namespace yeram_client
{
	class Component:public Entity
	{
	public:
		Component()=delete;
		Component(EComponentType _type);
		virtual ~Component();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		const EComponentType& GetType() { return mType; }
	private:
		const EComponentType mType;
	};
}


