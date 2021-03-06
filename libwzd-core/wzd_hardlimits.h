/*
 * wzdftpd - a modular and cool ftp server
 * Copyright (C) 2002-2008  Pierre Chifflier
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * As a special exemption, Pierre Chifflier
 * and other respective copyright holders give permission to link this program
 * with OpenSSL, and distribute the resulting executable, without including
 * the source code for OpenSSL in the source distribution.
 */

#ifndef __WZD_HARD_LIMITS__
#define __WZD_HARD_LIMITS__

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define	DEFAULT_SERVER_TICK	1L
#define	DEFAULT_CLIENT_TICK	10L

#define	HARD_REACTION_TIME	1L

/* FIXME should be a variable */
#define	HARD_XFER_TIMEOUT	30L
#define	HARD_IDENT_TIMEOUT	5

#define	TRFMSG_INTERVAL		1000000


#define	HARD_THREADLIMIT	2000

#define	HARD_MSG_LIMIT		1024
#define	HARD_MSG_LENGTH_MAX	16384

#define	MAX_IP_LENGTH		128
#define	HARD_IP_PER_USER	8
#define	HARD_IP_PER_GROUP	8

#define	MAX_GROUPS_PER_USER	32

#define	MAX_FLAGS_NUM		32
#define	MAX_PASS_LENGTH		48

#define	MAX_TAGLINE_LENGTH	256


#define	HARD_PERMFILE		".dirinfo"

/* interval of time to check dynamic ip (default: 1 mns) */
#define	HARD_DYNAMIC_IP_INTVL	"*"

/* interval of time to commit backend */
#define	HARD_COMMIT_BACKEND_INTVL	"*"

#define	HARD_LS_BUFFERSIZE	4096

/** \brief Maximum number of entries the LIST command can return */
#define MAX_DIRECTORY_ENTRIES   65535

/* the maximum number of channels for log */
#define MAX_LOG_CHANNELS 64
/* the number of reserved channels (with special behaviour) */
#define RESERVED_LOG_CHANNELS 10

/* do NOT ever change the following ! */  
/* NOTE: WZD_MAX_PATH _must be_ <= HARD_LAST_COMMAND_LENGTH (which is usually WZD_BUFFER_LEN)
 * if not, you might get truncation of paths for events. */
#define WZD_BUFFER_LEN	1024
#define WZD_MAX_PATH 1024

#define	HARD_BACKEND_NAME_LENGTH	256
#define	HARD_LAST_COMMAND_LENGTH	(WZD_BUFFER_LEN)
#define	HARD_USERNAME_LENGTH		256
#define	HARD_GROUPNAME_LENGTH		128

#endif /* __WZD_HARD_LIMITS__ */
