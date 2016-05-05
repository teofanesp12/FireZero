noinst_LTLIBRARIES = module-login.la

AM_CPPFLAGS = \
	-DUI_DIR=\""$(datadir)/firezero"\" \
	-DVERSION=\""$(VERSION)"\" \
	-DLOCALE_DIR=\""$(localedir)"\" \
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\" \
	-w \
	$(FIREZERO_CFLAGS) \
	-I$(top_srcdir)/src/include

module_login_la_CPPFLAGS = \
	$(AM_CPPFLAGS)

module_login_la_SOURCES = login.c

module_login_la_LIBADD = \
	$(FIREZERO_LIBS)

module_login_la_LDFLAGS = -module

-include $(top_srcdir)/git.mk
