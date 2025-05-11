cmake_minimum_required(VERSION 3.16)

project(ProyGen)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT 6.32 CONFIG REQUIRED)


include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file (GLOB macro_files 
      "*.mac"
)
file (COPY ${macro_files} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(mainProygen mainProygen.cc ${sources} ${headers})
target_link_libraries(mainProygen ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )

set(PRO_SCRIPTS
    salida_data1.root
  )

foreach(_script ${PRO_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(Proyecto DEPENDS mainProygen)
