# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine Dependencies
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

set ( BIN_DIR "${CMAKE_SOURCE_DIR}/bin" )
set ( LIBS_DIR "${CMAKE_SOURCE_DIR}/libs" )

# - - - - - - - - - - - - - - - - - GLM - - - - - - - - - - - - - - - - - - - - - -

set ( GLM_LIB_DIR "${LIBS_DIR}/glm" )
include_directories ( GLM_LIB_DIR )

# - - - - - - - - - - - - - - - - - Android API  - - - - - - - - - - - - - - - - - -

# Add Android Log Library
find_library( log-lib log )

# Android Lib
find_library( android_lib android )

# - - - - - - - - - - - - - - - - OpenGL - - - - - - - - - - - - - - - - - - - - - -

if ( BT_GL_VERSION_MAJOR EQUAL 2 )
    find_library( OpenGL GLESv2 )
elseif ( BT_GL_VERSION_MAJOR EQUAL 3 )
    find_library( OpenGL GLESv3 )
else ( BT_GL_VERSION_MAJOR EQUAL 2 )
    message ( FATAL_ERROR "${PROJECT_NAME} - OpenGL library version selector configuration required." )
endif ( BT_GL_VERSION_MAJOR EQUAL 2 )

if ( NOT EXISTS ${OpenGL} )
    message ( STATUS "${PROJECT_NAME} - OpenGL ES library not found !" )
endif ( NOT EXISTS ${OpenGL} )

if ( BT_CMAKE_DEBUG )
    message ( STATUS "${PROJECT_NAME} - OpenGL ES library found at ${OpenGL}" )
endif ( BT_CMAKE_DEBUG )

# - - - - - - - - - - - - - - - - zlib - - - - - - - - - - - - - - - - - - - - - - -

# Include zlib CMake
set ( ZLIB_DIR "${LIBS_DIR}/zlib" )
set ( ZLIB_INCLUDES_DIR "${ZLIB_DIR}/zlib/include" )
add_subdirectory ( "${ZLIB_DIR}/zlib" )

# - - - - - - - - - - - - - - - - OpenSL - - - - - - - - - - - - - - - - - - - - - -

# - - - - - - - - - - - - - - - - SOIL - - - - - - - - - - - - - - - - - - - - - - -

# - - - - - - - - - - - - - - - - - btEngine - - - - - - - - - - - - - - - - - - - -

# btEngine
set ( BT_CMAKE_DEBUG ON )
add_subdirectory ( "engine/btSDK" )