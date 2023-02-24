
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
# catch_discover_tests()
add_subdirectory(${PROJECT_SOURCE_DIR}/test/app)
