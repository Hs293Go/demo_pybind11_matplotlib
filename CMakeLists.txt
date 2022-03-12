cmake_minimum_required(VERSION 3.12.0)
project(demo_pyplot)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(${PROJECT_NAME}_readme src/demo_pyplot_readme.cpp)
target_include_directories(
  ${PROJECT_NAME}_readme PRIVATE ${PYBIND11_INCLUDE_DIRS}
                                 ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_readme PRIVATE ${Python_LIBRARIES}
                                                     Eigen3::Eigen)

add_executable(${PROJECT_NAME}_detailed src/demo_pyplot_detailed.cpp)
target_include_directories(
  ${PROJECT_NAME}_detailed PRIVATE ${PYBIND11_INCLUDE_DIRS}
                                   ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_detailed PRIVATE ${Python_LIBRARIES}
                                                       Eigen3::Eigen)
