#pragma once
#include "Component.h"
namespace yeram_client
{
	class Script :public Component
	{
	public:
		enum class EScriptType
		{
			Player,
			Bullet,
			Monster,
			Object,
			MAX
		};
		Script() = delete;
		Script(EScriptType _type);
		virtual ~Script();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		
		EScriptType GetScriptType() { return mScriptType; }
	private:
		EScriptType mScriptType;
	};
}


