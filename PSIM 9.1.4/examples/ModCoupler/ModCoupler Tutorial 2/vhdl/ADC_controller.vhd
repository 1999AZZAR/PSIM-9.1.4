--
-- Fichero: ADC_controller.vhd
--
-- Descripcion: bloque que calcula el error que sirve de entrada al regulador
-- incluyendo los efectos del modelo de ADC si los hubiera
----------------------------------------------------------------------
-- Autor: Pablo Zumel
-- Fecha: 01/06/06
----------------------------------------------------------------------
-- UC3M-GSEP
----------------------------------------------------------------------



library WORK, IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_arith.all;
  use IEEE.std_logic_signed.all;
  use WORK.ControllerPack.all;

entity ADC_controller is
  port( Clk          : in  std_logic;
        ADC_control  : out std_logic_vector(ADC_control_bit-1 downto 0);
		  ResN         : in std_logic -- señal de control de conversión
  	);
end ADC_controller;

architecture Comportamental of ADC_controller is
signal clk_aux : std_logic;
signal count_controller : integer range 0 to Ratio_frec-1;

begin

ADC_control(0)<=clk_aux;
 

  Frequency_adapter: process (clk,ResN)
    begin
	   if ResN='0' then
		  count_controller<=0;
      elsif clk='1' and clk'event then
        if count_controller=(Ratio_frec/128)-1 then
          count_controller<=0;
        else count_controller<=count_controller+1;
        end if;
      end if;
      
  end process Frequency_adapter;
  
  proceso_Clock_controller: process (count_controller)
  begin
    if count_controller<=(ramp_max/256) then
      clk_aux<='1';
    else clk_aux<='0';
    end if;
  end process proceso_Clock_controller;
   
 
  
end Comportamental;


