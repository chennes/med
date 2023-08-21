#!/bin/sh
file=`echo ${0##*/} | sed 's/\(^.*\)_Rd\.sh[ne]\{0,1\}$/\1/'`
output=/dev/null && test "x${OUTPUT}" = "xyes" && output=${file}.out
${CHECKER} ${EXECDIR}/${file} > ${output} 2>&1
