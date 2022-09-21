rem vdel -all
vlib work

@echo off
set VHDLDIR=.
vcom %VHDLDIR%\table_1500.vhd %VHDLDIR%\table_1600.vhd %VHDLDIR%\table_3000.vhd %VHDLDIR%\table_15000.vhd %VHDLDIR%\param_table.vhd %VHDLDIR%\SPWM_unipolarVariable_patron.vhd
rd /S /Q "../work"
move /Y work ..

pause