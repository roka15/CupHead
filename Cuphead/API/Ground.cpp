#include "Ground.h"
#include "Player.h"
#include "Character.h"
yeram_client::Ground::Ground()
{
	mCollider = AddComponent<Collider>();
}

yeram_client::Ground::~Ground()
{
}

void yeram_client::Ground::Initialize()
{
	GameObject::Initialize();
}

void yeram_client::Ground::Update()
{
	GameObject::Update();
}

void yeram_client::Ground::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

void yeram_client::Ground::Release()
{
	GameObject::Release();
}

void yeram_client::Ground::OnCollisionEnter(Collider* other)
{
	Player* player = dynamic_cast<Player*>(other->GetOwner());
	if (player == nullptr)
		return;

	Character* ch =  player->GetActiveCharacter();
	ch->ResetJump();
	ch->ResetDash();
	ch->SetNextAniInfo();

	Rigidbody* rigid = player->GetComponent<Rigidbody>();
	rigid->SetGround(true);

	Collider* cupheadCol = player->GetComponent<Collider>();
	Vector2 cupheadPos = cupheadCol->GetPos();

	Collider* groundCol = this->GetComponent<Collider>();
	Vector2 groundPos = groundCol->GetPos();

	float fLen = fabs(cupheadPos.y - groundPos.y);
	float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

	if (fLen < fSize)
	{
		Transform* cupTr = player->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();

		Vector2 cupPos = cupTr->GetPos();
		Vector2 grPos = grTr->GetPos();

		cupPos -= (fSize - fLen) - 1.0f;
		cupTr->SetPos(cupPos);
	}
}

void yeram_client::Ground::OnCollisionStay(Collider* other)
{
}

void yeram_client::Ground::OnCollisionExit(Collider* other)
{
}

void yeram_client::Ground::InitComponent()
{
	
}


