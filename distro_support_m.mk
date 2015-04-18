module_name1=session
module_name2=session_cookie
module_name3=session_crypto

ifneq ($(wildcard /etc/debian_version),)
  # Debian 7.x (wheezy) / Ubuntu 10.04,12.04
  ifneq ($(wildcard /etc/lsb-release),)  # Ubuntu 10.04,12.04
    APR_CRYPTO_PORTS=apr_crypto.slo apr_crypto_openssl.slo
  endif
  top_srcdir=/usr/share/apache2
  top_builddir=/usr/share/apache2
  header_file_dir=/usr/include/apache2
  include /usr/share/apache2/build/special.mk
  loader_file1=/etc/apache2/mods-available/$(module_name1).load
  loader_file2=/etc/apache2/mods-available/$(module_name2).load
  loader_file3=/etc/apache2/mods-available/$(module_name3).load
  loader_lines1=LoadFile $(libexecdir)/apache24compat.so\nLoadModule $(module_name1)_module $(libexecdir)/mod_$(module_name1).so
  loader_lines2=LoadModule $(module_name2)_module $(libexecdir)/mod_$(module_name2).so
  loader_lines3=LoadModule $(module_name3)_module $(libexecdir)/mod_$(module_name3).so
  ifneq ($(wildcard /etc/lsb-release),)  # Ubuntu 10.04,12.04
    CFLAGS+=-Iparts -Iapu
  endif
else ifneq ($(wildcard /etc/redhat-release),)
  # RHEL/CentOS 6.x
  APR_CRYPTO_PORTS=apr_crypto.slo apr_crypto_openssl.slo
  header_file_dir=/usr/include/httpd
  top_srcdir=/etc/httpd
  ifneq ($(wildcard /usr/lib64),)  # 64bit
    top_builddir=/usr/lib64/httpd
    include /usr/lib64/httpd/build/special.mk
  else
    top_builddir=/usr/lib/httpd
    include /usr/lib/httpd/build/special.mk
  endif
  loader_file1=/etc/httpd/conf.d/$(module_name1).conf-
  loader_file2=/etc/httpd/conf.d/$(module_name2).conf-
  loader_file3=/etc/httpd/conf.d/$(module_name3).conf-
  loader_lines1=LoadFile modules/apache24compat.so\nLoadModule $(module_name1)_module modules/mod_$(module_name1).so
  loader_lines2=LoadModule $(module_name2)_module modules/mod_$(module_name2).so
  loader_lines3=LoadModule $(module_name3)_module modules/mod_$(module_name3).so
  CFLAGS+=-Iparts -Iapu
else
  $(error unsupported platform)
endif

install-loader-config:
	echo -e "$(loader_lines1)" > $(loader_file1)
	echo "$(loader_lines2)" > $(loader_file2)
	echo "$(loader_lines3)" > $(loader_file3)
	chmod 644 $(loader_file1) $(loader_file2) $(loader_file3)

install-headers:
	cp mod_session.h $(header_file_dir)
	chmod 644 $(header_file_dir)/mod_session.h

install: install-modules-yes install-loader-config install-headers
