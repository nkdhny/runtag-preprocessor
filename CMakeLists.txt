project(runtagpreprocessor)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)
find_package( OpenCV REQUIRED )

find_program(PYTHON "python")

set(RUNTAG_LIBRARY_DIR "/home/nkdhny/Documents/runtag/runtagdetector/Debug/output")
set(RUNTAG_INCLUDE_DIR "/home/nkdhny/Documents/runtag/runtagdetector/Debug/output/include")


if (PYTHON)
    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
    set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/runtag/__init__.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

    configure_file(${SETUP_PY_IN} ${SETUP_PY})
    file(COPY runtag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON} ${SETUP_PY} build
                       COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                       DEPENDS ${DEPS})

    add_custom_target(pypreprocessor ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")
endif()
