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
		//main thread에서 fade out 실행이 완료되면 event를 킨다.
		//여기서 exit 와 enter 정보 셋팅
		EnterCriticalSection(&mCs);
		yeram_client::SceneManager::SetActivScene();
		//로드가 완료 되면 main thread에 알려주고 종료.
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
