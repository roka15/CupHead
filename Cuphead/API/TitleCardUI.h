#pragma once
#include "Script.h"
namespace yeram_client
{
	class TitleCardUI : public Script
	{
	public:
		TitleCardUI();
		virtual ~TitleCardUI();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		std::function<void()>& GetEnterEvent() { return mEnterEvent; }
		std::function<void()>& GetEscEvent() { return mEscEvent; }
	private:
		std::function<void()> mEnterEvent;
		std::function<void()> mEscEvent;

	};
}

