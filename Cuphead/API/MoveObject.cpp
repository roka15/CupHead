#include "MoveObject.h"
#include "GameObject.h"
#include "Collider.h"
namespace yeram_client
{
	MoveObject::MoveObject():Script()
	{
	}
	MoveObject::~MoveObject()
	{
	}

	void MoveObject::Create(std::wstring _ani_path, Vector2 _ani_offset, float _ani_duration, bool _ani_alpha, const Vector2& _speed, float _dspawn_time, const Vector2& _diff)
	{
	}
	
	
	void MoveObject::Move(const Vector2& _other)
	{
	}
	bool MoveObject::CheckMapOut()
	{
		return false;
	}
	void MoveObject::OnCollisionEnter(Collider* other)
	{
		Collider* col = GetOwner()->GetComponent<Collider>();

	}
	void MoveObject::OnCollisionStay(Collider* other)
	{
	}
	void MoveObject::OnCollisionExit(Collider* other)
	{
	}
}
