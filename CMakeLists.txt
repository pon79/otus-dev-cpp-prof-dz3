cmake_minimum_required(VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator LANGUAGES CXX VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(allocator main.cpp myallocator.h)

# ======== GOOGLE_TEST start ===========
#enable_testing()
#include(GoogleTest)

#add_executable(test_allocator test_allocator.cpp)
#target_link_libraries(test_allocator
#    gtest
#    gtest_main
#)

#gtest_discover_tests(test_allocator)

# ======== GOOGLE_TEST end ===========

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)


# ======== DEB pack start ===========
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT pon79job@gmail.com)

include(CPack)
# ======== DEB pack end ===========
