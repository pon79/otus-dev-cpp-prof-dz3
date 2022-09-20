#include <iostream>
#include <map>
#include <vector>
#include <utility> // pair
#include <functional> // less

#include "myallocator.h"
//#include "myvector.h"

int main()
{
    try
    {
//        MyAllocator<std::pair<int, int>, 10> my_allocator;
//        MyAllocator<int, 10> my_allocator;
//        my_allocator.allocate(8);

//        auto container = std::map<int, int, std::less<int>,  MyAllocator<std::pair<int, int>, 10>/* my_allocator*/>{};
//        auto container = std::vector<int, my_allocator>{};

        //        v.reserve(10);
//        for (int i = 0; i < 6; ++i) {
//            std::cout << "container size = " << container.size() << std::endl;
//            container
//            std::cout << std::endl;
//        }

        //
//        auto myV = MyVector<int, MyAllocator<int>>{};
//        myV.reserve(10);
//        for (int i = 0; i < 6; ++i) {
//            std::cout << "MyVector size = " << myV.size() << std::endl;
//            myV.push_back( i );
//            std::cout << std::endl;
//        }

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
