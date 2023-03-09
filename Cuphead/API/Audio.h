#pragma once
#include "Component.h"
namespace yeram_client
{
	class Audio :
		public Component
	{
	public:
		virtual void Render(HDC hdc)override;
	};
}


