/* :: ported from httpd-2.4.12/include/ap_config.h: l.179-l.186 */

#ifndef __has_attribute         /* check for supported attributes on clang */
#define __has_attribute(x) 0
#endif
#if (defined(__GNUC__) && __GNUC__ >= 4) || __has_attribute(sentinel)
#define AP_FN_ATTR_SENTINEL __attribute__((sentinel))
#else
#define AP_FN_ATTR_SENTINEL
#endif
