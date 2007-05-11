# - Find PostgreSQL
# Find the PostgreSQL includes and client library
# This module defines
#  POSTGRESQL_INCLUDE_DIR, where to find POSTGRESQL.h
#  POSTGRESQL_LIBRARIES, the libraries needed to use POSTGRESQL.
#  POSTGRESQL_FOUND, If false, do not try to use PostgreSQL.
#
# Copyright (c) 2006, Jaroslaw Staniek, <js@iidea.pl>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
   set(POSTGRESQL_FOUND TRUE)

else(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)

  find_path(POSTGRESQL_INCLUDE_DIR libpq-fe.h
      /usr/include/pgsql
      /usr/local/include/pgsql
      /usr/include/postgresql
      $ENV{ProgramFiles}/PostgreSQL/*/include
      $ENV{SystemDrive}/PostgreSQL/*/include
      )

  find_library(POSTGRESQL_LIBRARIES NAMES pq libpq
      PATHS
      /usr/lib
      /usr/local/lib
      /usr/lib/postgresql
      $ENV{ProgramFiles}/PostgreSQL/*/lib
      $ENV{SystemDrive}/PostgreSQL/*/lib
      )
      
  # This is required to detect the .a extensions on the libraries for Windows
  if(NOT POSTGRESQL_LIBRARIES)
    find_path(POSTGRESQL_LIBRARIES libpq.a
      $ENV{ProgramFiles}/PostgreSQL/*/lib
      $ENV{SystemDrive}/PostgreSQL/*/lib
      )
  endif(NOT POSTGRESQL_LIBRARIES)

  if(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
    set(POSTGRESQL_FOUND TRUE)
    message(STATUS "Found PostgreSQL: ${POSTGRESQL_INCLUDE_DIR}, ${POSTGRESQL_LIBRARIES}")
  else(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
    set(POSTGRESQL_FOUND FALSE)
    message(STATUS "PostgreSQL not found.")
  endif(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)

  mark_as_advanced(POSTGRESQL_INCLUDE_DIR POSTGRESQL_LIBRARIES)

endif(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
