noinst_LTLIBRARIES = module-managedb.la

AM_CPPFLAGS = \
	-DUI_DIR=\""$(datadir)/firezero"\" \
	-DVERSION=\""$(VERSION)"\" \
	-DLOCALE_DIR=\""$(localedir)"\" \
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\" \
	-w \
	$(FIREZERO_CFLAGS) \
	-I$(top_srcdir)/src/include

module_managedb_la_CPPFLAGS = \
	$(AM_CPPFLAGS)

module_managedb_la_SOURCES = managedb.c

module_managedb_la_LIBADD = \
	$(FIREZERO_LIBS)

module_managedb_la_LDFLAGS = -module

-include $(top_srcdir)/git.mk
