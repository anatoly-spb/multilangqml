cmake_minimum_required(VERSION 2.8.12)

project(multilangqml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
set (SOURCES "main.cpp" "qml.qrc" "translator.h" "translator.cpp" )
qt5_create_translation(GENERATED_QM ${SOURCES} ${PROJECT_NAME}_ru.ts ${PROJECT_NAME}_en.ts)

add_executable(${PROJECT_NAME} ${SOURCES} ${GENERATED_QM})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)
