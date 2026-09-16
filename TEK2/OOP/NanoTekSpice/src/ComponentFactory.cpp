/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ComponentFactory
*/

#include "ComponentFactory.hpp"
#include <stdexcept>
#include "components/special/InputComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/TrueComponent.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/elementary/AndComponent.hpp"
#include "components/elementary/OrComponent.hpp"
#include "components/elementary/XorComponent.hpp"
#include "components/elementary/NotComponent.hpp"
#include "components/gates/C4001.hpp"
#include "components/gates/C4011.hpp"
#include "components/gates/C4030.hpp"
#include "components/gates/C4069.hpp"
#include "components/gates/C4071.hpp"
#include "components/gates/C4081.hpp"
#include "components/gates/C4094.hpp"
#include "components/advanced/C4514.hpp"
#include "components/advanced/C4040.hpp"
#include "components/advanced/C4017.hpp"
#include "components/advanced/C4512.hpp"
#include "components/advanced/C4008.hpp"
#include "components/advanced/C4013.hpp"
#include "components/advanced/C2716.hpp"
#include "components/advanced/C4801.hpp"
#include "components/advanced/Logger.hpp"

/**
 * @file ComponentFactory.cpp
 * @brief Factory for creating components dynamically by type.
 *
 * ComponentFactory maintains a map of string keys to creator lambdas.
 * It supports all special, elementary, gate, and advanced components.
 *
 * Functions:
 * - createComponent(const std::string& type) : Return new component instance.
 *
 * Throws:
 * - std::runtime_error if component type is unknown.
 */

namespace nts {
    ComponentFactory::ComponentFactory()
    {
        _creators["input"] = []() { return std::make_unique<InputComponent>(); };
        _creators["output"] = []() { return std::make_unique<OutputComponent>(); };
        _creators["clock"] = []()  { return std::make_unique<ClockComponent>(); };
        _creators["true"] = []()  { return std::make_unique<TrueComponent>(); };
        _creators["false"] = []()  { return std::make_unique<FalseComponent>(); };
        _creators["and"] = []()  { return std::make_unique<AndComponent>(); };
        _creators["or"] = []()  { return std::make_unique<OrComponent>(); };
        _creators["xor"] = []()  { return std::make_unique<XorComponent>(); };
        _creators["not"] = []()  { return std::make_unique<NotComponent>(); };
        _creators["4001"] = []()  { return std::make_unique<C4001>(); };
        _creators["4011"] = []()  { return std::make_unique<C4011>(); };
        _creators["4030"] = []()  { return std::make_unique<C4030>(); };
        _creators["4069"] = []()  { return std::make_unique<C4069>(); };
        _creators["4071"] = []()  { return std::make_unique<C4071>(); };
        _creators["4081"] = []()  { return std::make_unique<C4081>(); };
        _creators["4094"] = []()  { return std::make_unique<C4094>(); };
        _creators["4514"] = []()  { return std::make_unique<C4514>(); };
        _creators["4040"] = []()  { return std::make_unique<C4040>(); };
        _creators["4017"] = []()  { return std::make_unique<C4017>(); };
        _creators["4512"] = []()  { return std::make_unique<C4512>(); };
        _creators["4008"] = []()  { return std::make_unique<C4008>(); };
        _creators["4013"] = []()  { return std::make_unique<C4013>(); };
        _creators["2716"] = []()  { return std::make_unique<C2716>(); };
        _creators["4801"] = []()  { return std::make_unique<C4801>(); };
        _creators["logger"] = []() { return std::make_unique<Logger>(); };
    }

    std::unique_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &type)
    {
        auto it = _creators.find(type);
        if (it == _creators.end())
            throw std::runtime_error("Unknown component type: " + type);
        return it->second();
    }
}
