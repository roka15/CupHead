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
	void PlayScene::Initalize()
	{
		Scene::Initalize();
		for (size_t i = 0; i < 500; i++)
		{
			Player* player = new Player();
			//player->SetPos(Vector2(0.0f, 0.0f + i));
			AddGameObject(player, ELayerType::Player);
		}
		
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
}