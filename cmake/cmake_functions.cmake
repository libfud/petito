function(add_common_dependency TargetName DepName)
    if (NOT "${TargetName}" STREQUAL "${DepName}")
        get_target_property(DepIncs ${DepName} INCLUDE_DIRECTORIES)
        target_include_directories(${TargetName} PUBLIC ${DepIncs})
        add_dependencies(${TargetName} ${DepName})
        target_link_libraries(${TargetName} PUBLIC ${DepName})
    endif()
endfunction()

macro(GetFnArgs pos multiValueArgs)
    set(opts "")
    set(singleValueArgs "")
    cmake_parse_arguments(PARSE_ARGV ${pos} STM "${opts}" "${singleValueArgs}" "${multiValueArgs}")
endmacro()

macro(AddTestTarget)
    set(TestModuleName Test${ModuleName})
    add_executable(${TestModuleName} ${STM_TEST_SOURCES})
    target_link_libraries(${TestModuleName}
        PRIVATE
        ${ModuleName}
        ${STM_EXTRA_LIBS}
        gtest gtest_main gmock)
    target_compile_options(${TestModuleName} BEFORE PRIVATE -Werror -Wno-error=array-bounds -Wunused-value)

    gtest_add_tests(
        TARGET ${TestModuleName}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/Test${ModuleName}.xml)
endmacro()

macro(AddLibraryTarget)
    include_directories(include ${STM_EXTRA_INCS})
    target_include_directories(mos6502_lib INTERFACE include)

    add_library(${ModuleName} ${STM_SOURCES})

    target_include_directories(${ModuleName} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${ModuleName} PRIVATE ${STM_EXTRA_LIBS})
    target_link_libraries(mos6502_lib INTERFACE ${ModuleName})
endmacro()

function(add_minimal_target ModuleName)
    GetFnArgs(0 "SOURCES;TEST_SOURCES;EXTRA_LIBS;EXTRA_INCS;EXTRA_DEPS")

    AddLibraryTarget()
    foreach(DEP ${STM_DEPS})
        add_common_dependency(${ModuleName} ${DEP})
    endforeach()
    unset(CMAKE_CXX_CLANG_TIDY)
    AddTestTarget()
endfunction()

function(add_target_multi_source ModuleName)
    GetFnArgs(0 "SOURCES;TEST_SOURCES;EXTRA_LIBS;EXTRA_INCS;EXTRA_DEPS")

    AddLibraryTarget()

    add_common_dependency(${ModuleName} Logger)
    add_common_dependency(${ModuleName} Result)
    foreach(DEP ${STM_DEPS})
        add_common_dependency(${ModuleName} ${DEP})
    endforeach()

    unset(CMAKE_CXX_CLANG_TIDY)
    AddTestTarget()
endfunction()

function(add_target ModuleName ModuleSource ModuleTestSource)
    GetFnArgs(3 "EXTRA_LIBS;EXTRA_INCS;EXTRA_DEPS")
    add_target_multi_source(
        ${ModuleName}
        SOURCES ${ModuleSource}
        TEST_SOURCES ${ModuleTestSource}
        EXTRA_LIBS ${STM_EXTRA_LIBS}
        EXTRA_INCS ${STM_EXTRA_INCS}
        EXTRA_DEPS ${STM_DEPS})
endfunction()
