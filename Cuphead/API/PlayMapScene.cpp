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

		CreateWorldMap(pos);

		Scene::Initialize();
	}
	void PlayMapScene::Update()
	{
		//test
		if (core::Input::GetKeyDown(core::EKeyCode::MouseRight))
		{
			SceneManager::LoadScene(ESceneType::BossMedusa);
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
		GameObject* player = mLayers[(UINT)ELayerType::Player]->FindObject(L"Player");
		Camera::SetTarget(player);
		Scene::OnEnter();
	}
	void PlayMapScene::OnExit()
	{
		Camera::SetTarget(nullptr);
		Scene::OnExit();
	}
	void PlayMapScene::CreateWorldMap(const Vector2& _startpos)
	{
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
		const Vector2& map_bl = CreateWroldGround(L"MapBL", _startpos, nullptr, ELayerType::BackObject,
												  L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03.bmp");
		const Vector2& map_br = CreateWroldGround(L"MapBR", Vector2{ _startpos.x+1874.0f ,_startpos.y}, nullptr, ELayerType::BackObject,
			                                      L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Right\\world3_mainland_04.bmp");
		const Vector2& map_tl = CreateWroldGround(L"MapTL", Vector2{ _startpos.x-154.0f,_startpos.y-1477.0f }, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Top\\Left\\world3_mainland_01.bmp");
		const Vector2& map_tr = CreateWroldGround(L"MapTR", Vector2{ map_br.x,map_br.y - 1439.0f }, nullptr, ELayerType::BackObject,
			L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Top\\Right\\world3_mainland_02.bmp");

		CreateMapBL(map_bl);
		CreateMapBR(map_br);
		CreateMapTL(map_tl);
		CreateMapTR(map_tr);
	}
	const Vector2& PlayMapScene::CreateWroldGround(const std::wstring _name, const Vector2& _pos, GameObject* _parent, ELayerType _type, const std::wstring _image_path)
	{
		Rectangle* map = GameObject::Instantiate<Rectangle>(_name, _pos, _parent, _type);
		{
			SpriteRenderer* render = map->AddComponent<SpriteRenderer>();
			render->SetImage(map->GetName().c_str()
				, _image_path);
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		
		return map->GetComponent<Transform>()->GetPos();
	}
	void  PlayMapScene::CreateMapBL(const Vector2& _original_pos)
	{
		Rectangle* mapbl_obj_doorl = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_L", Vector2{ _original_pos.x + 377l,_original_pos.y + 79l }, nullptr, ELayerType::BackObject);
		{
			SpriteRenderer* render = mapbl_obj_doorl->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorl->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_bl.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_obj_doorr = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_R", Vector2{ _original_pos.x + 377l,_original_pos.y + 79l }, nullptr, ELayerType::FrontObject);
		{
			SpriteRenderer* render = mapbl_obj_doorr->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_doorr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_br.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_obj_dooru = GameObject::Instantiate<Rectangle>(L"MapBL_Door1_U", Vector2{ _original_pos.x + 377l,_original_pos.y + 79l }, nullptr, ELayerType::FrontObject);
		{
			SpriteRenderer* render = mapbl_obj_dooru->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_obj_dooru->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_03_obj1_u.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_redbuildr = GameObject::Instantiate<Rectangle>(L"MapBL_RedBulid_R", Vector2{ _original_pos.x + 910l,_original_pos.y + 400l }, nullptr, ELayerType::FrontObject);
		{
			SpriteRenderer* render = mapbl_redbuildr->AddComponent<SpriteRenderer>();
			render->SetImage(mapbl_redbuildr->GetName().c_str()
				, L"..\\Resources\\Worldmap\\Inkwell Isle III\\Main Land\\Bottom\\Left\\world3_mainland_top_cornerBuilding01.bmp");
			render->SetRenderType(ERenderType::TransParentBlt);
		}
		Rectangle* mapbl_buliding = GameObject::Instantiate<Rectangle>(L"MapBL_Bulidings", Vector2{ _original_pos.x + 1020l,_original_pos.y + 800l }, nullptr, ELayerType::BackObject);
		{
			Animator* ani = mapbl_buliding->AddComponent<Animator>();
			std::wstring key = ani->CreateAnimations(L"..\\Resources\\MapObject\\World3\\Bottom\\Left\\YBuliding", Vector2::Zero, 0.5f);
			ani->Play(key, true);
			mapbl_buliding->SetName(key);
		}
		
	}
	void  PlayMapScene::CreateMapBR(const Vector2& _original_pos)
	{
		
	}
	void PlayMapScene::CreateMapTL(const Vector2& _original_pos)
	{
		
	}
	void PlayMapScene::CreateMapTR(const Vector2& _original_pos)
	{
		
	}
}