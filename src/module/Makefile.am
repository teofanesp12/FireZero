SUBDIRS = login managedb

AM_CPPFLAGS = \
	-DUI_DIR=\""$(datadir)/firezero"\" \
	-DVERSION=\""$(VERSION)"\" \
	-DLOCALE_DIR=\""$(localedir)"\" \
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\" \
	-w \
	$(FIREZERO_CFLAGS) \
	-I$(top_srcdir)/src/include

#module_login_la_CPPFLAGS = \
#	$(AM_CPPFLAGS)
MODULES= \
	login/.libs/module_login_la-login.o \
	managedb/.libs/module_managedb_la-managedb.o

DepModules = \
	$(MODULES)

all-am: Makefile module-all.o
all: all-recursive all-am
module-all.o: $(MODULES)
	$(LD) -r -o module.o $(DepModules) $(LIBS)

CLEANFILES = \
	module.o

-include $(top_srcdir)/git.mk
