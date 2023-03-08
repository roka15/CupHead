#include "PlayMapScene.h"
#include "Player.h"
namespace yeram_client
{
	PlayMapScene::PlayMapScene()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		Player* player = new Player();
		player->CreateCharacter(ESceneType::PlayMap, EPlayerType::Cuphead);

		AddGameObject(player, ELayerType::Player);
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