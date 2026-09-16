/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HH_
#define COMPONENTFACTORY_HH_
#include <memory>
#include <map>
#include <functional>
#include "IComponent.hpp"

namespace nts {
    class ComponentFactory {
        private:
            std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
        public:
            ComponentFactory();
            std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
    };
}

#endif
