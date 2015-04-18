vpath %.c parts:apu

mod_session.la: mod_session.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session.lo
mod_session_cookie.la: mod_session_cookie.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session_cookie.lo
mod_session_crypto.la: mod_session_crypto.slo $(APR_CRYPTO_PORTS)
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session_crypto.lo

apache24compat.la: from_core.slo from_util.slo $(APR_CRYPTO_PORTS)
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  from_core.lo from_util.lo $(patsubst %.slo,%.lo,$(APR_CRYPTO_PORTS)) $(patsubst %,-lcrypto,$(word 1,$(APR_CRYPTO_PORTS)))

DISTCLEAN_TARGETS = modules.mk
shared =  mod_session.la mod_session_cookie.la mod_session_crypto.la apache24compat.la
