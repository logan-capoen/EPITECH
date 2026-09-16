/*
** EPITECH PROJECT, 2026
** tests
** File description:
** test_factory.cpp
*/

#include <criterion/criterion.h>
#include "ComponentFactory.hpp"

Test(factory, create_input)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("input");

    cr_assert_not_null(component.get(), "input must not be null");
}

Test(factory, create_output)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("output");

    cr_assert_not_null(component.get(), "output must not be null");
}

Test(factory, create_clock)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("clock");

    cr_assert_not_null(component.get(), "clock must not be null");
}

Test(factory, create_true)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("true");

    cr_assert_not_null(component.get(), "true must not be null");
}

Test(factory, create_false)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("false");

    cr_assert_not_null(component.get(), "false must not be null");
}

Test(factory, create_and)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("and");

    cr_assert_not_null(component.get(), "and must not be null");
}

Test(factory, create_or)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("or");

    cr_assert_not_null(component.get(), "or must not be null");
}

Test(factory, create_xor)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("xor");

    cr_assert_not_null(component.get(), "xor must not be null");
}

Test(factory, create_not)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("not");

    cr_assert_not_null(component.get(), "not must not be null");
}

Test(factory, create_4001)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4001");

    cr_assert_not_null(component.get(), "4001 must not be null");
}

Test(factory, create_4011)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4011");

    cr_assert_not_null(component.get(), "4011 must not be null");
}

Test(factory, create_4030)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4030");

    cr_assert_not_null(component.get(), "4030 must not be null");
}

Test(factory, create_4069)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4069");

    cr_assert_not_null(component.get(), "4069 must not be null");
}

Test(factory, create_4071)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4071");

    cr_assert_not_null(component.get(), "4071 must not be null");
}

Test(factory, create_4081)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4081");

    cr_assert_not_null(component.get(), "4081 must not be null");
}

Test(factory, create_4094)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4094");

    cr_assert_not_null(component.get(), "4094 must not be null");
}

Test(factory, create_4514)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4514");

    cr_assert_not_null(component.get(), "4514 must not be null");
}

Test(factory, create_4040)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4040");

    cr_assert_not_null(component.get(), "4040 must not be null");
}

Test(factory, create_4017)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4017");

    cr_assert_not_null(component.get(), "4017 must not be null");
}

Test(factory, create_4512)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4512");

    cr_assert_not_null(component.get(), "4512 must not be null");
}

Test(factory, create_4008)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4008");

    cr_assert_not_null(component.get(), "4008 must not be null");
}

Test(factory, create_4013)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4013");

    cr_assert_not_null(component.get(), "4013 must not be null");
}

Test(factory, create_2716)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("2716");

    cr_assert_not_null(component.get(), "2716 must not be null");
}

Test(factory, create_4801)
{
    nts::ComponentFactory factory;
    auto component = factory.createComponent("4801");

    cr_assert_not_null(component.get(), "4801 must not be null");
}

Test(factory, unknown_component_throw)
{
    nts::ComponentFactory factory;

    cr_assert_throw(factory.createComponent("unknown"), std::runtime_error, "unknow type must throw std::runtime_error");
}

Test(factory, empty_string_throw)
{
    nts::ComponentFactory factory;

    cr_assert_throw(factory.createComponent(""), std::runtime_error, "empty string must throw std::runtime_error");
}