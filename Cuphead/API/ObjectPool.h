#pragma once
#include "CommonInclude.h"
#include "GameObject.h"
namespace core
{
	class yeram_client::Transform;
	typedef yeram_client::Transform Transform;
	template <typename T>
	class ObjectPool
	{
	public:
		static void Initialize(size_t _capacity=100);
		static void Release();
		static T* Spawn();
		static void DeSpawn(yeram_client::GameObject* _obj);
	private:
		static void UpgradePoolSize();
		ObjectPool() = delete;
		~ObjectPool() = delete;
	private:
		static size_t mcapacity;
		static size_t mlimit_capacity;
		static std::queue<T*> mpools;
	};
	template <typename T>
	size_t ObjectPool<T>::mcapacity = 0;
	template <typename T>
	std::queue<T*> ObjectPool<T>::mpools;
	template <typename T>
	size_t ObjectPool<T>::mlimit_capacity = 500;

	template<typename T>
	inline void ObjectPool<T>::Initialize(size_t _capacity)
	{
		mcapacity = _capacity;
		int temp_min = mcapacity<mlimit_capacity ? mcapacity : mlimit_capacity;
		for (int i = 0; i < temp_min; i++)
			mpools.push(new T());
	}
	template<typename T>
	inline void ObjectPool<T>::Release()
	{
		for (auto obj : mpools)
		{
			delete obj;
		}
	}
	template<typename T>
	inline T* ObjectPool<T>::Spawn()
	{
		if (mpools.size() <= 0)
		{
			UpgradePoolSize();
		}
		if (mcapacity > mlimit_capacity)
			return nullptr; // 에러 메세지 발생.

		T* obj = mpools.front();
		mpools.pop();
		obj->SetActive(true);
		return obj;
	}
	template<typename T>
	inline void ObjectPool<T>::DeSpawn(yeram_client::GameObject* _obj)
	{
		if (_obj == nullptr)
			return;
		T* obj = dynamic_cast<T*>(_obj);
		if (obj == nullptr)
			return;

		obj->SetActive(false);
		obj->GetComponent<Transform>()->SetPos(Vector2::Zero());
		mpools.push(obj);
		return obj;
	}
	template<typename T>
	inline void ObjectPool<T>::UpgradePoolSize()
	{
		if (mpools.size() == 0)
		{
			int add_cnt = mcapacity+(mcapacity / 2);
			for(int i=mcapacity;i<add_cnt;i++)
				mpools.push(GameObject<T>::Instantiate());

			mcapacity = add_cnt;
		}
	}
}


