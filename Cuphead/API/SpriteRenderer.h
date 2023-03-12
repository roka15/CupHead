#pragma once
#include "Component.h"
namespace yeram_client
{
	class Image;
	class SpriteRenderer :public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;
		void SetImage(const std::wstring& _filename,const std::wstring& _path);
		void SetRenderType(ERenderType _type)
		{
			mRenderType = _type;
		}
		const float& GetWidth(); 
		const float& GetHeight();
	private:
		Image* mImage;
		ERenderType mRenderType;
	};
}


