# - Try to find the OpenSSL encryption library
# Once done this will define
#
#  OPENSSL_FOUND - system has the OpenSSL library
#  OPENSSL_INCLUDE_DIR - the OpenSSL include directory
#  OPENSSL_LIBRARIES - The libraries needed to use OpenSSL

if (OPENSSL_INCLUDE_DIR AND OPENSSL_LIBRARIES)

  # in cache already
  SET(OPENSSL_FOUND TRUE)

else (OPENSSL_INCLUDE_DIR AND OPENSSL_LIBRARIES)

  FIND_PATH(OPENSSL_INCLUDE_DIR openssl/ssl.h
     /usr/include/
     /usr/local/include/
  )

  if(WIN32 AND MSVC)
      # /MD and /MDd are the standard values - if somone wants to use
      # others, the libnames have to change here too

      FIND_LIBRARY(SSL_EAY_DEBUG NAMES ssleay32MDd )
      FIND_LIBRARY(SSL_EAY_RELEASE NAMES ssleay32MD ssl ssleay32)
      FIND_LIBRARY(LIB_EAY_DEBUG NAMES libeay32MDd )
      FIND_LIBRARY(LIB_EAY_RELEASE NAMES libeay32MD ssl libeay32)

      IF(MSVC_IDE)
        IF(SSL_EAY_DEBUG AND SSL_EAY_RELEASE)
            SET(OPENSSL_LIBRARIES optimized ${SSL_EAY_RELEASE} ${LIB_EAY_RELEASE} debug ${SSL_EAY_DEBUG} ${LIB_EAY_DEBUG})
        ELSE(SSL_EAY_DEBUG AND SSL_EAY_RELEASE)
          MESSAGE(FATAL_ERROR "Could not find the debug and release version of openssl")
        ENDIF(SSL_EAY_DEBUG AND SSL_EAY_RELEASE)
      ELSE(MSVC_IDE)
        STRING(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
        IF(CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
          SET(OPENSSL_LIBRARIES ${SSL_EAY_DEBUG} ${LIB_EAY_DEBUG})
        ELSE(CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
          SET(OPENSSL_LIBRARIES ${SSL_EAY_RELEASE} ${LIB_EAY_RELEASE})
        ENDIF(CMAKE_BUILD_TYPE_TOLOWER MATCHES debug)
      ENDIF(MSVC_IDE)
      MARK_AS_ADVANCED(SSL_EAY_DEBUG SSL_EAY_RELEASE LIB_EAY_DEBUG LIB_EAY_RELEASE)
  else(WIN32 AND MSVC)

   FIND_LIBRARY(OPENSSL_LIBRARIES NAMES ssl ssleay32 ssleay32MD libeay32 libeay32MD
      PATHS
      /usr/lib
      /usr/local/lib
   )

  endif(WIN32 AND MSVC)

  if (OPENSSL_INCLUDE_DIR AND OPENSSL_LIBRARIES)
     set(OPENSSL_FOUND TRUE)
  endif (OPENSSL_INCLUDE_DIR AND OPENSSL_LIBRARIES)

  if (OPENSSL_FOUND)
     if (NOT OpenSSL_FIND_QUIETLY)
        message(STATUS "Found OpenSSL: ${OPENSSL_LIBRARIES}")
     endif (NOT OpenSSL_FIND_QUIETLY)
  else (OPENSSL_FOUND)
     if (OpenSSL_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find OpenSSL")
     endif (OpenSSL_FIND_REQUIRED)
  endif (OPENSSL_FOUND)

  MARK_AS_ADVANCED(OPENSSL_INCLUDE_DIR OPENSSL_LIBRARIES)

endif (OPENSSL_INCLUDE_DIR AND OPENSSL_LIBRARIES)
