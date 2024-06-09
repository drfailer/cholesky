#!/usr/bin/env bash

MATRIX_FILES_DIR=/scratch/rvc1/samples
CHOLESKY=/scratch/rvc1/cholesky
RESULT_OUTPUT_DIR=/scratch/rvc1/results-lapack-$1

mkdir -p $RESULT_OUTPUT_DIR

THREADS_MIN=8
THREADS_MAX=384
THREADS_INC=8

NB_MEASURES=1

mkdir -p $RESULT_OUTPUT_DIR

run_cholesky() {
  file=$1
  timesfile="times-$(echo $file | sed 's/\.in$/.txt/')"
  for ((threads=THREADS_MIN; threads<=THREADS_MAX; threads+=THREADS_INC)); do
    mkdir -p $RESULT_OUTPUT_DIR/$threads
    for ((i=0; i<$NB_MEASURES; i+=1)); do
      $CHOLESKY $MATRIX_FILES_DIR/$file $threads >> $RESULT_OUTPUT_DIR/$threads/$timesfile
    done
  done
}

if [ $# -eq 1 ]; then
  run_cholesky $1.in
else
  for file in $(ls $MATRIX_FILES_DIR); do
    run_cholesky $file
  done
fi
