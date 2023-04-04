#pragma once
#include "ObjectPool.h"

namespace yeram_client
{
#define SPAWN_BULLET_MAX 50
	class BulletManager
	{
	public:
		enum class EShotBulletType
		{
			NONE,
			Direct,
			Guided_Missile,
			ZigZag,
			Scatter,
			MAX
		};
	   
		static void Initialize();
		static void Update();         //run bullet update and render
		static void Render(HDC _hdc);
		static void Release();
		static void Shot(EShotBulletType _type, const Vector2& _start);//run¿¡ push
		static void Wait(EShotBulletType _type, const UINT& _id);//wait¿¡ push

		static void NextPos(GameObject* _obj);
	private:
		static bool MapOutCheck(GameObject* _obj);
	private:
		static std::map<EShotBulletType, std::queue<std::shared_ptr<GameObject>>> mWaitBullets;
		static std::map<EShotBulletType, std::vector<std::shared_ptr<GameObject>>> mRunBullets;
	};
}

