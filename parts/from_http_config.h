/* :: ported from httpd-2.4.12/include/http_config.h: l.412-l.438 */

/**
 * The APLOG_USE_MODULE macro is used choose which module a file belongs to.
 * This is necessary to allow per-module loglevel configuration.
 *
 * APLOG_USE_MODULE indirectly sets APLOG_MODULE_INDEX and APLOG_MARK.
 *
 * If a module should be backward compatible with versions before 2.3.6,
 * APLOG_USE_MODULE needs to be enclosed in a ifdef APLOG_USE_MODULE block.
 *
 * @param foo name of the module symbol of the current module, without the
 *            trailing "_module" part
 * @see APLOG_MARK
 */
#define APLOG_USE_MODULE(foo) \
    extern module AP_MODULE_DECLARE_DATA foo##_module;                  \
    static int * const aplog_module_index = &(foo##_module.module_index)

/**
 * AP_DECLARE_MODULE is a convenience macro that combines a call of
 * APLOG_USE_MODULE with the definition of the module symbol.
 *
 * If a module should be backward compatible with versions before 2.3.6,
 * APLOG_USE_MODULE should be used explicitly instead of AP_DECLARE_MODULE.
 */
#define AP_DECLARE_MODULE(foo) \
    APLOG_USE_MODULE(foo);                         \
    module AP_MODULE_DECLARE_DATA foo##_module
