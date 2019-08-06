// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(ObjectType target, std::string_view verb, EffectType effect, int ruleID)
    : target(target), verb(verb), effect(effect), ruleID(ruleID)
{
    // Do nothing
}
}  // namespace Baba