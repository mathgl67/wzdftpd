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

#ifndef __WZD_MD5CRYPT__
#define __WZD_MD5CRYPT__

/*! \addtogroup libwzd_auth
 *  @{
 */

#define MD5_MAGIC "$1$"
#define MD5_MAGIC_LEN 3

char * md5_crypt(const char *pw, const char *salt);
char * md5_hash_r(const char *pw, char * out, size_t len);

extern unsigned char itoa64[];
/*! @} */

#endif /* __WZD_MD5CRYPT__ */

