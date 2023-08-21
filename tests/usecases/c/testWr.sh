#!/bin/sh
file=`echo ${0##*/} | sed 's/\(^.*\)_Wr\.sh$/\1/'`
fileref=${file}
medint=
case $file in
       UsesCase_MEDfield_15b*) fileref=UsesCase_MEDfield_15
       ;;
       *)
       ;;
esac
test "x${CPYMED}" = "xyes" && ${CP} ${SRCDIR}/test.med.ref ${BUILDDIR}/${file}.med && chmod 644 ${BUILDDIR}/${file}.med
output=/dev/null && test "x${OUTPUT}" = "xyes" && output=${file}.out
${CHECKER} ${EXECDIR}/${file} ${SRCDIR}/dumps.ref/UsesCase_MEDstructElement_1_byid.med > ${output} 2>&1 && ${H5DUMP} ${BUILDDIR}/${file}.med > ${BUILDDIR}/${file}.dump && ( \
sed -e 's/H5T_STD_[BI]32[LB]E//g'  \
    -e 's/H5T_STD_I64BE//g' -e 's/H5T_STD_I64LE//g'  \
    -e 's/H5T_IEEE_F64BE//g' -e 's/H5T_IEEE_F64LE//g'  \
    -e 's/H5T_STD_[IU]8[LB]E//g'  \
    -e 's/HDF5.*{//g' \
${BUILDDIR}/${file}.dump > ${BUILDDIR}/${file}.dump.tmp && \
sed -e 's/H5T_STD_[BI]32[LB]E//g'  \
    -e 's/H5T_STD_I64BE//g' -e 's/H5T_STD_I64LE//g'  \
    -e 's/H5T_IEEE_F64BE//g' -e 's/H5T_IEEE_F64LE//g'  \
    -e 's/H5T_STD_[IU]8[LB]E//g'  \
    -e 's/HDF5.*{//g' \
${BUILDDIR}/dumps.ref/${fileref}.dump > ${BUILDDIR}/${file}.dump.ref && \
diff ${BUILDDIR}/${file}.dump.ref ${BUILDDIR}/${file}.dump.tmp && \
rm -f ${BUILDDIR}/${file}.dump.tmp && rm -f ${BUILDDIR}/${file}.dump.ref )
exit_code=$?
test "x${UPDATE}" = "xyes"  && test $exit_code -ne 0 && cp ${BUILDDIR}/${file}.med ${SRCDIR}/dumps.ref/${file}${medint}.med && svn st -v ${SRCDIR}/dumps.ref/${file}${medint}.med
exit $exit_code
