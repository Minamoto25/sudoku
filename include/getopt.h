/*
* Copyright (c) 1987, 1993, 1994
*      The Regents of the University of California.  All rights reserved.
*/
#ifndef INCLUDE_GETOPT_H_
#define INCLUDE_GETOPT_H_

extern int opterr;   /* if error message should be printed */
extern int optind;   /* index into parent argv vector */
extern int optopt;   /* character checked for validity */
extern int optreset; /* reset getopt  */
extern char *optarg; /* argument associated with option */

int getopt(int nargc, char *const nargv[], const char *ostr);

#endif  // INCLUDE_GETOPT_H_
