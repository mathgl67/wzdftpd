INCLUDE_DIRECTORIES(${WZDFTPD_SOURCE_DIR}
	${WZDFTPD_SOURCE_DIR}/libwzd-core
	${WZDFTPD_BINARY_DIR}
	)

ADD_DEFINITIONS(-DHAVE_CONFIG_H)

ADD_LIBRARY (libwzd_pam SHARED
	libpam_main.c
	libpam.def
	)

if (CYGWIN OR NOT WIN32)
  SET_TARGET_PROPERTIES(libwzd_pam PROPERTIES PREFIX "")
endif (CYGWIN OR NOT WIN32)

SET(libwzd_pam_LIBS libwzd_core)

IF(PAM_FOUND)
  SET(libwzd_pam_LIBS ${libwzd_pam_LIBS} ${PAM_LIBRARIES})
ENDIF(PAM_FOUND)

TARGET_LINK_LIBRARIES (libwzd_pam ${libwzd_pam_LIBS})

INSTALL(TARGETS libwzd_pam DESTINATION ${BACKENDS_INSTALL_PATH})
