#pragma once
#include "Scene.h"
namespace yeram_client
{
	class InWorldIntroScene :public Scene
	{
	public:
		InWorldIntroScene();
		InWorldIntroScene(std::wstring _name);
		virtual ~InWorldIntroScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;


		void ActiveShot1();
		void ActiveShot2();
		void ActiveShot3();
		void ActiveShot4();
		void ActiveShot5();
	private:
	};
}


