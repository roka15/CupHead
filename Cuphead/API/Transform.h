#pragma once
#include "Component.h"
namespace yeram_client
{
	class Transform :public Component
	{
	public:
		Transform();
		~Transform();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void SetPos(Vector2 _pos) { mPos = _pos; }
		void SetSize(Vector2 _size) { mSize = _size; }
		Vector2& GetPos() { return mPos; }
	private:
		Vector2 mPos;
		Vector2 mSize;
	};
}


