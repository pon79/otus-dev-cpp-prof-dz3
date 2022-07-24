#include <iostream>

int main()
{
    try
    {        


    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
