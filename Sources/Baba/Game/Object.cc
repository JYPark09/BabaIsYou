// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Game/Object.h>

#include <algorithm>
#include <stdexcept>

namespace Baba
{
Object::Object()
{
    static int ObjectID = 0;

    objectID_ = ObjectID++;
}

int Object::GetID() const
{
    return objectID_;
}

Object& Object::SetType(ObjectType type)
{
    if (type == ObjectType::INVALID)
    {
        throw std::runtime_error("Invalid object type");
    }

    type_ = type;

    return *this;
}

ObjectType Object::GetType() const
{
    return type_;
}

Object& Object::SetEffectType(EffectType type)
{
    if (type == EffectType::INVALID)
    {
        throw std::runtime_error("Invalid effect type");
    }

    static std::vector wordClasses(
        {WordClass::NOUN, WordClass::VERB, WordClass::PROPERTY}); 
    static std::vector wordClassStrs(
        {NOUN_TYPE_STR, VERB_TYPE_STR, PROPERTY_TYPE_STR});

    auto& str = EFFECT_TYPE_STR[static_cast<std::size_t>(type)];

    for (std::size_t i = 0; i < wordClasses.size(); i++)
    {
        if (std::find(wordClassStrs[i].begin(), wordClassStrs[i].end(), str) != wordClassStrs[i].end())
        {
            wordClass_= wordClasses[i];
        }
    }

    effectType_ = type;

    return *this;
}

EffectType Object::GetEffectType() const
{
    return effectType_;
}

WordClass Object::GetWordClass() const
{
    return wordClass_;
}

Object& Object::SetEffect(EffectType effect, int ruleID)
{
    EffectsBitset bitset;
    bitset.set(static_cast<int>(effect));
    enchants_.emplace(ruleID, bitset);

    return *this;
}

Object& Object::SetEffects(const std::vector<EffectType>& effects)
{
    for (auto& effect : effects)
    {
        SetEffect(effect);
    }

    return *this;
}

const EffectsBitset Object::GetEffects() const
{
    EffectsBitset result;

    for (const auto& enchant : enchants_)
    {
        result |= enchant.second;
    }

    return result;
}

void Object::Destroy()
{
    if (isDestroyed_)
    {
        throw std::runtime_error("Already destroyed object");
    }

    isDestroyed_ = true;
}

bool Object::IsDestroyed() const
{
    return isDestroyed_;
}

bool Object::operator==(const Object& other) const
{
    return (objectID_ == other.objectID_);
}

bool Object::operator!=(const Object& other) const
{
    return !(*this == other);
}
}  // namespace Baba
