#ifndef Print_h
#define Print_h

const int DEC = 10;

const int HEX = 16;

const int OCT = 8;

#if defined( BIN )
#undef BIN
#warning BIN previously defined; probably in a processor specific header.
#endif

const int BIN = 2;

// fix: Print in the rest of Print.h

#endif
