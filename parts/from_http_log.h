/* :: ported from httpd-2.4.12/include/http_log.h: l.111-l.117 */

/**
 * APLOGNO() should be used at the start of the format string passed
 * to ap_log_error() and friends. The argument must be a 5 digit decimal
 * number. It creates a tag of the form "AH02182: "
 * See docs/log-message-tags/README for details.
 */
#define APLOGNO(n)              "AH" #n ": "
