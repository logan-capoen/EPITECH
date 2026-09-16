/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_false.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/special/TrueComponent.hpp"

Test(false_component, compute_returns_True)
{
    nts::TrueComponent comp;
    cr_assert_eq(comp.compute(1), nts::Tristate::True);
}
