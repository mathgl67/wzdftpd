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

#ifndef __WZD_CLIENT_THREAD__
#define __WZD_CLIENT_THREAD__

int clear_read(int sock, char *msg, size_t length, int flags, unsigned int timeout, void * vcontext);
int clear_write(int sock, const char *msg, size_t length, int flags, unsigned int timeout, void * vcontext);

void * clientThreadProc(void *arg);

void client_die(wzd_context_t * context);

int command_list_init(wzd_command_t **list);
int command_list_add(wzd_command_t **list, const char *name, wzd_function_command_t fct, wzd_function_command_t helper);
void command_list_cleanup(wzd_command_t **list);
wzd_command_t * command_list_find(const char *name);

#define GLOBAL_FEATURES  " NON-FREE FTPD SUCKS\n MDTM\n SIZE\n SITE\n REST\n PRET\n XCRC\n XMD5\n"
#ifdef HAVE_OPENSSL
#define TEMP_FEAT  GLOBAL_FEATURES " AUTH TLS\n PBSZ\n PROT\n"
#else
#define TEMP_FEAT GLOBAL_FEATURES
#endif

#ifdef HAVE_UTF8
#define TEMP_FEAT2  TEMP_FEAT" UTF8\n"
#else
#define TEMP_FEAT2 TEMP_FEAT
#endif

#define SUPPORTED_FEATURES (TEMP_FEAT2 "End")

#endif /* __WZD_CLIENT_THREAD__ */
