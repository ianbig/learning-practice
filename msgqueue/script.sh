#!/bin/bash
# program:
#   use to test IPC 1 server multiple client by creating and client every 3~5 msec in background

Q_DIV=$(( 5 - 1 + 1))
SETNUM=1
FILE_LINE=$((${SETNUM} % Q_DIV + 1))
question=$(awk "NR==${FILE_LINE}" question.txt)

while true
do
    sleep .005
    ./client "${question}" &

    SETNUM=$((${SETNUM} + 1 ))
    FILE_LINE=$((${SETNUM} % Q_DIV + 1))
    question=$(awk "NR==${FILE_LINE}" question.txt)
    echo ${SETNUM}
done
