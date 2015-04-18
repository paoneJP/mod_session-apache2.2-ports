#include "apr.h"
#include "http_core.h"
#include "from_http_core.h"

/* :: ported from httpd-2.4.12/server/core.c: l.127-l.129 */

AP_DECLARE_DATA int ap_main_state = AP_SQ_MS_INITIAL_STARTUP;
AP_DECLARE_DATA int ap_run_mode = AP_SQ_RM_UNKNOWN;
AP_DECLARE_DATA int ap_config_generation = 0;


/* :: ported from httpd-2.4.12/server/core.c: l.4698-l.4710 */

AP_DECLARE(int) ap_state_query(int query)
{
    switch (query) {
    case AP_SQ_MAIN_STATE:
        return ap_main_state;
    case AP_SQ_RUN_MODE:
        return ap_run_mode;
    case AP_SQ_CONFIG_GEN:
        return ap_config_generation;
    default:
        return AP_SQ_NOT_SUPPORTED;
    }
}
