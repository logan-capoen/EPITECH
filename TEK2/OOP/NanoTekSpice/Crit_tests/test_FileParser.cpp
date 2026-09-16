/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** test_FileParser.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sstream>
#include <fstream>
#include <cstdio>
#include "FileParser.hpp"
#include "exceptions/SyntaxException.hpp"
#include "exceptions/NoChipsetsException.hpp"
#include "exceptions/FileNotFoundException.hpp"
#include "exceptions/DuplicateComponentException.hpp"

static FileParser makeParser(const std::string &input)
{
    FileParser parser;
    std::istringstream stream(input);
    parser.run(stream);
    return parser;
}

Test(fileparser_chipsets, parses_single_chipset)
{
    FileParser p = makeParser(".chipsets:\nand a1\n.links:");
    cr_assert_eq(p.getChipsets().size(), 1);
    cr_assert_str_eq(p.getChipsets()[0].type.c_str(), "and");
    cr_assert_str_eq(p.getChipsets()[0].name.c_str(), "a1");
}

Test(fileparser_chipsets, parses_multiple_chipsets)
{
    FileParser p = makeParser(".chipsets:\nand a1\nor o1\nnot n1\n.links:");
    cr_assert_eq(p.getChipsets().size(), 3);
}

Test(fileparser_chipsets, throws_on_duplicate_name)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\nand a1\n.links:"),
        std::exception
    );
}

Test(fileparser_chipsets, throws_on_extra_args_in_chipset)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1 extra\n.links:"),
        std::exception
    );
}

Test(fileparser_chipsets, throws_on_missing_name)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand\n.links:"),
        std::exception
    );
}

Test(fileparser_chipsets, names_stored_correctly)
{
    FileParser p = makeParser(".chipsets:\nand gate1\nor gate2\nnot gate3\n.links:");
    cr_assert_str_eq(p.getChipsets()[0].name.c_str(), "gate1");
    cr_assert_str_eq(p.getChipsets()[1].name.c_str(), "gate2");
    cr_assert_str_eq(p.getChipsets()[2].name.c_str(), "gate3");
}

Test(fileparser_links, parses_single_link)
{
    FileParser p = makeParser(".chipsets:\nand a1\ninput i1\n.links:\ni1:1 a1:1");
    cr_assert_eq(p.getLinks().size(), 1);
    cr_assert_str_eq(p.getLinks()[0].a.name.c_str(), "i1");
    cr_assert_eq(p.getLinks()[0].a.pin, 1);
    cr_assert_str_eq(p.getLinks()[0].b.name.c_str(), "a1");
    cr_assert_eq(p.getLinks()[0].b.pin, 1);
}

Test(fileparser_links, parses_multiple_links)
{
    FileParser p = makeParser(
        ".chipsets:\nand a1\ninput i1\ninput i2\n"
        ".links:\ni1:1 a1:1\ni2:1 a1:2"
    );
    cr_assert_eq(p.getLinks().size(), 2);
}

Test(fileparser_links, multiple_links_correct_pins)
{
    FileParser p = makeParser(
        ".chipsets:\nand a1\ninput i1\ninput i2\noutput o1\n"
        ".links:\ni1:1 a1:1\ni2:1 a1:2\na1:3 o1:1"
    );
    cr_assert_eq(p.getLinks().size(), 3);
    cr_assert_eq(p.getLinks()[2].a.pin, 3);
    cr_assert_eq(p.getLinks()[2].b.pin, 1);
}

Test(fileparser_links, link_with_large_pin_number)
{
    FileParser p = makeParser(".chipsets:\nand a1\ninput i1\n.links:\ni1:1 a1:23");
    cr_assert_eq(p.getLinks()[0].b.pin, 23);
}

Test(fileparser_links, links_section_can_be_empty)
{
    FileParser p = makeParser(".chipsets:\nand a1\n.links:\n");
    cr_assert_eq(p.getLinks().size(), 0);
}

Test(fileparser_links, throws_on_missing_colon_in_endpoint)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\n.links:\na1 a1:1"),
        std::exception
    );
}

Test(fileparser_links, throws_on_invalid_pin_number)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\n.links:\na1:abc a1:1"),
        std::exception
    );
}

Test(fileparser_links, throws_on_zero_pin_number)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\n.links:\na1:0 a1:1"),
        std::exception
    );
}

Test(fileparser_links, throws_on_negative_pin_number)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\n.links:\na1:-1 a1:1"),
        std::exception
    );
}

Test(fileparser_links, throws_on_missing_second_endpoint)
{
    cr_assert_throw(
        makeParser(".chipsets:\nand a1\n.links:\na1:1"),
        std::exception
    );
}

Test(fileparser_sections, throws_on_line_outside_section)
{
    cr_assert_throw(
        makeParser("and a1\n.chipsets:\n.links:"),
        std::exception
    );
}

Test(fileparser_sections, throws_on_no_chipsets_section)
{
    cr_assert_throw(
        makeParser(".links:"),
        std::exception
    );
}

Test(fileparser_sections, throws_on_links_before_chipsets)
{
    cr_assert_throw(
        makeParser(".links:\na1:1 a2:1\n.chipsets:\nand a1"),
        std::exception
    );
}

Test(fileparser_sections, throws_on_empty_input)
{
    cr_assert_throw(
        makeParser(""),
        std::exception
    );
}

Test(fileparser_comments, strips_inline_comments)
{
    FileParser p = makeParser(".chipsets:\nand a1 # this is a comment\n.links:");
    cr_assert_eq(p.getChipsets().size(), 1);
    cr_assert_str_eq(p.getChipsets()[0].name.c_str(), "a1");
}

Test(fileparser_comments, strips_full_line_comments)
{
    FileParser p = makeParser(".chipsets:\n# full comment\nand a1\n.links:");
    cr_assert_eq(p.getChipsets().size(), 1);
}

Test(fileparser_comments, strips_comment_in_links)
{
    FileParser p = makeParser(
        ".chipsets:\nand a1\ninput i1\n"
        ".links:\ni1:1 a1:1 # comment"
    );
    cr_assert_eq(p.getLinks().size(), 1);
}

Test(fileparser_comments, comment_only_lines_ignored)
{
    FileParser p = makeParser(
        "# header comment\n"
        ".chipsets:\n"
        "# comment between components\n"
        "and a1\n"
        ".links:\n"
        "# comment in links\n"
    );
    cr_assert_eq(p.getChipsets().size(), 1);
    cr_assert_eq(p.getLinks().size(), 0);
}

Test(fileparser_comments, hash_at_end_of_chipset_line)
{
    FileParser p = makeParser(".chipsets:\nand a1# no space\n.links:");
    cr_assert_eq(p.getChipsets().size(), 1);
}

Test(fileparser_whitespace, ignores_blank_lines)
{
    FileParser p = makeParser(".chipsets:\n\n\nand a1\n\n.links:\n\n");
    cr_assert_eq(p.getChipsets().size(), 1);
}

Test(fileparser_whitespace, trims_leading_and_trailing_spaces)
{
    FileParser p = makeParser(".chipsets:\n   and   a1   \n.links:");
    cr_assert_eq(p.getChipsets().size(), 1);
    cr_assert_str_eq(p.getChipsets()[0].type.c_str(), "and");
}

Test(fileparser_whitespace, multiple_spaces_between_type_and_name)
{
    FileParser p = makeParser(".chipsets:\nand    a1\n.links:");
    cr_assert_str_eq(p.getChipsets()[0].type.c_str(), "and");
    cr_assert_str_eq(p.getChipsets()[0].name.c_str(), "a1");
}

Test(fileparser_readfile, throws_on_missing_file)
{
    FileParser parser;
    cr_assert_throw(
        parser.readFile("nonexistent_file.nts"),
        std::exception
    );
}

Test(fileparser_readfile, reads_valid_file)
{
    {
        std::ofstream f("./test_parser_tmp.nts");
        f << ".chipsets:\nand a1\ninput i1\n.links:\ni1:1 a1:1\n";
    }
    FileParser parser;
    cr_assert_no_throw(parser.readFile("./test_parser_tmp.nts"), std::exception);
    cr_assert_eq(parser.getChipsets().size(), 2);
    cr_assert_eq(parser.getLinks().size(), 1);
    std::remove("./test_parser_tmp.nts");
}

Test(fileparser_readfile, populates_both_sections)
{
    {
        std::ofstream f("./tmp_extra.nts");
        f << ".chipsets:\nand g1\ninput i1\ninput i2\noutput o1\n";
        f << ".links:\ni1:1 g1:1\ni2:1 g1:2\ng1:3 o1:1\n";
    }
    FileParser parser;
    parser.readFile("./tmp_extra.nts");
    cr_assert_eq(parser.getChipsets().size(), 4);
    cr_assert_eq(parser.getLinks().size(), 3);
    std::remove("./tmp_extra.nts");
}

Test(fileparser_readfile, second_run_clears_previous_state)
{
    FileParser parser;
    std::istringstream s1(".chipsets:\nand a1\nor b1\n.links:");
    parser.run(s1);
    cr_assert_eq(parser.getChipsets().size(), 2);
    std::istringstream s2(".chipsets:\nnot n1\n.links:");
    parser.run(s2);
    cr_assert_eq(parser.getChipsets().size(), 1);
}