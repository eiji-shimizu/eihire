#include <iostream>
#include <stdexcept>

#include "Configuration.h"
//#include "propertiesMap.h"

using namespace Eihire;

int main()
{
    try
    {
        Configuration::Configuration config;
        std::cout << config.get("1") << std::endl;

        // for (auto e : config.propertiesMapList().at(0).properties())
        // {
        //     std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
        // }
        for (auto &p : config.propertiesMapList())
        {
            for (auto e : p.properties())
            {
                std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unexpected error." << std::endl;
    }

    // properties.set("1", "aaaa");
    // properties.set("2", "bbbb");
    // properties.set("33", "cccc");
    // properties.set("4", "dddd");

    // for (auto e : properties.properties())
    // {
    //     std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
    // }

    // properties.set("33", "ssss");
    // properties.set("3", "abcd");

    // std::cout << std::endl;
    // for (auto e : properties.properties())
    // {
    //     std::cout << "(" << e.first << ", " << e.second << ")" << std::endl;
    // }
}