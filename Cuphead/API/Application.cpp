#include "Application.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"
namespace yeram_client
{
	Application::Application() :mHwnd(NULL), mhdc(NULL)
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize(HWND _hWnd)
	{
		mHwnd = _hWnd;
		mhdc = GetDC(mHwnd);
		mWidth = 1600;
		mHeight = 900;
		//��Ʈ�� �ػ� ������ ���� ���� ������ ũ�� ���.
		RECT rect = { 0,0,mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		//������ ũ�� ���� �� ��� ����
		SetWindowPos(mHwnd, nullptr,100, 50, 
			rect.right-rect.left,
			rect.bottom-rect.top, false);
		ShowWindow(mHwnd, true);


		//�����
		mBackBuffer=CreateCompatibleBitmap(mhdc,mWidth,mHeight);
		mBackHdc = CreateCompatibleDC(mhdc);
		HBITMAP default_Bitmap=(HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(default_Bitmap);


		core::Input::Initialize();
		SceneManager::Initalize();
		Time::Initailize();
	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{
		core::Input::Update();
		SceneManager::Update();
		Time::Update();
	}
	void Application::Render()
	{
		Rectangle(mBackHdc, -1, -1, 1602, 902);
		core::Input::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		Time::Render(mBackHdc);

		//����۸� ���� dc�� �Ѱ��ֱ�. SRCCOPY : ������ �״�� ����.
		BitBlt(mhdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
	void Application::Release()
	{
		core::Input::Release();
		SceneManager::Release();
		Time::Release();
	}
	HWND Application::GetHandle()
	{
		return mHwnd;
	}
}