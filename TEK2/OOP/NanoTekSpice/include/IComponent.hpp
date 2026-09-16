/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** IComponent.hpp
*/


#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

/**
 * @file IComponent.hpp
 * @brief Defines the IComponent interface and the Tristate enumeration.
*/

#include <cstddef>

namespace nts
{
    /**
    * @enum Tristate
    * @brief Represents a three-valued logic state used throughout the simulation.
    *
    * All signal values in NanoTekSpice are expressed as Tristate to correctly
    * model uninitialized or floating pins alongside definite logic levels.
    */
    enum Tristate {
        Undefined = -1,
        True = 1,
        False = 0
    };

    /**
    * @class IComponent
    * @brief Pure interface that every NanoTekSpice component must implement.
    *
    * IComponent defines the minimal contract required by the simulation engine:
    * advancing state on a tick, computing an output pin value, and accepting
    * pin-level links to other components.
    */
    class IComponent
    {
        public:
            /**
            * @brief Virtual destructor.
            */
            virtual ~IComponent() = default;

            
            /**
            * @brief Advances the component's internal state by one simulation tick.
            *
            * @param tick The current simulation tick counter.
            */
            virtual void simulate(std::size_t tick) = 0;

            /**
            * @brief Computes and returns the logical value present on the given output pin.
            *
            * @param pin The output pin index to evaluate.
            * @return The Tristate value on that pin (True, False, or Undefined).
            */
            virtual nts::Tristate compute(std::size_t pin) = 0;

            /**
            * @brief Establishes a link between a local pin and a pin on another component.
            *
            * @param pin      The local pin index to connect.
            * @param other    The remote component to link to.
            * @param otherPin The pin index on the remote component.
            */
            virtual void setLink(std::size_t pin, nts::IComponent& other, std::size_t otherPin) = 0;
    };
}

#endif