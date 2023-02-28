#pragma once
<<<<<<< HEAD
#include "Entity.h"
#include "Image.h"
class Image;
class Animator;
namespace yeram_client
{
	class Animation:public Entity
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
		void Create(Image* _sheet,Vector2 _leftTop,UINT _col, UINT _row,UINT _size,Vector2 _offset,float _duration);
		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* _animator) { mAnimator = _animator; }
	private:
		Image* mSheet;
		std::vector<Sprite> mSpriteSheet;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
		Animator* mAnimator;
	};
=======

namespace yeram_client
{
	class Animation
	{

	private:
		float mTime;
		int mIdx;
	};

>>>>>>> 85c5f662ccfb749ecd2ef53254f5677e801cc315
}

