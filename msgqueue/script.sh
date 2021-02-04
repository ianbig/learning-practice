#!/bin/bash
# program:
#   use to test IPC 1 server multiple client by creating and client every 3~5 msec in background

# ./master &

DIV=$((5 - 3 + 1))
sleep_sec=$((${RANDOM} % ${DIV} + 3))
sleep_sec=$(echo "scale=3; ${sleep_sec} / 1000" | bc)

Q_DIV=$(( 5 - 1 + 1))
FILE_LINE=$((${RANDOM} % Q_DIV + 1))
question=$(awk "NR==${FILE_LINE}" question.txt)

sec=$(date '+%S')
i=0
echo ${sec}
while [ $(( $(date '+%S') - ${sec} )) -lt "10" ]
do
    # sleep ${sleep_sec}
    ./client "${question}" &

    i=$(( ${i} + 1))
    # sleep_sec=$((${RANDOM} % ${DIV} + 3))
    # sleep_sec=$(echo "scale=3; ${sleep_sec} / 1000" | bc)

    FILE_LINE=$((${RANDOM} % Q_DIV + 1))
    question=$(awk "NR==${FILE_LINE}" question.txt)
done

echo "Send out ${i} queries"