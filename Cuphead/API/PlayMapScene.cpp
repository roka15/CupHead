#include "PlayMapScene.h"
#include "Player.h"
#include "Rectangle.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Application.h"
#include "Camera.h"
#include "Layer.h"
#include "Animator.h"
#include "PixelCrash.h"
#include "WorldMapObject.h"
#include "Input.h"
#include "Time.h"
#include "ObjectPool.h"
#include "Camera.h"
#include "ColliderManager.h"
extern yeram_client::Application application;
namespace yeram_client
{
	PlayMapScene::PlayMapScene()
	{
		mCurType = ESceneType::PlayMap;
	}
	PlayMapScene::PlayMapScene(std::wstring _name)
	{
		mCurType = ESceneType::PlayMap;
		SetName(_name);
	}
	PlayMapScene::~PlayMapScene()
	{
	}
	void PlayMapScene::Initialize()
	{
		mLayers[(UINT)ELayerType::Player] = new Layer();
		mLayers[(UINT)ELayerType::BackObject] = new Layer();
		mLayers[(UINT)ELayerType::BackColObject] = new Layer();
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		//OnEnter();

	}
	void PlayMapScene::Update()
	{

		if (core::Input::GetKeyDown(core::EKeyCode::MouseRight))
		{
			SceneManager::LoadScene(ESceneType::Tutorial);
			
			//SceneManager::OpenLodingScreen();
		}
		if (core::Input::GetKeyDown(core::EKeyCode::N))
		{
			bool flag = FindObject(L"pixel_map")->GetComponent<SpriteRenderer>()->GetActive();
			FindObject(L"pixel_map")->GetComponent<SpriteRenderer>()->SetActive(!flag);
		}
		//화면 확대 축소
		/*if (core::Input::GetKeyDown(core::EKeyCode::MouseLeft))
		{
			Camera::SetCameraDistance(0.5f);
		}
		if (core::Input::GetKeyDown(core::EKeyCode::MouseRight))
		{
			Camera::SetCameraDistance(2.0f);
		}*/

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
		Camera::SetHorizontalMove(true);
		Camera::SetVerticalMove(true);
		ColliderManager::SetLayer(ELayerType::BackColObject, ELayerType::Player, true);
		Vector2 pos = application.GetWindowSize() / 2.0f;
		//GameObject* player_obj = mLayers[(UINT)ELayerType::Player]->FindObject(L"Player").get();
		std::shared_ptr<GameObject> player_obj = core::ObjectPool<Player>::Spawn();
		{
			player_obj->SetName(L"Player");
			Transform* tf = player_obj->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x,pos.y });


			std::shared_ptr<GameObject> player_reg = core::ObjectPool<Animator>::Spawn();
			player_reg->SetName(L"Reg");
			player_obj->AddChild(player_reg);
			std::shared_ptr<GameObject> player_head = core::ObjectPool<Animator>::Spawn();
			player_head->SetName(L"Head");
			player_obj->AddChild(player_head);

			std::shared_ptr<GameObject> player_shooter = core::ObjectPool<Animator>::Spawn();
			player_shooter->SetName(L"Shooter");
			player_obj->AddChild(player_shooter);

			Player* player = player_obj->GetComponent<Player>();
			player->CreateCharacter(EPlayerType::MsChalice);
			player->CreateCharacter(EPlayerType::Cuphead);
			player_obj->SetActive(false);

			if (player_obj != nullptr)
			{
				player_obj->SetActive(true);
				Camera::SetTarget(player_obj.get());
				Player* player = player_obj->GetComponent<Player>();
				player->ChangeCharacter(EPlayerType::Cuphead);
				Transform* tf = player_obj->GetComponent<Transform>();
				tf->SetPos(Vector2{ pos.x,pos.y });
			}
			
		}
		CreateWorldMap(pos);

#pragma region pixel crash
		std::shared_ptr<GameObject> pixel_map= core::ObjectPool<PixelCrash>::Spawn();
		pixel_map->SetName(L"pixel_map");
		pixel_map->SetCameraMoveActive(true);
		Transform* tf = pixel_map->GetComponent<Transform>();
		tf->SetPos(Vector2{ 300.0f,-1000.0f });
		PixelCrash* pixel = pixel_map->AddComponent<PixelCrash>();
		pixel->SetImage(L"pixel_map_dlc", L"..\\Resources\\MapObject\\dlc\\pixelmap\\dlc_main_land_pixel.bmp");
		pixel->SetTarget(player_obj);
		pixel_map->GetComponent<SpriteRenderer>()->SetActive(false);
		AddGameObject(pixel_map, ELayerType::FrontObject);
#pragma endregion

		AddGameObject(player_obj, ELayerType::Player);
		//Camera::PlayLoad();
		Scene::OnEnter();
	}
	void PlayMapScene::OnExit()
	{
		ColliderManager::SetLayer(ELayerType::BackColObject, ELayerType::Player, false);
		//switch 로 로드할 맵 타입에 따라 load 달리하기
		Camera::SetTarget(nullptr);
		Scene::OnExit();
	}
	void PlayMapScene::CreateWorldMap(const Vector2& _startpos)
	{
		Vector2 size = application.GetWindowSize();
		//temp map
		std::shared_ptr<GameObject> ocean = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			ocean->SetName(L"DLC_Water");
			ocean->SetCameraMoveActive(false);

			Transform* tf = ocean->GetComponent<Transform>();
			tf->SetSize(Vector2{ (long)size.x,(long)size.y + 200l });

			SpriteRenderer* render = ocean->GetComponent<SpriteRenderer>();
			render->SetImage(ocean->GetName().c_str()
				, L"..\\Resources\\MapObject\\dlc\\water\\dlc_water_multiply.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
			AddGameObject(ocean, ELayerType::BackObject);
		}
		Vector2 base_pos = { 300.0f,-1000.0f };
		std::shared_ptr<GameObject> map = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			map->SetName(L"DLC_Main_Map");
			Transform* tf = map->GetComponent<Transform>();
			tf->SetPos(base_pos);
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, L"..\\Resources\\MapObject\\dlc\\map\\dlc_main_land.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(map, ELayerType::BackColObject);
		}
		std::shared_ptr<GameObject> maptop = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			maptop->SetName(L"DLC_Main_Map_Top");
			Transform* tf = maptop->GetComponent<Transform>();
			tf->SetPos(Vector2{ 310.0f,-1000.0f });
			SpriteRenderer* render = maptop->AddComponent<SpriteRenderer>();
			render->SetImage(maptop->GetName().c_str()
				, L"..\\Resources\\MapObject\\dlc\\map\\dlc_main_top.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(maptop, ELayerType::FrontObject);
		}
#pragma region map object
		std::shared_ptr<GameObject> tutorial = core::ObjectPool<WorldMapObject>::Spawn();
		{
			tutorial->SetName(L"tutorial_obj");
			Vector2 pos = base_pos;
			pos.x += 1450.0f;
			pos.y += 700.0f;
			Transform* tf = tutorial->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = tutorial->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\object\\tutorial", Vector2::Zero, 0.1f);
			ani->Play(L"objecttutorial", true);
			WorldMapObject* wm = tutorial->GetComponent<WorldMapObject>();
			wm->SetColliderInfo();
			wm->SetSceneType(ESceneType::Tutorial);
			AddGameObject(tutorial, ELayerType::BackColObject);
		}

		std::shared_ptr<GameObject> saltbaker = core::ObjectPool<WorldMapObject>::Spawn();
		{
			saltbaker->SetName(L"objectsaltbaker");
			Vector2 pos = base_pos;
			pos.x += 1030.0f;
			pos.y += 730.0f;
			Transform* tf = saltbaker->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = saltbaker->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\object\\saltbaker", Vector2::Zero, 0.1f);
			ani->Play(L"objectsaltbaker", true);
			WorldMapObject* wm = saltbaker->GetComponent<WorldMapObject>();
			wm->SetColliderInfo();
			AddGameObject(saltbaker, ELayerType::BackColObject);
		}
		std::shared_ptr<GameObject> sb_left_house = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			sb_left_house->SetName(L"sbLeftHouse");
			Transform* tf = sb_left_house->GetComponent<Transform>();
			Vector2 pos = base_pos;
			pos.x += 830.0f;
			pos.y += 550.0f;
			tf->SetPos(pos);
			SpriteRenderer* render = sb_left_house->AddComponent<SpriteRenderer>();
			render->SetImage(sb_left_house->GetName().c_str()
				, L"..\\Resources\\MapObject\\dlc\\object\\bakershop_lefthouse\\bakery_neighbor.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(sb_left_house, ELayerType::FrontObject);
		}

		std::shared_ptr<GameObject> shop = core::ObjectPool<WorldMapObject>::Spawn();
		{
			shop->SetName(L"objectshop");
			Vector2 pos = base_pos;
			pos.x += 1800.0f;
			pos.y += 650.0f;
			Transform* tf = shop->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = shop->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\object\\shop", Vector2::Zero, 0.1f);
			ani->Play(L"objectshop", true);
			WorldMapObject* wm = shop->GetComponent<WorldMapObject>();
			wm->SetColliderInfo();
			AddGameObject(shop, ELayerType::BackColObject);
		}

		std::shared_ptr<GameObject> boogie_house = core::ObjectPool<WorldMapObject>::Spawn();
		{
			boogie_house->SetName(L"objectboogieh");
			Vector2 pos = base_pos;
			pos.x += 1130.0f;
			pos.y += 1450.0f;
			Transform* tf = boogie_house->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = boogie_house->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\object\\boogie", Vector2::Zero, 0.1f);
			ani->Play(L"objectboogie", true);
			WorldMapObject* wm = boogie_house->GetComponent<WorldMapObject>();
			wm->SetColliderInfo();
			AddGameObject(boogie_house, ELayerType::BackColObject);
		}
		std::shared_ptr<GameObject> boat_water = core::ObjectPool<Animator>::Spawn();
		{
			boat_water->SetName(L"boat_water");
			Vector2 pos = base_pos;
			pos.x += 30.0f;
			pos.y += 1640.0f;
			Transform* tf = boat_water->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = boat_water->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\npc\\boat_water", Vector2::Zero, 0.1f);
			ani->Play(L"npcboat_water", true);
			AddGameObject(boat_water, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> boat = core::ObjectPool<Animator>::Spawn();
		{
			boat->SetName(L"boat");
			Vector2 pos = base_pos;
			pos.x += 30.0f;
			pos.y += 1640.0f;
			Transform* tf = boat->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = boat->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\npc\\boat", Vector2::Zero, 0.1f);
			ani->Play(L"npcboat", true);
			AddGameObject(boat, ELayerType::BackObject);
		}
#pragma endregion

#pragma region npc
		std::shared_ptr<GameObject> boatman = core::ObjectPool<WorldMapObject>::Spawn();
		{
			boatman->SetName(L"boatman");
			Vector2 pos = base_pos;
			pos.x += 230.0f;
			pos.y += 1540.0f;
			Transform* tf = boatman->GetComponent<Transform>();
			tf->SetPos(pos);
			Animator* ani = boatman->GetComponent<Animator>();
			ani->CreateAnimations(L"..\\Resources\\MapObject\\dlc\\npc\\boatman", Vector2::Zero, 0.1f);
			ani->Play(L"npcboatman", true);
			WorldMapObject* wm = boatman->GetComponent<WorldMapObject>();
			wm->SetColliderInfo();
			AddGameObject(boatman, ELayerType::BackColObject);
		}
	
#pragma endregion


	}
	GameObject* PlayMapScene::CreateWroldGround(const std::wstring _name, const Vector2& _pos, GameObject* _parent, ELayerType _type, const std::wstring _image_path)
	{
		GameObject* return_ptr = nullptr;
		std::shared_ptr<GameObject> map = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			map->SetName(_name);
			map->SetParent(_parent);
			return_ptr = map.get();
			
			Transform* tf = map->GetComponent<Transform>();
			tf->SetPos(_pos);
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, _image_path);
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(map, _type);
		}

		return return_ptr;
	}
	void  PlayMapScene::CreateMapBL(GameObject* _parent)
	{
		std::shared_ptr<GameObject> mapbl_obj_doorl = core::ObjectPool<SpriteRenderer>::Spawn();
		_parent->AddChild(mapbl_obj_doorl);
		{
			mapbl_obj_doorl->SetName(L"MapBL_Door1_L");
			
			Transform* tf = mapbl_obj_doorl->GetComponent<Transform>();
			tf->SetOffset(Vector2{ 380.0f,73.0f });
			SpriteRenderer* render = mapbl_obj_doorl->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorl->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_bl.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mapbl_obj_doorl, ELayerType::BackObject);
		}
		std::shared_ptr<GameObject> mapbl_obj_doorr = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mapbl_obj_doorr->SetName(L"MapBL_Door1_R");
		
			Transform* tf = mapbl_obj_doorr->GetComponent<Transform>();
			tf->SetPos(Vector2{1180.0f,530.0f});
			SpriteRenderer* render = mapbl_obj_doorr->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_br.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mapbl_obj_doorr, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> mapbl_obj_dooru = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mapbl_obj_dooru->SetName(L"MapBL_Door1_U");
			
			Transform* tf = mapbl_obj_dooru->GetComponent<Transform>();
			tf->SetPos(Vector2{ 1180l ,530l });
			SpriteRenderer* render = mapbl_obj_dooru->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_dooru->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_u.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mapbl_obj_dooru, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> mapbl_redbuildr = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			mapbl_redbuildr->SetName(L"MapBL_RedBulid_R");
			
			Transform* tf = mapbl_redbuildr->GetComponent<Transform>();
			tf->SetPos(Vector2{1710l,850l });
			SpriteRenderer* render = mapbl_redbuildr->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_redbuildr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_top_cornerBuilding01.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
			AddGameObject(mapbl_redbuildr, ELayerType::FrontObject);
		}
		std::shared_ptr<GameObject> mapbl_buliding = core::ObjectPool<Animator>::Spawn();
		_parent->AddChild(mapbl_buliding);
		{
			mapbl_buliding->SetName(L"MapBL_Bulidings");
			
			Transform* tf = mapbl_buliding->GetComponent<Transform>();
			tf->SetOffset(Vector2{1020l,800l });
			Animator* ani = mapbl_buliding->AddComponent<Animator>();
			std::wstring key = ani->CreateAnimations(L"..\\Resources\\MapObject\\World3\\Bottom\\Left\\YBuliding", Vector2::Zero, 0.5f);
			ani->Play(key, true);
			mapbl_buliding->SetName(key);
			AddGameObject(mapbl_buliding, ELayerType::BackObject);
		}

	}
	void  PlayMapScene::CreateMapBR(GameObject* _original_pos)
	{

	}
	void PlayMapScene::CreateMapTL(GameObject* _original_pos)
	{

	}
	void PlayMapScene::CreateMapTR(GameObject* _original_pos)
	{

	}

}