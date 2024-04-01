    	(include "terra-interactive_stuff.inc")	
{"air"		
{on detonate			
("terra-interactive_stuff")			
{if stuff "fx_proj_pointer"			
else stuff "fx_bul_small"			
else stuff "fx_bul_med"			
else stuff "fx_10_15 fx_ap"		{spawn "metal_crush_small"}			
else stuff "fx_10_15"		{spawn "ex_air_norm"}			
else stuff "fx_16_24 fx_ap"		{spawn "metal_crush_small"}			
else stuff "fx_16_24"		{spawn "ex_air_norm"}			
else stuff "fx_25_40 fx_ap"		{spawn "metal_crush_small"}			
else stuff "fx_25_40"		{spawn "ex_air_norm"}			
else stuff "fx_45_89 fx_ap"		{spawn "metal_crush"}			
else stuff "fx_45_89 fx_cm"		{spawn "ex_air_cmnorm"}			
else stuff "fx_45_89"		{spawn "ex_air_norm2"}			
else stuff "fx_90_110 fx_ap"		{spawn "metal_crush"}			
else stuff "fx_90_110 fx_cm"		{spawn "ex_air_cmnorm"}			
else stuff "fx_90_110 fx_splitter_big"	{spawn "ex_air_med"}{spawn "splitters_ground_big"}
else stuff "fx_90_110"		{spawn "ex_air_med"}			
else stuff "fx_111_145 fx_ap"		{spawn "metal_crush_big"}		
else stuff "fx_111_145 fx_cm"		{spawn "ex_air_cmnorm"}			
else stuff "fx_111_145"		{spawn "ex_air_big"}		
else stuff "fx_146_299 fx_ap"		{spawn "metal_crush_big"}		
else stuff "fx_146_299 fx_cm"		{spawn "ex_air_cmbig"}	
else stuff "fx_146_299 fx_splitter_big"	{spawn "ex_air_big2"} {spawn "splitters_ground_big"}	
else stuff "fx_146_299"		{spawn "ex_air_big2"}
else stuff "fx_upto15kg fx_cm"	{spawn "ex_air_cmbig"}
else stuff "fx_upto15kg"	 	{spawn "ex_air_extrabig"}
else stuff "fx_upto50kg"	 	{spawn "ex_fx_upto50kg"}{spawn "ex_fx_upto50kg_debris_road"}
else stuff "fx_upto250kg"	 	{spawn "ex_fx_upto250kg"}{spawn "ex_fx_upto250kg_debris_road"}	
else stuff "fx_upto1000kg"	 	{spawn "ex_fx_upto1000kg"}{spawn "ex_fx_upto1000kg_debris_road"}
else stuff "molotov_coctail"		{spawn "ex_molot"}			
else stuff "fx_wp_small"		{spawn "ex_wpshell_small"} {spawn "smoke_volume" offset 0 0 100}
else stuff "fx_wp_med"		{spawn "ex_wpshell_medium"} {spawn "smoke_volume" offset 0 0 150}
else stuff "fx_wp_large"		{spawn "ex_wpshell_large"} {spawn "smoke_volume" offset 0 0 200}
else stuff "fx_gren fx_ap"		{spawn "metal_crush_small"}	
else stuff "fx_gren fx_cm"		{spawn "ex_air_norm"}
else stuff "fx_gren"			{spawn "ex_air_norm"}
else stuff "fx_tos"			
else stuff "fx_shmel"			
else stuff "fx_odab250_air"		{spawn "ex_odab250"}
else stuff "fx_nuq"			{spawn "expluto"}	
else stuff "fx_nuq_air"		{spawn "expluto_air"}
}		
}	
}	