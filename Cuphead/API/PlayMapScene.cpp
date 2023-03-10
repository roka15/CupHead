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
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		Vector2 pos = application.GetWindowSize() / 2.0f;
		Player* player = GameObject::Instantiate<Player>(L"Player", Vector2{ pos.x,pos.y }, nullptr, ELayerType::Player);
		{
			player->CreateCharacter(ESceneType::PlayMap, EPlayerType::Cuphead);
		}

		Vector2 size = application.GetWindowSize();
		//temp map
		Rectangle* ocean = GameObject::Instantiate<Rectangle>(L"MapBackGround", Vector2{ 0l,0l }, nullptr, ELayerType::BackObject);
		{
			Transform* tf = ocean->GetComponent<Transform>();
			tf->SetSize(Vector2{ (long)size.x,(long)size.y + 200l });

			SpriteRenderer* render = ocean->AddComponent<SpriteRenderer>();
			render->SetImage(ocean->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Ocean\\Bottom\\Left\\world3_water_04.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
		}
		Vector2 map_pos;
		Rectangle* map_bottm_left = GameObject::Instantiate<Rectangle>(L"MapBL", Vector2{ pos.x - 100l,pos.y - 100l }, nullptr, ELayerType::BackObject);
		{
			Transform* tf = map_bottm_left->GetComponent<Transform>();
			map_pos = tf->GetPos();

			SpriteRenderer* render = map_bottm_left->AddComponent<SpriteRenderer>();
			render->SetImage(map_bottm_left->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_obj_doorl = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_L", Vector2{ map_pos.x + 377l,map_pos.y + 79l }, map_bottm_left, ELayerType::BackObject);
		{
			SpriteRenderer* render = mapbl_obj_doorl->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorl->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_bl.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_obj_doorr = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_R", Vector2{ map_pos.x + 377l,map_pos.y + 79l }, nullptr, ELayerType::FrontObject);
		{
			SpriteRenderer* render = mapbl_obj_doorr->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_br.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_obj_dooru = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_U", Vector2{ map_pos.x + 377l,map_pos.y + 79l }, nullptr, ELayerType::FrontObject);
		{
			SpriteRenderer* render = mapbl_obj_dooru->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_dooru->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_u.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
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
		GameObject* player = mLayers[(UINT)ELayerType::Player]->FindObject(L"Player");
		Camera::SetTarget(player);
		Scene::OnEnter();
	}
	void PlayMapScene::OnExit()
	{
		Camera::SetTarget(nullptr);
		Scene::OnExit();
	}
}