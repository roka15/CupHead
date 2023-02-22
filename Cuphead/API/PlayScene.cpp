#include "PlayScene.h"
#include "Player.h"
namespace yeram_client
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Player* player = new Player();
		//player->SetPos(Vector2(0.0f, 0.0f + i));
		AddGameObject(player, ELayerType::Player);
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		mLayers[(UINT)ELayerType::Player]->Initalize();
	}
}