#include "BulletManager.h"
#include "Bullet.h"
namespace yeram_client
{
	std::map<BulletManager::EShotBulletType, std::queue<std::shared_ptr<GameObject>>> BulletManager::mWaitBullets;
	std::map<BulletManager::EShotBulletType, std::vector<std::shared_ptr<GameObject>>> BulletManager::mRunBullets;

	void BulletManager::Initialize()
	{
		core::ObjectPool<Bullet>::Initialize(new GameObject(), SPAWN_BULLET_MAX * ((UINT)EShotBulletType::MAX-1));
		for (int i = ((UINT)EShotBulletType::NONE+1); i < (UINT)EShotBulletType::MAX ; i++)
		{
			for (int j = 0; j < SPAWN_BULLET_MAX; j++)
			{
				std::shared_ptr<GameObject> obj = core::ObjectPool<Bullet>::Spawn();
				if (obj==nullptr)
					continue;
				mWaitBullets[(EShotBulletType)i].push(obj);
			}
		}
        //Coll
	}

	void BulletManager::Update()
	{
		for (auto& map : mRunBullets)
		{
			auto& vec = map.second;
			for (auto& obj : vec)
			{
				//update.
				obj->Update();
			}
		}
	}

	void BulletManager::Render(HDC _hdc)
	{
		for (auto& map : mRunBullets)
		{
			auto& vec = map.second;
			for (auto& obj : vec)
			{
				//update.
				obj->Render(_hdc);
			}
		}
	}

	void BulletManager::Release()
	{
		for (auto& map : mRunBullets)
		{
			auto& vec = map.second;
			for (auto& obj : vec)
				obj.reset();
		}

		for (auto& map : mWaitBullets)
		{
			auto& queue = map.second;
			while (queue.empty() == false)
			{
				std::shared_ptr<GameObject> obj = queue.front();
				queue.pop();
				obj.reset();
			}
		}
	
		core::ObjectPool<Bullet>::Release();
	}

	bool BulletManager::MapOutCheck(GameObject* _obj)
	{
		return false;
	}

	void BulletManager::Shot(EShotBulletType _type, const Vector2& _start)
	{
	}

	void BulletManager::Wait(EShotBulletType _type, const UINT& _id)
	{
	}

	void BulletManager::NextPos(GameObject* _obj)
	{
	}

}
