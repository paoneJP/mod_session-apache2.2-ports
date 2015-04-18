#include "apr.h"
#include "apr_strings.h"
#include "apr_lib.h"
#define APR_WANT_STDIO
#define APR_WANT_STRFUNC
#include "apr_want.h"
#include "http_core.h"
#include "ap_mpm.h"


/* :: ported from httpd-2.4.12/server/util.c: l.71-l.82 */

/* A bunch of functions in util.c scan strings looking for certain characters.
 * To make that more efficient we encode a lookup table.  The test_char_table
 * is generated automatically by gen_test_char.c.
 */
#include "test_char.h"

/* we assume the folks using this ensure 0 <= c < 256... which means
 * you need a cast to (unsigned char) first, you can't just plug a
 * char in here and get it to work, because if char is signed then it
 * will first be sign extended.
 */
#define TEST_CHAR(c, f)        (test_char_table[(unsigned)(c)] & (f))


/* :: ported from httpd-2.4.12/server/util.c: l.1586-l.1671 */

static char x2c(const char *what)
{
    char digit;

#if !APR_CHARSET_EBCDIC
    digit = ((what[0] >= 'A') ? ((what[0] & 0xdf) - 'A') + 10
             : (what[0] - '0'));
    digit *= 16;
    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A') + 10
              : (what[1] - '0'));
#else /*APR_CHARSET_EBCDIC*/
    char xstr[5];
    xstr[0]='0';
    xstr[1]='x';
    xstr[2]=what[0];
    xstr[3]=what[1];
    xstr[4]='\0';
    digit = apr_xlate_conv_byte(ap_hdrs_from_ascii,
                                0xFF & strtol(xstr, NULL, 16));
#endif /*APR_CHARSET_EBCDIC*/
    return (digit);
}

/*
 * Unescapes a URL, leaving reserved characters intact.
 * Returns 0 on success, non-zero on error
 * Failure is due to
 *   bad % escape       returns HTTP_BAD_REQUEST
 *
 *   decoding %00 or a forbidden character returns HTTP_NOT_FOUND
 */

static int unescape_url(char *url, const char *forbid, const char *reserved)
{
    int badesc, badpath;
    char *x, *y;

    badesc = 0;
    badpath = 0;
    /* Initial scan for first '%'. Don't bother writing values before
     * seeing a '%' */
    y = strchr(url, '%');
    if (y == NULL) {
        return OK;
    }
    for (x = y; *y; ++x, ++y) {
        if (*y != '%') {
            *x = *y;
        }
        else {
            if (!apr_isxdigit(*(y + 1)) || !apr_isxdigit(*(y + 2))) {
                badesc = 1;
                *x = '%';
            }
            else {
                char decoded;
                decoded = x2c(y + 1);
                if ((decoded == '\0')
                    || (forbid && ap_strchr_c(forbid, decoded))) {
                    badpath = 1;
                    *x = decoded;
                    y += 2;
                }
                else if (reserved && ap_strchr_c(reserved, decoded)) {
                    *x++ = *y++;
                    *x++ = *y++;
                    *x = *y;
                }
                else {
                    *x = decoded;
                    y += 2;
                }
            }
        }
    }
    *x = '\0';
    if (badesc) {
        return HTTP_BAD_REQUEST;
    }
    else if (badpath) {
        return HTTP_NOT_FOUND;
    }
    else {
        return OK;
    }
}


/* :: ported from httpd-2.4.12/server/util.c: l.1705-l.1720 */

AP_DECLARE(int) ap_unescape_urlencoded(char *query)
{
    char *slider;

    /* replace plus with a space */
    if (query) {
        for (slider = query; *slider; slider++) {
            if (*slider == '+') {
                *slider = ' ';
            }
        }
    }

    /* unescape everything else */
    return unescape_url(query, NULL, NULL);
}


/* :: ported from httpd-2.4.12/server/util.c: l.1738-l.1760 */

/* c2x takes an unsigned, and expects the caller has guaranteed that
 * 0 <= what < 256... which usually means that you have to cast to
 * unsigned char first, because (unsigned)(char)(x) first goes through
 * signed extension to an int before the unsigned cast.
 *
 * The reason for this assumption is to assist gcc code generation --
 * the unsigned char -> unsigned extension is already done earlier in
 * both uses of this code, so there's no need to waste time doing it
 * again.
 */
static const char c2x_table[] = "0123456789abcdef";

static APR_INLINE unsigned char *c2x(unsigned what, unsigned char prefix,
                                     unsigned char *where)
{
#if APR_CHARSET_EBCDIC
    what = apr_xlate_conv_byte(ap_hdrs_to_ascii, (unsigned char)what);
#endif /*APR_CHARSET_EBCDIC*/
    *where++ = prefix;
    *where++ = c2x_table[what >> 4];
    *where++ = c2x_table[what & 0xf];
    return where;
}


/* :: ported from httpd-2.4.12/server/util.c: l.1830-l.1855 */

AP_DECLARE(char *) ap_escape_urlencoded_buffer(char *copy, const char *buffer)
{
    const unsigned char *s = (const unsigned char *)buffer;
    unsigned char *d = (unsigned char *)copy;
    unsigned c;

    while ((c = *s)) {
        if (TEST_CHAR(c, T_ESCAPE_URLENCODED)) {
            d = c2x(c, '%', d);
        }
        else if (c == ' ') {
            *d++ = '+';
        }
        else {
            *d++ = c;
        }
        ++s;
    }
    *d = '\0';
    return copy;
}

AP_DECLARE(char *) ap_escape_urlencoded(apr_pool_t *p, const char *buffer)
{
    return ap_escape_urlencoded_buffer(apr_palloc(p, 3 * strlen(buffer) + 1), buffer);
}


/* :: ported from httpd-2.4.12/server/util.c: l.2967-l.3007 */

AP_DECLARE(char *) ap_get_exec_line(apr_pool_t *p,
                                    const char *cmd,
                                    const char * const * argv)
{
    char buf[MAX_STRING_LEN];
    apr_procattr_t *procattr;
    apr_proc_t *proc;
    apr_file_t *fp;
    apr_size_t nbytes = 1;
    char c;
    int k;

    if (apr_procattr_create(&procattr, p) != APR_SUCCESS)
        return NULL;
    if (apr_procattr_io_set(procattr, APR_FULL_BLOCK, APR_FULL_BLOCK,
                            APR_FULL_BLOCK) != APR_SUCCESS)
        return NULL;
    if (apr_procattr_dir_set(procattr,
                             ap_make_dirstr_parent(p, cmd)) != APR_SUCCESS)
        return NULL;
    if (apr_procattr_cmdtype_set(procattr, APR_PROGRAM) != APR_SUCCESS)
        return NULL;
    proc = apr_pcalloc(p, sizeof(apr_proc_t));
    if (apr_proc_create(proc, cmd, argv, NULL, procattr, p) != APR_SUCCESS)
        return NULL;
    fp = proc->out;

    if (fp == NULL)
        return NULL;
    /* XXX: we are reading 1 byte at a time here */
    for (k = 0; apr_file_read(fp, &c, &nbytes) == APR_SUCCESS
                && nbytes == 1 && (k < MAX_STRING_LEN-1)     ; ) {
        if (c == '\n' || c == '\r')
            break;
        buf[k++] = c;
    }
    buf[k] = '\0';
    apr_file_close(fp);

    return apr_pstrndup(p, buf, k);
}
