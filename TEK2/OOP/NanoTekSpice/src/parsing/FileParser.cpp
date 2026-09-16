/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** FileParser.cpp
*/

#include "FileParser.hpp"
#include "exceptions/SyntaxException.hpp"
#include "exceptions/NoChipsetsException.hpp"
#include "exceptions/FileNotFoundException.hpp"
#include "exceptions/DuplicateComponentException.hpp"

/**
 * @file FileParser.cpp
 * @brief Parses NTS circuit description files.
 *
 * FileParser handles reading, validating, and parsing `.nts` files
 * into chipsets and links. It supports comment stripping, trimming,
 * and endpoint parsing.
 *
 * Functions:
 * - run(std::istream&) : Parse from a stream.
 * - readFile(const char*) : Open file and parse contents.
 * - parseChipset(const std::string&) : Parse a chipset line.
 * - parseLink(const std::string&) : Parse a connection line.
 * - parseEndpoint(const std::string&) : Parse endpoint `name:pin`.
 * - cleanLine, trim, stripComments : Utility functions for preprocessing.
 *
 * Exceptions:
 * - SyntaxException
 * - NoChipsetsException
 * - FileNotFoundException
 * - DuplicateComponentException
 */

void FileParser::run(std::istream &input)
{
    std::string raw;
    Section section = Section::NONE;
    bool hasChipsets = false;

    _chipsets.clear();
    _links.clear();
    while (std::getline(input, raw))
    {
        std::string line = cleanLine(raw);
        if (line.empty())
            continue;
        if (line == ".chipsets:")
        {
            section = Section::CHIPSETS;
            continue;
        }
        if (line == ".links:")
        {
            if (!hasChipsets)
                throw NoChipsetsException();
            section = Section::LINKS;
            continue;
        }
        switch (section)
        {
        case Section::CHIPSETS:
            parseChipset(line);
            hasChipsets = true;
            break;
        case Section::LINKS:
            parseLink(line);
            break;
        default:
            throw SyntaxException("Line outside section");
        }
    }
    if (!hasChipsets)
        throw NoChipsetsException();
}

void FileParser::readFile(const char *filename)
{
    std::ifstream file(filename);

    if (!file)
        throw FileNotFoundException(filename);
    run(file);
}

void FileParser::stripComments(std::string &line)
{
    size_t pos = line.find('#');

    if (pos != std::string::npos)
        line.erase(pos);
}

std::string FileParser::trim(const std::string &str)
{
    const char *whitespace = " \t\r\n";
    size_t start = str.find_first_not_of(whitespace);

    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

std::string FileParser::cleanLine(const std::string &raw)
{
    std::string line = raw;

    stripComments(line);
    return trim(line);
}

Endpoint FileParser::parseEndpoint(const std::string &token)
{
    size_t colon = token.find(':');
    Endpoint endpoint;

    if (colon == std::string::npos)
        throw SyntaxException("Missing ':' in link");
    endpoint.name = token.substr(0, colon);
    try {
        endpoint.pin = std::stoi(token.substr(colon + 1));
        if (endpoint.pin <= 0) {
            throw SyntaxException("Pin number must be positive");
        }
    } catch (const std::invalid_argument&) {
        throw SyntaxException("Invalid pin number format");
    } catch (const std::out_of_range&) {
        throw SyntaxException("Pin number out of range");
    }
    return endpoint;
}

void FileParser::parseChipset(const std::string &line)
{
    std::stringstream stringStream(line);
    ChipsetLine chipsetLine;
    std::string extra;

    if (!(stringStream >> chipsetLine.type >> chipsetLine.name))
        throw SyntaxException("Invalid chipset line");
    if (stringStream >> extra)
        throw SyntaxException("Too many args in chipset");
    if (!_componentNames.insert(chipsetLine.name).second) {
        throw DuplicateComponentNameException(chipsetLine.name);
    }
    _chipsets.push_back(chipsetLine);
}

void FileParser::parseLink(const std::string &line)
{
    std::stringstream stringStream(line);
    std::string first, second;
    LinkLine link;

    if (!(stringStream >> first >> second))
        throw SyntaxException("Invalid link line");
    link.a = parseEndpoint(first);
    link.b = parseEndpoint(second);
    _links.push_back(link);
}

const std::vector<ChipsetLine> &FileParser::getChipsets() const
{
    return _chipsets;
}

const std::vector<LinkLine> &FileParser::getLinks() const
{
    return _links;
}