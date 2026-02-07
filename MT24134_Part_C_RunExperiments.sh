#!/bin/bash
MSG_SIZES=(1024 4096 16384 65536)
THREADS=(1 2 4 8)
DURATION=10

make clean
make

for size in "${MSG_SIZES[@]}"; do
  for th in "${THREADS[@]}"; do
    ./MT24134_Part_A1_Server $th $size & PID=$!
    sleep 1
    perf stat -e cycles,branch-misses,context-switches \
      ./MT24134_Part_A1_Client $DURATION $size \
      &> MT24134_perf_two_copy_${size}_${th}.csv
    kill $PID

    ./MT24134_Part_A2_Server $th $size & PID=$!
    sleep 1
    perf stat -e cycles,branch-misses,context-switches \
      ./MT24134_Part_A2_Client $DURATION $size \
      &> MT24134_perf_one_copy_${size}_${th}.csv
    kill $PID

    ./MT24134_Part_A3_Server $th $size & PID=$!
    sleep 1
    perf stat -e cycles,branch-misses,context-switches \
      ./MT24134_Part_A3_Client $DURATION $size \
      &> MT24134_perf_zero_copy_${size}_${th}.csv
    kill $PID
  done
done