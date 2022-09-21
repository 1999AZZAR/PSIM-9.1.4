//
// This example shows how to call PSIM through the command line option.
//
// The format to call the command-line version of PSIM is as follows:
//
//    PsimCmd.exe  -i "[input file]"  -o "[output file]"  -v "Var_name=Var_value" -g   
//
// The command line parameters are:
//      -i:  input schematic file. 
//      -o:  output result file in either text format (.txt) or binary format (.smv).
//      -v:  variable definition. "Var_name" is the variable name as defined in PSIM, and
//           "Var_value" is the numerical value of the variable. 
//           This parameter can be used multiple times. 
//           For example, to set the values of two parameters R1 and R2 in PSIM, use:
//              -v "R1=10" -v "R2=5" 
//      -t:  total time of the simulation
//      -s:  time step of the simulation
//      -g:  Run Simview after the simulation is complete.
//
//.......................................................................
//
// In this example, the circuit "L-C filter upstream link.sch" is simulated 5 times, with the
// resistance Ro incremented by 10 ohm each time. The starting value of Ro is 20 Ohm. The simulation
// results are saved to files out1,txt, out2.txt, ..., etc.
//
// Example: To run the simulation with Ro = 20 Ohm, the command line is:
//
//     PsimCmd.exe -i "L-C filter upstream link.sch" -o "out1.txt" -v "Ro=20"   
//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <process.h>



int main(int argc, char* argv[])
{

	char szBuffer[500];
	int i;
	double fRo =   20.;
	double fStep = 10.;

	for(i=0; i<5; i++)
	{

		sprintf(szBuffer, "PsimCmd.exe -i \"examples\\command line\\L-C filter upstream link.sch\" -o \"examples\\command line\\out%i.txt\" -v \"Ro=%g\" ",	
				i+1, fRo);
		system(szBuffer);

		fRo += fStep;
		
	}

	printf("\n");
	return 0;
}





