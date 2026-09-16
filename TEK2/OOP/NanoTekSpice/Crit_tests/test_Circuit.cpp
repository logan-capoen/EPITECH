/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** tests.cpp
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Circuit.hpp"
#include "IComponent.hpp"

Test(circuit, add_component_valid)
{
    nts::Circuit circuit;

    cr_assert_no_throw(
        circuit.addComponent("and", "and1"),
        std::exception
    );
}

Test(circuit, add_component_invalid_type)
{
    nts::Circuit circuit;

    cr_assert_throw(
        circuit.addComponent("invalid_type", "comp1"),
        std::exception
    );
}

Test(circuit, get_component_valid)
{
    nts::Circuit circuit;

    circuit.addComponent("and", "and1");
    cr_assert_no_throw(
        circuit.getComponent("and1"),
        std::exception
    );
}

Test(circuit, get_component_invalid)
{
    nts::Circuit circuit;

    cr_assert_throw(
        circuit.getComponent("nonexistent"),
        std::exception
    );
}

Test(circuit, link_components_valid)
{
    nts::Circuit circuit;

    circuit.addComponent("and", "and1");
    circuit.addComponent("input", "in1");
    cr_assert_no_throw(
        circuit.linkComponents("in1", 1, "and1", 1),
        std::exception
    );
}

Test(circuit, link_components_invalid_component)
{
    nts::Circuit circuit;

    circuit.addComponent("and", "and1");
    cr_assert_throw(
        circuit.linkComponents("nonexistent", 1, "and1", 1),
        std::exception
    );
}

Test(circuit, set_value_valid)
{
    nts::Circuit circuit;

    circuit.addComponent("input", "in1");
    cr_assert_no_throw(
        circuit.setValue("in1", nts::Tristate::True),
        std::exception
    );
}

Test(circuit, set_value_invalid_component)
{
    nts::Circuit circuit;

    cr_assert_throw(
        circuit.setValue("nonexistent", nts::Tristate::True),
        std::exception
    );
}

Test(circuit, simulate_empty)
{
    nts::Circuit circuit;

    cr_assert_no_throw(
        circuit.simulate(),
        std::exception
    );
}

Test(circuit, simulate_and_gate)
{
    nts::Circuit circuit;

    circuit.addComponent("and", "and1");
    circuit.addComponent("input", "in1");
    circuit.addComponent("input", "in2");
    circuit.addComponent("output", "out1");
    circuit.linkComponents("in1", 1, "and1", 1);
    circuit.linkComponents("in2", 1, "and1", 2);
    circuit.linkComponents("and1", 3, "out1", 1);
    circuit.setValue("in1", nts::Tristate::True);
    circuit.setValue("in2", nts::Tristate::True);
    cr_assert_no_throw(circuit.simulate(), std::exception);
    cr_assert_eq(
        circuit.getComponent("out1").compute(1),
        nts::Tristate::True
    );
}

Test(circuit, simulate_and_gate_false)
{
    nts::Circuit circuit;

    circuit.addComponent("and", "and1");
    circuit.addComponent("input", "in1");
    circuit.addComponent("input", "in2");
    circuit.addComponent("output", "out1");
    circuit.linkComponents("in1", 1, "and1", 1);
    circuit.linkComponents("in2", 1, "and1", 2);
    circuit.linkComponents("and1", 3, "out1", 1);
    circuit.setValue("in1", nts::Tristate::True);
    circuit.setValue("in2", nts::Tristate::False);
    cr_assert_no_throw(circuit.simulate(), std::exception);
    cr_assert_eq(
        circuit.getComponent("out1").compute(1),
        nts::Tristate::False
    );
}

Test(circuit, display, .init = cr_redirect_stdout)
{
    nts::Circuit circuit;

    circuit.addComponent("input", "in1");
    circuit.addComponent("output", "out1");
    circuit.setValue("in1", nts::Tristate::True);
    circuit.simulate();
    cr_assert_no_throw(circuit.display(), std::exception);
}