SUBDIRS = icons

install-data-local: update-icon-cache

@GSETTINGS_RULES@
desktopdir = $(datadir)/applications
desktop_in_files = firezero.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

pixmapsdir = $(datadir)/pixmaps
pixmaps_in_files = pixmaps/firezero.png pixmaps/firezero.xpm
pixmaps_DATA = $(pixmaps_in_files)

#
# GTK icon cache
#

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache

update-icon-cache:
	if test -z "$(DESTDIR)"; then \
	        echo "Updating Gtk icon cache."; \
	        $(gtk_update_icon_cache); \
	else \
	        echo "*** Icon cache not updated.  After (un)install, run this:"; \
	        echo "***   $(gtk_update_icon_cache)"; \
	        fi


EXTRA_DIST = \
	$(desktop_in_files) \
	$(pixmaps_in_files)

CLEANFILES = \
	$(desktop_DATA)

-include $(top_srcdir)/git.mk
