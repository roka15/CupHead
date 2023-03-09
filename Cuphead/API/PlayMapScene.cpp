#include "PlayMapScene.h"
#include "Player.h"
#include "Rectangle.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Application.h"
#include "Camera.h"

extern yeram_client::Application application;
namespace yeram_client
{
	PlayMapScene::PlayMapScene()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		Player* player = new Player();
		player->CreateCharacter(ESceneType::PlayMap, EPlayerType::Cuphead);
		Camera::SetTarger(player);
		Vector2 size = application.GetWindowSize();
		//temp map
		Rectangle* map = new Rectangle();
		{
			Transform* tf = map->GetComponent<Transform>();
			tf->SetPos(Vector2{ 0l,0l });
			tf->SetSize(Vector2{ (long)size.x,(long)size.y+200l });
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(L"MapBackGround"
				, L"..\\Resources\\Worldmap\\world1_temp.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
		}
		AddGameObject(player, ELayerType::Player);
		AddGameObject(map, ELayerType::BackObject);
	}
	PlayMapScene::~PlayMapScene()
	{
	}
	void PlayMapScene::Initialize()
	{
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
		//mLayers[(UINT)ELayerType::Player]->Initialize();
	}
}