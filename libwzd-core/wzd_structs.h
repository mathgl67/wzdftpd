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

#ifndef __WZD_STRUCTS__
#define __WZD_STRUCTS__

#include "wzd_hardlimits.h"

#include "wzd_types.h"

/*********************** ERRORS ***************************/

typedef enum {
  E_OK=0,

  E_NO_DATA_CTX,	/**< no data connection available */

  E_PARAM_NULL,		/**< parameter is NULL */
  E_PARAM_BIG,		/**< parameter is too long */
  E_PARAM_INVALID,	/**< parameter is invalid */

  E_WRONGPATH,		/**< path is invalid */

  E_NOTDIR,		/**< not a directory */
  E_ISDIR,		/**< is a directory */

  E_NOPERM,		/**< not enough perms */

  E_TIMEOUT,		/**< timeout on control connection */
  E_DATATIMEOUT,	/**< timeout on data connection */
  E_CONNECTTIMEOUT,	/**< timeout on connect() */
  E_PASV_FAILED,	/**< pasv connection failed */
  E_PORT_INVALIDIP,	/**< invalid address in PORT */
  E_XFER_PROGRESS,	/**< transfer in progress */
  E_XFER_REJECTED,	/**< transfer explicitely rejected by, for ex., script */

  E_CREDS_INSUFF,	/**< insufficient credits */

  E_USER_REJECTED,	/**< user rejected */
  E_USER_NO_HOME,	/**< user has no homedir */
  E_USER_NOIP,		/**< ip not allowed */
  E_USER_MAXUSERIP,	/**< max number of ip reached for user */
  E_USER_MAXGROUPIP,	/**< max number of ip reached for group */
  E_USER_CLOSED,	/**< site is closed for this login */
  E_USER_DELETED,	/**< user have been deleted */
  E_USER_NUMLOGINS,	/**< user has reached user num_logins limit */
  E_USER_TLSFORCED,	/**< user must be in TLS mode */

  E_GROUP_NUMLOGINS,	/**< user has reached group num_logins limit */

  E_PASS_REJECTED,	/**< wrong pass */

  E_FILE_NOEXIST,	/**< file does not exist */
  E_FILE_FORBIDDEN,	/**< access to file is forbidden */
  E_FILE_TYPE,	        /**< file has wrong type for operation */

  E_USER_IDONTEXIST,	/**< server said i don't exist ! */
  E_USER_ICANTSUICIDE,	/**< user is trying to kill its connection ! */
  E_USER_NOBODY,	/**< no user was matched by action */

  E_MKDIR_PARSE,	/**< directory name parsing gives errors */
  E_MKDIR_PATHFILTER,	/**< dirname rejected by pathfilter */

  E_COMMAND_FAILED,     /**< system command failed, check errno */
} wzd_errno_t;

/*********************** RIGHTS ***************************/

#define RIGHT_NONE      0x00000000

#define RIGHT_LIST      0x00000001
#define RIGHT_RETR      0x00000002
#define RIGHT_STOR      0x00000004

#define RIGHT_DELE      0x00000010


/* other rights - should not be used directly ! */
#define RIGHT_CWD       0x00010000
#define RIGHT_MKDIR     0x00020000
#define RIGHT_RMDIR     0x00040000
#define RIGHT_RNFR      0x00200000

typedef unsigned long wzd_perm_t;

/******************** BANDWIDTH LIMIT *********************/

/** @brief Limit bandwidth
 */
typedef struct limiter
{
  u32_t maxspeed;
#ifndef WIN32
  struct timeval current_time;
#else
  struct _timeb current_time;
#endif
  int bytes_transfered;
  float current_speed;
} wzd_bw_limiter;

/*********************** SITE *****************************/

/** @brief names of files used by site commands
 */
typedef struct {
  char * file_ginfo;
  char * file_group;
  char * file_groups;
  char * file_help;
  char * file_rules;
  char * file_swho;
  char * file_user;
  char * file_users;
  char * file_vfs;
  char * file_who;
} wzd_site_config_t;

/* opaque struct */
typedef struct wzd_site_fct_t wzd_site_fct_t;

/********************* IP CHECKING ************************/
typedef struct _wzd_ip_t {
  char  * regexp;
  struct _wzd_ip_t * next_ip;
} wzd_ip_t;

/************************ VFS *****************************/
typedef struct _wzd_vfs_t {
  char	* virtual_dir;
  char	* physical_dir;

  char	* target;

  struct _wzd_vfs_t	* prev_vfs, * next_vfs;
} wzd_vfs_t;

/*********************** DATA *****************************/
typedef enum {
  DATA_PORT,
  DATA_PASV
} data_mode_t;

/*********************** STATS ****************************/
/** @brief User statistics: number of files downloaded, etc
 */
typedef struct {
  u64_t             bytes_ul_total;
  u64_t             bytes_dl_total;
  unsigned long		files_ul_total;
  unsigned long		files_dl_total;
} wzd_stats_t;

/********************** USER, GROUP ***********************/

/** @brief User definition
 */
typedef struct {
  u32_t                 uid;
  char                  username[HARD_USERNAME_LENGTH];
  char			userpass[MAX_PASS_LENGTH];
  char                  rootpath[WZD_MAX_PATH];
  char                  tagline[MAX_TAGLINE_LENGTH];
  unsigned int          group_num;
  unsigned int          groups[MAX_GROUPS_PER_USER];
  u32_t 	        max_idle_time;
  wzd_perm_t            userperms;      /**< @brief default permissions */
  char                  flags[MAX_FLAGS_NUM];
  u32_t                 max_ul_speed;
  u32_t                 max_dl_speed;   /**< @brief bytes / sec */
  unsigned short	num_logins;	/**< @brief number of simultaneous logins allowed */
  char			ip_allowed[HARD_IP_PER_USER][MAX_IP_LENGTH];
  wzd_stats_t		stats;
  u64_t         	credits;
  unsigned int		ratio;
  unsigned short	user_slots;	/**< @brief user slots for gadmins */
  unsigned short	leech_slots;	/**< @brief leech slots for gadmins */
  time_t		last_login;
} wzd_user_t;

/** @brief Group definition */
typedef struct {
  unsigned int          gid;
  char                  groupname[HARD_GROUPNAME_LENGTH];
  char                  tagline[MAX_TAGLINE_LENGTH];
  wzd_perm_t            groupperms;
  u32_t 		max_idle_time;
  unsigned short	num_logins;	/**< number of simultaneous logins allowed */
  u32_t                 max_ul_speed;
  u32_t                 max_dl_speed;
  unsigned int		ratio;
  char			ip_allowed[HARD_IP_PER_GROUP][MAX_IP_LENGTH];
  char			defaultpath[WZD_MAX_PATH];
} wzd_group_t;

/*********************** BACKEND **************************/

/** IMPORTANT:
 *
 * all validation functions have the following return code:
 *
 *   0 = success
 *
 *   !0 = failure
 *
 * the last parameter of all functions is a ptr to current user
 */


typedef struct {
  char * name;
  char * param;
  void * handle;
  uid_t (*back_validate_login)(const char *, wzd_user_t *);
  uid_t (*back_validate_pass) (const char *, const char *, wzd_user_t *);
  wzd_user_t * (*back_get_user)(uid_t uid);
  wzd_group_t * (*back_get_group)(gid_t gid);
  uid_t (*back_find_user) (const char *, wzd_user_t *);
  gid_t (*back_find_group) (const char *, wzd_group_t *);
  int (*back_chpass) (const char *, const char *);
  int (*back_mod_user) (const char *, wzd_user_t *, unsigned long);
  int (*back_mod_group) (const char *, wzd_group_t *, unsigned long);
  int (*back_commit_changes) (void);

  struct wzd_backend_t * b;
} wzd_backend_def_t;


/************************ FLAGS ***************************/

#define	FLAG_SITEOP	'O'
#define	FLAG_DELETED	'D'
#define	FLAG_IDLE	'I'
#define	FLAG_SEE_IP	's'
#define	FLAG_SEE_HOME	't'
#define	FLAG_HIDDEN	'H'
#define	FLAG_GADMIN	'G'
#define	FLAG_TLS	'k'	/**< explicit and implicit connections only */
#define	FLAG_TLS_DATA	'K'	/**< user must use encrypted data connection */
#define	FLAG_ANONYMOUS	'A'	/**< anonymous users cannot modify filesystem */
#define	FLAG_COLOR	'5'	/**< enable use of colors */

/************************ MODULES *************************/

typedef int (*void_fct)(void);

typedef struct _wzd_hook_t {
  unsigned long mask;

  char *	opt;	/* used by custom site commands */

  void_fct	hook;
  char *	external_command;

  struct _wzd_hook_t	*next_hook;
} wzd_hook_t;

typedef struct _wzd_module_t {
  char *	name;

  void *	handle;

  struct _wzd_module_t	*next_module;
} wzd_module_t;

/* defined in binary, combine with OR (|) */

/* see also event_tab[] in wzd_mod.c */

#define	EVENT_LOGIN		0x00000001
#define	EVENT_LOGOUT		0x00000002

#define	EVENT_PREUPLOAD		0x00000010
#define	EVENT_POSTUPLOAD	0x00000020
#define	EVENT_PREDOWNLOAD	0x00000040
#define	EVENT_POSTDOWNLOAD	0x00000080

#define	EVENT_PREMKDIR		0x00000100
#define	EVENT_MKDIR		0x00000200
#define	EVENT_PRERMDIR		0x00000400
#define	EVENT_RMDIR		0x00000800

#define	EVENT_PREDELE 		0x00004000
#define	EVENT_DELE 		0x00008000

#define	EVENT_SITE		0x00010000
#define	EVENT_CRONTAB		0x00100000

/************************ SECTIONS ************************/

typedef struct wzd_section_t wzd_section_t;
/** @brief Section: definition, properties */
struct wzd_section_t {
  char *        sectionname;
  char *        sectionmask;
  char *        sectionre;

/*  regex_t *	pathfilter;*/
  void *	pathfilter;

  struct wzd_section_t * next_section;
};

/********************** SERVER STATS **********************/

/** @brief Server statistics: number of connections, etc */
typedef struct {
  unsigned long num_connections; /**< @brief total # of connections since server start */
  unsigned long num_childs; /**< @brief total # of childs process created since server start */
} wzd_server_stat_t;

/********************** SERVER PARAMS *********************/

/** @brief Server parameters: stored in server global memory space,
 * accessible to every thread.
 */
typedef struct _wzd_param_t {
  char * name;
  void * param;
  unsigned int length;

  struct _wzd_param_t	* next_param;
} wzd_param_t;

/*************************** TLS **************************/

#ifndef HAVE_OPENSSL
# define SSL     void
# define SSL_CTX void
#else
# include <openssl/ssl.h>
# include <openssl/rand.h>
# include <openssl/err.h>
#endif

typedef enum { TLS_CLEAR, TLS_PRIV } ssl_data_t; /* data modes */

typedef enum { TLS_SERVER_MODE=0, TLS_CLIENT_MODE } tls_role_t; 

typedef enum { TLS_NOTYPE=0, TLS_EXPLICIT, TLS_STRICT_EXPLICIT, TLS_IMPLICIT } tls_type_t; 

typedef enum { TLS_NONE, TLS_READ, TLS_WRITE } ssl_fd_mode_t; 

typedef enum {
  WZD_INET4=1,
  WZD_INET6=2
} net_family_t;

/** @brief SSL connection objects */
typedef struct {
  SSL *         obj;
  ssl_data_t    data_mode;
  SSL *         data_ssl;
  ssl_fd_mode_t ssl_fd_mode;
} wzd_ssl_t;

typedef struct {
  void * session;
  void * data_session;
} wzd_tls_t;

typedef enum {
  ASCII=0,
  BINARY
} xfer_t;

/************************* CONTEXT ************************/

/** important - must not be fffff or d0d0d0, etc.
 * to make distinction with unallocated zone
 */
#define	CONTEXT_MAGIC	0x0aa87d45

/** context::connection_flags field */
#define	CONNECTION_TLS	0x00000040
#define	CONNECTION_UTF8	0x00000100

typedef int (*read_fct_t)(fd_t,char*,size_t,int,unsigned int,void *);
typedef int (*write_fct_t)(fd_t,const char*,size_t,int,unsigned int,void *);

#include "wzd_action.h"

/** @brief Connection state
 */
typedef enum {
  STATE_UNKNOWN=0,
  STATE_CONNECTING, /* waiting for ident */
  STATE_LOGGING,
  STATE_COMMAND,
  STATE_XFER
} connection_state_t;

/** @brief Client-specific data
 */
typedef struct _context_t {
  unsigned long	magic;

  unsigned char	hostip[16];
  char          ident[MAX_IDENT_LENGTH];
  connection_state_t state;
  unsigned char	exitclient;
  fd_t          controlfd;
  fd_t          datafd;
  data_mode_t   datamode;
  net_family_t  datafamily;
  unsigned long	pid_child;
  unsigned long	thread_id;
  int           portsock;
  fd_t          pasvsock;
  read_fct_t    read_fct;
  write_fct_t   write_fct;
  int           dataport;
  unsigned char dataip[16];
  u64_t         resume;
  unsigned long	connection_flags;
  char          currentpath[WZD_MAX_PATH];
  unsigned int	userid;
  xfer_t        current_xfer_type;
  wzd_action_t	current_action;
  struct last_file_t	last_file;
  char		last_command[HARD_LAST_COMMAND_LENGTH];
  char          * data_buffer;
/*  wzd_bw_limiter * current_limiter;*/
  wzd_bw_limiter current_ul_limiter;
  wzd_bw_limiter current_dl_limiter;
  time_t        login_time;
  time_t	idle_time_start;
  time_t	idle_time_data_start;
  wzd_ssl_t   	ssl;
  wzd_tls_t   	tls;
  tls_role_t    tls_role;
} wzd_context_t;

/********************** COMMANDS **************************/

#include "wzd_commands.h"

/************************ MAIN CONFIG *********************/

typedef struct wzd_backend_t wzd_backend_t;
#include "wzd_backend.h"

/* macros used with options */
#define CFG_OPT_DENY_ACCESS_FILES_UPLOADED  0x00000001
#define CFG_OPT_HIDE_DOTTED_FILES           0x00000002
#define CFG_OPT_USE_SYSLOG                  0x00000010
#define CFG_OPT_UTF8_CAPABLE                0x00001000


#define CFG_CLR_OPTION(c,opt)   (c)->server_opts &= ~(opt)
#define CFG_SET_OPTION(c,opt)   (c)->server_opts |= (opt)
#define CFG_GET_OPTION(c,opt)   ( (c)->server_opts & (opt) )


/** @brief Server config
 *
 * Contains all variables specific to a server instance.
 */
typedef struct {
  char *	pid_file;
  char *	config_filename;
  time_t	server_start;
  unsigned char	serverstop;
  unsigned char	site_closed;
  wzd_backend_def_t	backend;
  int		max_threads;
  char *	logfilename;
  unsigned int	logfilemode;
  FILE *	logfile;
  char *	xferlog_name;
  int		xferlog_fd;
  int		loglevel;
  char *        logdir;
  unsigned int  umask;
  char *	dir_message;
  unsigned int	mainSocket;
  fd_t		controlfd; /**< external control: named pipe, unix socket, or socket */
  unsigned char	ip[MAX_IP_LENGTH];
  unsigned char	dynamic_ip[MAX_IP_LENGTH];
  unsigned int	port;
  u32_t         pasv_low_range;
  u32_t         pasv_high_range;
  unsigned char	pasv_ip[16];
  int		login_pre_ip_check;
  wzd_ip_t	*login_pre_ip_allowed;
  wzd_ip_t	*login_pre_ip_denied;
  wzd_vfs_t	*vfs;
  wzd_hook_t	*hook;
  wzd_module_t	*module;
  unsigned int  data_buffer_length; /**< size of buffer used for transfers. This has a great impact on performances */
  unsigned long	server_opts;
  wzd_server_stat_t	stats;
  SSL_CTX *	tls_ctx;
  tls_type_t	tls_type;
  CHTBL          * commands_list;
  wzd_site_fct_t	* site_list;
  wzd_section_t		* section_list;
  wzd_param_t		* param_list;

  wzd_bw_limiter	global_ul_limiter;
  wzd_bw_limiter	global_dl_limiter;
  wzd_site_config_t	site_config;

  struct CHTBL * htab;
} wzd_config_t;

WZDIMPORT extern wzd_config_t *	mainConfig;
WZDIMPORT extern List * context_list;

/************************ LIST ****************************/

#define	LIST_TYPE_SHORT		0x0001
#define	LIST_TYPE_LONG		0x0010
#define	LIST_SHOW_HIDDEN	0x0100
typedef unsigned long list_type_t;


#endif /* __WZD_STRUCTS__ */