library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
-- ********************************************************************** --
--                    Universidad Carlos III de Madrid		   	         --
--                 Departamento de Tecnología Electrónica			    --
--               Grupo de Sistemas Electrónicos de Potencia			    --
--														    --
--               GENERADOR DE ONDA UNIPOLAR PARA INVERSORES               --
--														    --
--                  Pablo zumel       		    --
--						   03/07/2007						    --
-- ********************************************************************** --


entity SPWM_unipolarVariablePatron is

Port (  Clk         : in  std_logic;
        ResN        : in  std_logic;
	     CyclePosT14 : out std_logic;
        CycleNegT23 : out std_logic;
	     PWM_23      : out std_logic;
	     PWM_14      : out std_logic;
	     sel_frec    : in std_logic_vector (3 downto 0)
     );
end SPWM_unipolarVariablePatron;

architecture Behavioral of SPWM_unipolarVariablePatron is


component  param_table       --configuracion tablas

   port ( Clk       : in std_logic;
	       ADDR      : in integer range 0 to 14;
	       DOUT      : out integer range 0 to 1023
   );
end component;

component  table_1500

   port ( Clk       : in std_logic;
	       ADDR      : in integer range 0 to 1023;
	       DOUT      : out integer range 0 to 999999;
	       LOUT      : out integer range 0 to 1
   );
end component;

component  table_3000

   port ( Clk       : in std_logic;
	       ADDR      : in integer range 0 to 1023;
	       DOUT      : out integer range 0 to 999999;
	       LOUT      : out integer range 0 to 1
   );
end component;


component  table_10000

   port ( Clk       : in std_logic;
	       ADDR      : in integer range 0 to 1023;
	       DOUT      : out integer range 0 to 999999;
	       LOUT      : out integer range 0 to 1
   );
end component;

component  table_1600

   port ( Clk       : in std_logic;
	       ADDR      : in integer range 0 to 1023;
	       DOUT      : out integer range 0 to 999999;
	       LOUT      : out integer range 0 to 1
   );
end component;


constant numero_frecs : integer:=15;
type int_vector is array (numero_frecs-1 downto 0) of integer range 0 to 999999;



signal sel_frec_int   : integer range 0 to 15;
signal tiempo         : integer range 0 to 999999;
signal en             : std_logic;
signal puntero_max    : integer range 0 to 1023;
signal puntero        : integer range 0 to 1023 :=0;
signal tablaIN_Aux    : integer;
signal Data_IN        : integer range 0 to 999999;
signal Data_IN_vector : int_vector;
signal nivel_IN       : integer ;
signal nivel_IN_0     : integer range 0 to 1;
signal nivel_IN_1     : integer range 0 to 1;
signal nivel_IN_2     : integer range 0 to 1;
signal nivel_IN_3     : integer range 0 to 1;
signal ADDR_vector    : int_vector :=(others=>0);
signal pwm_out        : std_logic_vector (4 downto 1);
signal estado         : std_logic;



begin

-- ******************************************
--      Instanciacion de las tablas
-- ******************************************
TablaParam: param_table
						    
   port map ( Clk      => Clk,
        		  ADDR     => sel_frec_int,
	           DOUT     => puntero_max 
             );
Tabla1500: table_1500
						    
   port map ( Clk      => Clk,
        		    ADDR     => ADDR_vector(0),
	           DOUT     => Data_IN_vector(0),
	           LOUT     => nivel_IN_0
	           );
	           
	           
Tabla3000: table_3000
						    
   port map ( Clk      => Clk,
        		    ADDR     => ADDR_vector(1),
	           DOUT     => Data_IN_vector(1),
	           LOUT     => nivel_IN_1
             );

Tabla10000: table_10000
						    
   port map ( Clk      => Clk,
        		    ADDR     => ADDR_vector(2),
	           DOUT     => Data_IN_vector(2),
	           LOUT     => nivel_IN_2
             );
             
Tabla1600: table_1600
						    
   port map ( Clk      => Clk,
        		    ADDR     => ADDR_vector(3),
	           DOUT     => Data_IN_vector(3),
	           LOUT     => nivel_IN_3
             );             


  
-- *****************************************************************************
--      Contador PRINCIPAL    --
-- ***************************************************************** --

   
Contador_principal: process (ResN,Clk)
 begin
  
  if ResN ='0' then
      tiempo<=0;
  elsif Clk='1' and Clk'event then
      if tiempo<999999 then
          tiempo<=tiempo+1;
      else tiempo <=0;
      end if;
  end if;
end process Contador_principal;

enable_principal: process (ResN,Clk)
begin
    
    if ResN='0' then
        en<='0';
    elsif Clk='1' and Clk'event then
      if tiempo=999999 then
          en<='1';
      else en<='0';
      end if;
    end if;
    
end process enable_principal;
          
        


-- *****************************************************************************
--      Lectura PARAMETROS TABLA    --
-- ***************************************************************** --

  lecturaTABLAparam: process(Clk,ResN)
    begin
      if ResN='0' then
          sel_frec_int<=0;
      elsif Clk='1' and Clk'event and en='1' then
          if sel_frec = "0011" then
              estado<= not estado;
            if estado='0' then 
                sel_frec_int<=0;
            elsif estado='1' then
                sel_frec_int<=3;
            end if;
          else sel_frec_int<=conv_integer(sel_frec);
          end if;
      end if;
--          puntero_max<=tablaIN_Aux;
            
  end process lecturaTABLAparam;
  

-- *****************************************************************************
--      Lectura  TABLA    --
-- ***************************************************************** --

lectura_tabla: process (Clk,ResN)
begin
    if ResN='0' then
        Data_IN<=0;
        nivel_IN<=0;
    elsif Clk='1' and Clk'event then
        Data_IN<=Data_IN_vector(sel_frec_int);
        case sel_frec_int is
            when 0 => nivel_IN<=nivel_IN_0;
            when 1 => nivel_IN<=nivel_IN_1;
            when 2 => nivel_IN<=nivel_IN_2;
            when 3 => nivel_IN<=nivel_IN_3;
            when others => nivel_IN<=nivel_IN_0;
        end case;
    end if;
end process lectura_tabla;

avance_puntero: process (Clk,ResN)
begin
      if ResN='0' then
          puntero<=0;
      elsif Clk='1' and Clk'event then
          if Data_IN=tiempo then
              if puntero=puntero_max then
                puntero<=0;
              else puntero<=puntero+1;
              end if;
          end if;
      end if;
  end process avance_puntero;

-- *****************************************************************************
--      Eleccion de TABLA    --
-- **********************************************************


eleccion_tabla: process(Clk,ResN)
begin
    if ResN='0' then
        for i in numero_frecs-1 downto 0 loop
          ADDR_vector(i)<=0;
		  end loop;
    elsif Clk='1' and Clk'event then
	    for i in numero_frecs-1 downto 0 loop
        if i= sel_frec_int then
		    ADDR_vector(i)<=puntero;
			 else ADDR_vector(i)<=0;
		  end if;
		  end loop;
    end if;
end process eleccion_tabla;
                
-- *****************************************************************************
--      Generación de disparos    --
-- ***************************************************************** --

PWM:  process (Clk,ResN)
 begin
 if ResN='0' then
     pwm_out<=(others=>'0');
 elsif Clk='1' and Clk'event then 
   if tiempo< 500000 then
       pwm_out(2)<='0';
       pwm_out(4)<='1';
       if nivel_IN=1 then
           pwm_out(1)<='1';
           pwm_out(3)<='0';
       else 
            pwm_out(1)<='0';
            pwm_out(3)<='1';
      end if;
    elsif tiempo> 500000 or tiempo= 500000 then
       pwm_out(1)<='0';
       pwm_out(3)<='1';
       if nivel_IN=1 then
           pwm_out(2)<='1';
           pwm_out(4)<='0';
       else 
            pwm_out(2)<='0';
            pwm_out(4)<='1';
      end if;
end if;
end if;
end process PWM;

CyclePosT14 <=pwm_out(4);
CycleNegT23 <=pwm_out(3);
PWM_23      <=pwm_out(2);
PWM_14      <=pwm_out(1);




end Behavioral;




     
  
 


