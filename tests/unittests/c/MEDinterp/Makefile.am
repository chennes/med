include $(top_srcdir)/config/automake.common

TESTS_ENVIRONMENT = eval H5DUMP=@H5DUMP@ SRCDIR="$(abs_srcdir)" BUILDDIR="$(abs_builddir)" \
		EXECDIR="$(abs_builddir)" CP=${CP} CPYMED="no" 

#TESTS_ENVIRONMENT += UPDATE="yes"
#TESTS_ENVIRONMENT += OUTPUT="yes" DIFFOUTPUT="yes"
#TESTS_ENVIRONMENT += OUTPUT="yes" CHECKER="libtool --mode=execute valgrind"

unittestsdir= $(bindir)/unittests

##check_PROGRAMS
##bin_PROGRAMS

AM_CFLAGS = -DDEF_LECT_ECR
#-DUSER_INTERLACE=MED_FULL_INTERLACE
#-DDEF_LECT_AJOUT

check_PROGRAMS = \
Test_MEDinterpCr \
Test_MEDinterpBaseFunctionWr \
Test_MEDinterpInfo \
Test_MEDinterpBaseFunctionRd \
Test_MEDinterpBaseFunctionCoeffSize \
Test_MEDfieldInterpWr \
Test_MEDfieldInterpInfo

# Les tests unitaires n'ont pas besoin d'être installés 
# unittests_PROGRAMS = \
# Test_MEDinterpBaseFunctionWr \
# Test_MEDinterpInfo \
# Test_MEDinterpBaseFunctionRd \
# Test_MEDinterpBaseFunctionCoeffSize \
# Test_MEDfieldInterpWr \
# Test_MEDfieldInterpInfo

LDADD = $(top_builddir)/src/libmedC.la

nodist_EXTRA_Test_MEDinterpCr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDinterpBaseFunctionWr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDinterpInfo_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDinterpBaseFunctionRd_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDinterpBaseFunctionCoeffSize_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDfieldInterpWr_SOURCES = dummy.cxx
nodist_EXTRA_Test_MEDfieldInterpInfo_SOURCES = dummy.cxx

# Les tests unitaires travaillent avec un fichier commun current.med (qui est dupliqué ds <nom_du_test>.med ds les scripts .shn)
# Il faut donc parfois un sous répertoire pour tester des fonctions qui travaillent sur un fichier current.med différent
# (sauf si on s'affranchit de l'utilisation du fichier current.med ou après l'avoir supprimé par un script .she)
# Les scripts doivent s'executer de façon séquentielle

SUFFIXES=  _Rd.sh _Rd.she _Wr.sh _Wr.shn
# Inference rules can have only one target before the colon (POSIX)
.c_Rd.sh: testRd.sh
	${LN_S} -f $(srcdir)/../testRd.sh $@
# les scripts .she sont les mêmes que les scripts .sh en lecture  mais provoquent la supression du fichier current.med
.c_Rd.she: testRd.sh
	${LN_S} -f $(srcdir)/../testRd.sh $@
.c_Wr.sh: testWr.sh
	${LN_S} -f $(srcdir)/../testWr.sh $@
# les scripts .shn sont les mêmes que les scripts .sh en écriture mais provoquent la comparaison du fichier avec un fichier de référence
.c_Wr.shn: testWr.sh
	${LN_S} -f $(srcdir)/../testWr.sh $@

TESTS_LEC = \
Test_MEDinterpInfo_Rd.sh \
Test_MEDinterpBaseFunctionRd_Rd.sh \
Test_MEDinterpBaseFunctionCoeffSize_Rd.sh \
Test_MEDfieldInterpInfo_Rd.she

TESTS_ECR = \
Test_MEDinterpCr_Wr.shn \
Test_MEDinterpBaseFunctionWr_Wr.shn \
Test_MEDfieldInterpWr_Wr.shn

BUILT_SOURCES=$(TESTS_ECR) $(TESTS_LEC)

TESTS = $(TESTS_ECR) $(TESTS_LEC)

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
./Test_MEDinterpCr.med \
./Test_MEDinterpBaseFunctionWr.med \
./Test_MEDfieldInterpWr.med \
./Test_MEDinterpCr.dump \
./Test_MEDinterpBaseFunctionWr.dump \
./Test_MEDfieldInterpWr.dump \
./current.med

CLEANFILES+= $(BUILT_SOURCES) *.dump *.dump.ref *.dump.tmp *med.out *.out *.out.ref *.out.tmp

SUBDIRS = dumps.ref . 
