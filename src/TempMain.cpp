#include <iostream>

#include "PropertiesMap.h"

using namespace Eihire;

int main()
{
    Configuration::PropertiesMap properties;
    properties.set("1", "aaaa");
    properties.set("2", "bbbb");
    properties.set("33", "cccc");
    properties.set("4", "dddd");

    for (auto e : properties.properties())
    {
        std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
    }

    properties.set("33", "ssss");
    properties.set("3", "abcd");

    std::cout << std::endl;
    for (auto e : properties.properties())
    {
        std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
    }
}