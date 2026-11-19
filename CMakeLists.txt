cmake_minimum_required(VERSION 3.21)

if(DEFINED LIB_PARENT_TARGET) # Use same target

  target_include_directories( ${LIB_PARENT_TARGET} PRIVATE include)

  target_sources( ${LIB_PARENT_TARGET} PRIVATE
      src/Drv_MPU60X0.c)

else() # Create new target

  # add name of the library
  set(LIBRARY_NAME DRVMPU60X0)

  # Bare-metal toolchains (arm-none-eabi) cannot link a test executable without
  # startup code / linker script: let CMake's compiler check build a static lib instead.
  set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

  PROJECT(${LIBRARY_NAME} C ASM)

  if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "This project [${LIBRARY_NAME}] has a top-level one called [${CMAKE_PROJECT_NAME}]")
  else()
    message(STATUS "[${LIBRARY_NAME}] stand-alone build: using cfg_ex/ and module_libs/")

     # GenUtl (fetched by west into module_libs/)
    add_library(GENUTL STATIC
      ${CMAKE_CURRENT_SOURCE_DIR}/module_libs/src/GenUtl.c
    )
    target_include_directories(GENUTL PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/module_libs/include
    )

    # Example configuration 
    add_library(${LIBRARY_NAME}_CFG STATIC
      ${CMAKE_CURRENT_SOURCE_DIR}/cfg_ex/Drv_MPU60X0_Cfg.c
    )
    target_include_directories(${LIBRARY_NAME}_CFG
      PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/cfg_ex
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(${LIBRARY_NAME}_CFG PUBLIC GENUTL)

  endif()

  # add the library source files
  add_library(${LIBRARY_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Drv_MPU60X0.c
    # ...
  )

  # add private include directory if necessary
  target_include_directories(${LIBRARY_NAME}
    PRIVATE
    # ...
  )

  # add public include directory
  target_include_directories(${LIBRARY_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/module_libs
  )

  # add library with cfg include
  target_link_libraries(${LIBRARY_NAME} PUBLIC ${LIBRARY_NAME}_CFG)

  target_link_libraries(${LIBRARY_NAME} PUBLIC m)

endif()
