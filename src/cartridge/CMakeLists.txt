find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_library(header_lib header.cpp)

add_minimal_target(
    cartridge_lib
    SOURCES cartridge.cpp mapper_000.cpp mapper_001.cpp
    TEST_SOURCES test_cartridge.cpp)

add_common_dependency(cartridge_lib Logger)
target_link_libraries(cartridge_lib PUBLIC header_lib)
