#ifndef CSPROF_NAME_H
#define CSPROF_NAME_H

/******************************************************************************
 * File: name.h 
 *
 * Purpose: maintain the name of the executable
 *
 * Modification history:
 *   28 October 2007 - created - John Mellor-Crummey
 *****************************************************************************/

/******************************************************************************
 * macros 
 *****************************************************************************/

#define UNKNOWN_MPI_RANK (-1)

/******************************************************************************
 * interface functions
 *****************************************************************************/

extern void csprof_set_executable_name(char *argv0);
extern const char *csprof_get_executable_name();

#if 0
void csprof_set_mpirank(int rank);
int csprof_get_mpirank();
#endif

#endif
