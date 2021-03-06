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

set ( BTXD_HEADERS "game/android/BTXDAndroid.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BTXD_SOURCES "game/android/BTXDAndroid.cpp" )

# =================================================================================
# LIBRARIES
# =================================================================================

include ( "cmake/libs.android.cmake" )

# =================================================================================
# MODULES
# =================================================================================

# CORE
add_subdirectory ( "game/core" )

# =================================================================================
# BUILD
# =================================================================================

# Create SHARED Library Object for Android
add_library ( btxdandroid-lib SHARED ${BTXD_HEADERS} ${BTXD_SOURCES} )

# Include btEngine
include_directories("engine/btSDK/public")

# Include BTXD.Core
include_directories ( "game/core" )

# Link SHARED Library Object
target_link_libraries ( btxdandroid-lib btxdGame_Core ${log-lib} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
