add_library(libApp OBJECT)

target_sources(
  libApp PRIVATE
  day_4.cpp
  day_5.cpp
  day_10.cpp
  utils.cpp
)

target_link_libraries(libApp PUBLIC common)
