/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** InputParser
*/

#include "InputParser.hpp"
#include <sstream>
#include <algorithm>

/**
 * @file InputParser.cpp
 * @brief Handles user input commands during simulation.
 *
 * InputParser provides a console interface for simulation control:
 *   - exit, display, simulate, loop, or setting input values.
 *
 * Behavior:
 * - Supports CTRL+C interruption for loop commands.
 * - Processes assignments like "inputName=1", "clock=U", etc.
 * - Trims whitespace and ignores empty lines.
 *
 * Methods:
 * - run() : Main loop reading from std::cin.
 * - processCommand(const std::string&) : Parse and execute command.
 * - handleExit, handleDisplay, handleSimulate, handleLoop, handleInput : Helpers.
 */

namespace nts {
    volatile sig_atomic_t InputParser::_loopInterrupted = 0;

    InputParser::InputParser(Circuit& circuit) : _circuit(circuit), _running(true) {}

    void InputParser::signalHandler(int)
    {
        _loopInterrupted = 1;
    }

    void InputParser::setupSignalHandler()
    {
        struct sigaction signal;

        signal.sa_handler = signalHandler;
        sigemptyset(&signal.sa_mask);
        signal.sa_flags = SA_RESTART | SA_RESETHAND;
        sigaction(SIGINT, &signal, nullptr);
    }

    void InputParser::restoreSignalHandler()
    {
        signal(SIGINT, SIG_IGN);
    }

    std::string InputParser::trim(const std::string& str) const
    {
        const char* whitespace = " \t\r\n";
        size_t start = str.find_first_not_of(whitespace);
        
        if (start == std::string::npos)
            return "";
        size_t end = str.find_last_not_of(whitespace);
        return str.substr(start, end - start + 1);
    }

    void InputParser::run()
    {
        std::string line;

        signal(SIGINT, SIG_IGN);
        while (_running) {
            std::cout << "> ";
            std::cout.flush();
            if (!std::getline(std::cin, line)) {
                break;
            }
            line = trim(line);
            if (line.empty())
                continue;
            processCommand(line);
        }
    }

    void InputParser::processCommand(const std::string& command)
    {
        if (command == "exit") {
            handleExit();
        } else if (command == "display") {
            handleDisplay();
        } else if (command == "simulate") {
            handleSimulate();
        } else if (command == "loop") {
            handleLoop();
        } else if (command.find('=') != std::string::npos) {
            handleInput(command);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    void InputParser::handleExit()
    {
        _running = false;
    }

    void InputParser::handleDisplay()
    {
        _circuit.display();
    }

    void InputParser::handleSimulate()
    {
        _circuit.simulate();
    }

    void InputParser::handleLoop()
    {
        _loopInterrupted = 0;
        setupSignalHandler();

        while (!_loopInterrupted) {
            _circuit.simulate();
            _circuit.display();
        }
        restoreSignalHandler();
        std::cout << std::endl;
    }

    void InputParser::handleInput(const std::string& command)
    {
        size_t equalPos = command.find('=');
        nts::Tristate value;
    
        if (equalPos == std::string::npos)
            return;
        std::string name = command.substr(0, equalPos);
        std::string valueStr = command.substr(equalPos + 1);

        name = trim(name);
        valueStr = trim(valueStr);
        if (valueStr == "0") {
            value = nts::False;
        } else if (valueStr == "1") {
            value = nts::True;
        } else if (valueStr == "U") {
            value = nts::Undefined;
        } else {
            std::cerr << "Invalid value: " << valueStr << " (must be 0, 1, or U)" << std::endl;
            return;
        }
        try {
            _circuit.setValue(name, value);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}