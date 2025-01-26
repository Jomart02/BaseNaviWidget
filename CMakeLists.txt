cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME BaseNaviWidgetLib)
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(./NavyComponents)

set(HDRS
    ./include/BaseNaviWidget.h
)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_library(${PROJECT_NAME} SHARED ${HDRS})
# Определяем макрос BASENAVIWIDGET_LIBRARY только при компиляции библиотеки
target_compile_definitions(${PROJECT_NAME} PRIVATE BASENAVIWIDGET_LIBRARY)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets nmeabuilder CoordinateEdit)

# Указываем, что заголовочные файлы библиотеки должны быть доступны для других проектов
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)