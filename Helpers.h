#ifndef INTERSORT_HELPERS
#define INTERSORT_HELPERS

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
#include <fstream>
#include <chrono>
#include <string>

static int kIndex = 0;

namespace Intersort {

    void printWelcomeScreen()
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;  
        std::cout << " ██╗███╗   ██╗████████╗███████╗██████╗ ███████╗ ██████╗ ██████╗ ████████╗\n";
        std::cout << " ██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔══██╗╚══██╔══╝\n";
        std::cout << " ██║██╔██╗ ██║   ██║   █████╗  ██████╔╝███████╗██║   ██║██████╔╝   ██║\n";   
        std::cout << " ██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗╚════██║██║   ██║██╔══██╗   ██║ \n";  
        std::cout << " ██║██║ ╚████║   ██║   ███████╗██║  ██║███████║╚██████╔╝██║  ██║   ██║ \n";  
        std::cout << " ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝\n";   
        std::cout << "-------------------------------------------------------------------------" << std::endl;  
        std::cout << "Version 0.0.1" << std::endl << std::endl;
    }

    template<typename T>
    void printVector(std::vector<T> &numbers)
    {
        std::cout << "[";
        for(auto & num : numbers)
            std::cout << num << ",";
        std::cout << '\b' << "]" << '\n';
    }

    template<typename T>
    void serializeContainer(T &container, unsigned int &totalCollisions)
    {
        std::string filename = "reports/container-" + std::to_string(++kIndex) + ".dat";
        std::ofstream file(filename.c_str());
        unsigned int collisions = 0;

        file << "===\n\n\n";
        for(auto const & set : container)
        {
            file << "[";
            if(!set.empty())
            {
                collisions = -1;
                for(auto & num : set)
                {
                    file << num << ",";
                    collisions++;
                }
                totalCollisions += collisions;
                file.seekp(-1, std::ios::end);
            }
            file << "]\n";
        }
        
        file.seekp(0, std::ios::beg);
        file << "Collisions = " << totalCollisions << "\n";
        file.close();
    }

    template<typename T>
    void serializeVector(std::vector<T> &numbers)
    {
        std::ofstream file("vector.dat");
        for(auto const & num : numbers)
        {
            file << num << ",";
        }
        file.seekp(-1, std::ios::end);
        file << " ";
    }

}

#endif