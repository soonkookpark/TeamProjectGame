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

    // 해시 함수 정의
    struct KeyHash {
        std::size_t operator()(const Keys& k) const {
            // 해시 함수 구현 예시: 각 필드의 해시 값을 조합해서 반환
            return std::hash<std::string>{}(k.usingClass) ^
                std::hash<std::string>{}(k.skillName) ^
                std::hash<int>{}(k.skillLevel);
        }
    };

    // 동등성 비교 함수 정의
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
        std::string skillImage; // 불러오는 방식
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



//찾아라 비밀의열쇠
//스킬 사용자
//스킬 순번
//스킬 종류
//스킬 레벨