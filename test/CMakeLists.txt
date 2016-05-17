find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

set(SOURCES
    test_sample.cpp
)

add_executable(test ${SOURCES})

target_link_libraries(
    test
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
