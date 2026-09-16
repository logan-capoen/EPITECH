/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** test_InputParser.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sstream>
#include "InputParser.hpp"
#include "Circuit.hpp"

struct InputParserFixture {
    nts::Circuit     circuit;
    nts::InputParser parser;

    InputParserFixture() : parser(circuit)
    {
        circuit.addComponent("input",  "in1");
        circuit.addComponent("output", "out1");
    }
};

Test(inputparser_run, run_exits_on_eof)
{
    nts::Circuit circuit;
    circuit.addComponent("input", "in1");
    nts::InputParser parser(circuit);
    std::istringstream input("");
    std::streambuf *old = std::cin.rdbuf(input.rdbuf());
    cr_assert_no_throw(parser.run(), std::exception);
    std::cin.rdbuf(old);
}

Test(inputparser_run, run_processes_exit_command)
{
    nts::Circuit circuit;
    circuit.addComponent("input", "in1");
    nts::InputParser parser(circuit);
    std::istringstream input("exit\n");
    std::streambuf *old = std::cin.rdbuf(input.rdbuf());
    cr_assert_no_throw(parser.run(), std::exception);
    std::cin.rdbuf(old);
}

Test(inputparser_run, run_ignores_blank_lines)
{
    nts::Circuit circuit;
    circuit.addComponent("input", "in1");
    nts::InputParser parser(circuit);
    std::istringstream input("\n\n\nexit\n");
    std::streambuf *old = std::cin.rdbuf(input.rdbuf());
    cr_assert_no_throw(parser.run(), std::exception);
    std::cin.rdbuf(old);
}

Test(inputparser_run, run_processes_multiple_commands)
{
    nts::Circuit circuit;
    circuit.addComponent("input", "in1");
    nts::InputParser parser(circuit);
    std::istringstream input("in1=1\nsimulate\nexit\n");
    std::streambuf *old = std::cin.rdbuf(input.rdbuf());
    cr_assert_no_throw(parser.run(), std::exception);
    std::cin.rdbuf(old);
}