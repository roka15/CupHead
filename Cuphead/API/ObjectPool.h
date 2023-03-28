#pragma once
#include "GameObject.h"
namespace core
{
	typedef yeram_client::Transform Transform;
	typedef yeram_client::GameObject GameObject;
	template <typename T>
	class ObjectPool
	{
	public:
		static void Initialize(size_t _capacity=100,size_t _max_capacity = 500);
		static void Release();
		static std::shared_ptr<T> Spawn();
		static void DeSpawn(GameObject* _obj);
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
	size_t ObjectPool<T>::mlimit_capacity = 0;

	template<typename T>
	inline void ObjectPool<T>::Initialize(size_t _capacity, size_t _max_capacity)
	{
		mcapacity = _capacity;
		mlimit_capacity = _max_capacity;
		int temp_min = mcapacity<mlimit_capacity ? mcapacity : mlimit_capacity;
		for (int i = 0; i < temp_min; i++)
			mpools.push(GameObject::Instantiate<T>());
	}
	template<typename T>
	inline void ObjectPool<T>::Release()
	{
		while (mpools.empty() == false)
		{
			T* obj = mpools.front();
			mpools.pop();
			obj->Release();
			delete obj;
		}
		mpools.~queue();
	}
	template<typename T>
	inline std::shared_ptr<T> ObjectPool<T>::Spawn()
	{
		if (mpools.size() <= 0)
		{
			UpgradePoolSize();
		}

		std::shared_ptr<T> obj(mpools.front(), DeSpawn);
		mpools.pop();
		obj->Initialize();
		obj->SetActive(true);
		return obj;
	}
	template<typename T>
	inline void ObjectPool<T>::DeSpawn(GameObject* _obj)
	{
		if (_obj == nullptr)
			return;
		T* obj = dynamic_cast<T*>(_obj);
		if (obj == nullptr)
			return;
		obj->InitComponent();
		obj->SetActive(false);
		obj->GetComponent<Transform>()->SetPos(Vector2::Zero);
		mpools.push(obj);
	}
	template<typename T>
	inline void ObjectPool<T>::UpgradePoolSize()
	{
		if (mpools.size() == 0)
		{
			int add_cnt = mcapacity == 1 ? mcapacity + 1 : mcapacity + (mcapacity / 2);

			if (add_cnt > mlimit_capacity)
				return;

			for(int i=mcapacity;i<add_cnt;i++)
				mpools.push(GameObject::Instantiate<T>());

			mcapacity = add_cnt;
		}
	}
}


