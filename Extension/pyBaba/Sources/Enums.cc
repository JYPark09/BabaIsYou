// Copyright(C) 2019 Junyeong Park

#include <pyBaba/Enums.h>

#include <Baba/Enums/Action.h>
#include <Baba/Enums/Game.h>
#include <Baba/Enums/ObjectType.h>

namespace py = pybind11;
using namespace Baba;

void buildActionEnum(py::module& m)
{
    py::enum_<Action>(m, "Action")
        .value("UP", Action::UP)
        .value("DOWN", Action::DOWN)
        .value("LEFT", Action::LEFT)
        .value("RIGHT", Action::RIGHT)
        .value("STAY", Action::STAY)
        .value("COUNT", Action::COUNT)
        .export_values();
}

void buildGameEnum(py::module& m)
{
    py::enum_<GameStep>(m, "GameStep")
        .value("INVALID", GameStep::INVALID)
        .value("START_BEGIN", GameStep::START_BEGIN)
        .value("START_LOAD_MAP", GameStep::START_LOAD_MAP)
        .value("MAIN_INIT", GameStep::MAIN_INIT)
        .value("MAIN_PARSE_RULES", GameStep::MAIN_PARSE_RULES)
        .value("MAIN_APPLY_RULES", GameStep::MAIN_APPLY_RULES)
        .value("MAIN_DETERMINE_RESULT", GameStep::MAIN_DETERMINE_RESULT)
        .value("MAIN_WAIT_ACTION", GameStep::MAIN_WAIT_ACTION)
        .value("MAIN_DO_ACTION", GameStep::MAIN_DO_ACTION)
        .value("END_WIN", GameStep::END_WIN)
        .value("END_DEFEAT", GameStep::END_DEFEAT)
        .value("COUNT", GameStep::COUNT)
        .export_values();

    py::enum_<GameResult>(m, "GameResult")
        .value("INVALID", GameResult::INVALID)
        .value("WIN", GameResult::WIN)
        .value("DEFEAT", GameResult::DEFEAT)
        .value("COUNT", GameResult::COUNT)
        .export_values();
}

void buildObjectTypeEnum(py::module& m)
{
#define X(a) .value(#a, ObjectType::a)
    py::enum_<ObjectType>(m, "ObjectType")
        .value("INVALID", ObjectType::INVALID)
        .value("OBJECT_TYPE", ObjectType::OBJECT_TYPE)
#include <Baba/Enums/ObjectType.def>
        .value("VERB_TYPE", ObjectType::VERB_TYPE)
#include <Baba/Enums/VerbType.def>
        .value("TEXT_TYPE", ObjectType::TEXT_TYPE)
#include <Baba/Enums/TextType.def>
        .value("PROP_TYPE", ObjectType::PROP_TYPE)
#include <Baba/Enums/PropertyType.def>
        .value("COUNT", ObjectType::COUNT)
        .export_values();
#undef X
}

void buildVerbTypeEnum(py::module& m)
{
#define X(a) .value(#a, VerbType::a)
    py::enum_<VerbType>(m, "VerbType")
        .value("INVALID", VerbType::INVALID)
#include <Baba/Enums/VerbType.def>
        .value("COUNT", VerbType::COUNT)
        .export_values();
#undef X
}

void buildPropertyTypeEnum(py::module& m)
{
#define X(a) .value(#a, PropertyType::a)
    py::enum_<PropertyType>(m, "PropertyType")
        .value("INVALID", PropertyType::INVALID)
#include <Baba/Enums/PropertyType.def>
        .value("COUNT", PropertyType::COUNT)
        .export_values();
#undef X
}

void buildTypeUtilities(py::module& m)
{
    m.def("ObjectToProperty", ObjectToProperty);
    m.def("PropertyToObject", PropertyToObject);
}
