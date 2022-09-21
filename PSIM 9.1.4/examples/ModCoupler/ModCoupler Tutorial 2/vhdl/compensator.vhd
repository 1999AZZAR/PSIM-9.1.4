--
-- Fichero: regulador.vhd
-- Descripcion: compensador digital
-- implementación directa de la ecuación en diferencias
----------------------------------------------------------------------
-- Autor: Pablo Zumel
-- Fecha: 26/05/05
----------------------------------------------------------------------
-- UC3M-GSEP
----------------------------------------------------------------------

library WORK, IEEE;
  use IEEE.std_logic_1164.all; 
  use IEEE.std_logic_arith.all;
  use IEEE.std_logic_signed.all;
  use IEEE.numeric_std.all;
  use WORK.ControllerPack.all;


entity regulador is
  
  port( Clk         : in  std_logic;
        ResN        : in  std_logic;
        ADC_data    : in  std_logic_vector(ADCres-1 downto 0);
        duty_out    : out integer range 0 to (2**(Res_d)-1) :=0;
        reference   : in  std_logic_vector (2 downto 0);
        div_frec_p  : in  std_logic;
        div_frec_z  : in  std_logic;
       ys           : out duty_data
	 );
  end regulador;

architecture Estructural of regulador is

  -- la señal que introducimos
  signal error               : dato_error:=0;         -- señal de error
  signal error_aux           : dato_error:=0;         -- señal de error
  signal ADC_data_integer : dato_error:=0;         -- señal de dato de entrada entero (el dato del ADC es std_logic_vector)
  
  signal x                : array_error:= (others =>0);  -- señal que se generará después del desplazamiento de señal de entrada (error)
  signal x_tot            : dato_y :=0;                    -- señal de salida del bloque de las X, que introduciremos en el bloque de las Y
  
 signal y                : array_y:= (others =>0);   -- señal que se generará después del desplazamiento de la señal de salida
 signal y_tot            : duty_data :=0;                        -- señal de salida del bloque de las Y

  signal count_controller_p  : integer range 0 to Ratio_frec;
  signal count_controller_z  : integer range 0 to Ratio_frec;
  signal Clk_reg_p           : std_logic;
  signal Clk_reg_z           : std_logic;
  signal y_tot_aux           : duty_Data :=0;
  signal ADC_data_aux0       : std_logic_vector (ADCres-1 downto 0);
  signal ADC_data_aux1       : std_logic_vector (ADCres-1 downto 0);
  signal ADC_data_aux2       : std_logic_vector (ADCres-1 downto 0);
  signal ADC_data_aux3       : std_logic_vector (ADCres-1 downto 0);
  signal ADC_data_aux4       : std_logic_vector (ADCres-1 downto 0);
  signal ADC_data_aux        : std_logic_vector (ADCres downto 0);
  signal ref_integer         : dato_error:=0; 
  signal reference_aux       : std_logic_vector (3 downto 0);  
begin


  Input_reg: process (ResN,Clk)
   begin
	  if ResN='0' then
	    ADC_data_aux0<=(others=>'0');
	    ADC_data_aux1<=(others=>'0');
	    ADC_data_aux2<=(others=>'0');
	    ADC_data_aux3<=(others=>'0');
	    ADC_data_aux4<=(others=>'0');
	    ref_integer<=0;
	  elsif Clk='1' and Clk'event then
	    ADC_data_aux0<=ADC_data;
	    ADC_data_aux1<=ADC_data_aux0;
	    ADC_data_aux2<=ADC_data_aux1;
	    ADC_data_aux3<=ADC_data_aux2;
	    ADC_data_aux4<=ADC_data_aux3;	    	    	    
	    ref_integer<=conv_integer(reference_aux)*8+52;
	  end if;
	end process Input_reg;


 ADC_data_aux( ADCres-1 downto 0)<= ADC_data_aux4( ADCres-1 downto 0);
 ADC_data_aux(ADCres)<='0';
 ADC_data_integer <= conv_integer(ADC_data_aux);
 
 reference_aux(2 downto 0)<=reference;
 reference_aux(3)<='0'; 
 
 error_aux <=(ref_integer-ADC_data_integer);
 error <=error_aux;
 
 ys<=y_tot;
 

  Frequency_adapter_poles: process (Clk,ResN)
    begin
      if ResN='0' then
        count_controller_p<=0;
      elsif Clk='1' and Clk'event then
        if div_frec_p='0' then
	  if count_controller_p>=(Ratio_frec_p)-1 then
            count_controller_p<=0;
          else count_controller_p<=count_controller_p+1;
	  end if;
	elsif div_frec_p='1' then   
	  if count_controller_p>=Ratio_frec-1 then
            count_controller_p<=0;
          else count_controller_p<=count_controller_p+1;
	  end if;
        end if;
      end if;
      
  end process Frequency_adapter_poles;
  
  Frequency_adapter_zeroes: process (Clk,ResN)
    begin
      if ResN='0' then
        count_controller_z<=0;
      elsif Clk='1' and Clk'event then
        if div_frec_z='0' then
	  if count_controller_z>=Ratio_frec_z-1 then
            count_controller_z<=0;
          else count_controller_z<=count_controller_z+1;
	  end if;
	elsif div_frec_z='1' then   
	  if count_controller_z>=Ratio_frec-1 then
            count_controller_z<=0;
          else count_controller_z<=count_controller_z+1;
	  end if;
        end if;
      end if;
      
  end process Frequency_adapter_zeroes;
  
  proceso_Clock_controller_p: process (clk)
  begin
  if div_frec_p='0' then    
	 if count_controller_p=Ratio_frec_p-1 then
        Clk_reg_p<='1';
    else Clk_reg_p<='0';
    end if;
  elsif div_frec_p='1' then 
    if count_controller_p=Ratio_frec-1 then
        Clk_reg_p<='1';
    else Clk_reg_p<='0';
    end if;
  end if;
  end process proceso_Clock_controller_p;
  
  proceso_Clock_controller_z: process (clk)
  begin
  if div_frec_z='0' then    
	 if count_controller_z=Ratio_frec_z-1 then
        Clk_reg_z<='1';
    else Clk_reg_z<='0';
    end if;
  elsif div_frec_z='1' then 
    if count_controller_z=Ratio_frec-1 then
        Clk_reg_z<='1';
    else Clk_reg_z<='0';
    end if;
  end if;
  end process proceso_Clock_controller_z;
  
  proceso_X: process (ResN, Clk)
  begin
  if ResN = '0' then
     x<=(others => 0);
  elsif Clk='0' and Clk'event and Clk_reg_z='1' then
    for i in (Regulsize-1) downto 1 loop
      x(i)<=x(i-1);
    end loop;
    x(0)<=error;
  end if;
  end process proceso_X; 
    
  productos_X: process (Clk)
  begin
      x_tot<=x(0)*b0+x(1)*b1+x(2)*b2+x(3)*b3;
  end process productos_X;

  proceso_Y: process (ResN, Clk)
  begin
 
 if ResN = '0' then
     y<=(others => 0);
  elsif Clk='1' and Clk'event  and Clk_reg_p='1' then
	   if (y_tot/K_x)<(2**(Res_d)) and (y_tot/K_x)>(-1*2**(Res_d)) then
	      y(0)<=(y_tot+(K_y/2))/K_y; 
	   elsif (y_tot/K_x)>=(2**(Res_d)-1) or (y_tot/K_x)<=(-1*2**(Res_d)) then
	    y(0)<=y(1);
	   end if;
      for i in (Regulsize-1) downto 1 loop
         y(i)<=y(i-1);
      end loop;
  end if;
  end process proceso_Y; 
    
  productos_Y: process (ResN,Clk)
  begin
  
  if ResN='0' then
    y_tot_aux<=0;
	 y_tot<=0;
  elsif Clk='1' and Clk'event then
	 y_tot_aux<=(a1*y(0)+a2*y(1)+a3*y(2));
    y_tot<=y_tot_aux+x_tot;
  end if;

  end process productos_Y;

 
 registro_salida:process (ResN,Clk)
 begin
 if ResN='0' then
   duty_out<=0;
 elsif Clk='1' and Clk'event then
   if (y_tot)>=0 then
	  if (y_tot*K_adc_pwm+(K_x/2))/K_x<(2**(Res_d)) and (y_tot*K_adc_pwm+(K_x/2))/K_x > 0 then
	    duty_out<=(y_tot*K_adc_pwm+(K_x/2))/K_x;      -- division con redondeo, en lugar de truncamiento
	  elsif (y_tot*K_adc_pwm+(K_x/2))/K_x>=(2**(Res_d)-1) then
	    duty_out<=(2**(Res_d)-1)-16;
	  end if;
	else duty_out<=0;
	end if; 
  end if; 
  end process registro_salida;
  
  end Estructural;

