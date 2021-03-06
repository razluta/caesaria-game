project(libpng)

file(GLOB PNG_HEADERS_LIST "*.h")
file(GLOB PNG_SOURCES_LIST "*.c")

include_directories(${ZLIB_INCLUDE_DIR})

add_library(${PROJECT_NAME} STATIC ${PNG_SOURCES_LIST})

#target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARY})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(X32_BUILD)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
endif()

# Expose public includes to other through cache variable.
set(PNG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(PNG_LIBRARY ${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Library Name" FORCE)
