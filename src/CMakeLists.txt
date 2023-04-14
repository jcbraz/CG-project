cmake_minimum_required(VERSION 3.24.2)

# Project Name
PROJECT(group_project)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add the tinyxml2 library
include(FetchContent)
FetchContent_Declare(
	tinyxml2
	GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
	GIT_TAG 9.0.0
)
FetchContent_MakeAvailable(
	tinyxml2
)
# add_executable(${PROJECT_NAME} engine.cpp geometricShapes.cpp)
add_executable(${PROJECT_NAME} engine.cpp geometricShapes.cpp geometricShapes.h engineMaterials.cpp parseXML.cpp)
target_link_libraries(${PROJECT_NAME} tinyxml2::tinyxml2)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
    
    if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
    
    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib tinyxml2)
    
    if(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    
else(WIN32) #Linux and Mac

    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} tinyxml2)
    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)
    
endif(WIN32)
