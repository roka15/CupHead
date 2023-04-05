#pragma once
#include "Scene.h"
namespace yeram_client
{
	class MedusaScene :public Scene
	{
	public:
		MedusaScene();
		MedusaScene(std::wstring _name);
		~MedusaScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	private:
		void CreateGround();
		void CreateBackGround();
	private:
		
	};
}


