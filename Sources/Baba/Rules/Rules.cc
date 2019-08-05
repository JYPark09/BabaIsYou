// Copyright(c) 2019 Junyeong Park

#include <Baba/Rules/Rules.h>

namespace Baba
{
GameRules& GameRules::GetInstance()
{
    static GameRules instance;
    return instance;
}

const int GameRules::AddBaseRule(std::string_view target, std::string_view verb, std::string_view effect)
{
    rules_.emplace_back(target, verb, effect, ruleCount);
    ++ruleCount;
}

void GameRules::DeleteRule(const int& ruleID)
{
    for (auto i = rules_.begin(); i != rules_.end(); ++i)
    {
        if (i->ruleID_ == ruleID)
        {
            i = rules_.erase(i);
        }
        else
        {
            ++i;
        }
    }
}
}  // namespace Baba