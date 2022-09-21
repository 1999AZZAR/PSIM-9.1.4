--
-- top_controller
--
-- Fichero: top_controller.vhd
--
-- Descripcion: bloque que une el regulador y el control del 
--              ADC para ser sintetizado en la FPGA

----------------------------------------------------------------------
-- Autor: Gustavo López, Pablo Zumel
-- Fecha: 6/10/05
----------------------------------------------------------------------
-- UC3M-GSEP
----------------------------------------------------------------------

library WORK, IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_arith.all;
  use IEEE.std_logic_signed.all;
  use WORK.ControllerPack.all;

  entity top_controller is
  	port(  clk  		: in  std_logic;
       	   reset        : in  std_logic;
           ADC_data     : in  std_logic_vector(7 downto 0);
	       reference    : in std_logic_vector (2 downto 0);
	       div_frec_p   : in std_logic;
	       div_frec_z   : in std_logic;
	       ADC_control  : out std_logic_vector (0 downto 0);
           OnOffHSM     : out std_logic;
           OnOffLSM     : out std_logic;
	       duty_mon     : out std_logic_vector (8 downto 0)	       
	       );
  end top_controller;

  architecture Estructural of top_controller is
  
  component DPWM 
  port( duty      : in  integer range 0 to (2**(Res_d)-1);
        ClkDPWM   : in  std_logic;
        ResN      : in  std_logic;
        OnOffHSM  : out  std_logic;
        OnOffLSM  : out  std_logic
         );
  end component;
  
  component regulador 
  port( Clk         : in  std_logic;
        ResN        : in  std_logic;
        ADC_data    : in  std_logic_vector(ADCres-1 downto 0);
	     duty_out    : out integer range 0 to (2**(Res_d)-1);
	     reference   : in  std_logic_vector (2 downto 0);
	     div_frec_p  : in std_logic;
	     div_frec_z  : in std_logic;
	     ys          : out duty_data

	 );
  end component;

  component ADC_controller
  port ( Clk         : in   std_logic;
         ADC_control : out  std_logic_vector (ADC_control_bit-1 downto 0);
			ResN        : in   std_logic
         ); 
  end component;
  

  signal duty_mon_aux   : integer range  0 to (2**(Res_d)-1);
  signal ys_aux         : duty_data;
  
  
  
  
  
  begin

  
  
  TheDPWM : DPWM
  port map (
         duty     => duty_mon_aux,
         ClkDPWM  => Clk,
         ResN     => reset,
         OnOffHSM => OnOffHSM,
         OnOffLSM => OnOffLSM
         );
   
  TheADCcontrol : ADC_controller
  port map (
         Clk => Clk,
         ADC_control => ADC_control,
			ResN =>reset
         );
 
  Theregulador : regulador
  port map(
        Clk         => Clk,
        ResN        => reset,
        ADC_data    => ADC_data,
	     duty_out    => duty_mon_aux,
	     reference   => reference,
	     div_frec_p    => div_frec_p,
	     div_frec_z    => div_frec_z,
	     ys           => ys_aux
	 );   
 duty_mon <=conv_std_logic_vector(duty_mon_aux,Res_d);
 end Estructural;














