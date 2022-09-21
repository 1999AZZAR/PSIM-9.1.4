library IEEE;
  
--In order to use type
use ieee.std_logic_1164.all;
--In order to use defined arithmetic functions (sum, diff, product)
use ieee.std_logic_arith.all;

entity Ruta_Datos2 is
  generic(
    k6        : real := -1.0);
  port(
    clk       : in  std_logic;
    reset     : in  std_logic;
    Id_sal    : in  real;
    Iq_sal    : in  real;
    Id_fil    : in  real;
    Iq_fil    : in  real;
    d_dqo_abc : out real;
    q_dqo_abc : out real;
    decoup    : in  real);  -- Ahora es entrada (se genera en Top_inversor)
                            -- Celia
end Ruta_Datos2;

architecture Ruta2 of Ruta_Datos2 is
  component h2_filter
    generic( 
      a1: real := -1.0; 
      b0: real :=  0.01419;
      b1: real := -0.01416);
    port(
      clk      : in  std_logic;
      reset    : in  std_logic;
      H2_in    : in  real;
      H2_out   : out real);        
  end component;
  signal s_Id_sal   : real := 0.0;
  signal s_Iq_sal   : real := 0.0;
  signal s_Id_fil   : real := 0.0;
  signal s_Iq_fil   : real := 0.0;
  signal s_H2_out1  : real := 0.0;
  signal s_H2_out2  : real := 0.0;
begin    
  uut1: h2_filter 
  port map (
    clk     => clk,
    reset   => reset, 
    H2_in   => s_Id_sal,
    H2_out  => s_H2_out1);

  uut2: h2_filter 
  port map (
    clk     => clk, 
    reset   => reset, 
    H2_in   => s_Iq_sal,
    H2_out  => s_H2_out2);

  P_BIEST: process(reset, clk)
  begin
    if reset='1' then
      s_Id_sal <= 0.0;
      s_Iq_sal <= 0.0;
      s_Id_fil <= 0.0;
      s_Iq_fil <= 0.0;
    elsif clk'event and clk='1' then
      s_Id_sal <= Id_sal;
      s_Iq_sal <= Iq_sal;
      s_Id_fil <= Id_fil;
      s_Iq_fil <= Iq_fil;
    end if;
  end process;
  d_dqo_abc <=  s_H2_out1 - (decoup*s_Iq_fil);
  q_dqo_abc <= (s_H2_out2 + (decoup*s_Id_fil))*K6;
end Ruta2;

