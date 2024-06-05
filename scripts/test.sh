#!/usr/bin/env bash

MATRIX_FILES_DIR=../../test-generator/build/test
CHOLESKY=../cholesky
RESULT_OUTPUT_DIR=./result

mkdir -p $RESULT_OUTPUT_DIR

for file in $(ls $MATRIX_FILES_DIR); do
  timesfile="times-$(echo $file | sed 's/\.in$/.txt/')"
  for i in {1..10}; do
    $CHOLESKY $MATRIX_FILES_DIR/$file lapack >> $RESULT_OUTPUT_DIR/$timesfile
  done
done
