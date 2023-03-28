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
		struct GroundInfo
		{
			Vector2 mDiff;
			Vector2 mSpeed;
		};
		void CreateGround();
		void CreateBackGround();
	private:

		void GroundUpdate();
		bool CheckOutMap(GameObject* _obj);
		void GroundInfoRelease();

	private:
		std::map<std::wstring, std::queue<std::shared_ptr<GameObject>>> mGroundsInfo;
		std::map<std::wstring, GroundInfo> mGroundInfos;
		bool mYFlag;
		float mTime;

	};
}


