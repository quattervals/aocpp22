add_library(libApp OBJECT)

target_sources(
  libApp PRIVATE
  day_1.cpp
  day_4.cpp
  utils.cpp
)

target_link_libraries(libApp PUBLIC common)

