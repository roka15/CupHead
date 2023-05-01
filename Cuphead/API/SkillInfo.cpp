#include "SkillInfo.h"

namespace yeram_client
{
	SkillInfo::SkillInfo():mSkillCoolTime(0.0),mUseTime(0.0)
	{
	}

	SkillInfo::SkillInfo(double _cooltime, double _usetime):mSkillCoolTime(_cooltime),mUseTime(_usetime)
	{
	}

	SkillInfo::~SkillInfo()
	{
	}
}
