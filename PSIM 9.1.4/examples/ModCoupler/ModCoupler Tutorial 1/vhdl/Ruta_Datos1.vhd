library IEEE;
  
--In order to use type
use ieee.std_logic_1164.all;
--In order to use defined arithmetic functions (sum, diff, product)
use ieee.std_logic_arith.all;

entity Ruta_Datos1 is
  generic ( 
    -- k1       : real := 0.02734375;
    -- k2       : real := -0.02734375;
    -- k3       : real := 0.1220703125;
    -- k4       : real := -0.1220703125;
    k5       : real := 0.666666666666666666666666666667);
  port(
    clk      : in  std_logic;
    reset    : in  std_logic;
    Id       : in  real;
    Iq       : in  real;
    Vd       : in  real;
    Vq       : in  real;
    Pref     : in  real;
    Qref     : in  real;
    Id_sal   : out real;
    Iq_sal   : out real;
    Id_fil   : out real;
    Iq_fil   : out real);       
end Ruta_Datos1;

architecture Ruta1 of Ruta_Datos1 is
  signal sid    : real := 1.0;
  signal siq    : real := 1.0;
  signal svd    : real := 1.0;
  signal svq    : real := 1.0;
  signal spref  : real := 0.0;
  signal sqref  : real := 0.0;
  signal a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q : real := 1.0;
 begin    
  P_BIEST: process(reset, clk)
  begin
    if reset='1' then
      sid <= 0.0;
      siq <= 0.0;
      svd <= 1.0;
      svq <= 1.0;
      spref <= 5000.0;
      sqref <= 0.0;
    elsif clk'event and clk='1' then
      sid <= Id;
      siq <= Iq;
      svd <= Vd;
      svq <= Vq;
      spref <= Pref;
      sqref <= Qref;
    end if;
  end process;
--  p      <= k1*sid;
--  q      <= k2*siq;
  p      <= sid;
  q      <= -siq;
  Id_fil <= p;
  Iq_fil <= q;
--  a      <= k3*svd;
--  b      <= k4*svq;
  a      <= svd;
  b      <= -svq;
  c      <= a*spref;
  d      <= b*sqref;
  e      <= b*spref;
  f      <= a*sqref;
  g      <= c+d;
  h      <= e-f;
  i      <= a*a;
  j      <= b*b;
  k      <= i+j;
  l      <= g/k;
  m      <= h/k;
  n      <= l*k5;
  o      <= m*k5;
  Id_sal <= n-p;
  Iq_sal <= o-q;
end Ruta1;