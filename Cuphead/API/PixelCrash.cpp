#include "PixelCrash.h"
#include "Player.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"
#include "Image.h"
yeram_client::PixelCrash::PixelCrash() :Script()
{
	SetName(L"PixelCrash");
	mSprite = nullptr;
	mCollider = nullptr;
	mTarget = nullptr;
}

yeram_client::PixelCrash::~PixelCrash()
{
}

void yeram_client::PixelCrash::Initialize()
{
	Script::Initialize();
	mSprite = mOwner->AddComponent<SpriteRenderer>();
	mCollider = mOwner->AddComponent<Collider>();
	mSprite->Initialize();
	mCollider->Initialize();
}

void yeram_client::PixelCrash::Update()
{
	if (mTarget == nullptr)
		return;

	Transform* tf = mTarget->GetComponent<Transform>();
	Player* player = mTarget->GetComponent<Player>();
	Vector2 offset = player->GetMoveOffset();
	Transform* pixel_tf = mOwner->GetComponent<Transform>();
	Vector2 pos = tf->GetPos();
	Vector2 pixel_pos = pixel_tf->GetPos();
	Vector2 result_pos = pos - pixel_pos;

	COLORREF color = mImage->GetPixel(result_pos.x, result_pos.y);
	if (color == RGB(255, 0, 255))
	{
		tf->SetPos(pos - offset);
		SceneManager::ChagePosGameObjects(-offset);
	}
}

void yeram_client::PixelCrash::Render(HDC hdc)
{
}

void yeram_client::PixelCrash::Release()
{
	if (mTarget != nullptr)
		mTarget.reset();
	Script::Release();
}

void yeram_client::PixelCrash::OnCollisionEnter(Collider* other)
{
}

void yeram_client::PixelCrash::OnCollisionStay(Collider* other)
{
}

void yeram_client::PixelCrash::OnCollisionExit(Collider* other)
{
}

void yeram_client::PixelCrash::SetImage(std::wstring _name, std::wstring _path)
{
	mSprite->SetImage(_name, _path);
	mImage = mSprite->GetImage();
}
