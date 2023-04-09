#pragma once

enum class ESceneType
{
	NONE,
	Title,
	MainMenu,
	PlayMap,
	BossMedusa,
	Tutorial,
    MoveWorldIntro,
	InWorldIntro,
	Ending,
	MAX,
};
enum class  ELayerType
{
	NONE,
	BackObject,
	BackColObject,
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
	Rigidbody,
	Script,
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
	STAY=1,
	LEFT=2,
	RIGHT=4,
	UP=8,
	DOWN=16,
	SIT=32,
	RUN=64,
	MAX
};
enum class EStateType
{
	START,
	ING,
	NOTHING,
};