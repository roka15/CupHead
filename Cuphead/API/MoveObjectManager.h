#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class MoveObjectManager
	{
	public:
		static void Initialize();
		static void Release();
		static std::shared_ptr<GameObject> Create(
							const Vector2& _speed,
							float _dspawn_time,
							const Vector2& _diff,
			                bool _regular_loop,
			                const Vector2& _pos,
			                const Vector2& _scale,
							std::wstring _ani_path,
							Vector2 _ani_offset,
							float _ani_duration,
							bool _ani_alpha=false);

		static void MapOut(GameObject* _obj);
	private:
		static std::map<std::wstring,std::queue<std::shared_ptr<GameObject>>> m_regular_queue;
		static std::queue<std::shared_ptr<GameObject>> m_irregular_queue;
	};

}

