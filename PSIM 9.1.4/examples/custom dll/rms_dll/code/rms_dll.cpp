// This is a sample C program for Microsoft C/C++ 6.0.
// The generated DLL is to be linked to PSIM.

// To compile the program into DLL, you can open the workspace file "msvc_dll.dsw" 
// as provided.

// This sample program calculates the rms of a 60-Hz input in[0], and
// stores the output in out[0].

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

__declspec(dllexport) void simuser (double t, double delt, double *in, double *out)
{
// Place your code here............begin

//  Define "sum" as "static" in order to retain its value.
	static double nsum=0., sum=0., rms;
	double Tperiod;

	Tperiod=1./60.;

	if (t >= nsum*Tperiod)
	{
		nsum=nsum+1.;
		rms = sqrt(sum*delt/Tperiod);
		sum=0.;
	}

	out[0] = rms;
	sum=sum+in[0]*in[0];

// Place your code here............end
}
