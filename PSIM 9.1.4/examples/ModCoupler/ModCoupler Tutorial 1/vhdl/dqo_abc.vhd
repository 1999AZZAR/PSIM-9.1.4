library IEEE;
  
--In order to use type
use ieee.std_logic_1164.all;
--In order to use defined arithmetic functions (sum, diff, product)
use ieee.std_logic_arith.all;
--BASIC package
--use work.basic.all;
use ieee.math_real.all;

entity dqo_abc is
  generic( 
    a1          : real := 0.6666666666666666666666667); -- 2/3
  port(
    clk         : in  std_logic;
    reset       : in  std_logic;
    d           : in  real;
    q           : in  real;
    w           : in  real;
    a           : out real;
    b           : out real;
    c           : out real); 
end dqo_abc;

architecture d of dqo_abc is
  signal sd  : real := 0.0;
  signal sq  : real := 0.0;
  signal sw  : real := 0.0;
begin    
  P_BIEST: process(reset, clk)
  begin
    if reset='1' then
      sd <= 0.0;
      sq <= 0.0;
      sw  <= 0.0;
    elsif clk'event and clk='1' then
      sd <= d;
      sq <= q;
      sw  <=w;
    end if;
  end process;
         
  a <=(cos(sw)*sd)+(sin(sw)*sq)+(0.0);--'o' vale '-1'
  b <=(cos(sw-(a1*MATH_PI))*sd)+(sin(sw-(a1*MATH_PI))*sq)+(0.0);
  c <=(cos(sw+(a1*MATH_PI))*sd)+(sin(sw+(a1*MATH_PI))*sq)+(0.0); 
end d;
