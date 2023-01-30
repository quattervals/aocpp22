message(STATUS "Enable testing with Catch2")

set(TEST_APP_NAME ${PROJECT_NAME}_app_test)

add_executable(${TEST_APP_NAME}
  test_app_day_4.cpp
  test_app_day_5.cpp
  test_app_day_10.cpp
)

target_include_directories(${TEST_APP_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/app
  ${PROJECT_SOURCE_DIR}/test
)

target_link_libraries(${TEST_APP_NAME} Catch2::Catch2WithMain libApp common)

add_custom_target(${TEST_APP_NAME}_execution ALL
  DEPENDS ${TEST_APP_NAME})

catch_discover_tests(${TEST_APP_NAME})

add_custom_command(
  TARGET ${TEST_APP_NAME}_execution
  POST_BUILD
  COMMAND ctest --output-on-failure -V
  VERBATIM
)
