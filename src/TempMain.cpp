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

        std::cout << config.get("Eihire.properties", "abcd") << std::endl;
        std::cout << config.find("Eihirea.properties", "abcd") << std::endl;

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
}