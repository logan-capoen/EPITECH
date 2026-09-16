/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** ALib
*/

#ifndef ALib_HPP_
#define ALib_HPP_

#include "ILib.hpp"

class ALib : public ILib{
    public:
        ALib() = default;
        virtual ~ALib() = default;
        const std::string get_name() const override;
        LibType get_type() const override;

    protected:
        std::string _name = "Undefine";
        LibType _type = LibType::UNDEFINE;
};

#endif