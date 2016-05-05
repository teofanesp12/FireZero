AM_CPPFLAGS = \
	-DUI_DIR=\""$(datadir)/firezero"\" \
	-DVERSION=\""$(VERSION)"\" \
	-DLOCALE_DIR=\""$(localedir)"\" \
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\" \
	-w \
	$(FIREZERO_CFLAGS) \
	-I$(top_srcdir)/src/include

noinst_LTLIBRARIES = module-tools.la

module_tools_la_CPPFLAGS = \
	$(AM_CPPFLAGS)

module_tools_la_SOURCES = \
	firez-application.c \
	firez-window.c

module_tools_la_LIBADD = \
	$(FIREZERO_LIBS)
#	$(top_srcdir)/src/module/module.o

module_tools_la_LDFLAGS = -module


-include $(top_srcdir)/git.mk
