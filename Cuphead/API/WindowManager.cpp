#include "WindowManager.h"
#include "Application.h"
#include "UI.h"
#include "Rectangle.h"
#include "SpriteRenderer.h"
#include "Transform.h"
extern yeram_client::Application application;
namespace yeram_client
{
	std::map<EWindowType, GameObject*> WindowManager::mRegisterWindows;
	std::stack<std::pair<EWindowType, GameObject*>> WindowManager::mActiveWindow;
	int WindowManager::mCursorIndex;

	std::pair<EWindowType, GameObject*> WindowManager::FindUIGroup(EWindowType _group_key)
	{
		auto itr = mRegisterWindows.find(_group_key);
		if (itr == mRegisterWindows.end())
			return;
		else
			return std::make_pair(_group_key,itr->second);
	}
	void WindowManager::ActiveWindow(UINT _group_key)
	{
		std::pair<EWindowType,GameObject*> window = FindUIGroup((EWindowType)_group_key);
		window.second->SetActive(true);
		if (window.second != nullptr)
		{
			mActiveWindow.push(window);
		}

		mCursorIndex = 0;
	}
	EWindowType WindowManager::ActiveType()
	{
		return mActiveWindow.top().first;
	}
	void WindowManager::CursorDownEvent()
	{
		GameObject* window = mActiveWindow.top().second;
		UINT cnt = window->GetChildCount();
		if (cnt >= mCursorIndex)
			return;
		mCursorIndex++;
	}
	void WindowManager::CursorUpEvent()
	{
		if (0 >= mCursorIndex)
			return;
		mCursorIndex--;
	}
	void WindowManager::CursorClickEvent()
	{
		GameObject* window = mActiveWindow.top().second;
		UI* ui = dynamic_cast<UI*>(window->FindChild(mCursorIndex));
		if (ui == nullptr)
			return;
		ui->execute();
	}
	void WindowManager::InActiveWindow()
	{
		std::pair<EWindowType, GameObject*> window = mActiveWindow.top();
		window.second->SetActive(false);
		mActiveWindow.pop();
	}
	void WindowManager::Initialize()
	{
		CreateMainMenuWindow();
	}
	void WindowManager::Release()
	{
		for (auto window : mRegisterWindows)
		{
			window.second->Release();
			delete window.second;
			window.second = nullptr;
		}
	}
	WindowManager::WindowManager()
	{
	}
	WindowManager::~WindowManager()
	{
	}
	void WindowManager::CreateMainMenuWindow()
	{
		Vector2 size = application.GetWindowSize();
#pragma region main menu window
		Rectangle* rectangle = GameObject::Instantiate<Rectangle>(L"MenuBackGround", Vector2{ 0,0 }, nullptr, ELayerType::UI);
		{
			Transform* tf = rectangle->GetComponent<Transform>();
			tf->SetSize(Vector2{ (long)size.x,(long)size.y });

			SpriteRenderer* render = rectangle->AddComponent<SpriteRenderer>();
			render->SetImage(rectangle->GetName().c_str()
				, L"..\\Resources\\mainscreen.bmp");
			render->SetRenderType(ERenderType::StretchBlt);
			render->SetOwner(rectangle);
		}
		mRegisterWindows.insert(std::make_pair(EWindowType::MainMenu, rectangle));


		UI* start_btn = GameObject::Instantiate<UI>(L"MenuStartBTNT", Vector2{ 100,300 }, rectangle);
		{
			Transform* tf = start_btn->GetComponent<Transform>();
			tf->SetSize(Vector2{ 400,400 });
			start_btn->SetImage(start_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Start\\Start.bmp");
			SpriteRenderer* render = start_btn->GetComponent<SpriteRenderer>();
			render->SetRenderType(ERenderType::TransParentBlt);
			
			//start_btn->SetClickEvent(std::bind(&SceneManager::LoadScene,(UINT)ESceneType::PlayMap));
		}

		UI* end_btn = GameObject::Instantiate<UI>(L"MenuEndBTNT", Vector2{ 100,100 }, rectangle);
		{
			Transform* tf = start_btn->GetComponent<Transform>();
			tf->SetSize(Vector2{ 400,400 });
			start_btn->SetImage(start_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Exit\\Exit.bmp");
			SpriteRenderer* render = start_btn->GetComponent<SpriteRenderer>();
			render->SetRenderType(ERenderType::TransParentBlt);
		}

		UI* options_btn = GameObject::Instantiate<UI>(L"MenuOptionsBTNT", Vector2{ 100,500 }, rectangle);
		{
			Transform* tf = options_btn->GetComponent<Transform>();
			tf->SetSize(Vector2{ 400,400 });
			options_btn->SetImage(options_btn->GetName().c_str(), L"..\\Resources\\Menu_Screen\\Options\\Options.bmp");
			SpriteRenderer* render = options_btn->GetComponent<SpriteRenderer>();
			render->SetRenderType(ERenderType::TransParentBlt);
			//start_btn->SetClickEvent(std::bind(& WindowManager::ActiveWindow,(UINT)EWindowType::Options));
		}

		rectangle->AddChild(start_btn);
		rectangle->AddChild(end_btn);
		rectangle->AddChild(options_btn);
#pragma endregion
	}
}

