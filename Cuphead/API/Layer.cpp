#include "Layer.h"
namespace yeram_client
{
	Layer::Layer()
	{
		mbActive = true;
	}
	Layer::~Layer()
	{

	}
	void Layer::Initialize()
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetActive() == false)
				continue;
			obj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetActive() == false)
				continue;
			obj->Render(hdc);
		}
	}
	void Layer::Release()
	{
		for (GameObject* obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			obj->Release();
			delete obj;
			obj = nullptr;
		}
	}
	GameObject* Layer::FindObject(std::wstring _name)
	{
		for (auto obj : mObjs)
		{
			if (obj->GetName() == _name)
				return obj;
		}
		return nullptr;
	}
	std::vector<GameObject*>& Layer::GetGameObjectList()
	{
		return mObjs;
	}
	void Layer::ChagePosGameObjects(const Vector2& _offset)
	{
		for (auto obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			size_t str_pos = obj->GetName().find(L"BackGround");
			if (str_pos == std::wstring::npos)
			{
				Transform* tf = obj->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				tf->CaluatePos(_offset);
			}
		}
	}
	void Layer::ChageScaleGameObjects(const Vector2& _scale)
	{
		for (auto obj : mObjs)
		{
			if (obj == nullptr)
				continue;
			size_t str_pos = obj->GetName().find(L"BackGround");
			if (str_pos == std::wstring::npos)
			{
				Transform* tf = obj->GetComponent<Transform>();
				Vector2 pos = tf->GetPos();
				//tf->SetScale(_scale);
				tf->CaluateSclae(_scale);
			}
		}
	}
	void Layer::AddGameObject(GameObject* obj)
	{
		mObjs.push_back(obj);
	}
}