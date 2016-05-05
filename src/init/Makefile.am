bin_PROGRAMS = firezero

firezero_SOURCES = main.c

AM_CPPFLAGS = \
	-DUI_DIR=\""$(datadir)/firezero"\" \
	-DVERSION=\""$(VERSION)"\" \
	-DLOCALE_DIR=\""$(localedir)"\" \
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\" \
	-w \
	$(FIREZERO_CFLAGS) \
	-I$(top_srcdir)/src/include

firezero_CPPFLAGS = \
	$(AM_CPPFLAGS)

firezero_LDADD = \
	$(FIREZERO_LIBS) \
	$(top_srcdir)/src/module/module.o \
	$(top_srcdir)/src/tools/module-tools.la

#$(top_srcdir)/src/module/module.o:
#	@echo "Validate Modules..."

-include $(top_srcdir)/git.mk
