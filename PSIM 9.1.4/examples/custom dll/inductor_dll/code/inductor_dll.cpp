// This is a sample C program for Microsoft C/C++ 6.0.
// The generated DLL is to be linked to PSIM.

// To compile the program into DLL, you can open the workspace file "msvc_dll.dsw" 
// as provided.

// This sample program simulates an inductor through user defined code. 
// It reads the voltage from PSIM, and calculates and sends the current back to PSIM.

// Variables:
//      t: Time, passed from PSIM by value
//   delt: Time step, passed from PSIM by value
//     in: input array, passed from PSIM by reference
//    out: output array, sent back to PSIM (Note: the values of out[*] can
//         be modified in PSIM)

// The maximum length of the input and output array "in" and "out" is 30.

// Because we used static/global variables in this example, the DLL 
// can only be used once per schematic file.  


#include <math.h>
#include <stdio.h>

__declspec(dllexport) void simuser (double t, double delt, double *in, double *out)
{
// Place your code here............begin

//  Define "sum" as "static" in order to retain its value.
	static double lambda=0.0;
	static double L=0.005;

	double v, i;

	// Receive the voltage from PSIM
	v = in[0];
	
	// Integrate the voltage to obtain the flux linkage
	lambda = lambda + v*delt;

	// Calculate the current
	i = lambda / L;

	// Send the current back to PSIM
	out[0] = i;

// Place your code here............end
}
