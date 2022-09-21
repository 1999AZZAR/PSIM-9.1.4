--
-- PACKAGE de constantes del regulador
--
-- Fichero: compensator_pack.vhd
--
-- Descripcion: contiene las constantes y tipos utilizados en el modelo del regulador   (VERSION DE REGULADOR SIMPLIFICADO CON UN POLO EN EL ORIGEN)
----------------------------------------------------------------------
-- Autor: Pablo Zumel
-- Fecha: 01/07/06
----------------------------------------------------------------------
-- UC3M-GSEP
----------------------------------------------------------------------

library WORK, IEEE;
  use IEEE.std_logic_1164.all;
  use IEEE.std_logic_arith.all;
  use IEEE.std_logic_signed.all;
 
package ControllerPack is 

 
  
   constant RegulSize         : integer:= 4;     -- número de datos pasados que utiliza el regulador
                                            
   constant ADCres            : integer:=8;     -- tamaño de palabra proporcionado por el ADC
   
   constant ADC_control_bit   : integer:=1;      -- número de señales de control del ADC
   
   constant Res_d             : integer:=9;      -- resolución en bits del ciclo de trabajo
                                                 -- a resolucion de d debe ser mejor que la resolucion del ADC
   
   constant ramp_max          : integer:=511;    -- valor maximo de la rampa para que la frecuencia de conmutacion
   												 -- sea la que tiene que ser
   												 
   constant Ratio_frec         : integer:=512;    -- realción entre la frecuencia del DPWM y la de muestreo
   constant Ratio_frec_p       : integer:=128;    -- realción entre la frecuencia del DPWM y la de muestreo
   constant Ratio_frec_z       : integer:=256;    -- realción entre la frecuencia del DPWM y la de muestreo
   
	constant ADC_gain          : real   :=21.7;    -- parametro de ajuste del fondo de escala del ADC
   

-- Tipos de datos   


-- Tipos de datos utilizados en la ecuacion en diferencias (parte X)

   subtype dato_error     is integer; -- range -(2**(ADCres+4)-1) to (2**(ADCres+4)-1);   
   type    array_error    is array (RegulSize-1 downto 0) of dato_error;
   

-- Tipos de datos utilizados en la ecuacion en diferencias (parte Y)

   subtype dato_y         is integer; -- range -(2**(30)-1) to (2**(30)-1);
   type    array_y        is array (RegulSize-1 downto 0) of dato_y;
   
   subtype duty_data      is integer range -(2**(30)-1) to (2**(30)-1);

-- Matriz de coeficientes del regulador
   
   type coeff is array (Regulsize-1 downto 0) of integer;


-- Coeficientes del regulador

      
	constant K_x      : integer := 1024*8;
	constant K_adc_pwm: integer := 1; 		
    
    constant K_x1     : integer := 8;				

    constant b0       : integer :=    20387*K_x1;
    constant b1       : integer :=    -17419*K_x1;
    constant b2       : integer :=   -20279*K_x1; 
    constant b3       : integer :=    17527*K_x1; 
       
    constant b        : coeff :=(b3,b2,b1,b0);
       
     
    constant a1       : integer :=  1078; 
    constant a2       : integer :=  -55; 
    constant a3       : integer :=  1; 
  
    
    constant a        : coeff   :=(a3,a2,a1,1);
    
    
    constant K_y      : integer := 1024; 
  
  
  
  
    constant total_gain : integer := K_x; 
    					                  


end ControllerPack;
package body ControllerPAck is

  -- Función de desplazamiento

   FUNCTION	 desplazamiento (VECTOR: STD_LOGIC_VECTOR ; NUMERO: NATURAL) return STD_LOGIC_VECTOR IS
   
    	variable VECTOR_Long: INTEGER := VECTOR'LENGTH-1;
    	variable RESULTADO: STD_LOGIC_VECTOR(VECTOR_Long downto 0) := (others =>'0');
    	variable CEROS : std_logic_vector(NUMERO-1 downto 0);
    	variable BITS  : std_logic_vector(VECTOR_Long-NUMERO downto 0);
    	
  begin
    CEROS := (others =>'0');
    BITS  :=  VECTOR (VECTOR_Long downto NUMERO);
    RESULTADO := CEROS & BITS;
    return RESULTADO;
  end desplazamiento;
  
  end ControllerPack;
  