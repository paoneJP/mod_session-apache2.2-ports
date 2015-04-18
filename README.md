mod_session-apache2.2-ports
===========================

This is a backported version of a mod_session series work with apache 2.2.


## What is mod_session?

Read documents provided with apache 2.4.

 * http://httpd.apache.org/docs/2.4/en/mod/mod_session.html


## Ported modules

 * mod_session
 * mod_session_cookie
 * mod_session_crypto
 * some routines found only in apache 2.4. (from core.c, util.c, and util_cookie.c)
 * apr_crypto routines from apr-util 1.5. (this routines are used if you have apr-util < 1.4)


## Build and Install

Just run make and make install.

    $ cd mod_session-apache2.2-ports
    $ make
    $ sudo make install

``make install`` command also installs LoadModule configuration in distro 
specific directory.


## License

Read the LICENSE and NOTICE files provided by original software.

 * Apache HTTP Server
   - NOTICE.httpd
   - LICENSE.httpd
 * Apache Portable Runtime Utility Library
   - NOTICE.apr-util
   - LICENSE.apr-util

Backport work is made by Takashi Yahata (@paoneJP).


## changelog

 * first release
   - apache httpd 2.4.12
   - apr-util 1.5.4
