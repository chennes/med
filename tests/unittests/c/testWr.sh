#!/bin/sh
# file=`basename $0 | sed 's/\.sh.\{0,1\}$//g'`
file=`echo ${0##*/} | sed 's/\(^.*\)_Wr\.sh[ne]\{0,1\}$/\1/'`
shn=`basename $0 | sed 's/^.*\(.\)$/\1/'`
medint=""
output=/dev/null && test "x${OUTPUT}" = "xyes" && output=${file}.out
${CHECKER} ${EXECDIR}/${file} > ${output} 2>&1 && (test "x${shn}" = "xn" && ${CP} ${BUILDDIR}/current.med ${BUILDDIR}/${file}.med || true) && \
${H5DUMP} ${BUILDDIR}/${file}.med > ${BUILDDIR}/${file}.dump && ( \
sed -e 's/H5T_STD_I32BE//g' -e 's/H5T_STD_I32LE//g'	 \
    -e 's/H5T_STD_I64BE//g' -e 's/H5T_STD_I64LE//g'  \
    -e 's/H5T_IEEE_F64BE//g' -e 's/H5T_IEEE_F64LE//g'  \
    -e 's/H5T_STD_[IU]8[BL]E//g'  \
    -e 's/HDF5.*{//g' \
${BUILDDIR}/${file}.dump > ${BUILDDIR}/${file}.dump.tmp && \
sed -e 's/H5T_STD_I32BE//g' -e 's/H5T_STD_I32LE//g'	 \
    -e 's/H5T_STD_I64BE//g' -e 's/H5T_STD_I64LE//g'  \
    -e 's/H5T_IEEE_F64BE//g' -e 's/H5T_IEEE_F64LE//g'  \
    -e 's/H5T_STD_[IU]8[BL]E//g'  \
    -e 's/HDF5.*{//g' \
${BUILDDIR}/dumps.ref/${file}.dump > ${BUILDDIR}/${file}.dump.ref && \
diff ${BUILDDIR}/${file}.dump.ref ${BUILDDIR}/${file}.dump.tmp && \
rm -f ${BUILDDIR}/${file}.dump.tmp && rm -f ${BUILDDIR}/${file}.dump.ref )
exit_code=$?
test "x${UPDATE}" = "xyes"  && test $exit_code -ne 0 && cp ${BUILDDIR}/${file}.med ${SRCDIR}/dumps.ref/${file}${medint}.med && svn st -v ${SRCDIR}/dumps.ref/${file}${medint}.med
exit $exit_code

#${EXECDIR}/dump.sh `basename $0 | sed 's/\.sh//g' `
