/* :: ported from httpd-2.4.12/include/http_core.h: l.927-l.980 */

/** Query the server for some state information
 * @param query_code Which information is requested
 * @return the requested state information
 */
AP_DECLARE(int) ap_state_query(int query_code);

/*
 * possible values for query_code in ap_state_query()
 */

  /** current status of the server */
#define AP_SQ_MAIN_STATE        0
  /** are we going to serve requests or are we just testing/dumping config */
#define AP_SQ_RUN_MODE          1
    /** generation of the top-level apache parent */
#define AP_SQ_CONFIG_GEN        2

/*
 * return values for ap_state_query()
 */

  /** return value for unknown query_code */
#define AP_SQ_NOT_SUPPORTED       -1

/* values returned for AP_SQ_MAIN_STATE */
  /** before the config preflight */
#define AP_SQ_MS_INITIAL_STARTUP   1
  /** initial configuration run for setting up log config, etc. */
#define AP_SQ_MS_CREATE_PRE_CONFIG 2
  /** tearing down configuration */
#define AP_SQ_MS_DESTROY_CONFIG    3
  /** normal configuration run */
#define AP_SQ_MS_CREATE_CONFIG     4
  /** running the MPM */
#define AP_SQ_MS_RUN_MPM           5
  /** cleaning up for exit */
#define AP_SQ_MS_EXITING           6

/* values returned for AP_SQ_RUN_MODE */
  /** command line not yet parsed */
#define AP_SQ_RM_UNKNOWN           1
  /** normal operation (server requests or signal server) */
#define AP_SQ_RM_NORMAL            2
  /** config test only */
#define AP_SQ_RM_CONFIG_TEST       3
  /** only dump some parts of the config */
#define AP_SQ_RM_CONFIG_DUMP       4

