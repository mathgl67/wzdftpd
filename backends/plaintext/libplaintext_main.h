/* vi:ai:et:ts=8 sw=2
 */
/*
 * wzdftpd - a modular and cool ftp server
 * Copyright (C) 2002-2004  Pierre Chifflier
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

#ifndef __LIBWZD_PLAINTEXT_MAIN__
#define __LIBWZD_PLAINTEXT_MAIN__

gid_t FCN_FIND_GROUP(const char *name, wzd_group_t * group);




wzd_group_t * plaintext_get_group_from_gid(gid_t gid);

wzd_user_t * user_allocate_new(void);

wzd_group_t * group_allocate_new(void);


extern char * USERS_FILE;

extern List user_list;
extern List group_list;

extern unsigned int group_count, group_count_max;
extern unsigned int user_count, user_count_max;

#endif /* __LIBWZD_PLAINTEXT_MAIN__ */
