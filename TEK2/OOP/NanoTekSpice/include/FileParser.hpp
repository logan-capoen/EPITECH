/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** FileParser.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

enum class Section {
    NONE,
    CHIPSETS,
    LINKS
};

struct ChipsetLine {
    std::string type;
    std::string name;
};

struct Endpoint {
    std::string name;
    int pin;
};

struct LinkLine {
    Endpoint a;
    Endpoint b;
};

class FileParser {
    private:
        std::vector<ChipsetLine> _chipsets;
        std::vector<LinkLine> _links;
        std::set<std::string> _componentNames;

        void parseChipset(const std::string& line);
        void parseLink(const std::string& line);
        void stripComments(std::string& line);
        std::string trim(const std::string& s);
        std::string cleanLine(const std::string& raw);
        Endpoint parseEndpoint(const std::string& token);

    public:
        FileParser() = default;
        ~FileParser() = default;

        void readFile(const char *filename);
        void run(std::istream& input);
        const std::vector<ChipsetLine>& getChipsets() const;
        const std::vector<LinkLine>& getLinks() const;
};
