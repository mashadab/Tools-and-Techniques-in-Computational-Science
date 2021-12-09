AM_CXXFLAGS = $(GRVY_CFLAGS) $(MASA_CXXFLAGS) $(HDF5_CFLAGS)
LIBS = $(GRVY_LIBS) $(MASA_LIBS) $(HDF5_LIBS)

if PETSC_ENABLED	
include $(PETSC_DIR)/lib/petsc/conf/variables
AM_CXXFLAGS	+= -DINCLUDE_PETSC $(PETSC_CC_INCLUDES) 
endif

bin_PROGRAMS = solve_heatcond
solve_heatcond_SOURCES = main_code.cpp global_timer.h solver.cpp assemble.cpp assemble_RHS.cpp assemble_Texact.cpp verification_debug.cpp hdf5_write_output_file.cpp write_output_file.cpp

if PETSC_ENABLED
LIBS	+= ${PETSC_LIB}
endif

