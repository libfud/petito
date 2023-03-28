find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_minimal_target(
    Logger
    SOURCES logger.cpp
    TEST_SOURCES test_logger.cpp
    EXTRA_LIBS fmt spdlog::spdlog)
