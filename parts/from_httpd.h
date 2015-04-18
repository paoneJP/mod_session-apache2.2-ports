/* :: ported from httpd-2.4.12/include/httpd.h: l.1605-l.1610 */

/**
 * Unescape an application/x-www-form-urlencoded string
 * @param query The query to unescape
 * @return 0 on success, non-zero otherwise
 */
AP_DECLARE(int) ap_unescape_urlencoded(char *query);


/* :: ported from httpd-2.4.12/include/httpd.h: l.1654-l.1668 */

/**
 * Escape a string as application/x-www-form-urlencoded
 * @param p The pool to allocate from
 * @param s The path to convert
 * @return The converted URL
 */
AP_DECLARE(char *) ap_escape_urlencoded(apr_pool_t *p, const char *s);

/**
 * Escape a string as application/x-www-form-urlencoded, to a preallocated buffer
 * @param c The preallocated buffer to write to
 * @param s The path to convert
 * @return The converted URL (c)
 */
AP_DECLARE(char *) ap_escape_urlencoded_buffer(char *c, const char *s);


/* :: ported from httpd-2.4.12/include/httpd.h: l.2249-l.2259 */

/**
 * Short function to execute a command and return the first line of
 * output minus \r \n. Useful for "obscuring" passwords via exec calls
 * @param p the pool to allocate from
 * @param cmd the command to execute
 * @param argv the arguments to pass to the cmd
 * @return ptr to characters or NULL on any error
 */
AP_DECLARE(char *) ap_get_exec_line(apr_pool_t *p,
                                    const char *cmd,
                                    const char * const *argv);
