/* vi:ai:et:ts=8 sw=2
 */
/*
 * wzdftpd - a modular and cool ftp server
 * Copyright (C) 2002-2003  Pierre Chifflier
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

/* XXX FIXME
 * IMPORTANT NOTES: this module does not like unloading,
 * it provokes a segfault at thread exit
 */

#include <stdio.h>

#ifdef _MSC_VER
#include <winsock2.h>
#include <direct.h>
#include <io.h>

#include "../../visual/gnu_regex_dist/regex.h"
#else
#include <dirent.h>
#include <sys/types.h>
#include <regex.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>



#include <tcl.h>

/*#include <wzd.h>*/
#include "wzd_structs.h"
#include "wzd_log.h"
#include "wzd_misc.h"
#include "wzd_libmain.h"
#include "wzd_mod.h" /* essential to define WZD_MODULE_INIT */

/***** Private vars ****/
static Tcl_Interp * interp=NULL;

/***** EVENT HOOKS *****/
int my_event_hook(unsigned long event_id, const char *p1, const char *p2);

/***********************/
/* WZD_MODULE_INIT     */

int WZD_MODULE_INIT(void)
{
  interp = Tcl_CreateInterp();
  if (!interp) {
    out_log(LEVEL_HIGH,"TCL could not create interpreter\n");
    return -1;
  }
/*  hook_add(&getlib_mainConfig()->hook,EVENT_SITE,(void_fct)&sfv_hook_site);*/
  out_log(LEVEL_INFO,"TCL module loaded\n");
  return 0;
}

void WZD_MODULE_CLOSE(void)
{
  Tcl_DeleteInterp(interp);
  interp = NULL;
/*  Tcl_Exit(0);*/
  out_log(LEVEL_INFO,"TCL module unloaded\n");
}

int my_event_hook(unsigned long event_id, const char *p1, const char *p2)
{
  fprintf(stderr,"*** ID: %lx, %s %s\n",event_id,
      (p1)?p1:"(NULL)",(p2)?p2:"(NULL)");
  return 0;
}

void moduletest(void)
{
  fprintf(stderr,"mainConfig: %lx\n",(unsigned long)getlib_mainConfig()->logfile);
  libtest();
  out_log(LEVEL_INFO,"max threads: %d\n",getlib_mainConfig()->max_threads);
}