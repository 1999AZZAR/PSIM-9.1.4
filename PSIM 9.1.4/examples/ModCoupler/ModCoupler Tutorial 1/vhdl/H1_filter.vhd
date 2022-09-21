library IEEE;
  
--In order to use type
use ieee.std_logic_1164.all;
--In order to use defined arithmetic functions (sum, diff, product)
use ieee.std_logic_arith.all;

entity H1_filter is
  --Real coefficients
  generic( 
    a1     : real := -0.9752;
    b0     : real :=  0.01242;
    b1     : real :=  0.01242);
  port(
    clk    : in  std_logic;
    reset  : in  std_logic;
    --In
    H1_in  : in  real;
    --Out
    H1_out : out real);        
end H1_filter;

architecture H1 of H1_filter is
  signal act_input, prev_input, act_output, prev_output: real :=0.0;
begin    
  P_BIEST_1: process(reset, clk)
  begin
    if reset='1' then
      act_input <= 0.0;
      prev_input <= 0.0;
    elsif clk'event and clk='1' then
      act_input <= H1_in;
      prev_input <= act_input;
    end if;
  end process;
  P_BIEST_2: process (reset,clk)
  begin
    if reset = '1' then
      prev_output <= 0.0;
    elsif clk'event and clk='1' then
      prev_output <= act_output;
    end if;
  end process;
  act_output  <= (b0*act_input + b1*prev_input)-(a1*prev_output);
  H1_out      <= act_output;
end H1;