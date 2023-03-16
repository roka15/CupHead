#include "Input.h"
#include "Time.h"
namespace core
{

	std::vector<Input::Key> Input::mKeys;
	Input::PushInfo Input::mBeforPush;
	float Input::mTime;
	int ASCII[(UINT)EKeyCode::MAX] =
	{
		'A','S','D','W','K',VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN,VK_LBUTTON,VK_RBUTTON,VK_SPACE
	};
	
	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)EKeyCode::MAX; i++)
		{
			Key keyInfo;
			keyInfo.keycode = (EKeyCode)i;
			keyInfo.state = EKeyState::NONE;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}
	void Input::Update()
	{
		mTime += yeram_client::Time::DeltaTime();

		for (UINT i = 0; i < (UINT)EKeyCode::MAX; i++)
		{
			
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				//���� �ð��ӿ� �����־���.
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = EKeyState::Pressed;
				}
				else
				{
					mKeys[i].state = EKeyState::Down;
				}
				mKeys[i].bPressed = true;
			}
			else if (GetAsyncKeyState(ASCII[i]) & 0x8001)//hold
			{

			}
			else //���� �ȴ����ִ�.
			{
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = EKeyState::Up;
				}
				else
				{
					mKeys[i].state = EKeyState::NONE;
				}

				mKeys[i].bPressed = false;
			}
		}
	}
	void Input::Render(HDC _hdc)
	{
	}
	void Input::Release()
	{
	}
}