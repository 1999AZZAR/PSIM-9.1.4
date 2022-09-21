@title Psim Command Test
@Echo OFF
@Echo Copyright (c) 2006-2008 Powersim Inc
@Echo This is a sample batch file which uses PsimCmd.exe. It is assumed that this file resides in folder "\Examples\Command Line\" in the "PSIM" folder


REM  Usage: PsimCmd.exe -i "[input file]" -o "[output file]" -v "VarName1=VarValue"  -v "VarName2=VarValue" -t "TotalTime" -s "TimeStep" -g -K -L
REM
REM  Except input file, all other parameters are optional.
REM  Command line parameters:
REM    -i:  followed by the input schematic file.
REM    -o:  followed by the output text (.txt) or binary (.smv) file.
REM    -t:  followed by the Total Time for simulation.
REM    -s:  followed by the Time Step of simulation.
REM    -v:  followed by a variable. This parameter can be used multiple times.
REM         example:  -v "TR=5.25"  -v "m0=4.5e-9" 
REM    -o:  followed by the output text (.txt) or binary (.smv) file.
REM    -g:  Run Simview after simulation is complete.
REM    -K:  Set 'Save flag' in Simulation control.
REM    -L:  Set 'Load flag' in Simulation control. Continue from previous simulation result.


REM  The batch command "for" below changes the variable R from 20 to 60, with a step of 10 (the sequence will be:
REM  20,30,40,50,60). 
REM  The command format is:   
REM      FOR /L %variable IN (start,step,end) DO command [command-parameters]
REM
REM  Please note:  
REM    - Since this command is in the batch file, two percentage signs %% must be used before the variable name R.
REM    - The variable can only be a single letter. For example, a variable name of "Ro" will not work.
REM
REM  For more information on the "for" command, launch a command prompt window, and type 
REM      help for

@Pause

@Echo ON
for /L %%R in (20,10,60) do ..\..\PsimCmd.exe -i "L-C filter upstream link.sch" -o "out%%R.txt" -v "Ro=%%R" -g

@Pause
