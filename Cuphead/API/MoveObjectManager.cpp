#include "MoveObjectManager.h"
#include "Application.h"
#include "Animator.h"
#include "Transform.h"
#include "Rectangle.h"
#include "ObjectPool.h"
#include "MoveObject.h"

extern yeram_client::Application application;
namespace yeram_client
{
	const byte MoveObjectManager::DirByte::left = 0x01;
	const byte MoveObjectManager::DirByte::right = 0x02;
	const byte MoveObjectManager::DirByte::up = 0x04;
	const byte MoveObjectManager::DirByte::down = 0x08;
	const byte MoveObjectManager::DirByte::all = 0x0F;


	std::map<std::wstring, std::queue<std::shared_ptr<GameObject>>>  MoveObjectManager::m_regular_queue;
	std::map<UINT,std::shared_ptr<GameObject>>  MoveObjectManager::m_irregular_map;
	RECT MoveObjectManager::WindowRect = { 0,0,0,0 };
	void MoveObjectManager::Initialize()
	{
		core::ObjectPool<MoveObject>::Initialize(GameObject::Instantiate<Rectangle>());
		Vector2 win_size = application.GetWindowSize();
		WindowRect.right = win_size.x;
		WindowRect.bottom = win_size.y;
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

		for (auto& map : m_irregular_map)
		{
			map.second.reset();
		}
		m_irregular_map.clear();

		core::ObjectPool<MoveObject>::Release();
	}
	std::shared_ptr<GameObject> MoveObjectManager::Create
	(const Vector2& _speed,
		float _dspawn_time,
		const Vector2& _diff,
		const byte _outdir,
		const Vector2& _dir,
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
		owner->GetComponent<MoveObject>()->CreateInfo(_speed, _dspawn_time, _diff, _outdir,_dir, _regular_loop);
		Animator* ani = owner->AddComponent<Animator>();
		std::wstring key = ani->CreateAnimations(_ani_path, _ani_offset, _ani_duration, _ani_alpha);
		ani->Play(key, true);
		owner->SetName(key);
		Transform* tf = owner->GetComponent<Transform>();
		tf->SetPos(_pos);
		tf->SetScale(_scale);
		MoveObject* mo = owner->GetComponent<MoveObject>();
		if (_regular_loop == true)
		{
			m_regular_queue[owner->GetName()].push(owner);
		}
		else
		{
			m_irregular_map.insert(std::make_pair(mo->GetID(),owner));
		}
		return owner;
	}

	bool MoveObjectManager::MapOutCheck(GameObject* _obj)
	{
		Transform* tf = _obj->GetComponent<Transform>();
		Animator* ani = _obj->GetComponent<Animator>();
		MoveObject* mo = _obj->GetComponent<MoveObject>();

		Vector2 pos = tf->GetPos();
		Vector2 size = ani->GetSpriteSize();
		byte dir = mo->GetOutCheckDir();
		bool flag = false;
		if (dir == DirByte::all)
		{
			if (pos.x + size.x < WindowRect.left || pos.x - size.x >WindowRect.right
				|| pos.y + size.y<WindowRect.top || pos.y - size.y>WindowRect.bottom)
				return true;
		}

		if ((dir& DirByte::left) == DirByte::left)
		{
			if (pos.x + size.x < WindowRect.left)
			{
				flag = true;
			}
		}
		if ((dir& DirByte::right) == DirByte::right)
		{
			if (pos.x - size.x > WindowRect.right)
			{
				flag = true;
			}
		}
		if ((dir & DirByte::up) == DirByte::up)
		{
			if (pos.y + size.y < WindowRect.top)
			{
				flag = true;
			}
		}
		if ((dir & DirByte::down) == DirByte::down)
		{
			if (pos.y - size.y > WindowRect.bottom)
			{
				flag = true;
			}
		}
		if (flag == true)
			return true;

		return false;
	}

	void MoveObjectManager::SetSpawnPos(GameObject* _obj)
	{
		Transform* tf = _obj->GetComponent<Transform>();
		MoveObject* mo = _obj->GetComponent<MoveObject>();

		bool regular = mo->GetRegular();
		if (regular == true)
		{
			Vector2 diff = mo->GetDiff();
			diff.x -= 1;

			std::wstring  name = _obj->GetName();
			std::queue<std::shared_ptr<GameObject>>& move_queue = m_regular_queue[name];
			Transform* spawn_tf = move_queue.back()->GetComponent<Transform>();
			Vector2 spawn_pos = spawn_tf->GetPos();

			diff.x += spawn_pos.x;
			diff.y += spawn_pos.y;

			tf->SetPos(diff);

			std::shared_ptr<GameObject> obj = move_queue.front();
			move_queue.pop();
			move_queue.push(obj);
		}
		else
		{
			//맵밖에 나가면 dspawn 되도록 한다.
			tf->SetPos(mo->GetStartPos());
			SceneManager::RemoveObject(_obj);
			std::map<UINT,std::shared_ptr<GameObject>>::iterator itr 
				= m_irregular_map.find(mo->GetID());

			if (itr != m_irregular_map.end())
			{
				itr->second.reset();
				m_irregular_map.erase(itr);
			}
		}

	}

	void MoveObjectManager::Move(GameObject* _obj)
	{
	}


}

