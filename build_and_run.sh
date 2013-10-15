#!/bin/bash -e

PERF_FILE="./perf_result"

if [ -f $PERF_FILE ];
then
  rm perf_result.dot
fi

. make.sh

for size in 50 100 200 300 400 500 600 700 800 900 1000
do
  echo $size
  echo "------------------------"
  (time ./floyd $size)
  echo "------------------------"
done
