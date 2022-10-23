include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

set(GAME_TEST_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GAME_TEST_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

include_directories(${GAME_TEST_INSTALL_INCLUDE_DIR})
set(SOURCE_FILES ./test.cpp)

enable_testing()

add_executable(
    game_test
    test.cpp
)

target_link_libraries(
    game_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(game_test)

install(TARGETS game_test DESTINATION ${GAME_TEST_INSTALL_BIN_DIR})
