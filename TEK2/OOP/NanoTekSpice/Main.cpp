/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** main
*/

#include <iostream>
#include <exception>
#include "FileParser.hpp"
#include "Circuit.hpp"
#include "InputParser.hpp"

/**
 * @file main.cpp
 * @brief Entry point for NanoTekSpice simulator.
 *
 * The main function:
 * - Validates command line arguments.
 * - Loads `.nts` file using FileParser.
 * - Builds Circuit with components and links.
 * - Starts InputParser loop for user commands.
 *
 * Returns:
 * - 0 on normal termination.
 * - 84 on error (invalid args, file not found, unknown component, etc.).
 */

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit_file.nts>" << std::endl;
        return 84;
    }
    try {
        nts::Circuit circuit;
        FileParser parser;

        parser.readFile(argv[1]);
        for (const ChipsetLine& chipset : parser.getChipsets()) {
            circuit.addComponent(chipset.type, chipset.name);
        }
        for (const LinkLine& link : parser.getLinks()) {
            circuit.linkComponents(link.a.name, link.a.pin, link.b.name, link.b.pin);
        }
        nts::InputParser handler(circuit);
        handler.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}