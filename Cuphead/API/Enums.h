#pragma once

enum class ESceneType
{
	NONE,
	Title,
	MainMenu,
	PlayMap,
	BossMedusa,
	Ending,
	MAX,
};
enum class  ELayerType
{
	NONE,
	BackObject,
	Monster,
	Player,
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
	Collider,
	SpriteRenderer,
	Animator,
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