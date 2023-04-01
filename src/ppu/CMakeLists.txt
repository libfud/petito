find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# add_library(ppu_lib ppu.cpp)

add_minimal_target(
    ppu_lib
    SOURCES ppu.cpp ppu_ctrl.cpp ppu_mask.cpp ppu_status.cpp
    TEST_SOURCES test_ppu.cpp)

add_common_dependency(ppu_lib Logger)
