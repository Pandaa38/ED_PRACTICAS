cmake_minimum_required(VERSION 3.16)
project(Mini_Practica_1)


set(CMAKE_CXX_STANDARD 17)
set(BASE_FOLDER ./)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${BASE_FOLDER}/include)
add_library(image ${BASE_FOLDER}/src/image.cpp ${BASE_FOLDER}/src/imageIO.cpp)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/rebobinar.cpp)
add_executable(rebobinar ${BASE_FOLDER}/src/rebobinar.cpp ${BASE_FOLDER}/src/video.cpp)
target_link_libraries(rebobinar LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/morphing.cpp)
add_executable(morphing ${BASE_FOLDER}/src/morphing.cpp ${BASE_FOLDER}/src/video.cpp)
target_link_libraries(morphing LINK_PUBLIC image)
endif()

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

#Generar el zip
set(ZIP_OUT ${CMAKE_CURRENT_BINARY_DIR}/zip)
add_custom_target(mrproper 
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${ZIP_OUT}"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "CMakeFiles"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeCache.txt"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeDoxyfile.in"
            COMMAND ${CMAKE_COMMAND} -E remove "CMakeDoxygenDefaults.cmake"
            COMMAND ${CMAKE_COMMAND} -E remove "libimage.a"
            COMMAND ${CMAKE_COMMAND} -E remove "cmake_install.cmake"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "doc_doxygen"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "quienesquien_autogen"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
)            



