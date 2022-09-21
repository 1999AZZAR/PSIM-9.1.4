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

//  Define following variables as "static" in order to retain their value.
	static double yv=0.0;
	static double yi=0.0;
	static double uv=0.0;
	static double ui=0.0;
	static double iref = 0.0;
	static int count=0;
	static int Ncount = 0;
	static int flagSample=1;
	static int npulse=0;
	static int npulse_next=0;
	static int gating=0;



	double Voref=10.5, Vcarr=10., Va, iL, Vo, Vm;
	double errv, erri, Ts=33.33e-6;

// Calculate the no. of counts in one period
	Ncount=Ts/delt;

// Check if the counter reaches the end of the period. If yes,
// set the sampling flag to 1. 
	if (count == Ncount)
	{
		flagSample=1;
//      Reset the counter to 0.
		count=0;
//      Update the on-time pulse width
		npulse=npulse_next;
	}

// If the sampling flag is 1, sample the inputs and calculate the
// on-time pulse width npulse.
	if (flagSample == 1)
	{
//		Reset the sampling flag
		flagSample=0;

//		Sample the inputs
		Va=fabs(in[0]);
		iL=in[1];
		Vo=in[2];

//		Calculate the outer loop PI controller using Trapezoidal Rule
		errv=Voref-Vo;
		yv=yv+(33.33*errv+uv)*Ts/2.;

		iref=(errv+yv)*Va;

//		Calculate the inner loop PI controller
		erri=iref-iL;
		yi=yi+(3400.*erri+ui)*Ts/2.;

		Vm=yi+0.3*erri;

//		Calculate the on-time pulse width.
//      Note that this value is not used within this sampling period, but 
//      is used at the beginning of the next sampling period.
		npulse_next=Ncount * (Vm/Vcarr);

//		Store old values
		uv=33.33*errv;
		ui=3400.*erri;

	}

// Generate the switch gating signal
	if (count <= npulse )
	{gating=1;}
	else
	{gating=0;}

// Output
	out[0]=gating;
	out[1]=iref;
	out[2]=npulse;

// Note: Among the 3 output variables, "gating" is calculated at
// every time step, but "iref" and "npulse" are calculated only
// once in one sampling period. Both "gating" and "iref" can be
// defined as either static or non-static. 
	
// But if "iref" is defined as non-static, its value will be zero at 
// the points other than the sampling point. In order to see the 
// value at the sampling point, the print step Iprint in the simulation
// control in SIMCAD must be set to 1. Otherwise the sampling point 
// may be skipped, resulting in a waveform of all zero.


// The variable "npulse" must be declared as static as its
// value is used at every time step and must be retained.


// Increment the counter by 1
	count++;

// Place your code here............end
}
