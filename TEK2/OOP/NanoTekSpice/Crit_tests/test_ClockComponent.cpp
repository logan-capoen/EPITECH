/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** tests_clock.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/special/ClockComponent.hpp"

Test(clock, constructor_initial_display_is_undefined)
{
    nts::ClockComponent clock;
    cr_assert_eq(clock.displayValue(), 'U');
}

Test(clock, simulate_applies_set_value)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    cr_assert_no_throw(clock.simulate(1), std::exception);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, simulate_toggles_false_to_true)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    clock.simulate(2);
    cr_assert_eq(clock.displayValue(), '1');
}

Test(clock, simulate_toggles_true_to_false)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    clock.simulate(2);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, simulate_multiple_cycles)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '0');
    clock.simulate(2);
    cr_assert_eq(clock.displayValue(), '1');
    clock.simulate(3);
    cr_assert_eq(clock.displayValue(), '0');
    clock.simulate(4);
    cr_assert_eq(clock.displayValue(), '1');
}

Test(clock, simulate_undefined_stays_undefined)
{
    nts::ClockComponent clock;
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), 'U');
}

Test(clock, set_value_true_applied_after_simulate)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '1');
}

Test(clock, set_value_false_applied_after_simulate)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, set_value_overrides_toggle)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    clock.simulate(2);
    clock.setValue(nts::Tristate::False);
    clock.simulate(3);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, set_value_called_twice_last_wins)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '1');
}

Test(clock, set_value_undefined_applied)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    clock.setValue(nts::Tristate::Undefined);
    clock.simulate(2);
    cr_assert_eq(clock.displayValue(), 'U');
}

Test(clock, compute_returns_true_after_set_true)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
}

Test(clock, compute_returns_false_after_set_false)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);
}

Test(clock, compute_returns_undefined_before_simulate)
{
    nts::ClockComponent clock;
    cr_assert_eq(clock.compute(1), nts::Tristate::Undefined);
}

Test(clock, compute_does_not_change_display_value)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    clock.compute(1);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, display_value_true_returns_1)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::True);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '1');
}

Test(clock, display_value_false_returns_0)
{
    nts::ClockComponent clock;
    clock.setValue(nts::Tristate::False);
    clock.simulate(1);
    cr_assert_eq(clock.displayValue(), '0');
}

Test(clock, display_value_undefined_returns_U)
{
    nts::ClockComponent clock;
    cr_assert_eq(clock.displayValue(), 'U');
}