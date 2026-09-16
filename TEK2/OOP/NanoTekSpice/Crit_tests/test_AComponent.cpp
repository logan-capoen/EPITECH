/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** tests_acomponent.cpp
*/
#include <criterion/criterion.h>
#include "AComponent.hpp"
#include "exceptions/InvalidPinException.hpp"

class TestComponent : public nts::AComponent {
public:
    TestComponent()
    {
        _inputs[1] = false;
        _inputs[2] = false;
        _outputs[3] = {0, 0};
    }

    nts::Tristate compute(std::size_t pin) override
    {
        (void)pin;
        return nts::Tristate::Undefined;
    }
};

Test(acomponent, set_link_valid)
{
    TestComponent comp1;
    TestComponent comp2;

    cr_assert_no_throw(
        comp1.setLink(1, comp2, 3),
        std::exception
    );
}

Test(acomponent, set_link_invalid_pin_source)
{
    TestComponent comp1;
    TestComponent comp2;

    cr_assert_throw(
        comp1.setLink(99, comp2, 1),
        std::exception
    );
}

Test(acomponent, set_link_invalid_pin_dest)
{
    TestComponent comp1;
    TestComponent comp2;

    cr_assert_throw(
        comp1.setLink(1, comp2, 99),
        std::exception
    );
}

Test(acomponent, get_link_no_link)
{
    TestComponent comp;

    cr_assert_eq(comp.getLink(1), nts::Tristate::Undefined);
}

Test(acomponent, simulate_no_throw)
{
    TestComponent comp;

    cr_assert_no_throw(comp.simulate(0), std::exception);
}

Test(tristate, and_true_true)
{
    nts::Tristate a = nts::True;
    nts::Tristate b = nts::True;

    cr_assert_eq(a && b, nts::True);
}

Test(tristate, and_true_false)
{
    nts::Tristate a = nts::True;
    nts::Tristate b = nts::False;

    cr_assert_eq(a && b, nts::False);
}

Test(tristate, and_false_false)
{
    nts::Tristate a = nts::False;
    nts::Tristate b = nts::False;

    cr_assert_eq(a && b, nts::False);
}

Test(tristate, and_undefined_false)
{
    nts::Tristate a = nts::Undefined;
    nts::Tristate b = nts::False;

    cr_assert_eq(a && b, nts::False);
}

Test(tristate, and_undefined_true)
{
    nts::Tristate a = nts::Undefined;
    nts::Tristate b = nts::True;

    cr_assert_eq(a && b, nts::Undefined);
}

Test(tristate, or_true_false)
{
    nts::Tristate a = nts::True;
    nts::Tristate b = nts::False;

    cr_assert_eq(a || b, nts::True);
}

Test(tristate, or_false_false)
{
    nts::Tristate a = nts::False;
    nts::Tristate b = nts::False;

    cr_assert_eq(a || b, nts::False);
}

Test(tristate, or_undefined_true)
{
    nts::Tristate a = nts::Undefined;
    nts::Tristate b = nts::True;

    cr_assert_eq(a || b, nts::True);
}

Test(tristate, or_undefined_false)
{
    nts::Tristate a = nts::Undefined;
    nts::Tristate b = nts::False;

    cr_assert_eq(a || b, nts::Undefined);
}

Test(tristate, xor_true_false)
{
    nts::Tristate a = nts::True;
    nts::Tristate b = nts::False;

    cr_assert_eq(a ^ b, nts::True);
}

Test(tristate, xor_true_true)
{
    nts::Tristate a = nts::True;
    nts::Tristate b = nts::True;

    cr_assert_eq(a ^ b, nts::False);
}

Test(tristate, xor_false_false)
{
    nts::Tristate a = nts::False;
    nts::Tristate b = nts::False;

    cr_assert_eq(a ^ b, nts::False);
}

Test(tristate, xor_undefined)
{
    nts::Tristate a = nts::Undefined;
    nts::Tristate b = nts::True;

    cr_assert_eq(a ^ b, nts::Undefined);
}

Test(tristate, not_true)
{
    nts::Tristate a = nts::True;

    cr_assert_eq(!a, nts::False);
}

Test(tristate, not_false)
{
    nts::Tristate a = nts::False;

    cr_assert_eq(!a, nts::True);
}

Test(tristate, not_undefined)
{
    nts::Tristate a = nts::Undefined;

    cr_assert_eq(!a, nts::Undefined);
}