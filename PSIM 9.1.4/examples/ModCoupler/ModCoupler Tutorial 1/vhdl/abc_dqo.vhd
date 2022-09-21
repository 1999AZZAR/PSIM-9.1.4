library IEEE;
  
--In order to use type
use ieee.std_logic_1164.all;
--In order to use defined arithmetic functions (sum, diff, product)
use ieee.std_logic_arith.all;
--In order to use common real constants, common real functions, and real trascendental functions.
use ieee.math_real.all;

entity abc_dqo is
  generic( 
    a1    : real := 0.666666666666666666666666666667; -- 2/3
    a2    : real := 0.333333333333333333333333333333); -- 1/3
  port(
    clk    : in  std_logic;
    reset  : in  std_logic;
    a      : in  real;
    b      : in  real;
    c      : in  real;
    w      : in  real;
    d      : out real;
    q      : out real);
end abc_dqo;

architecture a of abc_dqo is
  signal sa    : real := 0.1;
  signal sb    : real := 0.1;
  signal sc    : real := 0.1; 
  signal sw    : real := 0.1; 
begin    
  sa   <= a;
  sb   <= b;
  sc   <= c;
  sw   <= w;
  d    <= a1*((cos(sw)*sa)+(cos(sw-(a1*MATH_PI))*sb)+(cos(sw+(a1*MATH_PI))*sc));
  q    <= a1*((sin(sw)*sa)+(sin(sw-(a1*MATH_PI))*sb)+(sin(sw+(a1*MATH_PI))*sc));
end a;
