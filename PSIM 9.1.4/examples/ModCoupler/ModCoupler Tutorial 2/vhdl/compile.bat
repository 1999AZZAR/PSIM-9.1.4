rem vdel -all
vlib work

@echo off
set VHDLDIR=.
vcom %VHDLDIR%\compensator_pack.vhd %VHDLDIR%\ADC_controller.vhd %VHDLDIR%\DPWM.vhd %VHDLDIR%\compensator.vhd %VHDLDIR%\top_controller.vhd
rd /S /Q "../work"
move /Y work ..

pause



