#pragma once
#include "Scene.h"
namespace yeram_client
{
	class SaltBakerIntroScene :
		public Scene
	{
	public:
		SaltBakerIntroScene();
		SaltBakerIntroScene(std::wstring _name);
		virtual ~SaltBakerIntroScene();
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();
	private:
		double mTime;
		bool mbStartTimer;
		bool mbSoundFlag;
		double mNextSceneTime;
	};
}


