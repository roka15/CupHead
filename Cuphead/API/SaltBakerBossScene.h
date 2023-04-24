#pragma once
#include "Scene.h"
namespace yeram_client
{
	class SaltBakerBossScene :public Scene
	{
	public:
		SaltBakerBossScene();
		SaltBakerBossScene(const std::wstring _name);
		virtual ~SaltBakerBossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();
	private:
		void Phase1_Info_Register();
		void Phase2_Info_Register();
		void Phase3_Info_Register();

		void Phase1_Run();
		void Phase2_Run();
		void Phase3_Run();
	private:
		bool mbPhase1_Flag;
		bool mbPhase2_Flag;
		bool mbPhase3_Flag;
	};
}


