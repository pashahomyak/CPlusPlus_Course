add_executable(sfml2_1 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(sfml2_1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml2_1 PUBLIC cxx_std_17)
target_compile_definitions(sfml2_1 PRIVATE SFML_STATIC)

target_link_libraries(sfml2_1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})