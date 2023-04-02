find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# add_library(ppu_lib ppu.cpp)

find_package(SDL2 REQUIRED)

add_minimal_target(
    ppu_lib
    SOURCES ppu.cpp ppu_ctrl.cpp ppu_mask.cpp ppu_status.cpp
    TEST_SOURCES
    test_ppu.cpp
    test_ppu_ctrl.cpp
    test_ppu_mask.cpp
    test_ppu_status.cpp
)

target_include_directories(ppu_lib PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(ppu_lib PRIVATE cartridge_lib ${SDL2_LIBRARIES})

add_common_dependency(ppu_lib Logger)
