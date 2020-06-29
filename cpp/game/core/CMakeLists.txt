# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# BattleTanksXD.Core
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
set ( PROJECT_NAME "BattleTanksXD.Core" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "BattleTanksXD Core-Module." )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# HEADERS
# =================================================================================

set ( BTXD_CORE_HEADERS
        "game/BTXDGame.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BTXD_CORE_SOURCES
        "game/BTXDGame.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Add STATIC Library Object
add_library ( btxdGame_Core STATIC ${BTXD_CORE_HEADERS} ${BTXD_CORE_SOURCES} )

# Include btEngine
include_directories("../../engine/btSDK/public")

# Link
target_link_libraries ( btxdGame_Core btEngine )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
