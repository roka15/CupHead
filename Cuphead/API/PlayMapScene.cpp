#include "PlayMapScene.h"
#include "Player.h"
#include "Rectangle.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Application.h"
#include "Camera.h"
#include "Layer.h"
extern yeram_client::Application application;
namespace yeram_client
{
	PlayMapScene::PlayMapScene()
	{
		mCurType = ESceneType::PlayMap;
	}
	PlayMapScene::~PlayMapScene()
	{
	}
	void PlayMapScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();

		Player* player = GameObject::Instantiate<Player>(L"Player", Vector2{ 0,0 }, ELayerType::Player);
		{
			player->CreateCharacter(ESceneType::PlayMap, EPlayerType::Cuphead);
			Camera::SetTarger(player);
		}
		Vector2 size = application.GetWindowSize();
		//temp map
		Rectangle* map = GameObject::Instantiate<Rectangle>(L"Map", Vector2{ 0l,0l }, ELayerType::BackObject);
		{
			Transform* tf = map->GetComponent<Transform>();
			tf->SetSize(Vector2{ (long)size.x,(long)size.y + 200l });

			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, L"..\\Resources\\Worldmap\\world1_temp.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
		}
		Scene::Initialize();
	}
	void PlayMapScene::Update()
	{
		Scene::Update();
	}
	void PlayMapScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayMapScene::Release()
	{
		Scene::Release();
	}
	void PlayMapScene::OnEnter()
	{
	}
	void PlayMapScene::OnExit()
	{
		Scene::OnExit();
	}
}