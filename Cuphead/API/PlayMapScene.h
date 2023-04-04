#pragma once
#include "Scene.h"
namespace yeram_client
{
	class Rectangle;
	class PlayMapScene :public Scene
	{
	public:
		PlayMapScene();
		PlayMapScene(std::wstring _name);
		~PlayMapScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

	private:
		void CreateWorldMap(const Vector2& _startpos);

		GameObject* CreateWroldGround(const std::wstring _name, const Vector2& _pos, GameObject* _parent, ELayerType _type, const std::wstring _image_path);
		void  CreateMapBL(GameObject* _parent);
		void  CreateMapBR(GameObject* _original_pos);
		void CreateMapTL(GameObject* _original_pos);
		void CreateMapTR(GameObject* _original_pos);

		
	private:
	
	};
}


