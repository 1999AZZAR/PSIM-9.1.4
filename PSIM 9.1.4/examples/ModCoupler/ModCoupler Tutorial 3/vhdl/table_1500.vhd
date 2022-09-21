library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity table_1500 is


    Port ( Clk   : in std_logic;
           ADDR  : in integer  range 0 to 1023; 
           DOUT  : out integer range 0 to 999999;
           LOUT  : out integer range 0 to 1 
	);

end table_1500;

architecture Behavioral of table_1500 is
type matrice_angulo is array (0 to 55) of integer range 0 to 999999;  
type matrice_bit    is array (0 to 55) of integer range 0 to 1; 

constant angulos1500: matrice_angulo :=( 

-- ************ Ma=0.8 ************* --
30772 	,
36353 	,
61632 	,
72536 	,
92668 	,
108395	,
123967	,
143808	,
155611	,
178684	,
187676	,
212974	,
220233	,
246664	,
253336	,
279767	,
287026	,
312324	,
321316	,
344389	,
356192	,
376033	,
391605	,
407332	,
427464	,
438368	,
463647	,
469228	,
530772	,
536353	,
561632	,
572536	,
592668	,
608395	,
623967	,
643808	,
655611	,
678684	,
687676	,
712974	,
720233	,
746664	,
753336	,
779767	,
787026	,
812324	,
821316	,
844389	,
856192	,
876033	,
891605	,
907332  ,
927464  ,                
938368  ,
963647  ,
969228  
        
  
     






           
-- ******************************** --
);

constant nivel1500: matrice_bit :=(

-- ************ Ma=0.8 ************* --

0       ,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1	,
0	,
1












            
-- ******************************** --
);


begin
  Process(Clk)
    begin 
      if Clk'event and Clk='1' then
         DOUT <= angulos1500(ADDR);
         LOUT <= nivel1500(ADDR);
      end if;
  end process;
      
end Behavioral;



