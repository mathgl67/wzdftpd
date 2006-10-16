INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)

CHECK_INCLUDE_FILES ("execinfo.h" HAVE_EXECINFO_H)
CHECK_INCLUDE_FILES ("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILES ("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES ("inttypes.h" HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES ("unistd.h" HAVE_UNISTD_H)
CHECK_INCLUDE_FILES ("utime.h" HAVE_UTIME_H)

CHECK_INCLUDE_FILES ("dl.h" HAVE_DL_H)
CHECK_INCLUDE_FILES ("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILES ("malloc.h" HAVE_MALLOC_H)
CHECK_INCLUDE_FILES ("sys/param.h;sys/mount.h" HAVE_SYS_MOUNT_H)
CHECK_INCLUDE_FILES ("sys/statvfs.h" HAVE_SYS_STATVFS_H)

CHECK_INCLUDE_FILES ("pthread.h" HAVE_PTHREAD)

CHECK_FUNCTION_EXISTS("backtrace" HAVE_BACKTRACE)
CHECK_FUNCTION_EXISTS("inet_ntoa" HAVE_INET_NTOA)
CHECK_FUNCTION_EXISTS("inet_ntop" HAVE_INET_NTOP)
CHECK_FUNCTION_EXISTS("inet_pton" HAVE_INET_PTON)
CHECK_FUNCTION_EXISTS("regcomp" HAVE_REGCOMP)
CHECK_FUNCTION_EXISTS("strlcat" HAVE_STRLCAT)
CHECK_FUNCTION_EXISTS("strptime" HAVE_STRPTIME)
CHECK_FUNCTION_EXISTS("strtok_r" HAVE_STRTOK_R)
CHECK_FUNCTION_EXISTS("strtoull" HAVE_STRTOULL)
CHECK_FUNCTION_EXISTS("statvfs" HAVE_STATVFS)

# unicode
IF (WITH_UTF8)
CHECK_INCLUDE_FILES ("iconv.h" HAVE_ICONV)
CHECK_INCLUDE_FILES ("langinfo.h" HAVE_LANGINFO_CODESET)
CHECK_INCLUDE_FILES ("wchar.h" HAVE_WCHAR_H)
ENDIF (WITH_UTF8)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

