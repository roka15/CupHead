#pragma once
#include "Script.h"
namespace yeram_client
{
	class Animator;
	class CutScenePlayAnimation :
		public Script
	{
	public:
		CutScenePlayAnimation();
		virtual ~CutScenePlayAnimation();
		virtual void Initialize()override;
		virtual void Update();
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		void SetAnimation(std::wstring _ani_name, double _time); 
	private:
		std::queue<std::pair<std::wstring, double>> mAniQueue;
		double mLimitTime;
		double mCurTime;
		Animator* mAni;
	};
}


