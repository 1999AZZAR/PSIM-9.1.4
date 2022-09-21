library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

--  Uncomment the following lines to use the declarations that are
--  provided for instantiating Xilinx primitive components.
--library UNISIM;
--use UNISIM.VComponents.all;

entity param_table is


    Port ( Clk   : in std_logic;
           ADDR  : in integer range 0 to 15; 
           DOUT  : out integer range 0 to 1023	 
	);

end param_table;

architecture Behavioral of param_table is
type matrice is array (0 to 15) of integer range 0 to 1023;  
constant parametro:matrice :=(

-- ************ Ma=1.0 ************* --

55	,	--	1500
115	,	--	3000
395	,	--	15000
63	,	--	9090,909091
59	,	--	8000
59	,	--	7142,857143
59	,	--	6250
59	,	--	5000
59	,	--	4545,454545
59	,	--	4000
59	,	--	3030,30303
59	,	--	2500
59	,	--	2000
59	,	--	1600
59,		--	1503,759398
59
 


-- ******************************** --
);

begin
  Process(Clk)
    begin 
      if Clk'event and Clk='1' then
         DOUT <= parametro(ADDR);
      end if;
  end process;
      
end Behavioral;



