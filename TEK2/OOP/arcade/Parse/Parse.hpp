/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** Parse
*/

#ifndef PARSE_HPP_
#define PARSE_HPP_

#include <string>

class Parse {
    public:
        Parse();
        ~Parse();
        void parse(int ac, char **av);
        void isTTY(char **env) const;

    private:
        int _argc;
        char **_argv;
        bool isValidLibFormat(const std::string &libPath) const;
};

#endif /* !PARSE_HPP_ */
