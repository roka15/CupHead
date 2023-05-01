#pragma once
namespace yeram_client
{
	class SkillInfo
	{
	public:
		SkillInfo();
		SkillInfo(double _cooltime, double _usetime);
		virtual ~SkillInfo();
		double GetUseTime() { return mUseTime; }
		void SetUseTime(double _usetime) { mUseTime = _usetime; }
		double GetCoolTime() { return mSkillCoolTime; }
	private:
		double mSkillCoolTime;
		double mUseTime;
	};

}

