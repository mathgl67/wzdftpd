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

#ifndef __WZD_SITE_GROUP__
#define __WZD_SITE_GROUP__

int do_site_group(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);
int do_site_grpadd(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);
int do_site_grpdel(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);
int do_site_grpren(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);

int do_site_ginfo(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);
int do_site_gsinfo(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);

int do_site_grpaddip(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);
int do_site_grpdelip(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);

int do_site_grpratio(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);

int do_site_grpchange(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);

int do_site_grpkill(wzd_string_t *ignored, wzd_string_t *command_line, wzd_context_t * context);


/* Help commands */
int do_site_help_grpadd(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpdel(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpren(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpaddip(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpdelip(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpratio(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_grpchange(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);
int do_site_help_group(wzd_string_t *cname, wzd_string_t *command_line, wzd_context_t * context);


#endif /* __WZD_SITE_GROUP__ */
