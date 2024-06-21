#!/usr/bin/env bash

MATRIX_FILES_DIR=../../test-generator/scripts/cholesky/
CHOLESKY=../cholesky
RESULT_OUTPUT_DIR=./results

NB_MEASURES=10
THREADS=(10 15 20 25 30 35 40)

mkdir -p $RESULT_OUTPUT_DIR

run_cholesky() {
  file=$1
  timesfile="times-$(echo $file | sed 's/\.in$/.txt/')"
  for threads in "${THREADS[@]}"; do
    mkdir -p $RESULT_OUTPUT_DIR/$threads
    echo "$CHOLESKY $MATRIX_FILES_DIR/$file $threads >> $RESULT_OUTPUT_DIR/$threads/$timesfile"
    for ((i=0; i<$NB_MEASURES; i+=1)); do
      $CHOLESKY $MATRIX_FILES_DIR/$file $threads >> $RESULT_OUTPUT_DIR/$threads/$timesfile
    done
  done
}

run_cholesky_manual() {
  if [ $# -eq 1 ]; then
    run_cholesky $1.in
  else
    for file in $(ls $MATRIX_FILES_DIR); do
      run_cholesky $file
    done
  fi
}

run_cholesky_auto() {
  timesfile="times-$1.txt"
  file=$1.in
  echo "$CHOLESKY $MATRIX_FILES_DIR/$file >> $RESULT_OUTPUT_DIR/$timesfile"
  $CHOLESKY $MATRIX_FILES_DIR/$file >> $RESULT_OUTPUT_DIR/$timesfile
}

run_cholesky_auto $1
