# Package overloads
set(ACE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dep/acelite)
set(ACE_LIBRARY "ace")
set(BZIP2_LIBRARIES "bzip2")
set(ZLIB_LIBRARIES "zlib")

# We require at least Visual Studio 15 2017(aka 14.0) which has version nr 1900.		
IF(NOT FORCE_UNSUPPORTED_COMPILER AND MSVC_VERSION LESS 1900)		
  MESSAGE(FATAL_ERROR "Visual Studio 15 2017 or newer is required!")		
ENDIF()

# check the CMake preload parameters (commented out by default)

# overload CMAKE_INSTALL_PREFIX if not being set properly
#if( WIN32 )
#  if( NOT CYGWIN )
#    if( NOT CMAKE_INSTALL_PREFIX )
#      set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")
#    endif()
#  endif()
#endif()

include(${CMAKE_SOURCE_DIR}/cmake/compiler/msvc/settings.cmake)
