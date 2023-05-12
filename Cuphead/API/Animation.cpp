#include "Animation.h"
#include "Animator.h"
#include "Image.h"
#include "Time.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Resources.h"
namespace yeram_client
{
	Animation::Animation()
		:mAnimator(nullptr),
		mTime(0.0f),
		mbComplete(false),
		mSpriteIndex(0)
	{
	}

	Animation::~Animation()
	{

	}

	void Animation::Initialize()
	{
	}

	void Animation::Update()
	{
		if (mbComplete == true)
			return;
		std::wstring str = this->mAnimator->GetOwner()->GetName();
		mTime += Time::DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mSpriteSheet.size() <= (mSpriteIndex + 1))
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex++;
			}
		}

		if (mbAlpha == true)
		{

		}
	}

	void Animation::Render(HDC _hdc)
	{
		Transform* tf = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 scale = tf->GetScale();
		Vector2 pos = tf->GetPos();
		pos = Camera::CaluatePos(pos);
		pos += mSpriteSheet[mSpriteIndex].offset;
		// �̹����� �׷��� ��ǥ�� ������Ʈ ��ǥ�� ���� �߰��� �׷�����.
	   // ĳ������ ���� �������� �������� ���
		pos.x -= mSpriteSheet[mSpriteIndex].size.x *scale.x/ 2.0f;
		pos.y -= mSpriteSheet[mSpriteIndex].size.y*scale.y;

		std::wstring str = this->mAnimator->GetOwner()->GetName();
		Image* image = Resources::Find<Image>(mImageKey);
		CreateImage(image);

		if (mbAlpha == false)
		{
			TransparentBlt(_hdc, pos.x, pos.y,
				mSpriteSheet[mSpriteIndex].size.x * scale.x,
				mSpriteSheet[mSpriteIndex].size.y * scale.y,
				image->GetHDC(), mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
				, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
				(RGB(255, 0, 255)));
		}
		else
		{
			//���귮 ����
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255; // 0(����)~255(������) ���İ�
			
			AlphaBlend(_hdc, pos.x, pos.y,
				mSpriteSheet[mSpriteIndex].size.x * scale.x,
				mSpriteSheet[mSpriteIndex].size.y * scale.y,
				image->GetHDC(), mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y,
				mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
				func);
		}


	}

	void Animation::Create(const std::wstring& _key, Vector2 _leftTop, UINT _col, UINT _row, UINT _size, Vector2 _offset, float _duration, const std::vector<Vector2> _origin_size, bool _alpha)
	{
		mImageKey =_key;
		Image* find_image = Resources::Find<Image>(mImageKey);
		CreateImage(find_image);
		mbAlpha = _alpha;
		Vector2 size = Vector2::One;
		size.x = find_image->GetWidth() / (float)_col;
		size.y = find_image->GetHeight() / (float)_row;

		mOriginSize = _origin_size;

		for (size_t i = 0; i < _size; i++)
		{
			Sprite sprite_info;
			sprite_info.leftTop.x = _leftTop.x + (size.x * i);
			sprite_info.leftTop.y = _leftTop.y;
			sprite_info.size = size;
			sprite_info.offset = _offset;
			sprite_info.duration = _duration;

			mSpriteSheet.push_back(sprite_info);
		}
	}

	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}


	void Animation::Stop()
	{
		mbComplete = true;
	}

	void Animation::CreateImage(Image*& _image)
	{
		//image�� ������ �ʾ� ���� �ƴµ� ����� ���� ��û�� ���� ��� �����ϵ��� ��.
	
		if (_image == nullptr)
		{
			std::wstring animationName = GetName();
			if (mAnimator->FindPubAnimation(GetName()) == true)
			{
				Animator::CreateAniInfo pubInfo = mAnimator->GetPubAnimation(GetName());
				std::wstring imageName = pubInfo.mImageKey;
				if (animationName.compare(imageName) != 0) // ���� sprite �� ���
				{
					_image = Resources::Load<Image>(imageName,pubInfo.mPath);
					Resources::Insert<Image>(imageName, _image);
					core::ResourceDeleterThread::RegisterResourceInfo(_image);
				}
				else // ���� �о�ͼ� spriteȭ ��Ű�� ���
				{
					mAnimator->CreateAnimations(pubInfo.mPath, pubInfo.mOffset, pubInfo.mDuration, pubInfo.mAlpha);
					_image = Resources::Find<Image>(pubInfo.mImageKey);
				}
			}
		}

	}

}
