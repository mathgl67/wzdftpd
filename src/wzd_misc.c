#include "wzd.h"

char *time_to_str(time_t time)
{ /* This support functionw as written by George Shearer (Dr_Delete) */

  static char workstr[100];
  unsigned short int days=(time/86400),hours,mins,secs;
  hours=((time-(days*86400))/3600);
  mins=((time-(days*86400)-(hours*3600))/60);
  secs=(time-(days*86400)-(hours*3600)-(mins*60));

  workstr[0]=(char)0;
  if(days)
    sprintf(workstr,"%dd",days);
  if(hours)
    sprintf(workstr,"%s%s%dh",workstr,(workstr[0])?", ":"",hours);
  if(mins)
    sprintf(workstr,"%s%s%dm",workstr,(workstr[0])?", ":"",mins);
  if(secs)
    sprintf(workstr,"%s%s%ds",workstr,(workstr[0])?", ":"",secs);
  if (!days && !hours && !mins && !secs)
    sprintf(workstr,"0 seconds");

  return(workstr);
}

void chop(char *s)
{
  char *r;

  if ((r=(char*) strchr(s,'\r')))
    *r = '\0';
  if ((r=(char*) strchr(s,'\n')))
    *r = '\0';
}

/* returns 1 if file is perm file */
int is_perm_file(const char *filename)
{
  const char *endfile;

  if (filename) {
    endfile = filename + (strlen(filename) - strlen(HARD_PERMFILE));
    if (strlen(filename)>strlen(HARD_PERMFILE)) {
      if (strcasecmp(HARD_PERMFILE,endfile)==0)
        return 1;
    }
  }
  return 0;
}

#define WORK_BUF_LEN	8192

void v_format_message(int code, unsigned int length, char *buffer, va_list argptr)
{
  const char * token, *token2;
  const char * msg;
  char *ptr;
  unsigned int size;
  char work_buf[WORK_BUF_LEN];
  /* XXX 4096 should ALWAYS be >= length */

#ifdef DEBUG
  if (length > WORK_BUF_LEN) {
    fprintf(stderr,"*** WARNING *** message too long, will be truncated\n");
    length = WORK_BUF_LEN;
  }
#endif

  msg = getMessage(code);
  ptr = work_buf;

  /* first, format message */
  vsnprintf(work_buf,WORK_BUF_LEN,msg,argptr);

  /* adjust size, we will need more space to put the code and \r\n */
  length -= 7;
  
  if (!strpbrk(work_buf,"\r\n")) { /* simple case, msg on one line */
    snprintf(buffer,length,"%d %s\r\n",code,work_buf);
  }
  else { /* funnier, multiline */
    /* find first line break */
    token = strtok_r(work_buf,"\r\n",&ptr);

    /* first line begins by 123- */
    snprintf(buffer,length,"%d-%s\r\n",code,token);
    size = strlen(token);
    length = length - size - 6;
    buffer = buffer + size + 6;

    /* next line */
    token = strtok_r(NULL,"\r\n",&ptr);

    while (1) {
      size = strlen(token);
      /* find next token */
      token2 = strtok_r(NULL,"\r\n",&ptr);
      if (!token2) { /* no more line, remove the - */
	snprintf(buffer,length,"%d %s\r\n",code,token);
        break;
      }
      /* copy line into out buffer */
      snprintf(buffer,length,"%s\r\n",token);
      /* adjust length */
      length = length - size - 2;
      /* check remaining size */
      /* adjust buffer position */
      buffer = buffer + size + 2;
      /* loop */
      token = token2;
    }
  }
}

void format_message(int code, unsigned int length, char *buffer, ...)
{
  va_list argptr;

  va_start(argptr,buffer); /* note: ansi compatible version of va_start */

  v_format_message(code,length,buffer,argptr);
}


/************* BANDWIDTH LIMITATION *********/
wzd_bw_limiter * limiter_new(int maxspeed)
{
  wzd_bw_limiter *l_new;
  struct timezone tz;

  l_new = malloc(sizeof(wzd_bw_limiter));
  l_new->maxspeed = maxspeed;
  l_new->bytes_transfered = 0;
  gettimeofday(&(l_new->current_time),&tz);

  return l_new;
}

void limiter_add_bytes(wzd_bw_limiter *l, int byte_count, int force_check)
{
  long dif;
  struct timeval tv;
  struct timezone tz;

  if (!l) return;
  if (l->maxspeed == 0) return;

  l->bytes_transfered += byte_count;

  /* if at least 1 second of data is downloaded, assess the situation
   * and determine how much time to wait */
  if ( (l->bytes_transfered >= l->maxspeed) || force_check )
  {
    gettimeofday( &tv, &tz );
    dif = (tv.tv_sec - l->current_time.tv_sec) * 1000
      + (tv.tv_usec - l->current_time.tv_usec) / 1000;
    dif = (((1000L * l->bytes_transfered) / l->maxspeed) - dif) * 1000L;

    /* if usleep takes too long, this will compensate by
     * putting the expecting time after usleep into l->current_time
     * instead of reading the real time after an inacurrate
     * usleep, allowing the transfer to catch up */
    memcpy(&(l->current_time), &tv, sizeof(struct timeval));
    l->current_time.tv_usec += (dif % 1000000);
    l->current_time.tv_sec += (dif / 1000000);
fprintf(stderr,"dif: %ld\n",dif);
    if (dif > 0)
      usleep(dif);
    l->bytes_transfered = 0;
/*    l->bytes_transfered -= l->maxspeed;
    if (l->bytes_transfered < 0)
      l->bytes_transfered = 0;*/
  }
}

void limiter_free(wzd_bw_limiter *l)
{
  if (l)
    free(l);
}


/* cookies */
int cookies_replace(char * buffer, unsigned int buffersize, void * void_param, void * void_context)
{
  unsigned long length=0;
  wzd_context_t * context = void_context;
  char work_buffer[4096];
  char tmp_buffer[4096];
  char *srcptr, *dstptr;
  unsigned int bytes_written=0;
  char * cookie;
  unsigned int cookielength;
  unsigned int l;
  char c;
  wzd_context_t * param_context=NULL;
  wzd_user_t * user = NULL;
  wzd_user_t * context_user = NULL;

  if (buffersize > 4095) {
#ifdef DEBUG
    fprintf(stderr,"BUFFER SIZE too long !!\n");
#endif
    return -1;
  }

  memset(work_buffer,0,4096);
  srcptr = buffer;
  dstptr = work_buffer;

  while ( (c=*srcptr++) != '\0' ) {
    if ( c != '%' ) {
      *dstptr++ = c;
      bytes_written++;
      if (bytes_written == buffersize) {
        memcpy(buffer,work_buffer,buffersize);
        return 1;
      }
      continue;
    }

    if ( *srcptr == '%' ) {
      *dstptr++ = c;
      srcptr++;
      bytes_written++;
      continue;
    }

    length = 0;

    /* test if a number is written here - is the exact length the cookie will have */
    if ( *srcptr>='0' && *srcptr <= '9') {
      char *ptr;
      length = strtol(srcptr,&ptr,10);
      if (*ptr != '.') {
	length = 0;
      }
      srcptr = ptr + 1;
    }

    cookielength = 0;
    cookie = NULL;

    if (strncmp(srcptr,"my",2)==0)
    { param_context=context; srcptr += 2; }
    if (strncmp(srcptr,"user",4)==0)
    { param_context=void_param; srcptr += 4; }

    if (param_context == NULL) {
      /* happens when using %username and void_param is not correctly set */
      return 1;
    }

    if (mainConfig->backend.backend_storage == 0) {
      user = &mainConfig->user_list[param_context->userid];
      context_user = &mainConfig->user_list[context->userid];
#if BACKEND_STORAGE
    } else {
      user = &param_context->user;
      context_user = &context->user;
#endif
    }

    if (param_context) {
      /* name */
      if (strncmp(srcptr,"name",4)==0) {
        cookie = user->username;
        cookielength = strlen(cookie);
        srcptr += 4; /* strlen("name"); */
      }
      /* ip_allow */
      if (strncmp(srcptr,"ip_allow",8)==0) {
	char *endptr;
        srcptr += 8; /* strlen("ip_allow"); */
	l = strtoul(srcptr,&endptr,10);
	if (endptr-srcptr > 0) {
	  if (l < HARD_IP_PER_USER) {
            strncpy(tmp_buffer,user->ip_allowed[l],4095);
	  } else {
	    snprintf(tmp_buffer,4096,"Invalid ip index %u",l);
	  }
	  srcptr = endptr;
	} else {
	  snprintf(tmp_buffer,4096,"Invalid ip index");
	}
	cookie = tmp_buffer;
	cookielength = strlen(cookie);
      }
      /* ip */
      if (strncmp(srcptr,"ip",2)==0) {
        if (context_user->flags && strchr(context_user->flags,FLAG_SEE_IP)) {
        snprintf(tmp_buffer,4096,"%d.%d.%d.%d",param_context->hostip[0],
  	  param_context->hostip[1],param_context->hostip[2],
          param_context->hostip[3]);
        } else { /* not allowed to see */
          strcpy(tmp_buffer,"xxx.xxx.xxx.xxx");
        }
        cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 2; /* strlen("ip"); */
      }
      /* flags */
      if (strncmp(srcptr,"flags",5)==0) {
	if (user->flags && strlen(user->flags)>0) {
	  strncpy(tmp_buffer,user->flags,MAX_FLAGS_NUM);
	} else {
	  strcpy(tmp_buffer,"no flags");
	}
	cookie = tmp_buffer;
	cookielength = strlen(cookie);
	srcptr += 5; /* strlen("flags"); */
      }
      /* group */
      if (strncmp(srcptr,"group",5)==0) {
        wzd_group_t group, *gptr;
	int gid;
	int ret;
        if ( (user->group_num > 0)) {
          ret = backend_find_group(user->groups[0],&group,&gid);
	  if (mainConfig->backend.backend_storage==0) {
	    gptr = &mainConfig->group_list[ret];
	  } else {
	    gptr = &group;
	  }
          snprintf(tmp_buffer,4096,"%s",group.groupname);
        } else {
          strcpy(tmp_buffer,"nogroup");
        }
        cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 5; /* strlen("group"); */
      }
      /* home */
      if (strncmp(srcptr,"home",4)==0) {
        if (user->flags && strchr(user->flags,FLAG_SEE_IP)) {
          cookie = user->rootpath;
        } else { /* user not allowed to see */
          strcpy(tmp_buffer,"- some where -");
          cookie = tmp_buffer;
        }
        cookielength = strlen(cookie);
        srcptr += 4; /* strlen("home"); */
      }
      /* lastcmd */
      if (strncmp(srcptr,"lastcmd",7)==0) {
	strncpy(tmp_buffer,param_context->last_command,4095);
	/* modify special commands, to not appear explicit */
	if (strncasecmp(tmp_buffer,"site",4)==0) {
	  char * ptr;
	  ptr = strpbrk(tmp_buffer+5," \t");
	  if (ptr) {
	    memset(ptr+1,'x',strlen(tmp_buffer)-(ptr-tmp_buffer+1));
	  }
	}
        cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 7; /* strlen("lastcmd"); */
      }
      /* maxdl */
      if (strncmp(srcptr,"maxdl",5)==0) {
	snprintf(tmp_buffer,4096,"%ld",user->max_dl_speed);
	cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 5; /* strlen("maxdl"); */
      }
      /* maxidle */
      if (strncmp(srcptr,"maxidle",7)==0) {
	snprintf(tmp_buffer,4096,"%ld",user->max_idle_time);
	cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 7; /* strlen("maxidle"); */
      }
      /* maxul */
      if (strncmp(srcptr,"maxul",5)==0) {
	snprintf(tmp_buffer,4096,"%ld",user->max_ul_speed);
	cookie = tmp_buffer;
        cookielength = strlen(cookie);
        srcptr += 5; /* strlen("maxul"); */
      }
      /* tag */
      if (strncmp(srcptr,"tag",3)==0) {
        if (strlen(user->tagline) > 0) {
          cookie = user->tagline;
        } else {
          strcpy(tmp_buffer,"no tagline set");
          cookie = tmp_buffer;
        }
        cookielength = strlen(cookie);
        srcptr += 3; /* strlen("tag"); */
      }
    } /* if param_context */
    /* end of cookies */


    /* TODO if length is non null, we will proceed differently: write maximum length chars, and pad with spaces (FIXME) */
    if (length <= 0) {
      if (bytes_written+cookielength >= buffersize) {
        return 1;
      }
  
      memcpy(dstptr,cookie,cookielength);
      bytes_written += cookielength;
      dstptr += cookielength;
    } else { /* length > 0 */
      if (bytes_written+cookielength >= buffersize) {
        return 1;
      }
  
      if (length < cookielength) {
        memcpy(dstptr,cookie,length);
        bytes_written += length;
        dstptr += length;
      } else {
        memcpy(dstptr,cookie,cookielength);
        bytes_written += cookielength;
        dstptr += cookielength;
	/* TODO check that total length will not exceed buffer size */
	while (cookielength < length) {
	  bytes_written++;
	  *dstptr++ = ' '; /* FIXME choose padding character */
	  cookielength++;
	}
      } /* length < cookielength */
    } /* length <= 0 */
    
  }

  memcpy(buffer,work_buffer,buffersize);
  return 0;
}


/* used to translate text to binary word for rights */
unsigned long right_text2word(const char * text)
{
  unsigned long word=0;
  const char * ptr = text;

  do {
    while ( (*ptr)==' ' || (*ptr)=='\t' || (*ptr)=='+' || (*ptr)=='|' ) {
      ptr++;
    }
    if (*ptr == '\0' || *ptr == '\r' || *ptr=='\n') break;

    if (strncasecmp(ptr,"RIGHT_LIST",strlen("RIGHT_LIST"))==0) {
     word += RIGHT_LIST;
     ptr += strlen("RIGHT_LIST");
    }
    if (strncasecmp(ptr,"RIGHT_RETR",strlen("RIGHT_RETR"))==0) {
     word += RIGHT_RETR;
     ptr += strlen("RIGHT_RETR");
    }
    if (strncasecmp(ptr,"RIGHT_STOR",strlen("RIGHT_STOR"))==0) {
     word += RIGHT_STOR;
     ptr += strlen("RIGHT_STOR");
    }
    if (strncasecmp(ptr,"RIGHT_CWD",strlen("RIGHT_CWD"))==0) {
     word += RIGHT_CWD;
     ptr += strlen("RIGHT_CWD");
    }
    if (strncasecmp(ptr,"RIGHT_RNFR",strlen("RIGHT_RNFR"))==0) {
     word += RIGHT_RNFR;
     ptr += strlen("RIGHT_RNFR");
    }
  } while (*ptr);

  return word;
}


/* IP allowing */
int ip_add(wzd_ip_t **list, const char *newip)
{
  wzd_ip_t * new_ip_t, *insert_point;

  /* of course this should never happen :) */
  if (list == NULL) return -1;

  if (strlen(newip) < 1) return -1;
  if (strlen(newip) >= MAX_IP_LENGTH) return -1; /* upper limit for an hostname */

  new_ip_t = malloc(sizeof(wzd_ip_t));
  new_ip_t->regexp = malloc(strlen(newip)+1);
  strcpy(new_ip_t->regexp,newip);
  new_ip_t->next_ip = NULL;

  /* tail insertion, be aware that order is important */
  insert_point = *list;
  if (insert_point == NULL) {
    *list = new_ip_t;
  } else {
    while (insert_point->next_ip != NULL)
      insert_point = insert_point->next_ip;

    insert_point->next_ip = new_ip_t;
  }

  return 0;
}

/* dst can be composed of wildcards */
int my_str_compare(const char * src, const char *dst)
{
  const char * ptr_src;
  const char * ptr_dst;
  char c;

  ptr_src = src;
  ptr_dst = dst;

  while ((c = *ptr_src)) {
    if (*ptr_dst=='*') { /* wildcard * */
      if (*(ptr_dst+1)=='\0') return 1; /* terminated with a *, ok */
      ptr_dst++;
      c = *ptr_dst;
      while (*ptr_src && c!=*ptr_src)
        ptr_src++;
      if (!*ptr_src) break; /* try next ip */
      continue;
    }
    if (*ptr_dst=='?') { /* wildcard ?, match one char and continue */
      ptr_src++;
      ptr_dst++;
      continue;
    }
    if (*ptr_dst!=c) break; /* try next ip */
    ptr_dst++;
    ptr_src++;
  }
  
  /* test if checking was complete */
  if (*ptr_dst == '\0') return 1;

  return 0;
}
  

int ip_inlist(wzd_ip_t *list, const char *ip)
{
  wzd_ip_t * current_ip;
  const char * ptr_ip;
  char * ptr_test;
  struct hostent *host;

  current_ip = list;
  while (current_ip) {
    ptr_ip = ip;
    ptr_test = current_ip->regexp;
    if (*ptr_test == '\0') return 0; /* ip has length 0 ! */

    if (*ptr_test == '+') {
      char buffer[30];
      unsigned char * host_ip;

      ptr_test++;
      host = gethostbyname(ptr_test);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
        current_ip = current_ip->next_ip;
        continue;
      }

      host_ip = (unsigned char*)(host->h_addr);
      snprintf(buffer,29,"%d.%d.%d.%d",
        host_ip[0],host_ip[1],host_ip[2],host_ip[3]);
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST IP %s\n",buffer);
#endif
      if (my_str_compare(buffer,ip)==1)
        return 1;
    } else
    if (*ptr_test == '-') {
      unsigned char host_ip[5];
      int i1, i2, i3, i4;

      ptr_test++;
      if (sscanf(ptr_ip,"%d.%d.%d.%d",&i1,&i2,&i3,&i4)!=4) {
        out_log(LEVEL_HIGH,"INVALID IP (%s:%d) %s\n",__FILE__,__LINE__,
          ptr_ip);
        return 0;
      }
      host_ip[0] = i1;
      host_ip[1] = i2;
      host_ip[2] = i3;
      host_ip[3] = i4;

      host = gethostbyaddr(host_ip,4,AF_INET);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
        current_ip = current_ip->next_ip;
        continue;
      }

      /* XXX do not forget the alias list ! */
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST NAME %s\n",ptr_test);
#endif
      if (my_str_compare(host->h_name,ptr_test)==1)
        return 1;
    } else
    { /* ip does not begin with + or - */
#if DEBUG
out_err(LEVEL_CRITICAL,"IP %s\n",ptr_test);
#endif
      if (my_str_compare(ptr_ip,ptr_test)==1) return 1;
    } /* ip does not begin with + or - */
  
    current_ip = current_ip->next_ip;
  } /* while current_ip */
  
  return 0;
}

void ip_free(wzd_ip_t *list)
{
  wzd_ip_t * current, *next;

  if (!list) return;
  current = list;

  while (current) {
    next = current->next_ip;

    free(current->regexp);
    free(current);

    current = next;
  }
}

int user_ip_add(wzd_user_t * user, const char *newip)
{
  int i;

  /* of course this should never happen :) */
  if (user == NULL || newip==NULL);

  if (strlen(newip) < 1) return -1;
  if (strlen(newip) >= MAX_IP_LENGTH) return -1; /* upper limit for an hostname */

  /* tail insertion, be aware that order is important */
  for (i=0; i<HARD_IP_PER_USER; i++) {
    if (user->ip_allowed[i][0] == '\0') {
      strncpy(user->ip_allowed[i],newip,MAX_IP_LENGTH-1);
      return 0;
    }
  }
  return 1; /* full */
}

int user_ip_inlist(wzd_user_t * user, const char *ip)
{
  int i;
  const char * ptr_ip;
  char * ptr_test;
  struct hostent *host;

  i = 0;
  while (user->ip_allowed[i][0] != '\0') {
    ptr_ip = ip;
    ptr_test = user->ip_allowed[i];
    if (*ptr_test == '\0') return 0; /* ip has length 0 ! */
    
    if (*ptr_test == '+') {
      char buffer[30];
      unsigned char * host_ip;
      
      ptr_test++;
      host = gethostbyname(ptr_test);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
	i++;
        continue;
      }
      
      host_ip = (unsigned char*)(host->h_addr);
      snprintf(buffer,29,"%d.%d.%d.%d",
        host_ip[0],host_ip[1],host_ip[2],host_ip[3]);
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST IP %s\n",buffer);
#endif
      if (my_str_compare(buffer,ip)==1)
        return 1;
    } else
    if (*ptr_test == '-') {
      unsigned char host_ip[5];
      int i1, i2, i3, i4;

      ptr_test++;
      if (sscanf(ptr_ip,"%d.%d.%d.%d",&i1,&i2,&i3,&i4)!=4) {
        out_log(LEVEL_HIGH,"INVALID IP (%s:%d) %s\n",__FILE__,__LINE__,
          ptr_ip);
        return 0;
      }
      host_ip[0] = i1;
      host_ip[1] = i2;
      host_ip[2] = i3;
      host_ip[3] = i4;

      host = gethostbyaddr(host_ip,4,AF_INET);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
	i++;
        continue;
      }

      /* XXX do not forget the alias list ! */
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST NAME %s\n",ptr_test);
#endif
      if (my_str_compare(host->h_name,ptr_test)==1)
        return 1;
    } else
    { /* ip does not begin with + or - */
#if DEBUG
out_err(LEVEL_CRITICAL,"IP %s\n",ptr_test);
#endif
      if (my_str_compare(ptr_ip,ptr_test)==1) return 1;
    } /* ip does not begin with + or - */

    i++;
  } /* while current_ip */

  return 0;
}

int group_ip_add(wzd_group_t * group, const char *newip)
{
  int i;

  /* of course this should never happen :) */
  if (group == NULL || newip==NULL);

  if (strlen(newip) < 1) return -1;
  if (strlen(newip) >= MAX_IP_LENGTH) return -1; /* upper limit for an hostname */

  /* tail insertion, be aware that order is important */
  for (i=0; i<HARD_IP_PER_GROUP; i++) {
    if (group->ip_allowed[i][0] == '\0') {
      strncpy(group->ip_allowed[i],newip,MAX_IP_LENGTH-1);
      return 0;
    }
  }
  return 1; /* full */
}

int group_ip_inlist(wzd_group_t * group, const char *ip)
{
  int i;
  const char * ptr_ip;
  char * ptr_test;
  struct hostent *host;

  i = 0;
  while (group->ip_allowed[i][0] != '\0') {
    ptr_ip = ip;
    ptr_test = group->ip_allowed[i];
    if (*ptr_test == '\0') return 0; /* ip has length 0 ! */
    
    if (*ptr_test == '+') {
      char buffer[30];
      unsigned char * host_ip;
      
      ptr_test++;
      host = gethostbyname(ptr_test);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
	i++;
        continue;
      }
      
      host_ip = (unsigned char*)(host->h_addr);
      snprintf(buffer,29,"%d.%d.%d.%d",
        host_ip[0],host_ip[1],host_ip[2],host_ip[3]);
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST IP %s\n",buffer);
#endif
      if (my_str_compare(buffer,ip)==1)
        return 1;
    } else
    if (*ptr_test == '-') {
      unsigned char host_ip[5];
      int i1, i2, i3, i4;

      ptr_test++;
      if (sscanf(ptr_ip,"%d.%d.%d.%d",&i1,&i2,&i3,&i4)!=4) {
        out_log(LEVEL_HIGH,"INVALID IP (%s:%d) %s\n",__FILE__,__LINE__,
          ptr_ip);
        return 0;
      }
      host_ip[0] = i1;
      host_ip[1] = i2;
      host_ip[2] = i3;
      host_ip[3] = i4;

      host = gethostbyaddr(host_ip,4,AF_INET);
      if (!host) {
        /* XXX could not resolve hostname - warning in log ? */
	i++;
        continue;
      }

      /* XXX do not forget the alias list ! */
#if DEBUG
out_err(LEVEL_CRITICAL,"HOST NAME %s\n",ptr_test);
#endif
      if (my_str_compare(host->h_name,ptr_test)==1)
        return 1;
    } else
    { /* ip does not begin with + or - */
#if DEBUG
out_err(LEVEL_CRITICAL,"IP %s\n",ptr_test);
#endif
      if (my_str_compare(ptr_ip,ptr_test)==1) return 1;
    } /* ip does not begin with + or - */

    i++;
  } /* while current_ip */

  return 0;
}

