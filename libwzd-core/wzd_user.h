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

#ifndef __WZD_USER_H__
#define __WZD_USER_H__

/** @brief User definition
 */
struct wzd_user_t {
  uid_t                  uid;
  u16_t                  backend_id;
  char                   username[HARD_USERNAME_LENGTH];
  char                   userpass[MAX_PASS_LENGTH];
  char                   rootpath[WZD_MAX_PATH];
  char                   tagline[MAX_TAGLINE_LENGTH];
  unsigned int           group_num;
  unsigned int           groups[MAX_GROUPS_PER_USER];
  u32_t                  max_idle_time;
  wzd_perm_t             userperms;      /**< @brief default permissions */
  char                   flags[MAX_FLAGS_NUM];
  u32_t                  max_ul_speed;
  u32_t                  max_dl_speed;   /**< @brief bytes / sec */
  unsigned short         num_logins;     /**< @brief number of simultaneous logins allowed */
  struct wzd_ip_list_t * ip_list;
  wzd_stats_t            stats;
  u64_t                  credits;
  unsigned int           ratio;
  unsigned short         user_slots;     /**< @brief user slots for gadmins */
  unsigned short         leech_slots;    /**< @brief leech slots for gadmins */
  time_t                 last_login;
};

/** \brief Allocate a new empty structure for a user
 */
wzd_user_t * user_allocate(void);

/** \brief Initialize members of struct \a user
 */
void user_init_struct(wzd_user_t * user);

/** \brief Free memory used by a \a user structure
 */
void user_free(wzd_user_t * user);

/** \brief Register a user to the main server
 * \return The uid of the registered user, or -1 on error
 */
uid_t user_register(wzd_user_t * user, u16_t backend_id);

/** \brief Update a registered user atomically. Datas are copied,
 * and old user is freed.
 * A pointer to the old user is still valid (change is done in-place)
 * If the uid had changed, the user will be moved
 * \return 0 if ok
 */
int user_update(uid_t uid, wzd_user_t * new_user);

/** \brief Unregister a user to the main server
 * The \a user struct must be freed using user_free()
 * \warning Unregistering a user at runtime can break the server if the user is being used
 * \return The unregistered user structure, or NULL on error
 */
wzd_user_t * user_unregister(uid_t uid);

/** \brief Free memory used to register users
 * \warning Also free ALL registered users !
 */
void user_free_registry(void);

/** \brief Get registered user using the \a uid
 * \return The user, or NULL
 */
wzd_user_t * user_get_by_id(uid_t uid);

/** \brief Get registered user using the \a name
 * \return The user, or NULL
 */
wzd_user_t * user_get_by_name(const char * username);

/** \brief Get list or users register for a specific backend
 * The returned list is terminated by -1, and must be freed with wzd_free()
 */
uid_t * user_get_list(u16_t backend_id);

/** \brief Find the first free uid, starting from \a start
 */
uid_t user_find_free_uid(uid_t start);

/** \brief Add an ip to the list of authorized/forbidden ips
 * \return 0 if ok
 */
int user_ip_add(wzd_user_t * user, const char * ip, int is_authorized);

#endif /* __WZD_USER_H__ */
