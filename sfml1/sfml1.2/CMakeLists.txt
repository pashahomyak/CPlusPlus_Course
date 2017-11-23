add_executable(sfm1.2 LPS.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfm1.2 PUBLIC cxx_std_17)
target_compile_definitions(sfm1.2 PRIVATE SFML_STATIC)

target_link_libraries(sfm1.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})