/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_false.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "components/special/FalseComponent.hpp"

Test(false_component, compute_returns_false)
{
    nts::FalseComponent comp;
    cr_assert_eq(comp.compute(1), nts::Tristate::False);
}
