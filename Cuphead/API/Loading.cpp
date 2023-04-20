#include "Loading.h"
#include "SceneManager.h"
#include "Scene.h"

bool core::Loading::mbStop;
CRITICAL_SECTION core::Loading::mCs;
HANDLE core::Loading::mEvent;
bool core::Loading::mbLoading;

void core::Loading::Initialize()
{
	mEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&mCs);
}
DWORD __stdcall core::Loading::LoadingFunc(PVOID _Param)
{
	while (mbStop==false)
	{
		WaitForSingleObject(mEvent, INFINITE);
		mbLoading = true;
		//main thread���� fade out ������ �Ϸ�Ǹ� event�� Ų��.
		//���⼭ exit �� enter ���� ����
		EnterCriticalSection(&mCs);
		yeram_client::SceneManager::SetActivScene();
		//�ε尡 �Ϸ� �Ǹ� main thread�� �˷��ְ� ����.
		yeram_client::SceneManager::LoadingComplete();
		LeaveCriticalSection(&mCs);
		WaitForSingleObject(mEvent, INFINITE);
		mbLoading = false;
	}
	return 0;
}

void core::Loading::Release()
{
	mbStop = true;
	DeleteCriticalSection(&mCs);
}
