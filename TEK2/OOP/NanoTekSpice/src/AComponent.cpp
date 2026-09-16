/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"
#include "Link.hpp"
#include "exceptions/InvalidPinException.hpp"
#include "exceptions/InputAlreadyTakenException.hpp"

/**
 * @file AComponent.cpp
 * @brief Base class and link management for all components.
 *
 * AComponent provides:
 * - Pin validation (checkPin)
 * - Input/output mapping
 * - Link creation between components (setLink, getLink)
 * - Tristate operator overloads (&&, ||, ^, !)
 *
 * Classes:
 * - AComponent : Base component functionality.
 * - Link : Encapsulates a connection between two components.
 *
 * Behavior:
 * - simulate() is virtual and may be overridden.
 * - getLink returns the value of the connected component’s pin.
 */

namespace nts
{
    Link::Link(IComponent& component, std::size_t pin): _other(component), _otherPin(pin) {}

    size_t Link::getOtherPin()
    {
        return _otherPin;
    }

    IComponent& Link::getOther()
    {
        return _other;
    }

    void AComponent::simulate(std::size_t)
    {
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent& other, std::size_t otherPin)
    {
        checkPin(*this, pin);
        AComponent* otherAComp = dynamic_cast<AComponent*>(&other);
        checkPin(*otherAComp, otherPin);
        _links[pin] = std::make_unique<Link>(other, otherPin);
    }

    nts::Tristate AComponent::getLink(std::size_t pin)
    {
        auto it = _links.find(pin);

        if (it == _links.end())
            return nts::Undefined;
        return it->second->getOther().compute(it->second->getOtherPin());
    }

    void AComponent::checkPin(AComponent& component, size_t pin)
    {
        auto itInput = component._inputs.find(pin);
        auto itOutput = component._outputs.find(pin);

        if (itInput == component._inputs.end() && itOutput == component._outputs.end())
            throw InvalidPinException(std::to_string(pin));
    }

    std::map<std::size_t, bool> AComponent::getInputs(void)
    {
        return _inputs;
    }
    
    void AComponent::resetInputs(void)
    {
        for (auto it = _inputs.begin(); it != _inputs.end(); it++) {
            it->second = false;
        }
    }

    Tristate operator &&(Tristate first, Tristate second)
    {
        if (first == nts::True && second == True) {
            return True;
        } else if (first == nts::False || second == nts::False)
            return nts::False;
        return nts::Undefined;
    }

    Tristate operator ||(Tristate first, Tristate second)
    {
        if (first == True || second == True)
            return True;
        else if (first == False && second == False)
            return False;
        return Undefined;
    }

    Tristate operator ^(Tristate first, Tristate second)
    {
        if ((first == True && second == False) || (first == False && second == True))
            return True;
        else if ((first == False && second == False) || (first == True && second == True))
            return False;
        return Undefined;
    }

    Tristate operator !(Tristate element)
    {
        if (element == True)
            return False;
        if (element == False)
            return True;
        return Undefined;
    }
}