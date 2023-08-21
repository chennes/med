include $(top_srcdir)/config/automake.common

DEFAULT_INCLUDES = -I. -I$(srcdir)

if ENABLE_FORTRAN

TESTS_ENVIRONMENT = eval H5DUMP=@H5DUMP@ SRCDIR=$(srcdir) SRCDIR="$(abs_srcdir)" BUILDDIR="$(abs_builddir)" \
		EXECDIR="$(abs_builddir)" CP=${CP} CPYMED="no"

#TESTS_ENVIRONMENT += UPDATE="yes"
#TESTS_ENVIRONMENT += OUTPUT="yes" 
#TESTS_ENVIRONMENT += OUTPUT="yes" CHECKER="libtool\ --mode=execute\ valgrind"

AM_LDFLAGS+= $(FTLDFLAGS)
LIBS += $(FTLIBS)
AM_LIBTOOLFLAGS = --tag=F77

testfdir = $(bindir)/testf

SUFFIXES=  _Rd.sh _Rd.she _Wr.sh _Wr.shn
# Inference rules can have only one target before the colon (POSIX)
.f_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
# les scripts .she sont les mêmes que les scripts .sh en lecture  mais provoquent la supression du fichier current.med
.f_Rd.she: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
.f_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@
# les scripts .shn sont les mêmes que les scripts .sh en écriture mais provoquent la comparaison du fichier avec un fichier de référence
.f_Wr.shn: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@


TESTS_LEC = Unittest_MEDlibrary_1_Rd.sh  Unittest_MEDsupportMesh_2_Rd.sh Unittest_MEDsupportMesh_3_Rd.sh \
Unittest_MEDstructElement_2_Rd.sh Unittest_MEDstructElement_3_Rd.sh \
Unittest_MEDstructElement_5_Rd.sh Unittest_MEDstructElement_6_Rd.sh \
Unittest_MEDstructElement_8_Rd.sh Unittest_MEDstructElement_10_Rd.sh \
Unittest_MEDstructElement_11_Rd.sh Unittest_MEDlink_2_Rd.sh Unittest_MEDlink_3_Rd.sh \
Unittest_MEDlocalization_2_Rd.sh Unittest_MEDlocalization_3_Rd.sh \
Unittest_MEDinterp_2_Rd.sh Unittest_MEDinterp_3_Rd.sh \
Unittest_MEDparameter_2_Rd.sh Unittest_MEDparameter_3_Rd.sh

TESTS_ECR = Unittest_MEDfile_1_Wr.sh Unittest_MEDsupportMesh_1_Wr.sh Unittest_MEDstructElement_1_Wr.sh  \
Unittest_MEDstructElement_4_Wr.sh Unittest_MEDstructElement_7_Wr.sh  Unittest_MEDstructElement_9_Wr.sh \
Unittest_MEDprofile_1_Wr.sh Unittest_MEDlink_1_Wr.sh Unittest_MEDlocalization_1_Wr.sh \
Unittest_MEDinterp_1_Wr.sh Unittest_MEDparameter_1_Wr.sh Unittest_MEDfilter_1_Wr.sh \
Unittest_MEDfilter_2_Wr.sh

BUILT_SOURCES=$(TESTS_ECR) $(TESTS_LEC)

TESTS =  $(TESTS_ECR) $(TESTS_LEC)

EXTRA_DIST = testRd.sh testWr.sh

LDADD = $(top_builddir)/src/libmed.la

# Les tests unitaires n'ont pas besoin d'être installés 
#testf_PROGRAMS = 
check_PROGRAMS = \
Unittest_MEDlibrary_1 Unittest_MEDfile_1 Unittest_MEDsupportMesh_1 Unittest_MEDsupportMesh_2 \
Unittest_MEDsupportMesh_3 Unittest_MEDstructElement_1  Unittest_MEDstructElement_2 Unittest_MEDstructElement_3 \
Unittest_MEDstructElement_4  Unittest_MEDstructElement_5  Unittest_MEDstructElement_6 Unittest_MEDstructElement_7 \
Unittest_MEDstructElement_8 Unittest_MEDstructElement_9 Unittest_MEDstructElement_10 \
Unittest_MEDstructElement_11 Unittest_MEDprofile_1 Unittest_MEDprofile_2 Unittest_MEDlink_1 \
Unittest_MEDlink_2 Unittest_MEDlink_3 \
Unittest_MEDlocalization_1 Unittest_MEDlocalization_2 Unittest_MEDlocalization_3 \
Unittest_MEDinterp_1 Unittest_MEDinterp_2 Unittest_MEDinterp_3 \
Unittest_MEDparameter_1 Unittest_MEDparameter_2 Unittest_MEDparameter_3 \
Unittest_MEDfilter_1 Unittest_MEDfilter_2


Unittest_MEDlibrary_1_SOURCES = Unittest_MEDlibrary_1.f 
Unittest_MEDfile_1_SOURCES = Unittest_MEDfile_1.f 
Unittest_MEDsupportMesh_1_SOURCES = Unittest_MEDsupportMesh_1.f 
Unittest_MEDsupportMesh_2_SOURCES = Unittest_MEDsupportMesh_2.f 
Unittest_MEDsupportMesh_3_SOURCES = Unittest_MEDsupportMesh_3.f 
Unittest_MEDstructElement_1_SOURCES = Unittest_MEDstructElement_1.f
Unittest_MEDstructElement_2_SOURCES = Unittest_MEDstructElement_2.f 
Unittest_MEDstructElement_3_SOURCES = Unittest_MEDstructElement_3.f 
Unittest_MEDstructElement_4_SOURCES = Unittest_MEDstructElement_4.f 
Unittest_MEDstructElement_5_SOURCES = Unittest_MEDstructElement_5.f 
Unittest_MEDstructElement_6_SOURCES = Unittest_MEDstructElement_6.f 
Unittest_MEDstructElement_7_SOURCES = Unittest_MEDstructElement_7.f 
Unittest_MEDstructElement_8_SOURCES = Unittest_MEDstructElement_8.f 
Unittest_MEDstructElement_9_SOURCES = Unittest_MEDstructElement_9.f
Unittest_MEDstructElement_10_SOURCES = Unittest_MEDstructElement_10.f 
Unittest_MEDstructElement_11_SOURCES = Unittest_MEDstructElement_11.f 
Unittest_MEDprofile_1_SOURCES = Unittest_MEDprofile_1.f 
Unittest_MEDprofile_2_SOURCES = Unittest_MEDprofile_2.f 
Unittest_MEDlink_1_SOURCES = Unittest_MEDlink_1.f 
Unittest_MEDlink_2_SOURCES = Unittest_MEDlink_2.f 
Unittest_MEDlink_3_SOURCES = Unittest_MEDlink_3.f 
Unittest_MEDlocalization_1_SOURCES = Unittest_MEDlocalization_1.f
Unittest_MEDlocalization_2_SOURCES = Unittest_MEDlocalization_2.f
Unittest_MEDlocalization_3_SOURCES = Unittest_MEDlocalization_3.f
Unittest_MEDinterp_1_SOURCES = Unittest_MEDinterp_1.f
Unittest_MEDinterp_2_SOURCES = Unittest_MEDinterp_2.f
Unittest_MEDinterp_3_SOURCES = Unittest_MEDinterp_3.f
Unittest_MEDparameter_1_SOURCES = Unittest_MEDparameter_1.f
Unittest_MEDparameter_2_SOURCES = Unittest_MEDparameter_2.f
Unittest_MEDparameter_3_SOURCES = Unittest_MEDparameter_3.f
Unittest_MEDfilter_1_SOURCES = Unittest_MEDfilter_1.f
Unittest_MEDfilter_2_SOURCES = Unittest_MEDfilter_2.f


CLEANFILES= \
Unittest_MEDfile_1.med \
Unittest_MEDfile_1.dump \
Unittest_MEDsupportMesh_1.med \
Unittest_MEDsupportMesh_1.dump \
Unittest_MEDstructElement_1.med \
Unittest_MEDstructElement_1.dump \
Unittest_MEDstructElement_4.med \
Unittest_MEDstructElement_4.dump \
Unittest_MEDstructElement_7.med \
Unittest_MEDstructElement_7.dump \
Unittest_MEDstructElement_9.med \
Unittest_MEDstructElement_9.dump \
Unittest_MEDprofile_1.med \
Unittest_MEDprofile_1.dump \
Unittest_MEDlink_1.med \
Unittest_MEDlink_1.dump \
Unittest_MEDlocalization_1.med \
Unittest_MEDlocalization_1.dump \
Unittest_MEDinterp_1.med \
Unittest_MEDinterp_1.dump \
Unittest_MEDparameter_1.med \
Unittest_MEDparameter_1.dump \
Unittest_MEDfilter_1.med \
Unittest_MEDfilter_1.dump \
Unittest_MEDfilter_2.med \
Unittest_MEDfilter_2.dump 

CLEANFILES+= $(BUILT_SOURCES) *.dump *.dump.ref *.dump.tmp *med.out *.out *.out.ref *.out.tmp


SUBDIRS = dumps.ref .

endif
