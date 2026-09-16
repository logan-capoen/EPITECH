/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** InputParser
*/

#ifndef INPUTPARSER_HPP_
#define INPUTPARSER_HPP_

#include <string>
#include <iostream>
#include <csignal>
#include "Circuit.hpp"

namespace nts {
    class InputParser {
        private:
            Circuit& _circuit;
            bool _running;
            static volatile sig_atomic_t _loopInterrupted;

            void processCommand(const std::string& command);
            void handleExit();
            void handleDisplay();
            void handleSimulate();
            void handleLoop();
            void handleInput(const std::string& command);
            static void signalHandler(int signum);
            void setupSignalHandler();
            void restoreSignalHandler();
            std::string trim(const std::string& str) const;
        public:
            InputParser(Circuit& circuit);
            ~InputParser() = default;

            void run();
    };
}

#endif /* !INPUTPARSER_HPP_ */