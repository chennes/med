include $(top_srcdir)/config/automake.common

TESTS_ENVIRONMENT = eval H5DUMP=@H5DUMP@ SRCDIR="$(abs_srcdir)" BUILDDIR="$(abs_builddir)" \
		EXECDIR="$(abs_builddir)" CP=${CP} CPYMED="no" 

#TESTS_ENVIRONMENT += UPDATE="yes"
#TESTS_ENVIRONMENT += OUTPUT="yes" DIFFOUTPUT="yes"
#TESTS_ENVIRONMENT += OUTPUT="yes" CHECKER="libtool\ --mode=execute\ valgrind"

unittestsdir= $(bindir)/unittests

##check_PROGRAMS
##bin_PROGRAMS

AM_CFLAGS = -DDEF_LECT_ECR
#-DUSER_INTERLACE=MED_FULL_INTERLACE
#-DDEF_LECT_AJOUT

# Les tests unitaires n'ont pas besoin d'être installés 
#unittests_PROGRAMS =
check_PROGRAMS = \
Unittest_MEDlibrary_1 \
Unittest_MEDfile_1 \
Unittest_MEDparameter_1 \
Test_MEDsupportMesh \
Test_MEDstructElementCr \
Test_MEDstructElementConstAttWithProfileWr \
Test_MEDstructElementVarAttCr \
Test_MEDmeshStructElementVarAttWr \
Test_MEDnStructElement \
Test_MEDstructElementInfoByName \
Test_MEDstructElementInfo \
Test_MEDstructElementConstAttInfo \
Test_MEDstructElementConstAttRd \
Test_MEDstructElementVarAttInfo \
Test_MEDmeshStructElementVarAttRd \
Test_MEDmeshEntityInfo

LDADD = $(top_builddir)/src/libmedC.la

nodist_EXTRA_Unittest_MEDfile_1_SOURCES = dummy.cxx
nodist_EXTRA_Unittest_MEDlibrary_1_SOURCES = dummy.cxx
nodist_EXTRA_Unittest_MEDparameter_1_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDsupportMesh_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementCr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementConstAttWithProfileWr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDnStructElement_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementInfoByName_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementInfo_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementConstAttInfo_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementConstAttRd_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementVarAttCr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDstructElementVarAttInfo_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDmeshStructElementVarAttWr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDmeshStructElementVarAttRd_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDmeshEntityInfo_SOURCES = dummy.cxx

# Les tests unitaires travaillent avec un fichier commun current.med (qui est dupliqué ds <nom_du_test>.med ds les scripts .shn)
# Il faut donc parfois un sous répertoire pour tester des fonctions qui travaillent sur un fichier current.med différent
# (sauf si on s'affranchit de l'utilisation du fichier current.med ou après l'avoir supprimé par un script .she)
# Les scripts doivent s'executer de façon séquentielle

SUFFIXES=  _Rd.sh _Rd.she _Wr.sh _Wr.shn
# Inference rules can have only one target before the colon (POSIX)
.c_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
# les scripts .she sont les mêmes que les scripts .sh en lecture  mais provoquent la supression du fichier current.med
.c_Rd.she: testRd.sh
	${LN_S} -f $(srcdir)/testRd.sh $@
.c_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@
# les scripts .shn sont les mêmes que les scripts .sh en écriture mais provoquent la comparaison du fichier avec un fichier de référence
.c_Wr.shn: testWr.sh
	${LN_S} -f $(srcdir)/testWr.sh $@

TESTS_LEC = Unittest_MEDlibrary_1_Rd.sh \
Test_MEDnStructElement_Rd.sh \
Test_MEDstructElementInfoByName_Rd.sh \
Test_MEDstructElementInfo_Rd.sh \
Test_MEDstructElementConstAttInfo_Rd.sh \
Test_MEDstructElementConstAttRd_Rd.sh \
Test_MEDstructElementVarAttInfo_Rd.sh \
Test_MEDmeshStructElementVarAttRd_Rd.she \
Test_MEDmeshEntityInfo_Rd.sh

TESTS_ECR = Unittest_MEDfile_1_Wr.sh \
Unittest_MEDparameter_1_Wr.sh \
Test_MEDsupportMesh_Wr.shn \
Test_MEDstructElementCr_Wr.shn \
Test_MEDstructElementConstAttWithProfileWr_Wr.shn \
Test_MEDstructElementVarAttCr_Wr.shn \
Test_MEDmeshStructElementVarAttWr_Wr.shn

BUILT_SOURCES=$(TESTS_ECR) $(TESTS_LEC)

TESTS = $(TESTS_ECR) $(TESTS_LEC)

EXTRA_DIST = testRd.sh testWr.sh

#check_local:
#	$(MAKE) check_test_ecr
#	$(MAKE) check_test_lec SRC_REP=$(srcdir)
#	$(MAKE) check_test_lec SRC_REP=$(srcdir)/2.3.1

#check_test_ecr: $(TESTS_ECR)
#	@for testfile in $1 \
#	do \
#	  $$testfile \
#	done

#check_test_lec: $(TESTS_LEC)
#	@for testfile in $1 \
#	do \
#	  dump.sh $$testfile @H5DUMP@ SRCDIR=$(srcdir) $(SRC_REP)\
#	done


CLEANFILES = \
./Unittest_MEDfile_1.med \
./Unittest_MEDparameter_1.med \
./Test_MEDsupportMesh.med \
./Test_MEDstructElementCr.med \
./Test_MEDstructElementConstAttWithProfileWr.med \
./Test_MEDstructElementVarAttCr.med \
./Test_MEDmeshStructElementVarAttWr.med \
./Unittest_MEDfile_1.dump \
./Unittest_MEDparameter_1.dump \
./Test_MEDsupportMesh.dump \
./Test_MEDstructElementCr.dump \
./Test_MEDstructElementConstAttWithProfileWr.dump \
./Test_MEDstructElementVarAttCr.dump \
./Test_MEDmeshStructElementVarAttWr.dump \
./current.med

#CLEANFILES+= $(TESTS_ECR) $(TESTS_LEC)
CLEANFILES+= $(BUILT_SOURCES) *.dump *.dump.ref *.dump.tmp *med.out *.out *.out.ref *.out.tmp

SUBDIRS = dumps.ref . MEDinterp MEDmesh
