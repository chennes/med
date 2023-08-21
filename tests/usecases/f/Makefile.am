include $(top_srcdir)/config/automake.common

DEFAULT_INCLUDES = -I. -I$(srcdir)

if ENABLE_FORTRAN

TESTS_ENVIRONMENT = eval H5DUMP=@H5DUMP@ SRCDIR=$(srcdir) SRCDIR="$(abs_srcdir)" BUILDDIR="$(abs_builddir)" \
		EXECDIR="$(abs_builddir)" CP=${CP} CPYMED="no"
#TESTS_ENVIRONMENT += UPDATE="yes"

AM_LDFLAGS+= $(FTLDFLAGS)
LIBS += $(FTLIBS)
AM_LIBTOOLFLAGS = --tag=F77

testfdir = $(bindir)/testf

SUFFIXES=  _Rd.sh _Wr.sh

#Pour la génération des tests en _Rd.sh et _Wr.sh à partir des deux scripts testWr.sh et testRd.sh
.f_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
.f_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@
.f90_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
.f90_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@
.F90_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
.F90_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@

if WITHF90

mycheckPROGRAMS = \
UsesCase_MEDmesh_2 \
UsesCase_MEDmesh_3 \
UsesCase_MEDmesh_5 \
UsesCase_MEDmesh_7 \
UsesCase_MEDmesh_8 \
UsesCase_MEDmesh_11 \
UsesCase_MEDmesh_12 \
UsesCase_MEDmesh_14 \
UsesCase_MEDfield_2 \
UsesCase_MEDfield_3 \
UsesCase_MEDfield_5 \
UsesCase_MEDfield_6
#UsesCase_MEDmesh_16 

myTESTS_LEC = \
UsesCase_MEDmesh_2_Rd.sh \
UsesCase_MEDmesh_3_Rd.sh \
UsesCase_MEDmesh_5_Rd.sh \
UsesCase_MEDmesh_7_Rd.sh \
UsesCase_MEDmesh_8_Rd.sh \
UsesCase_MEDmesh_11_Rd.sh \
UsesCase_MEDmesh_12_Rd.sh \
UsesCase_MEDmesh_14_Rd.sh \
UsesCase_MEDfield_2_Rd.sh \
UsesCase_MEDfield_3_Rd.sh \
UsesCase_MEDfield_5_Rd.sh \
UsesCase_MEDfield_6_Rd.sh
#UsesCase_MEDmesh_16_Rd.sh 

UsesCase_MEDmesh_2_SOURCES  = UsesCase_MEDmesh_2.f90
UsesCase_MEDmesh_3_SOURCES  = UsesCase_MEDmesh_3.f90
UsesCase_MEDmesh_5_SOURCES  = UsesCase_MEDmesh_5.f90
UsesCase_MEDmesh_7_SOURCES  = UsesCase_MEDmesh_7.f90
UsesCase_MEDmesh_8_SOURCES  = UsesCase_MEDmesh_8.f90
UsesCase_MEDmesh_11_SOURCES = UsesCase_MEDmesh_11.f90
UsesCase_MEDmesh_12_SOURCES = UsesCase_MEDmesh_12.f90
UsesCase_MEDmesh_14_SOURCES = UsesCase_MEDmesh_14.f90
UsesCase_MEDfield_2_SOURCES = UsesCase_MEDfield_2.f90
UsesCase_MEDfield_3_SOURCES = UsesCase_MEDfield_3.f90
UsesCase_MEDfield_5_SOURCES = UsesCase_MEDfield_5.f90
UsesCase_MEDfield_6_SOURCES = UsesCase_MEDfield_6.f90
#UsesCase_MEDmesh_16_SOURCES = UsesCase_MEDmesh_16.f90

endif

TESTS_LEC = $(myTESTS_LEC)

TESTS_ECR = \
UsesCase_MEDmesh_1_Wr.sh \
UsesCase_MEDmesh_4_Wr.sh \
UsesCase_MEDmesh_6_Wr.sh \
UsesCase_MEDmesh_9_Wr.sh \
UsesCase_MEDmesh_10_Wr.sh \
UsesCase_MEDmesh_13_Wr.sh \
UsesCase_MEDfield_1_Wr.sh \
UsesCase_MEDfield_4_Wr.sh
#UsesCase_MEDmesh_15_Wr.sh 

BUILT_SOURCES=$(TESTS_ECR) $(TESTS_LEC)

TESTS = $(TESTS_ECR) $(TESTS_LEC)

EXTRA_DIST = testRd.sh testWr.sh

LDADD = $(top_builddir)/src/libmed.la

if INSTALLTEST

testf_PROGRAMS = \
UsesCase_MEDmesh_1 \
UsesCase_MEDmesh_4 \
UsesCase_MEDmesh_6 \
UsesCase_MEDmesh_9 \
UsesCase_MEDmesh_10 \
UsesCase_MEDmesh_13 \
UsesCase_MEDfield_1 \
UsesCase_MEDfield_4 $(mycheckPROGRAMS)
#UsesCase_MEDmesh_15 

else


check_PROGRAMS = \
UsesCase_MEDmesh_1 \
UsesCase_MEDmesh_4 \
UsesCase_MEDmesh_6 \
UsesCase_MEDmesh_9 \
UsesCase_MEDmesh_10 \
UsesCase_MEDmesh_13 \
UsesCase_MEDfield_1 \
UsesCase_MEDfield_4 $(mycheckPROGRAMS)
#UsesCase_MEDmesh_15 

endif

UsesCase_MEDmesh_1_SOURCES  = UsesCase_MEDmesh_1.f 
UsesCase_MEDmesh_4_SOURCES  = UsesCase_MEDmesh_4.f
UsesCase_MEDmesh_6_SOURCES  = UsesCase_MEDmesh_6.f
UsesCase_MEDmesh_9_SOURCES  = UsesCase_MEDmesh_9.f
UsesCase_MEDmesh_10_SOURCES = UsesCase_MEDmesh_10.f
UsesCase_MEDmesh_13_SOURCES = UsesCase_MEDmesh_13.f
#UsesCase_MEDmesh_15_SOURCES = UsesCase_MEDmesh_15.f
UsesCase_MEDfield_1_SOURCES = UsesCase_MEDfield_1.f
UsesCase_MEDfield_4_SOURCES = UsesCase_MEDfield_4.f

CLEANFILES= \
UsesCase_MEDmesh_1.med \
UsesCase_MEDmesh_4.med \
UsesCase_MEDmesh_6.med \
UsesCase_MEDmesh_9.med \
UsesCase_MEDmesh_10.med \
UsesCase_MEDmesh_13.med \
UsesCase_MEDmesh_15.med \
UsesCase_MEDfield_1.med \
UsesCase_MEDfield_4.med \
\
UsesCase_MEDmesh_1.dump \
UsesCase_MEDmesh_4.dump \
UsesCase_MEDmesh_6.dump \
UsesCase_MEDmesh_9.dump \
UsesCase_MEDmesh_10.dump \
UsesCase_MEDmesh_13.dump \
UsesCase_MEDmesh_15.dump \
UsesCase_MEDfield_1.dump \
UsesCase_MEDfield_4.dump

CLEANFILES+= $(TESTS_ECR) $(TESTS_LEC)
CLEANFILES+= $(BUILT_SOURCES) *med.out *.out *.out.ref *.out.tmp *.dump.ref *.dump.tmp

SUBDIRS = dumps.ref .

endif
#endif ENABLE_FORTRAN
