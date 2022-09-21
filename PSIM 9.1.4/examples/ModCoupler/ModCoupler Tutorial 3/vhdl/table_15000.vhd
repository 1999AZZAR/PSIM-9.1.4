library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity table_10000 is


    Port ( Clk   : in std_logic;
           ADDR  : in integer  range 0 to 1023; 
           DOUT  : out integer range 0 to 999999;
           LOUT  : out integer range 0 to 1 
	);

end table_10000;

architecture Behavioral of table_10000 is
type matrice_angulo10000 is array (0 to 395) of integer range 0 to 999999;  
type matrice_bit10000    is array (0 to 395) of integer range 0 to 1; 

constant angulos10000: matrice_angulo10000 :=( 

-- ************ Ma=0.8 ************* --
4938  	,
5064  	,
9876  	,
10128 	,
14815 	,
15191 	,
19753 	,
20254 	,
24691 	,
25317 	,
29630 	,
30380 	,
34569 	,
35442 	,
39509 	,
40504 	,
44449 	,
45565 	,
49390 	,
50626 	,
54331 	,
55686 	,
59273 	,
60745 	,
64215 	,
65804 	,
69158 	,
70862 	,
74103 	,
75919 	,
79047 	,
80975 	,
83993 	,
86030 	,
88940 	,
91084 	,
93888 	,
96136 	,
98837 	,
101188	,
103787	,
106238	,
108738	,
111288	,
113690	,
116336	,
118644	,
121382	,
123599	,
126427	,
128555	,
131471	,
133513	,
136513	,
138472	,
141554	,
143432	,
146593	,
148394	,
151630	,
153358	,
156666	,
158323	,
161700	,
163290	,
166733	,
168258	,
171764	,
173229	,
176792	,
178200	,
181820	,
183174	,
186845	,
188149	,
191868	,
193127	,
196890	,
198106	,
201910	,
203087	,
206927	,
208069	,
211943	,
213054	,
216957	,
218040	,
221969	,
223029	,
226979	,
228019	,
231987	,
233012	,
236994	,
238006	,
241998	,
243002	,
247000	,
248000	,
252000	,
253000	,
256998	,
258002	,
261994	,
263006	,
266988	,
268013	,
271981	,
273021	,
276971	,
278031	,
281960	,
283043	,
286946	,
288057	,
291931	,
293073	,
296913	,
298090	,
301894	,
303110	,
306873	,
308132	,
311851	,
313155	,
316826	,
318180	,
321800	,
323208	,
326771	,
328236	,
331742	,
333267	,
336710	,
338300	,
341677	,
343334	,
346642	,
348370	,
351606	,
353407	,
356568	,
358446	,
361528	,
363487	,
366487	,
368529	,
371445	,
373573	,
376401	,
378618	,
381356	,
383664	,
386310	,
388712	,
391262	,
393762	,
396213	,
398812	,
401163	,
403864	,
406112	,
408916	,
411060	,
413970	,
416007	,
419025	,
420953	,
424081	,
425897	,
429138	,
430842	,
434196	,
435785	,
439255	,
440727	,
444314	,
445669	,
449374	,
450610	,
454435	,
455551	,
459496	,
460491	,
464558	,
465431	,
469620	,
470370	,
474683	,
475309	,
479746	,
480247	,
484809	,
485185	,
489872	,
490124	,
494936	,
495062	,
504938	,
505064	,
509876	,
510128	,
514815	,
515191	,
519753	,
520254	,
524691	,
525317	,
529630	,
530380	,
534569	,
535442	,
539509	,
540504	,
544449	,
545565	,
549390	,
550626	,
554331	,
555686	,
559273	,
560745	,
564215	,
565804	,
569158	,
570862	,
574103	,
575919	,
579047	,
580975	,
583993	,
586030	,
588940	,
591084	,
593888	,
596136	,
598837	,
601188	,
603787	,
606238	,
608738	,
611288	,
613690	,
616336	,
618644	,
621382	,
623599	,
626427	,
628555	,
631471	,
633513	,
636513	,
638472	,
641554	,
643432	,
646593	,
648394	,
651630	,
653358	,
656666	,
658323	,
661700	,
663290	,
666733	,
668258	,
671764	,
673229	,
676792	,
678200	,
681820	,
683174	,
686845	,
688149	,
691868	,
693127	,
696890	,
698106	,
701910	,
703087	,
706927	,
708069	,
711943	,
713054	,
716957	,
718040	,
721969	,
723029	,
726979	,
728019	,
731987	,
733012	,
736994	,
738006	,
741998	,
743002	,
747000	,
748000	,
752000	,
753000	,
756998	,
758002	,
761994	,
763006	,
766988	,
768013	,
771981	,
773021	,
776971	,
778031	,
781960	,
783043	,
786946	,
788057	,
791931	,
793073	,
796913	,
798090	,
801894	,
803110	,
806873	,
808132	,
811851	,
813155	,
816826	,
818180	,
821800	,
823208	,
826771	,
828236	,
831742	,
833267	,
836710	,
838300	,
841677	,
843334	,
846642	,
848370	,
851606	,
853407	,
856568	,
858446	,
861528	,
863487	,
866487	,
868529	,
871445	,
873573	,
876401	,
878618	,
881356	,
883664	,
886310	,
888712	,
891262	,
893762	,
896213	,
898812	,
901163	,
903864	,
906112	,
908916	,
911060	,
913970	,
916007	,
919025	,
920953	,
924081	,
925897	,
929138	,
930842	,
934196	,
935785	,
939255	,
940727	,
944314	,
945669	,
949374	,
950610	,
954435	,
955551	,
959496	,
960491	,
964558	,
965431	,
969620	,
970370	,
974683	,
975309	,
979746	,
980247	,
984809	,
985185	,
989872	,
990124	,
994936	,
995062	
      	
	
      


            
-- ******************************** --
);

constant nivel10000: matrice_bit10000 :=( 

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
         DOUT <= angulos10000(ADDR);
         LOUT <= nivel10000(ADDR);
      end if;
  end process;
      
end Behavioral;



