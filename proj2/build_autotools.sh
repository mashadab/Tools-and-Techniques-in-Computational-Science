#!/bin/bash

#For make checks, export PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH
module load hdf5

module load petsc

export PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH

export CLASSPATH=/work/00161/karl/stampede2/public

export MODULEPATH=$CLASSPATH/ohpc/pub/modulefiles/:$MODULEPATH

module swap intel gnu7

autoreconf -f -i

./configure CC=mpicc CXX=mpicxx --with-masa=$CLASSPATH/masa-gnu7-0.50 \
--with-grvy=$CLASSPATH/grvy-gnu7-0.34 \
--with-hdf5=$TACC_HDF5_DIR \
--with-petsc=$TACC_PETSC_DIR

# For configuring without PETSc
#./configure --with-masa=$CLASSPATH/masa-gnu7-0.50 \
#--with-grvy=$CLASSPATH/grvy-gnu7-0.34 \
#--with-hdf5=$TACC_HDF5_DIR \
#--enable-coverage


