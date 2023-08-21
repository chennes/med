#include $(top_srcdir)/config/automake.common.2.3.6
include $(top_srcdir)/config/automake.common
include $(srcdir)/../config/medimport.common

DEFAULT_INCLUDES = -I. -I$(srcdir)

AM_CPPFLAGS+=-I$(srcdir)/../include -I$(builddir) -DMED_MESGERR_FOR_TOOLS

noinst_LTLIBRARIES = libMaj400To410.la
libMaj400To410_la_SOURCES   = \
MAJ_400_410_champs.c

# buildCxxFile =  \
# MAJ_400_410_champsbuilt.cxx

# noinst_LTLIBRARIES += libMaj400To410cxx.la
# libMaj400To410cxx_la_SOURCES   = $(buildCxxFile)

MAJ_400_410_champs.c:_MEDfieldValueUpdateEntityList41.c

BUILT_SOURCES= _MEDfieldValueUpdateEntityList41.c

_MEDfieldValueUpdateEntityList41.c:
	${LN_S} -f $(top_srcdir)/src/ci/_MEDfieldValueUpdateEntityList41.c $@

# CLEANFILES = $(buildCxxFile)
EXTRA_DIST = CMakeLists.txt
