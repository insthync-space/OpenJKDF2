set(ZLIB_HOST_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}_ROOT
    ${CMAKE_BINARY_DIR}/zlib/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}
)
set(ZLIB_HOST_ROOT ${ZLIB_HOST_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}_ROOT})
set(ZLIB_HOST_TARGET_NAME ZLIB_HOST_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR})
set(ZLIB_HOST_BINARY_DIR ${ZLIB_HOST_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}_ROOT})
set(ZLIB_HOST_LIBRARY_TARGET_NAME ZLIB::ZLIB_HOST_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR})

# *Replicate* variables generated by `FindZLIB`
set(ZLIB_HOST_FOUND TRUE)
set(ZLIB_HOST_INCLUDE_DIRS ${ZLIB_HOST_ROOT}/include)
set(ZLIB_HOST_LIBRARIES z)
if(CMAKE_HOST_WIN32 AND TARGET_WIN32)
    if(ZLIB_HOST_USE_STATIC_LIBS)
        set(ZLIB_HOST_LIBRARIES zlibstatic)
    else()
        set(ZLIB_HOST_LIBRARIES zlib)
    endif()
endif()

set(ZLIB_HOST_STATIC_LIBRARY_PATH ${ZLIB_HOST_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${ZLIB_HOST_LIBRARIES}${CMAKE_STATIC_LIBRARY_SUFFIX})
set(ZLIB_HOST_SHARED_LIBRARY_PATH ${ZLIB_HOST_ROOT}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${ZLIB_HOST_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX})
set(ZLIB_HOST_IMPORT_LIBRARY_PATH ${ZLIB_HOST_ROOT}/lib/${CMAKE_IMPORT_LIBRARY_PREFIX}${ZLIB_HOST_LIBRARIES}${CMAKE_IMPORT_LIBRARY_SUFFIX})

set(ZLIB_HOST_INSTALL_DIR ${ZLIB_HOST_BINARY_DIR})
ExternalProject_Add(
    ${ZLIB_HOST_TARGET_NAME}
    SOURCE_DIR          ${CMAKE_SOURCE_DIR}/lib/zlib
    BINARY_DIR          ${ZLIB_HOST_BINARY_DIR}
    INSTALL_DIR         ${ZLIB_HOST_INSTALL_DIR}
    UPDATE_DISCONNECTED TRUE
    CMAKE_ARGS          --install-prefix ${ZLIB_HOST_INSTALL_DIR}
                        ${ZLIB_HOST_TOOLCHAIN_ARG}
                        -DCMAKE_BUILD_TYPE:STRING=Release
    BUILD_BYPRODUCTS    ${ZLIB_HOST_STATIC_LIBRARY_PATH} ${ZLIB_HOST_DYNAMIC_LIBRARY_PATH} ${ZLIB_HOST_IMPORT_LIBRARY_PATH}
)

set(ZLIB_HOST_VERSION 1.2.13)
# Legacy vars, for the sake of completeness
set(ZLIB_HOST_VERSION_STRING ${ZLIB_HOST_VERSION})
string(REGEX REPLACE "^([0-9]+).*" "\\1" ZLIB_HOST_VERSION_MAJOR ${ZLIB_HOST_VERSION})
set(ZLIB_HOST_MAJOR_VERSION ${ZLIB_HOST_VERSION_MAJOR})
string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" ZLIB_HOST_VERSION_MINOR ${ZLIB_HOST_VERSION})
set(ZLIB_HOST_MINOR_VERSION ${ZLIB_HOST_VERSION_MINOR})
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" ZLIB_HOST_VERSION_PATCH ${ZLIB_HOST_VERSION})
set(ZLIB_HOST_PATCH_VERSION ${ZLIB_HOST_VERSION_PATCH})
set(ZLIB_HOST_VERSION_PATCH_TWEAK 0)

# *Replicate* targets generated by `FindZLIB`
file(MAKE_DIRECTORY ${ZLIB_HOST_INCLUDE_DIRS})
if(ZLIB_HOST_USE_STATIC_LIBS)
    add_library(${ZLIB_HOST_LIBRARY_TARGET_NAME} STATIC IMPORTED)
    set_property(
        TARGET ${ZLIB_HOST_LIBRARY_TARGET_NAME}
        PROPERTY IMPORTED_LOCATION ${ZLIB_HOST_STATIC_LIBRARY_PATH}
    )
else()
    add_library(${ZLIB_HOST_LIBRARY_TARGET_NAME} SHARED IMPORTED)
    set_target_properties(
        ${ZLIB_HOST_LIBRARY_TARGET_NAME} PROPERTIES
        IMPORTED_LOCATION ${ZLIB_HOST_SHARED_LIBRARY_PATH}
        IMPORTED_IMPLIB   ${ZLIB_IMPORT_STATIC_LIBRARY_PATH}
    )
    target_include_directories(${ZLIB_HOST_LIBRARY_TARGET_NAME} INTERFACE ${ZLIB_HOST_INCLUDE_DIR})
    target_link_directories(${ZLIB_HOST_LIBRARY_TARGET_NAME} INTERFACE ${ZLIB_HOST_INCLUDE_DIR}/../lib)
endif()
add_dependencies(${ZLIB_HOST_LIBRARY_TARGET_NAME} ${ZLIB_HOST_TARGET_NAME})
