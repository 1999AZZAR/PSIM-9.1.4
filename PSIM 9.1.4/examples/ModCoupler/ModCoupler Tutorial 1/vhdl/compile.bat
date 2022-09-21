rem vdel -all
vlib work

@echo off
set VHDLDIR=.
vcom %VHDLDIR%\abc_dqo.vhd %VHDLDIR%\dqo_abc.vhd %VHDLDIR%\H1_filter.vhd %VHDLDIR%\H2_filter.vhd %VHDLDIR%\Ruta_Datos1.vhd %VHDLDIR%\Ruta_Datos2.vhd %VHDLDIR%\Top_Inversor.vhd
rd /S /Q "../work"
move /Y work ..

pause



