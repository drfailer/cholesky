#!/usr/bin/env bash

# MATRIX_FILES_DIR=../../test-generator/scripts/cholesky/
MATRIX_FILES_DIR=../../test-generator/build/cholesky/
CHOLESKY=../cholesky
RESULT_OUTPUT_DIR=./result

THREADS_MIN=10
THREADS_MAX=40
THREADS_INC=5

mkdir -p $RESULT_OUTPUT_DIR

for file in $(ls $MATRIX_FILES_DIR); do
  timesfile="times-$(echo $file | sed 's/\.in$/.txt/')"
  for ((threads=THREADS_MIN; threads<=THREADS_MAX; threads+=THREADS_INC)); do
    mkdir -p $RESULT_OUTPUT_DIR/$threads
    for i in {1..10}; do
      $CHOLESKY $MATRIX_FILES_DIR/$file lapack >> $RESULT_OUTPUT_DIR/$threads/$timesfile
    done
  done
done
