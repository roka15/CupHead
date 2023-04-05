#pragma once

enum class ESceneType
{
	NONE,
	Title,
	MainMenu,
	PlayMap,
	BossMedusa,
	BossDevil,
	Ending,
	MAX,
};
enum class  ELayerType
{
	NONE,
	BackObject,
	Ground,
	Monster,
	Player,
	Bullet,
	FrontObject,
	Effect,
	UI,
	MAX,
};
enum class EGameObjectType
{
	NONE,
	MAX,
};
enum class EComponentType
{
	NONE,
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	Script,
	Rigidbody,
	MAX,
};
enum class ERenderType
{
	BitBlt,
	TransParentBlt,
	StretchBlt,
};
enum class EPlayerType
{
	Cuphead,
	MugMan,
	MsChalice,
	MAX
};
enum class EWindowType
{
	MainMenu,
	Options,
	MAX

};
enum class EDirType
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};
enum class EStateType
{
	START,
	ING,
	NOTHING,
};