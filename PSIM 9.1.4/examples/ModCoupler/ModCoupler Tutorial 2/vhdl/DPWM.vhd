--
-- Fichero: DPWM.vhd
--
-- Descripcion: bloque que genera los pulsos de disparo de los transistores 
-- a partir del valor de ciclo de trabajo calculado por el regulador.
-- este fichero compara la salida con un rampa para generar los pulsos de disparo
----------------------------------------------------------------------
-- Autor: Gustavo López, Pablo Zumel
-- Fecha: 26/05/05
----------------------------------------------------------------------
-- UC3M-GSEP
----------------------------------------------------------------------

library WORK, IEEE;
  use IEEE.std_logic_1164.all;
--  use WORK.BuckPack.all;
  use WORK.ControllerPack.all;

entity DPWM is
  port( duty      : in  integer range 0 to (2**(Res_d)-1);
        ClkDPWM   : in  std_logic;
        ResN      : in  std_logic;
        OnOffHSM  : out  std_logic;
        OnOffLSM  : out  std_logic
             
  );
end DPWM;

----------------------------------------------------------------------
-- Significado de los puertos:
-- duty : valor del ciclo de trabajo proporcionado por el regulador
-- ClkDPWM : valor del ciclo de reloj, que se debe ajustar en función
-- de la resolución de d y de la frecuencia de conmutación
-- ResN : reset por nivel bajo
-- OnOffHSM :  señal de disparo para el MOSFET prinicipal
-- OnOffLSM :  señal de disparo para el MOSFET recitificador síncrono
-----------------------------------------------------------------------


architecture Comportamental of DPWM is

  signal   ramp         : integer range 0 to (ramp_max);-- Rampa para comparar
  signal   OnOffHSM_aux : std_logic;-- Señal auxiliar para OnOffHSM
  signal   OnOffLSM_aux : std_logic;-- Señal auxiliar para OnOffLSM
  signal   duty_aux     : integer range -(ramp_max) to (ramp_max);
  
  constant dead_time    : integer :=4;

begin
 
 ramp_generator : process (ClkDPWM, ResN)
  -- rampa para obtener el valor numérico del ciclo de trabajo del LSM
  begin
    if ResN='0' then
      ramp<=0;
    elsif ClkDPWM='1' and ClkDPWM'event then
      if ramp > (ramp_max-1) then
         ramp <= 0;
      else ramp <= ramp +1;
      end if;
    end if;
  end process  ramp_generator;
  
  duty_limit : process (ClkDPWM)
  	begin 
  		if duty > (ramp_max)-(2*dead_time) then
  			duty_aux <= (ramp_max)-(2*dead_time);
  		elsif duty < 2*(dead_time) then
  			duty_aux <= 2*(dead_time);
  		else duty_aux<=duty;
  		end if;
  end process duty_limit;

  

  OnOffHSM_aux<='1' when (ramp > dead_time) and (ramp < duty_aux) else '0';
  OnOffHSM<=OnOffHSM_aux;
  OnOffLSM_aux<='1' when (ramp > (duty_aux+dead_time)) else '0';
  OnOffLSM<=OnOffLSM_aux;
  
end Comportamental;

















----
---- Fichero: DPWM.vhd
----
---- Descripcion: bloque que genera los pulsos de disparo de los transistores 
---- a partir del valor de ciclo de trabajo calculado por el regulador.
---- este fichero compara la salida con un rampa para generar los pulsos de disparo
------------------------------------------------------------------------
---- Autor: Gustavo López, Pablo Zumel
---- Fecha: 26/05/05
------------------------------------------------------------------------
---- UC3M-GSEP
------------------------------------------------------------------------
--
--library WORK, IEEE;
--  use IEEE.std_logic_1164.all;
--  use WORK.BuckPack.all;
--  use WORK.ControllerPack.all;
--
--entity DPWM is
--  port( duty      : in  integer range 0 to (2**(Res_d)-1);
--        ClkDPWM   : in  std_logic;
--        ResN      : in  std_logic;
--        OnOffHSM  : out  std_logic;
--        OnOffLSM  : out  std_logic
--             
--  );
--end DPWM;
--
------------------------------------------------------------------------
---- Significado de los puertos:
---- duty : valor del ciclo de trabajo proporcionado por el regulador
---- ClkDPWM : valor del ciclo de reloj, que se debe ajustar en función
---- de la resolución de d y de la frecuencia de conmutación
---- ResN : reset por nivel bajo
---- OnOffHSM :  señal de disparo para el MOSFET prinicipal
---- OnOffLSM :  señal de disparo para el MOSFET recitificador síncrono
-------------------------------------------------------------------------
--
--
--architecture Comportamental of DPWM is
--
--  signal   ramp         : integer range 0 to (ramp_max);-- Rampa para comparar
--  signal   OnOffHSM_aux : std_logic;-- Señal auxiliar para OnOffHSM
--  signal   OnOffLSM_aux : std_logic;-- Señal auxiliar para OnOffLSM
--  signal   duty_aux     : integer range -(ramp_max) to (ramp_max);
-- -- signal   duty_aux     : integer range 0 to (2**(Res_d)-1);
--  constant dead_time    : integer :=5;
--
--begin
-- 
-- ramp_generator : process (ClkDPWM, ResN)
--  -- rampa para obtener el valor numérico del ciclo de trabajo del LSM
--  begin
--    if ResN='0' then
--      ramp<=0;
--    elsif ClkDPWM='1' and ClkDPWM'event then
--      if ramp > (ramp_max-1) then
--         ramp <= 0;
--      else ramp <= ramp +1;
--      end if;
--    end if;
--  end process  ramp_generator;
--  
--  duty_limit : process (ClkDPWM)
--  	begin 
--      if duty > (ramp_max)-(2*dead_time) then
--  			duty_aux <= (ramp_max)-(2*dead_time);
--  		elsif duty < 2*(dead_time) then
--  			duty_aux <= 2*(dead_time);
--  		else duty_aux<=duty;
--  		end if;
--  end process duty_limit;
--
--  
--
--  OnOffHSM_aux<='1' when (ramp > dead_time) and (ramp < duty_aux) else '0';
--  OnOffHSM<=OnOffHSM_aux;
--  OnOffLSM_aux<='1' when (ramp > (duty_aux+dead_time)) else '0';
--  OnOffLSM<=OnOffLSM_aux;
--  
--end Comportamental;
--
--
