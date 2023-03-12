#pragma once
#include "Scene.h"
namespace yeram_client
{
	class PlayMapScene:public Scene
	{public:
		PlayMapScene();
		~PlayMapScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;
	private:
		void CreateWorldMap(const Vector2& _startpos);
		
		const Vector2& CreateWroldGround(const std::wstring _name, const Vector2& _pos, GameObject* _parent, ELayerType _type,const std::wstring _image_path);
		void  CreateMapBL(const Vector2& _original_pos);
		void  CreateMapBR(const Vector2& _original_pos);
		void CreateMapTL(const Vector2& _original_pos);
		void CreateMapTR(const Vector2& _original_pos);
	};
}


