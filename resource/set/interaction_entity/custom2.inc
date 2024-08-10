{"t-64bm2"
	{on spawn
		{call "rand_tex"}	
	}
	{on "rand_tex"	
				(define "rand_tex" 
						{if rand %r1
							{delay 0.05 
								{tex_mod "%r2"}	
							}
						}
				)	
("rand_tex" r1(0.15) r2(serb_1))	
("rand_tex" r1(0.15) r2(serb_2))	


	}
	
}
{"toyota_hilux_dshkm"
	{on spawn
		{call "rand_tex"}	
	}
	{on "rand_tex"	
				(define "rand_tex" 
						{if rand %r1
							{delay 0.05 
								{tex_mod "%r2"}	
							}
						}
				)	
("rand_tex" r1(0.25) r2(hamas1))	
("rand_tex" r1(0.25) r2(hamas2))	
("rand_tex" r1(0.10) r2(un))
("rand_tex" r1(0.15) r2(red2))
("rand_tex" r1(0.15) r2(5))

("rand_tex" r1(0.15) r2(2))

	}
	
}
{"toyota_hilux_spg9"
	{on spawn
		{call "rand_tex"}	
	}
	{on "rand_tex"	
				(define "rand_tex" 
						{if rand %r1
							{delay 0.05 
								{tex_mod "%r2"}	
							}
						}
				)	
("rand_tex" r1(0.25) r2(hamas1))	
("rand_tex" r1(0.25) r2(hamas2))	
("rand_tex" r1(0.10) r2(un))
("rand_tex" r1(0.15) r2(red2))
("rand_tex" r1(0.15) r2(5))

("rand_tex" r1(0.15) r2(2))

	}
	
}
{"toyota_hilux_ammo"
	{on spawn
		{call "rand_tex"}	
	}
	{on "rand_tex"	
				(define "rand_tex" 
						{if rand %r1
							{delay 0.05 
								{tex_mod "%r2"}	
							}
						}
				)	
("rand_tex" r1(0.25) r2(hamas1))	
("rand_tex" r1(0.25) r2(hamas2))	
("rand_tex" r1(0.10) r2(un))
("rand_tex" r1(0.15) r2(red2))
("rand_tex" r1(0.15) r2(5))

("rand_tex" r1(0.15) r2(2))

	}
	
}
{"toyota_hilux_tow"
	{on spawn
		{call "rand_tex"}	
	}
	{on "rand_tex"	
				(define "rand_tex" 
						{if rand %r1
							{delay 0.05 
								{tex_mod "%r2"}	
							}
						}
				)	
("rand_tex" r1(0.25) r2(hamas1))	
("rand_tex" r1(0.25) r2(hamas2))	
("rand_tex" r1(0.10) r2(un))
("rand_tex" r1(0.15) r2(red2))
("rand_tex" r1(0.15) r2(5))
("rand_tex" r1(0.15) r2(ter))
("rand_tex" r1(0.15) r2(2))

	}
	
}

{"stugna-p"		
	{on fire "gun2" 			
		{spawn "proj_probe" "Foresight1" x {tags add "Foresight1"}}		
	}		
	{on "cut_parts" overload			
		{add_view "smoke_dead_norm" "deathfx" "FXfire1"}			
		{view start "deathfx"}			
			(define "cut_part"				
				{tear "piece_medium_steel" bone %0					
					{impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position}					
					{call "check_delete_part"}				
				}			
			)			
		("cut_part" args "part1")			
		("cut_part" args "part2")			
		("cut_part" args "part3")			
		("cut_part" args "part5")			
		("cut_part" args "gun")			
		("cut_part" args "turret")			
		{delay 14 {view stop "deathfx"}}		
	}		
}


{"btr4e"
	{on spawn			
		{add_view "smoke_zenit" 	"zenite_smoke" "foresight1"}					
 	}
	{on fire "gun" 	      	    	 
		{spawn "BMP2_canon_fire" "Foresight1" x}								
		{view start "flashbarrel_gun"}						
		{view start "smoke_add"}			
		{delay 0.16 "shell_off"			
			{view start "zenite_smoke"}
		}		
		{view pause "smoke_add"}			
		{view pause "flashbarrel_gun"}
			
		{delay 5			
			{view pause "zenite_smoke"}		
		}	
		{spawn "gilza_30mm" "fx_invers"
	        	{add_view "smoke_zenit" "smoke_shell" "fx_invers"}
			{view start "smoke_shell"}
			{impulse up 0.1 0.1 dir 4 0  cz 0.3 0.3 com }
			{delay 5
				{view pause "smoke_shell"}
                        		}
			{delay 7
				{hide 7}
			}
		}
	}
}
(define "btr-4e_sound"
	{on "add_movement_sound" overload
		{link_sound "move"		"vehicle/wheels/Truck_loop_3"}
		{link_sound "engine"		"vehicle/engine/Brdm_engine_1"}
		{link_sound "rotate_turret" 	"vehicle/bmp-1_ukr/turret_b1"}
		{link_sound "exhaust"		"vehicle/engine/brdm_start"}
		{link_sound "engine_end"	"vehicle/engine/brdm_shut_off"}
	}
)
{"btr-4e"
	("atgm_single_launcher" weapon(gun2) foresight(foresight6) tail(tailR_))
}

{"btr4e1"
	{on spawn			
		{add_view "smoke_zenit" 	"zenite_smoke" "foresight1"}					
 	}
	{on fire "gun" 	      	    	 
		{spawn "BMP2_canon_fire" "Foresight1" x}								
		{view start "flashbarrel_gun"}						
		{view start "smoke_add"}			
		{delay 0.16 "shell_off"			
			{view start "zenite_smoke"}
		}		
		{view pause "smoke_add"}			
		{view pause "flashbarrel_gun"}
			
		{delay 5			
			{view pause "zenite_smoke"}		
		}	
		{spawn "gilza_30mm" "fx_invers"
	        	{add_view "smoke_zenit" "smoke_shell" "fx_invers"}
			{view start "smoke_shell"}
			{impulse up 0.1 0.1 dir 4 0  cz 0.3 0.3 com }
			{delay 5
				{view pause "smoke_shell"}
                        		}
			{delay 7
				{hide 7}
			}
		}
	}
}
(define "btr-4e_sound"
	{on "add_movement_sound" overload
		{link_sound "move"		"vehicle/wheels/Truck_loop_3"}
		{link_sound "engine"		"vehicle/engine/Brdm_engine_1"}
		{link_sound "rotate_turret" 	"vehicle/bmp-1_ukr/turret_b1"}
		{link_sound "exhaust"		"vehicle/engine/brdm_start"}
		{link_sound "engine_end"	"vehicle/engine/brdm_shut_off"}
	}
)
{"btr4e1"
	("atgm_single_launcher" weapon(gun2) foresight(foresight6) tail(tailR_))
}
{"btr4e1_ptur"
	{on spawn			
		{add_view "smoke_zenit" 	"zenite_smoke" "foresight1"}					
 	}
	{on fire "gun" 	      	    	 
		{spawn "BMP2_canon_fire" "Foresight1" x}								
		{view start "flashbarrel_gun"}						
		{view start "smoke_add"}			
		{delay 0.16 "shell_off"			
			{view start "zenite_smoke"}
		}		
		{view pause "smoke_add"}			
		{view pause "flashbarrel_gun"}
			
		{delay 5			
			{view pause "zenite_smoke"}		
		}	
		{spawn "gilza_30mm" "fx_invers"
	        	{add_view "smoke_zenit" "smoke_shell" "fx_invers"}
			{view start "smoke_shell"}
			{impulse up 0.1 0.1 dir 4 0  cz 0.3 0.3 com }
			{delay 5
				{view pause "smoke_shell"}
                        		}
			{delay 7
				{hide 7}
			}
		}
	}
}
(define "btr4e_sound"
	{on "add_movement_sound" overload
		{link_sound "move"		"vehicle/wheels/Truck_loop_3"}
		{link_sound "engine"		"vehicle/engine/Brdm_engine_1"}
		{link_sound "rotate_turret" 	"vehicle/bmp-1_ukr/turret_b1"}
		{link_sound "exhaust"		"vehicle/engine/brdm_start"}
		{link_sound "engine_end"	"vehicle/engine/brdm_shut_off"}
	}
)
{"btr-4e1_ptur"
	("atgm_single_launcher" weapon(gun2) foresight(foresight6) tail(tailR_))
}


{"btr3e"	
	("atgm_single_launcher"
		weapon(gun2)
		foresight(foresight6)
		tail(foresight6)
	)
}


{"btr-4e1_wtht_pt"
	{on spawn			
		{add_view "smoke_zenit" 	"zenite_smoke" "foresight1"}					
 	}
	{on fire "gun" 	      	    	 
		{spawn "BMP2_canon_fire" "Foresight1" x}								
		{view start "flashbarrel_gun"}						
		{view start "smoke_add"}			
		{delay 0.16 "shell_off"			
			{view start "zenite_smoke"}
		}		
		{view pause "smoke_add"}			
		{view pause "flashbarrel_gun"}
			
		{delay 5			
			{view pause "zenite_smoke"}		
		}	
		{spawn "gilza_30mm" "fx_invers"
	        	{add_view "smoke_zenit" "smoke_shell" "fx_invers"}
			{view start "smoke_shell"}
			{impulse up 0.1 0.1 dir 4 0  cz 0.3 0.3 com }
			{delay 5
				{view pause "smoke_shell"}
                        		}
			{delay 7
				{hide 7}
			}
		}
	}
}
(define "btr-4e_sound"
	{on "add_movement_sound" overload
		{link_sound "move"		"vehicle/wheels/Truck_loop_3"}
		{link_sound "engine"		"vehicle/engine/Brdm_engine_1"}
		{link_sound "rotate_turret" 	"vehicle/bmp-1_ukr/turret_b1"}
		{link_sound "exhaust"		"vehicle/engine/brdm_start"}
		{link_sound "engine_end"	"vehicle/engine/brdm_shut_off"}
	}
)



{"ptur_konkurs_2"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"ptur_konkurs_3"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"metis_m_odkb"	
	("atgm_single_launcher"
		weapon(gun2)
		foresight(foresight1)
		tail(foresight1)
	)
}

{"milan_stan_un"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"milan_stan_2"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"toyota_hilux_tow"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"shershen_d_stan_4"	
	("atgm_multi_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"brdm2grom"	
	("atgm_single_launcher"
		weapon(gun2)
		foresight(foresight2)
		tail(foresight2)
	)
}
	
{"hj8_stan_2"	
	("atgm_single_launcher"
		weapon(gun)
		foresight(foresight1)
		tail(foresight1)
	)
}
{"tank_avlb"
	("abrams_sound")
	{on "specability" 
		{ani_play "close" 0.1} 
                {delay 40
		{spawn "qm" "qiao" x}
                {delay 0.1
		{bone hide "Mesh08"}
		{bone cut "qiao"}}
                {delay 5
		{ani_play "close" -0.4} }}          
 	}
}
{"t-64b_ser"
	("T64_sound")
	("2a46_type_gun")
}



{"chapparal"
	("m113_sound")	  	
	{on spawn			
	{add_view	 "flash_gun_big"	"shooter00"	"shooter00"}			
	{add_view	 "flash_gun_big"	"shooter01"	"shooter01"}
	{add_view	 "flash_gun_big"	"shooter02"	"shooter02"}			
	{add_view	 "flash_gun_big"	"shooter03"	"shooter03"}
	
	{add_view	 "startsmoke_big"	"shooter00"	"shooter00"}			
	{add_view	 "startsmoke_big"	"shooter01"	"shooter01"}
	{add_view	 "startsmoke_big"	"shooter02"	"shooter02"}			
	{add_view	 "startsmoke_big"	"shooter03"	"shooter03"}	
	}		
	{on fire "gun2" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "aim-9l_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				  else ("fire_barrel" args 02)				  else ("fire_barrel" args 03)				 			
	}		
	}	
	}	


{"hawk"
	("m113_sound")	  	
	{on spawn			
	{add_view	 "flash_gun_big"	"shooter00"	"shooter00"}			
	{add_view	 "flash_gun_big"	"shooter01"	"shooter01"}
	{add_view	 "flash_gun_big"	"shooter02"	"shooter02"}			
	
	{add_view	 "startsmoke_big"	"shooter00"	"shooter00"}			
	{add_view	 "startsmoke_big"	"shooter01"	"shooter01"}
	{add_view	 "startsmoke_big"	"shooter02"	"shooter02"}			 	
	}		
	{on fire "ptur1" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "mim23b_ihawk_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				  else ("fire_barrel" args 02)				 			
	}		
	}	
	}	




{"s125x2"
	("Ural375_sound")	  	
	{on spawn			
	{add_view	 "flash_gun_big"	"shooter00"	"shooter00"}			
	{add_view	 "flash_gun_big"	"shooter01"	"shooter01"}			
	
	{add_view	 "startsmoke_big"	"shooter00"	"shooter00"}			
	{add_view	 "startsmoke_big"	"shooter01"	"shooter01"}		 	
	}		
	{on fire "gun2" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "s125_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				 			
	}		
	}	
	}	


{"s125x4"	  	
	{on spawn			
	{add_view	 "flash_gun_big"	"shooter00"	"shooter00"}			
	{add_view	 "flash_gun_big"	"shooter01"	"shooter01"}
	{add_view	 "flash_gun_big"	"shooter02"	"shooter02"}			
	{add_view	 "flash_gun_big"	"shooter03"	"shooter03"}
	
	{add_view	 "startsmoke_big"	"shooter00"	"shooter00"}			
	{add_view	 "startsmoke_big"	"shooter01"	"shooter01"}
	{add_view	 "startsmoke_big"	"shooter02"	"shooter02"}			
	{add_view	 "startsmoke_big"	"shooter03"	"shooter03"}	
	}		
	{on fire "gun2" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "s125_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				  else ("fire_barrel" args 02)				  else ("fire_barrel" args 03)				 			
	}		
	}	
	}	




{"s75"	  			
	{on fire "gun2" 			
	{spawn "s75_carrier" "shooter00"   x}				
	}	
	}	

