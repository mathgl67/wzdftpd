#ifndef __WZD_MISC__
#define __WZD_MISC__

char * time_to_str(time_t time);

void chop(char *s);

/* returns 1 if file is perm file */
int is_perm_file(const char *filename);

/* formats the message if multiline, e.g 220-hello\r\n220 End */
void v_format_message(int code, unsigned int length, char *buffer, va_list argptr);
void format_message(int code, unsigned int length, char *buffer, ...);

/* Bandwidth limitation */

wzd_bw_limiter * limiter_new(int maxspeed);
void limiter_add_bytes(wzd_bw_limiter *l, int byte_count, int force_check);
void limiter_free(wzd_bw_limiter *l);

/* cookies */
int cookies_replace(char * buffer, unsigned int buffersize, void * void_param, void * void_context);

/* used to translate text to binary word for rights */
unsigned long right_text2word(const char * text);

/* IP allowing */
int ip_add(wzd_ip_t **list, const char *newip);
int ip_inlist(wzd_ip_t *list, const char *ip);
void ip_free(wzd_ip_t *list);

int user_ip_add(wzd_user_t * user, const char *newip);
int user_ip_inlist(wzd_user_t * user, const char *ip);

int group_ip_add(wzd_group_t * group, const char *newip);
int group_ip_inlist(wzd_group_t * group, const char *ip);

#endif /* __WZD_MISC__ */

