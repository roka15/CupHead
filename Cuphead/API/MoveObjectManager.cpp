#include "MoveObjectManager.h"
#include "Animator.h"
#include "Transform.h"
#include "Rectangle.h"
#include "ObjectPool.h"
#include "MoveObject.h"

namespace yeram_client
{
	std::map<std::wstring, std::queue<std::shared_ptr<GameObject>>>  MoveObjectManager::m_regular_queue;
	std::queue<std::shared_ptr<GameObject>>  MoveObjectManager::m_irregular_queue;
	void MoveObjectManager::Initialize()
	{
		core::ObjectPool<MoveObject>::Initialize(GameObject::Instantiate<Rectangle>());
		
	}
	
	void MoveObjectManager::Release()
	{
		for (auto& map : m_regular_queue)
		{
			auto& queue = map.second;
			while (queue.empty() == false)
			{
				int cnt = queue.front().use_count();
				queue.front().reset();
				queue.pop();
			}
		}

		while (m_irregular_queue.empty() == false)
		{
			m_irregular_queue.front().reset();
			m_irregular_queue.pop();
		}
		
		core::ObjectPool<MoveObject>::Release();
	}
	std::shared_ptr<GameObject> MoveObjectManager::Create
	(const Vector2& _speed,
		float _dspawn_time,
		const Vector2& _diff,
		bool _regular_loop,
		const Vector2& _pos,
		const Vector2& _scale,
		std::wstring _ani_path,
		Vector2 _ani_offset,
		float _ani_duration,
		bool _ani_alpha)
	{
		std::shared_ptr<GameObject> owner = core::ObjectPool<MoveObject>::Spawn2();
	
		int cnt = owner.use_count();
		Animator* ani = owner->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(L"..\\Resources\\MM\\Ground\\Back1", Vector2::Zero, 0.1f);
		ani->Play(key, true);
		owner->SetName(key);
		Transform* tf = owner->GetComponent<Transform>();
		tf->SetPos(_pos);
		tf->SetScale(_scale);
		if (_regular_loop == true)
		{
			m_regular_queue[owner->GetName()].push(owner);
		}
		else
		{
			m_irregular_queue.push(owner);
		}
		return owner;
	}

	void MoveObjectManager::MapOut(GameObject* _obj)
	{
	}
	
}

