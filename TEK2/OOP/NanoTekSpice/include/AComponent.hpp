/*
** EPITECH PROJECT, 2026
** nts
** File description:
** AComponent
*/

#pragma once

/**
 * @file AComponent.hpp
 * @brief Defines AComponent, the abstract base for all concrete components,
 *        plus Tristate stream and logical operators.
 */

#include <memory>
#include <map>
#include <cstddef>
#include <ostream>
#include "IComponent.hpp"
#include "Link.hpp"

namespace nts
{
    class AComponent : public IComponent
    {
        private:
            /**
            * @brief Validates that @p pin is a declared input or output of @p component.
            *
            * @param component The component whose pin maps are checked.
            * @param pin       The pin index to validate.
            * @throws InvalidPinException if @p pin is absent from both _inputs and _outputs.
            */
            void checkPin(AComponent&, size_t);
        protected:
            /**
            * @brief Links established on this component, keyed by local pin index.
            *
            * Each Link points to a remote IComponent and a remote pin index.
            * Populated by setLink().
            */
            std::map<std::size_t, std::unique_ptr<Link>> _links;

            /**
            * @brief Declared input pins and their "consumed this tick" flags.
            *
            * Keys are valid input pin indices. The boolean is set to true once the pin
            * has been read during the current tick, and cleared by resetInputs() at the
            * end of each simulation step.
            */
            std::map<std::size_t, bool> _inputs;

            /**
            * @brief Cached Tristate results for each output pin, keyed by pin index.
            *
            * Derived classes write their computed values here inside compute() so that
            * repeated queries within the same tick do not re-evaluate logic.
            */
            std::map<std::size_t, Tristate> _results;

            /**
            * @brief Declared output pins and their gate-mapping information.
            *
            * Keys are valid output pin indices. The pair stores implementation-defined
            * indices used by the derived class to locate the gate and input position
            * associated with this output (e.g. gate index + input slot within that gate).
            */
            std::map<std::size_t, std::pair<std::size_t, std::size_t>> _outputs;
        public:
            AComponent() = default;
            ~AComponent() override = default;
            void simulate(std::size_t tick) override;
            virtual nts::Tristate compute(std::size_t pin) override = 0;
            void setLink(std::size_t pin, nts::IComponent& other, std::size_t otherPin) final;
            virtual nts::Tristate getLink(std::size_t pin) final;
            virtual std::map<std::size_t, bool> getInputs(void) final;
            virtual void resetInputs(void) final;
    };

    std::ostream &operator <<(std::ostream &s, Tristate v);
    Tristate operator &&(Tristate first, Tristate second);
    Tristate operator ||(Tristate first, Tristate second);
    Tristate operator ^(Tristate first, Tristate second);
    Tristate operator !(Tristate state);
}
