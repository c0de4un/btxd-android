# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# BattleTanksXD.Android
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# =================================================================================
# CMake Meta-Data
# =================================================================================

cmake_minimum_required(VERSION 3.5)

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( PROJECT_NAME "BattleTanksXD.Android" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "BattleTanksXD for Android" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# HEADERS
# =================================================================================

set ( BTXD_HEADERS "game/BTXDAndroid.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BTXD_SOURCES "game/BTXDAndroid.cpp" )

# =================================================================================
# LIBRARIES
# =================================================================================

# Add Android Log Library
find_library( log-lib log )

# btEngine
add_definitions ( -DBT_DEBUG=1 )
add_definitions ( -DDEBUG=1 )
add_subdirectory ( "engine/btSDK" )

# =================================================================================
# BUILD
# =================================================================================

# Create SHARED Library Object for Android
add_library ( btxdandroid-lib SHARED ${BTXD_HEADERS} ${BTXD_SOURCES} )

# Include btEngine
include_directories("engine/btSDK/public")

# Link SHARED Library Object
target_link_libraries ( btxdandroid-lib btEngine ${log-lib} )