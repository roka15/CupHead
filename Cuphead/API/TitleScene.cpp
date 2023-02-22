#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"
yeram_client::TitleScene::TitleScene()
{
}

yeram_client::TitleScene::~TitleScene()
{
}

void yeram_client::TitleScene::Initialize()
{
	Scene::Initialize();
}

void yeram_client::TitleScene::Update()
{
	if (core::Input::GetKeyState(core::EKeyCode::A) == core::EKeyState::Down)
	{
		SceneManager::LoadScene(ESceneType::Play);
	}
	Scene::Update();
}

void yeram_client::TitleScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void yeram_client::TitleScene::Release()
{
	Scene::Release();
}

void yeram_client::TitleScene::OnEnter()
{

}

void yeram_client::TitleScene::OnExit()
{

}
