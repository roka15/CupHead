#pragma once
#include "Component.h"
namespace yeram_client
{
	class Collider :
		public Component
	{
	public:
		virtual void Render(HDC hdc)override;

	};
}

