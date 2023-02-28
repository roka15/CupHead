#include "PlayScene.h"
#include "Player.h"
namespace yeram_client
{
	PlayScene::PlayScene()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		Player* player = new Player(ERenderType::TransParentBlt);
		
		//player->SetPos(Vector2(0.0f, 0.0f + i));
		AddGameObject(player, ELayerType::Player);
		
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		
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
		Scene::OnExit();
		mLayers[(UINT)ELayerType::Player]->Initalize();
	}
}