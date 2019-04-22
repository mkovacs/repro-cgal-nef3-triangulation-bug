cmake_minimum_required(VERSION 3.12)

project(repro
    VERSION 0.1.0
    DESCRIPTION "Example of bug in CGAL::convert_nef_polyhedron_to_polygon_mesh&lt;Nef_polyhedron_3, Surface_mesh> triangulation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS thread)
find_package(CGAL REQUIRED COMPONENTS Core)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    Boost::thread
    CGAL::CGAL
    CGAL::CGAL_Core
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
