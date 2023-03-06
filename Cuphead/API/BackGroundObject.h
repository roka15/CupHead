#pragma once
#include "GameObject.h"
namespace yeram_client
{
	class BackGroundObject : public GameObject
	{
	public:
		BackGroundObject();
		BackGroundObject(const std::wstring& _obj_name,const std::wstring& _image_path, ERenderType _type, Vector2 _pos, Vector2 _size);
		virtual ~BackGroundObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

	private:
		void SetImage(Image* _image)
		{
			//mSheet = _image;
		}
		
		void SetTransform(Vector2 _pos, Vector2 _size);
	
		
	};

}

