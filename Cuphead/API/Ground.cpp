#include "Ground.h"
#include "Player.h"
#include "GameObject.h"
#include "Character.h"

yeram_client::Ground::Ground():Script()
{
	SetName(L"Ground");
}

yeram_client::Ground::~Ground()
{
}

void yeram_client::Ground::Initialize()
{
	Script::Initialize();
	mCollider = GetOwner()->AddComponent<Collider>();
}

void yeram_client::Ground::Update()
{
	
}

void yeram_client::Ground::Render(HDC hdc)
{
	
}

void yeram_client::Ground::Release()
{
	
}

void yeram_client::Ground::OnCollisionEnter(Collider* other)
{
	GameObject* other_obj = other->GetOwner();
	Player* player = other_obj->GetComponent<Player>();
	if (player == nullptr)
		return;

	Character* ch =  player->GetActiveCharacter();
	ch->ResetJump();
	ch->ResetDash();
	ch->SetNextAniInfo();

	Rigidbody* rigid = other_obj->GetComponent<Rigidbody>();
	rigid->SetGround(true);

	Collider* cupheadCol = other_obj->GetComponent<Collider>();
	Vector2 cupheadPos = cupheadCol->GetPos();

	Collider* groundCol = mOwner->GetComponent<Collider>();
	Vector2 groundPos = groundCol->GetPos();

	float fLen = fabs(cupheadPos.y - groundPos.y);
	float fSize = (cupheadCol->GetSize().y/2.0f)+ (groundCol->GetSize().y/2.0f);///2.0f) + (groundCol->GetSize().y);/// 2.0f);

	if (fLen < fSize)
	{
		Transform* cupTr = other_obj->GetComponent<Transform>();
		Transform* grTr = mOwner->GetComponent<Transform>();

		Vector2 cupPos = cupTr->GetPos();
		Vector2 grPos = grTr->GetPos();

		cupPos.y -= (fSize - fLen) - 1.0f;
		cupTr->SetPos(cupPos);
	}
}

void yeram_client::Ground::OnCollisionStay(Collider* other)
{
}

void yeram_client::Ground::OnCollisionExit(Collider* other)
{
}



