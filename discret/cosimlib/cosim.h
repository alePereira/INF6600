#ifndef COSIM_H
#define COSIM_H

#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

enum TimeUnit {s, ms, us, ns};

extern void close_cosim();

extern void set_cosim();

extern LPVOID set_simcontext();

inline extern void WriteSignalToSimulink (double, const int );

inline extern double ReadSignalFromSimulink (const int );

extern HANDLE PassSemPtrsClient ();
extern HANDLE PassSemPtrsCreator ();

inline extern void SwitchContextFlag ();
inline extern void SwitchContext ();
//inline extern void delay(double, TimeUnit);


#endif