#pragma once
#include "Engine.h"
namespace yeram_client
{
	class GameObject;
	class MoveObjectManager
	{
	public:
		struct DirByte
		{
			static const byte left;
			static const byte right;
			static const byte up;
			static const byte down;
			static const byte all;
		};
		static void Initialize();
		static void Release();
		static std::shared_ptr<GameObject> Create(
			const Vector2& _speed,
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
			bool _ani_alpha = false);

		static bool MapOutCheck(GameObject* _obj);
		static void SetSpawnPos(GameObject* _obj);
		static void Move(GameObject* _obj);
	private:
		
		//���������� �پ �̵��ϴ� ������Ʈ�� ����.
		static std::map<std::wstring, std::queue<std::shared_ptr<GameObject>>> m_regular_queue;
		//�ؿ����� ��� update�� �Ŵ������� �������µ� ���� ������ layer ���� update ������
		//�ϴ� ����.
		//�ܵ����� �̵��ϴ� ������Ʈ ����.
		static std::map<UINT,std::shared_ptr<GameObject>> m_irregular_map;
		static RECT WindowRect;
	};

}

