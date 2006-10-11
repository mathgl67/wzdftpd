PROJECT (WZDFTPD C)

# enable submission to Dart Testing Dashboard
INCLUDE(Dart)

# read version from file "VERSION" and trim CR/LF
FILE(READ "VERSION" VERSION)
STRING(REPLACE "\n" "" WZD_VERSION ${VERSION})

# split major, minor and revision
STRING(REGEX REPLACE "([0-9]+)[.]([0-9]+)[.](.*)$" "\\1" WZD_MAJOR ${WZD_VERSION})
STRING(REGEX REPLACE "([0-9]+)[.]([0-9]+)[.](.*)$" "\\2" WZD_MINOR ${WZD_VERSION})
STRING(REGEX REPLACE "([0-9]+)[.]([0-9]+)[.](.*)$" "\\3" WZD_REVISION ${WZD_VERSION})

SET(WZD_VERSION_LONG "wzdftpd ${CMAKE_SYSTEM_NAME} mt ${WZD_VERSION}")

IF (NOT WIN32)
  EXEC_PROGRAM("date"
      ARGS "+%Y%m%d"
      OUTPUT_VARIABLE DATE)
ENDIF (NOT WIN32)

IF (DATE)
  SET(WZD_BUILD_NUM "${DATE}")
ELSE (DATE)
  SET(WZD_BUILD_NUM "unknown")
ENDIF (DATE)

IF(WIN32)
SET(WZD_DEFAULT_CONF "wzd-win32.cfg")
ELSE(WIN32)
SET(WZD_DEFAULT_CONF "/etc/wzdftpd/wzd.cfg")
ENDIF(WIN32)


add_subdirectory(cmake)


# most of the following code is taken from http://websvn.kde.org/trunk/KDE/kdelibs/
# and adapted. Thanks KDE guys for your work !

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# make some more macros available
include (MacroLibrary)

# macro_optional_find_package() is the same as FIND_PACKAGE(<name>) but additionally
# creates an OPTION(WITH_<name>)
# so the checking for the software can be disabled via ccmake or -DWITH_<name>=OFF
macro_optional_find_package(GnuTLS)
macro_optional_find_package(MySQL)
IF (GNUTLS_FOUND)
  MESSAGE(STATUS "GnuTLS was found, disabling OpenSSL check. Use -DWITH_GNUTLS=OFF to disable GnuTLS")
ELSE (GNUTLS_FOUND)
  macro_optional_find_package(OpenSSL)
ENDIF (GNUTLS_FOUND)
macro_optional_find_package(PerlDev)
macro_optional_find_package(PostgreSQL)
macro_optional_find_package(TCLDev)
macro_optional_find_package(Zeroconf)

OPTION(WITH_IPV6 "enable IPv6 support" OFF)
OPTION(WITH_UTF8 "enable UTF-8 support" ON)

OPTION(WITH_TESTS "enable unit tests" ON)

find_package(Threads REQUIRED)
ADD_DEFINITIONS(-DWZD_MULTITHREAD)

#########################################################################
# Disallow in-source build
macro_ensure_out_of_source_build("wzdftpd requires an out of source build. Please create a separate build directory and run 'cmake path_to_wzdftpd [options]' there.")

# create config.h
include(ConfigureChecks)

# Configure options
SET(WZD_BUILD_OPTS "")

if (DEBUG)
  message(STATUS "Configuring for debug")
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "debug")
  ADD_DEFINITIONS(-DDEBUG)
  SET(CMAKE_BUILD_TYPE Debug)
else (DEBUG)
  message(STATUS "Configuring for release")
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "release")
  SET(CMAKE_BUILD_TYPE Release)
endif (DEBUG)

if (GNUTLS_FOUND)
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "tls")
  ADD_DEFINITIONS(-DHAVE_GNUTLS)
endif (GNUTLS_FOUND)

if (OPENSSL_FOUND)
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "ssl")
  ADD_DEFINITIONS(-DHAVE_OPENSSL)
endif (OPENSSL_FOUND)

if (WITH_IPV6)
  message(STATUS "Configuring for IPv6")
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "ipv6")
  ADD_DEFINITIONS(-DIPV6_SUPPORT)
endif (WITH_IPV6)

if (WITH_UTF8)
  message(STATUS "Configuring for UTF-8")
  SET(WZD_BUILD_OPTS  ${WZD_BUILD_OPTS} "utf8")
  ADD_DEFINITIONS(-DHAVE_UTF8)
endif (WITH_UTF8)

include(PlatformSpecific)

include(Installation)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/wzd_version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/wzd_version.h)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/wzdftpd/wzd.cfg.sample.cmake ${CMAKE_CURRENT_BINARY_DIR}/wzdftpd/wzd.cfg.sample)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/wzdftpd.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/wzdftpd.pc @ONLY)

add_subdirectory (libwzd-core)
add_subdirectory (wzdftpd)
add_subdirectory (backends)
add_subdirectory (modules)

add_subdirectory (libwzd)
add_subdirectory (tools)

IF (WITH_TESTS)
  ENABLE_TESTING()

  add_subdirectory (tests)
ENDIF (WITH_TESTS)

# export dependencies
EXPORT_LIBRARY_DEPENDENCIES(wzdftpd.cmake)

SET(doc_FILES AUTHORS ChangeLog COPYING INSTALL NEWS Permissions.ReadMeFirst README
  TLS.ReadMeFirst UPGRADING wzd_tls.cnf)

INSTALL(FILES ${doc_FILES} DESTINATION ${DOC_INSTALL_PATH})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/wzdftpd.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)