#pragma once
#include "Entity.h"
#include "Image.h"

namespace yeram_client
{
	class Image;
	class Animator;
	class Animation :public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				:leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};
		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC _hdc);
		void Create(Image* _sheet, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration);
		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* _animator) { mAnimator = _animator; }
		void SetSpriteIndex(UINT _index) { mSpriteIndex = _index; }
		const Vector2& GetSpriteSize() { return mSpriteSheet[0].size; }
	private:
		Image* mSheet;
		std::vector<Sprite> mSpriteSheet;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
		Animator* mAnimator;
	};
}

