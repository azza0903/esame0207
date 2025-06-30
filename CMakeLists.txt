cmake_minimum_required(VERSION 3.10)
project(DiarioAttivita)
set(CMAKE_CXX_STANDARD 17)

# Aggiunta di Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Per GoogleTest più veloce
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Aggiunta dell'eseguibile principale
add_executable(DiarioAttivita
     main.cpp
    DiarioAttivita.cpp
)

# Test
add_executable(test_diario
    test_DiarioAttivita.cpp
    DiarioAttivita.cpp
)

target_link_libraries(test_diario
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_diario)

