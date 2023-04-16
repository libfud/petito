find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# add_library(ppu_lib ppu.cpp)

find_package(SDL2 REQUIRED)

set(PPU_SOURCES
    ppu.cpp
    ppu_ctrl.cpp
    ppu_mask.cpp
    ppu_status.cpp
    ppu_object.cpp
    loopy_register.cpp
    virtual_screen.cpp
    # ppu_jackass.cpp
)

add_minimal_target(
    ppu_lib
    SOURCES ${PPU_SOURCES}
    TEST_SOURCES
    test_ppu.cpp
    test_ppu_ctrl.cpp
    test_ppu_mask.cpp
    test_ppu_status.cpp
    test_loopy.cpp
    test_ppu_object.cpp
)

target_include_directories(ppu_lib PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(ppu_lib PRIVATE cartridge_lib nes_lib ${SDL2_LIBRARIES}
 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_common_dependency(ppu_lib Logger)
