#!/bin/sh
file=`echo ${0##*/} | sed 's/\(^.*\)_Rd\.sh$/\1/'`
#basename n'est pas forcément disponible sur tous les unix
#file=basename $0 | sed 's/\(^.*\)\.sh$/\1/'

output=/dev/null && test "x${OUTPUT}" = "xyes" && output=${file}.out
${CHECKER} ${EXECDIR}/${file} > ${output} 2>&1
