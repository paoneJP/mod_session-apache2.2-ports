mod_session.la: mod_session.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session.lo
mod_session_cookie.la: mod_session_cookie.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session_cookie.lo
mod_session_crypto.la: mod_session_crypto.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_session_crypto.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_session.la mod_session_cookie.la mod_session_crypto.la
