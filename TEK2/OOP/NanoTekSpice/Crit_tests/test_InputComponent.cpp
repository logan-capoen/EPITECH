/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_input.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/special/InputComponent.hpp"

Test(input_component, constructor_display_is_undefined)
{
    nts::InputComponent input;
    cr_assert_eq(input.displayValue(), 'U');
}

Test(input_component, constructor_compute_returns_undefined)
{
    nts::InputComponent input;
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
}

Test(input_component, set_value_not_applied_before_simulate)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    cr_assert_eq(input.displayValue(), 'U');
}

Test(input_component, set_value_true_applied_after_simulate)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '1');
}

Test(input_component, set_value_false_applied_after_simulate)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '0');
}

Test(input_component, set_value_undefined_applied_after_simulate)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    input.setValue(nts::Tristate::Undefined);
    input.simulate(2);
    cr_assert_eq(input.displayValue(), 'U');
}

Test(input_component, set_value_called_twice_last_wins)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '1');
}

Test(input_component, simulate_no_throw)
{
    nts::InputComponent input;
    cr_assert_no_throw(input.simulate(1), std::exception);
}

Test(input_component, simulate_propagates_value)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
}

Test(input_component, simulate_keeps_last_value_if_not_changed)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.simulate(1);
    input.simulate(2);
    cr_assert_eq(input.displayValue(), '0');
}

Test(input_component, simulate_updates_on_value_change)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '0');
    input.setValue(nts::Tristate::True);
    input.simulate(2);
    cr_assert_eq(input.displayValue(), '1');
}

Test(input_component, compute_returns_true_after_set_true)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
}

Test(input_component, compute_returns_false_after_set_false)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::False);
}

Test(input_component, compute_does_not_alter_display_value)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    input.compute(1);
    cr_assert_eq(input.displayValue(), '1');
}

Test(input_component, compute_consistent_across_pins)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.compute(1), input.compute(2));
}

Test(input_component, display_value_returns_1_when_true)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::True);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '1');
}

Test(input_component, display_value_returns_0_when_false)
{
    nts::InputComponent input;
    input.setValue(nts::Tristate::False);
    input.simulate(1);
    cr_assert_eq(input.displayValue(), '0');
}

Test(input_component, display_value_returns_U_when_undefined)
{
    nts::InputComponent input;
    cr_assert_eq(input.displayValue(), 'U');
}