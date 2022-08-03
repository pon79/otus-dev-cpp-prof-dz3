#include <iostream>
#include <vector>

#include "myallocator.h"

int main()
{
    try
    {        
        auto v = std::vector<int, MyAllocator<int>>{};
        // v.reserve(5);
        for (int i = 0; i < 6; ++i) {
            std::cout << "vector size = " << v.size() << std::endl;
            v.emplace_back(i);
            std::cout << std::endl;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
