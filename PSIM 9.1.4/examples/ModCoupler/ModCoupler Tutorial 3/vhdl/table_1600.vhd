library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity table_1600 is


    Port ( Clk   : in std_logic;
           ADDR  : in integer  range 0 to 1023; 
           DOUT  : out integer range 0 to 999999;
           LOUT  : out integer range 0 to 1 
	);

end table_1600;

architecture Behavioral of table_1600 is
type matrice_angulo is array (0 to 63) of integer range 0 to 999999;  
type matrice_bit    is array (0 to 63) of integer range 0 to 1; 

constant angulos1600: matrice_angulo :=( 

-- ************ Ma=0.8 ************* --
27397 	,
31743 	,
54849 	,
63387 	,
82412 	,
94839 	,
110140	,
126019	,
138085	,
156866	,
166296	,
187335	,
194818	,
217401	,
223690	,
247057	,
252943	,
276310	,
282599	,
305182	,
312665	,
333704	,
343134	,
361915	,
373981	,
389860	,
405161	,
417588	,
436613	,
445151	,
468257	,
472603	,
527397	,
531743	,
554849	,
563387	,
582412	,
594839	,
610140	,
626019	,
638085	,
656866	,
666296	,
687335	,
694818	,
717401	,
723690	,
747057	,
752943	,
776310	,
782599	,
805182  ,
812665  ,                
833704  ,
843134  ,
861915  ,
873981  ,
889860  ,
905161  ,    
917588  ,
936613  ,
945151  ,
968257  ,
972603   
      
           
-- ******************************** --
);

constant nivel1600: matrice_bit :=(

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
1	,
0	,
1	,
0	,
1       ,
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
         DOUT <= angulos1600(ADDR);
         LOUT <= nivel1600(ADDR);
      end if;
  end process;
      
end Behavioral;



