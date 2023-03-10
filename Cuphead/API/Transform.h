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
		void SetScale(Vector2 _scale) { mScale = _scale; }
		void SetSize(Vector2 _size) { mSize = _size; }
		Vector2& GetPos() { return mPos; }
		Vector2& GetScale() { return mScale; }
		Vector2& GetSize() { return mSize; }
		void CaluatePos(const Vector2& _offset);
	private:
		Vector2 mPos;
		Vector2 mScale;
		Vector2 mSize;
	};
}


