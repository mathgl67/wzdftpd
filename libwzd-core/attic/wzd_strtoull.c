/* vi:ai:et:ts=8 sw=2
 */
/** \file
  * \brief strtoull() replacement
  */

#include "wzd_all.h"

#include <stdlib.h>
#include <ctype.h> /* isspace, etc. */


#include "wzd_strtoull.h"

#if (!HAVE_STRTOULL )
/* taken from glibc-2.2.2: strtod.c, and stripped down a lot.  There are 
   still a few leftover references to decimal points and exponents, 
   but it works for bases 10 and 16 */

#define RETURN(val,end)      \
    do { if (endptr != NULL) *endptr = (char *) (end);      \
 return val; } while (0)

__int64 strtoull (const char *nptr, char **endptr, int baseignore)
{
  int negative;/* The sign of the number.  */
  int exponent;/* Exponent of the number.  */

  /* Numbers starting `0X' or `0x' have to be processed with base 16.  */
  int base = 10;

  /* Number of bits currently in result value.  */
  int bits;

  /* Running pointer after the last character processed in the string.  */
  const char *cp, *tp;
  /* Start of significant part of the number.  */
  const char *startp, *start_of_digits;
  /* Total number of digit and number of digits in integer part.  */
  int dig_no;
  /* Contains the last character read.  */
  char c;

  i64_t n = 0;
  char const *p;

  /* Prepare number representation.  */
  exponent = 0;
  negative = 0;
  bits = 0;

  /* Parse string to get maximal legal prefix.  We need the number of
     characters of the integer part, the fractional part and the exponent.  */
  cp = nptr - 1;
  /* Ignore leading white space.  */
  do
    c = *++cp;
  while (isspace (c));

  /* Get sign of the result.  */
  if (c == '-')
    {
      negative = 1;
      c = *++cp;
    }
  else if (c == '+')
    c = *++cp;

  if (c < '0' || c > '9')
    {
      /* It is really a text we do not recognize.  */
      RETURN (0, nptr);
    }

  /* First look whether we are faced with a hexadecimal number.  */
  if (c == '0' && tolower (cp[1]) == 'x')
    {
      /* Okay, it is a hexa-decimal number.  Remember this and skip
 the characters.  BTW: hexadecimal numbers must not be
 grouped.  */
      base = 16;
      cp += 2;
      c = *cp;
    }

  /* Record the start of the digits, in case we will check their grouping.  */
  start_of_digits = startp = cp;

  /* Ignore leading zeroes.  This helps us to avoid useless computations.  */
  while (c == '0')
    c = *++cp;

  /* If no other digit but a '0' is found the result is 0.0.
     Return current read pointer.  */
  if ((c < '0' || c > '9')
      && (base == 16 && (c < tolower ('a') || c > tolower ('f')))
      && (base == 16 && (cp == start_of_digits || tolower (c) != 'p'))
      && (base != 16 && tolower (c) != 'e'))
    {
      tp = start_of_digits;
      /* If TP is at the start of the digits, there was no correctly
 grouped prefix of the string; so no number found.  */
      RETURN (0, tp == start_of_digits ? (base == 16 ? cp - 1 : nptr) : tp);
    }

  /* Remember first significant digit and read following characters until the
     decimal point, exponent character or any non-FP number character.  */
  startp = cp;
  dig_no = 0;
  while (1)
    {
      if ((c >= '0' && c <= '9')
  || (base == 16 && tolower (c) >= 'a' && tolower (c) <= 'f'))
++dig_no;
      else
break;
      c = *++cp;
    }

  /* The whole string is parsed.  Store the address of the next character.  */
  if (endptr)
    *endptr = (char *) cp;

  if (dig_no == 0) 
    return 0;

  for (p=start_of_digits; p!=cp; p++) {
    n = n * (i64_t)base;
    c = tolower (*p);
    c = (c >= 'a') ? (10+c-'a') : c-'0';
    n = n + (i64_t)c;
    //printf ("after shifting in digit %c, n is %lld\n", *p, n);
  }
  return negative? -n : n;
}
#endif  /* HAVE_STRTOULL */
