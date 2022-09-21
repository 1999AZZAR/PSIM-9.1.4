library IEEE;
  
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity Top_Inversor is

port(clk, reset		: in  std_logic;
	Ia, Ib, Ic		: in  real;
    Va, Vb, Vc		: in  real;
    Vdc_sw			: in  real;
    w				: in  real;
    P_ref, Q_ref	: in  real;
    L				: in  real;
    I_GBT1			: out std_logic;
    I_GBT2			: out std_logic;
    I_GBT3			: out std_logic;
    I_GBT4			: out std_logic;
    I_GBT5			: out std_logic;
    I_GBT6			: out std_logic);
	         
end Top_Inversor;

architecture Top of Top_Inversor is
    
  component h1_filter
  port(
    clk    : in  std_logic;
    reset  : in  std_logic;
    H1_in  : in  real;
    H1_out : out real);        
  end component;
	
  component abc_dqo
  port(
    clk    : in  std_logic;
    reset  : in  std_logic;
    a      : in  real;
    b      : in  real;
    c      : in  real;
    w      : in  real;
    d      : out real;
    q      : out real);
  end component;
   
  component ruta_datos1
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
  end component;
   
  component ruta_datos2
    port(
    clk       : in  std_logic;
    reset     : in  std_logic;
    Id_sal    : in  real;
    Iq_sal    : in  real;
    Id_fil    : in  real;
    Iq_fil    : in  real;
    d_dqo_abc : out real;
    q_dqo_abc : out real;
    decoup    : in  real); 
  end component;
	
  component dqo_abc
    port(
    clk         : in  std_logic;
    reset       : in  std_logic;
    d           : in  real;
    q           : in  real;
    w           : in  real;
    a           : out real;
    b           : out real;
    c           : out real); 
   end component;

   signal   s_Decoup     : real :=  0.0094205037;--Value obtained from psim	
   signal   s_L          : real :=  0.0;
   signal   s_Vdc_sw     : real :=  0.00001;
   signal   s_Ia_fil     : real := 0.0;
   signal   s_Ib_fil     : real := 0.0;
   signal   s_Ic_fil     : real := 0.0;
   signal   s_Id         : real := 0.0;
   signal   s_Iq         : real := 0.0;
   signal   s_Vd         : real := 0.0;
   signal   s_Vq         : real := 0.0;
   signal   s_Id_fil     : real := 0.0;
   signal   s_Iq_fil     : real := 0.0;
   signal   s_Id_sal     : real := 0.0;
   signal   s_Iq_sal     : real := 0.0;
   signal   s_d_dqo_abc  : real := 0.0;
   signal   s_q_dqo_abc  : real := 0.0;
   signal   s_Vmod_a     : real := 0.0;
   signal   s_Vmod_b     : real := 0.0;
   signal   s_Vmod_c     : real := 0.0;
   signal   s_w          : real := 0.0;
   signal   s_Gen        : real  := -1.0;
   signal   s_wt: real := 0.0;

  begin    

  uut1: h1_filter 
    port map (
      clk       => clk, 
      reset     => reset, 
      H1_in     => Ia, 
      H1_out    => s_Ia_fil);

  uut2: h1_filter 
    port map (
      clk       => clk, 
      reset     => reset, 
      H1_in     => Ib, 
      H1_out    => s_Ib_fil);
    
  uut3: h1_filter 
    port map (
      clk       => clk, 
      reset     => reset, 
      H1_in     => Ic, 
      H1_out    => s_Ic_fil);
    
  uut4: abc_dqo 
    port map (
      clk       => clk, 
      reset     => reset, 
      a         => s_Ia_fil,
      b         => s_Ib_fil,
      c         => s_Ic_fil,
      w         => s_wt,
      d         => s_Id,
      q         => s_Iq);
    
  uut5: abc_dqo 
    port map (
      clk       => clk, 
      reset     => reset, 
      a         => Va,
      b         => Vb,
      c         => Vc,
      w         => s_wt,
      d         => s_Vd,
      q         => s_Vq); 
    
  uut6: ruta_datos1
    port map (
      clk       => clk,
      reset     => reset,
      Id        => s_Id,
      Iq        => s_Iq,
      Vd        => s_Vd,
      Vq        => s_Vq,
      Pref      => P_ref,
      Qref      => Q_ref,
      Id_sal    => s_Id_sal,
      Iq_sal    => s_Iq_sal,
      Id_fil    => s_Id_fil,
      Iq_fil    => s_Iq_fil);       

  uut7: ruta_datos2
    port map (
      clk       => clk,
      reset     => reset,
      Id_sal    => s_Id_sal,
      Iq_sal    => s_Iq_sal,
      Id_fil    => s_Id_fil,
      Iq_fil    => s_Iq_fil,
      d_dqo_abc => s_d_dqo_abc,
      q_dqo_abc => s_q_dqo_abc,
      decoup    => s_Decoup);

  uut8: dqo_abc
    port map (
      clk       => clk,
      reset     => reset,
      d         => s_d_dqo_abc,
      q         => s_q_dqo_abc,
      w         => s_wt,
      a         => s_Vmod_a,
      b         => s_Vmod_b,
      c         => s_Vmod_c);

    s_Decoup <= (s_L*s_w)/(s_Vdc_sw);

  P_WT: process(reset, clk)
  begin
    if reset='1' then
      s_wt <= 0.0;
    elsif clk'event and clk='1' then
      s_wt <= s_wt + w*0.000008;
      if s_wt > 6.283185307179586 then
        s_wt <= s_wt - 6.283185307179586476;
      end if;
    end if;
  end process;   
  
  P_BIEST: process(reset, clk)
  begin
    if reset='1' then
       s_w          <= 0.0100;
       s_L          <= 0.0001;
       s_Vdc_sw     <= 0.1000;
    elsif clk'event and clk='1' then
       s_w          <= w;
       s_L        <= L;
       s_Vdc_sw   <= Vdc_sw;
    end if;
  end process;

  CMP: process(s_Vmod_a, s_Vmod_b, s_Vmod_c, s_Gen,clk)
  begin
    if s_Vmod_a > s_Gen then 
        I_GBT1 <= '1';
        I_GBT4 <= '0';
    else
        I_GBT1 <= '0';
        I_GBT4 <= '1';
    end if;
    
    if s_Vmod_b > s_Gen then
        I_GBT2 <= '1';
        I_GBT5 <= '0';
    else
        I_GBT2 <= '0';
        I_GBT5 <= '1';
    end if;
    if s_Vmod_c > s_Gen then
        I_GBT3 <= '1';
        I_GBT6 <= '0';
    else
        I_GBT3 <= '0';
        I_GBT6 <= '1';
    end if;
  end PROCESS;

  GEN:process
    constant period: time := 660 us;
    constant amplitude: real:= 2.0;
    constant resolution: integer := 1000;
  begin
    s_Gen <= -1.0;
    for i in 1 to resolution loop
      s_Gen <= s_Gen+amplitude/real(resolution);
      wait for period/resolution/2;
    end loop;
    for i in 1 to resolution loop
      s_Gen <= s_Gen-amplitude/real(resolution);
      wait for period/resolution/2;
    end loop;
  end process; 
end Top;