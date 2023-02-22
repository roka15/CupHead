#pragma once

enum class ESceneType
{
	NONE,
	Title,
	Play,
	Ending,
	MAX,
};
enum class  ELayerType
{
	NONE,
	BG,
	Monster,
	Player,
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
	MAX,
};
