#include "PlayMapScene.h"
#include "Player.h"
#include "Rectangle.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Application.h"
#include "Camera.h"
#include "Layer.h"
#include "Animator.h"
#include "Input.h"
#include "Time.h"
#include "ObjectPool.h"
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
		mLayers[(UINT)ELayerType::FrontObject] = new Layer();
		//OnEnter();

	}
	void PlayMapScene::Update()
	{

		if (core::Input::GetKeyDown(core::EKeyCode::MouseRight))
		{
			SceneManager::LoadScene(ESceneType::BossMedusa);
			SceneManager::OpenLodingScreen();
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
		Vector2 pos = application.GetWindowSize() / 2.0f;
		GameObject* player_obj = mLayers[(UINT)ELayerType::Player]->FindObject(L"Player").get();
		if (player_obj != nullptr)
		{
			player_obj->SetActive(true);
			Camera::SetTarget(player_obj);
			Player* player = player_obj->GetComponent<Player>();
			player->ChangeCharacter(EPlayerType::Cuphead);
			Transform* tf = player_obj->GetComponent<Transform>();
			tf->SetPos(Vector2{ pos.x,pos.y });
		}

		CreateWorldMap(pos);
		//Camera::PlayLoad();
		Scene::OnEnter();
	}
	void PlayMapScene::OnExit()
	{
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
			ocean->SetName(L"MapBackGround");
			AddGameObject(ocean, ELayerType::BackObject);

			Transform* tf = ocean->GetComponent<Transform>();
			tf->SetSize(Vector2{ (long)size.x,(long)size.y + 200l });

			SpriteRenderer* render = ocean->GetComponent<SpriteRenderer>();
			render->SetImage(ocean->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Ocean\\Bottom\\Left\\world3_water_04.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
		}
		GameObject* bl_parent = CreateWroldGround(L"MapBL", _startpos, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03.bmp");
		GameObject* br_parent = CreateWroldGround(L"MapBR", Vector2{ _startpos.x + 1874.0f ,_startpos.y }, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Right\\world3_mainland_04.bmp");
		GameObject* tl_parent = CreateWroldGround(L"MapTL", Vector2{ _startpos.x - 154.0f,_startpos.y - 1477.0f }, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Top\\Left\\world3_mainland_01.bmp");
		GameObject* tr_parent = CreateWroldGround(L"MapTR", Vector2{ _startpos.x + 1874.0f,_startpos.y - 1440.0f }, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Top\\Right\\world3_mainland_02.bmp");

		CreateMapBL(bl_parent);
		CreateMapBR(br_parent);
		CreateMapTL(tl_parent);
		CreateMapTR(tr_parent);

		/*std::shared_ptr<GameObject> map = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			map->SetName(L"MapBL");
			AddGameObject(map, ELayerType::BackObject);
			Transform* tf = map->GetComponent<Transform>();
			tf->SetPos(_startpos);
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}

		std::shared_ptr<GameObject> mapbl_obj_doorl = core::ObjectPool<SpriteRenderer>::Spawn();
		map->AddChild(mapbl_obj_doorl);
		{
			mapbl_obj_doorl->SetName(L"MapBL_Door1_L");
			AddGameObject(mapbl_obj_doorl, ELayerType::BackObject);
			Transform* tf = mapbl_obj_doorl->GetComponent<Transform>();
			tf->SetOffset(Vector2{380.0f,73.0f});
			SpriteRenderer* render = mapbl_obj_doorl->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorl->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_bl.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}*/

	}
	GameObject* PlayMapScene::CreateWroldGround(const std::wstring _name, const Vector2& _pos, GameObject* _parent, ELayerType _type, const std::wstring _image_path)
	{
		std::shared_ptr<GameObject> map = core::ObjectPool<SpriteRenderer>::Spawn();
		{
			map->SetName(_name);
			map->SetParent(_parent);
			AddGameObject(map, _type);
			Transform* tf = map->GetComponent<Transform>();
			tf->SetPos(_pos);
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, _image_path);
			render->SetRenderType(ERenderType::TransParentBlt);
		}

		return map.get();
	}
	void  PlayMapScene::CreateMapBL(GameObject* _parent)
	{
		std::shared_ptr<GameObject> mapbl_obj_doorl = core::ObjectPool<SpriteRenderer>::Spawn();
		_parent->AddChild(mapbl_obj_doorl);
		{
			mapbl_obj_doorl->SetName(L"MapBL_Door1_L");
			AddGameObject(mapbl_obj_doorl, ELayerType::BackObject);
			Transform* tf = mapbl_obj_doorl->GetComponent<Transform>();
			tf->SetOffset(Vector2{ 380.0f,73.0f });
			SpriteRenderer* render = mapbl_obj_doorl->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorl->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_bl.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		std::shared_ptr<GameObject> mapbl_obj_doorr = core::ObjectPool<SpriteRenderer>::Spawn();
		_parent->AddChild(mapbl_obj_doorr);
		{
			mapbl_obj_doorr->SetName(L"MapBL_Door1_R");
			AddGameObject(mapbl_obj_doorr, ELayerType::FrontObject);
			Transform* tf = mapbl_obj_doorr->GetComponent<Transform>();
			tf->SetOffset(Vector2{380.0f,69.0f});
			SpriteRenderer* render = mapbl_obj_doorr->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_br.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		std::shared_ptr<GameObject> mapbl_obj_dooru = core::ObjectPool<SpriteRenderer>::Spawn();
		_parent->AddChild(mapbl_obj_dooru);
		{
			mapbl_obj_dooru->SetName(L"MapBL_Door1_U");
			AddGameObject(mapbl_obj_dooru, ELayerType::FrontObject);
			Transform* tf = mapbl_obj_dooru->GetComponent<Transform>();
			tf->SetOffset(Vector2{380l,70l });
			SpriteRenderer* render = mapbl_obj_dooru->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_dooru->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_u.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		std::shared_ptr<GameObject> mapbl_redbuildr = core::ObjectPool<SpriteRenderer>::Spawn();
		_parent->AddChild(mapbl_redbuildr);
		{
			mapbl_redbuildr->SetName(L"MapBL_RedBulid_R");
			AddGameObject(mapbl_redbuildr, ELayerType::FrontObject);
			Transform* tf = mapbl_redbuildr->GetComponent<Transform>();
			tf->SetOffset(Vector2{910l,400l });
			SpriteRenderer* render = mapbl_redbuildr->GetComponent<SpriteRenderer>();
			render->SetImage(mapbl_redbuildr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_top_cornerBuilding01.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		std::shared_ptr<GameObject> mapbl_buliding = core::ObjectPool<Animator>::Spawn();
		_parent->AddChild(mapbl_buliding);
		{
			mapbl_buliding->SetName(L"MapBL_Bulidings");
			AddGameObject(mapbl_buliding, ELayerType::BackObject);
			Transform* tf = mapbl_buliding->GetComponent<Transform>();
			tf->SetOffset(Vector2{1020l,800l });
			Animator* ani = mapbl_buliding->AddComponent<Animator>();
			std::wstring key = ani->CreateAnimations(L"..\\Resources\\MapObject\\World3\\Bottom\\Left\\YBuliding", Vector2::Zero, 0.5f);
			ani->Play(key, true);
			mapbl_buliding->SetName(key);
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