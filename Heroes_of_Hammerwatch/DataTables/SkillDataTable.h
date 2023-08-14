#pragma once
#include "DataTable.h"
#include "Skill.h"

class SkillDataTable : public DataTable

{
    struct Keys
    {
        std::string usingClass;
        std::string skillName;
        int skillLevel;

    };

    // �ؽ� �Լ� ����
    struct KeyHash {
        std::size_t operator()(const Keys& k) const {
            // �ؽ� �Լ� ���� ����: �� �ʵ��� �ؽ� ���� �����ؼ� ��ȯ
            return std::hash<std::string>{}(k.usingClass) ^
                std::hash<std::string>{}(k.skillName) ^
                std::hash<int>{}(k.skillLevel);
        }
    };

    // ��� �� �Լ� ����
    struct KeyEqual {
        bool operator()(const Keys& lhs, const Keys& rhs) const {
            return lhs.usingClass == rhs.usingClass &&
                lhs.skillName == rhs.skillName &&
                lhs.skillLevel == rhs.skillLevel;
        }
    };

    struct SkillInfo
    {
        std::string usingClass;
        std::string skillName;
        Skill::SKillType skillType;
        int skillLevel;
        int costMana;
        float skillCoolTime;
        std::string skillExplain;
        std::string skillImage; // �ҷ����� ���
        float chargeLength;
        int heal;
        float duration;
        int skillArcRange;
        int reduceMagicDamage;
        int reducePhysicsDamage;
        int rate;
        int stack;
    };
protected:
    std::unordered_map <Keys , SkillInfo, KeyHash, KeyEqual > sTables;
public:
    SkillDataTable();
    virtual bool Load() override;
    virtual void Release() override;

    SkillInfo& Get(std::string className, std::string skillNames, int level) { return sTables[{className, skillNames, level}]; };
};



//ã�ƶ� ����ǿ���
//��ų �����
//��ų ����
//��ų ����
//��ų ����