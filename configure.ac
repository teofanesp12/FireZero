dnl Process this file with autoconf to produce a configure script.

AC_INIT(firezero, 0.01)
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([src])
AC_CONFIG_AUX_DIR([build-aux])

AC_PROG_CC
AC_CONFIG_HEADERS([src/include/config.h])
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, glib-compile-resources)

AC_CANONICAL_HOST


dnl AM_SILENT_RULES([yes])
AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz foreign])
AM_MAINTAINER_MODE([enable])




GLIB_GSETTINGS

dnl ###########################################################################
dnl Dependencies
dnl ###########################################################################

GLIB_REQUIRED=2.40.0
GTK_REQUIRED=3.16.7
PQ_REQUIRED=9.4.5

PKG_CHECK_MODULES(FIREZERO, [
    gtk+-3.0 >= $GTK_REQUIRED
    glib-2.0 >= $GLIB_REQUIRED
    libpq >= $PQ_REQUIRED
])

dnl Dependencies in Modules:


dnl ###########################################################################
dnl Internationalization
dnl ###########################################################################

IT_PROG_INTLTOOL([0.50])
AC_SUBST(GETTEXT_PACKAGE, firezero)


dnl ******************************
dnl Initialize libtool
dnl ******************************
LT_PREREQ(2.2)
LT_INIT([disable-static])

PKG_PROG_PKG_CONFIG


dnl *******************
dnl Special directories
dnl *******************

dnl privlibdir='${libdir}'/FireZero
dnl AC_SUBST(privlibdir)

dnl moduledir="modules"
dnl AC_SUBST(moduledir)


dnl ###########################################################################
dnl Files to generate
dnl ###########################################################################
dnl help/Makefile
AC_CONFIG_FILES([
Makefile
data/Makefile
data/icons/Makefile
data/icons/32x32/Makefile
data/icons/32x32/apps/Makefile
data/icons/48x48/Makefile
data/icons/48x48/apps/Makefile
data/icons/64x64/Makefile
data/icons/64x64/apps/Makefile
po/Makefile.in
src/Makefile
src/init/Makefile
src/tools/Makefile
src/module/Makefile
src/module/login/Makefile
src/module/managedb/Makefile
])

AC_OUTPUT

AC_MSG_NOTICE([

        FireZero $VERSION
        ==================

        prefix:     ${prefix}
        compiler:   ${CC}
        locale:     ${localedir}

        Now type 'make' to build $PACKAGE
])
