{"cv9040"		
	{on spawn			
		{add_view	"flash_gun_big"			"flashbarrel5"			"Foresight5"}			
		{add_view "zenit_gilz"		"shell_mgun"	"fxshell_mg"}			}		
		("25mm_bushmaster")		
		("ajax_sound")		
		{on fire "mgun" 			
			{view start "flashbarrel5"}			
			{view start "shell_mgun"}			
			{kill_delay "flashbarrel5"}			
			{delay 0.08 "flashbarrel5"				
			{view pause "flashbarrel5"}				
			{view pause "shell_mgun"}			
		}			
		("cw_check_shooting" weap_id(mgun))		
		}	
}
{"9k33_osa_akm"		
	("btr80_sound")	  

	("radar_lifting90_params" triplex(additional_triplex) visor(visor_radar) anim_rotate(radar_loop) anim_lift(radar_lift) marker(antirad_generator_rus))	

	{on spawn	
		{add_view	 "startsmoke_big"	"shooter00"	"tail00"}			
		{add_view	 "startsmoke_big"	"shooter01"	"tail01"}			
		{add_view	 "startsmoke_big"	"shooter02"	"tail02"}		
		{add_view	 "startsmoke_big"	"shooter03"	"tail03"}		
		{add_view	 "startsmoke_big"	"shooter04"	"tail04"}		
		{add_view	 "startsmoke_big"	"shooter05"	"tail05"}			
	}
		
	{on fire "gun2" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "9m33_missile_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				  else ("fire_barrel" args 02)				  else ("fire_barrel" args 03)				  else ("fire_barrel" args 04)				  else ("fire_barrel" args 05)		
		}		
	}			
}

{"9k33_osa_akm_isis"		
	("btr80_sound")	  

	("radar_lifting90_params" triplex(additional_triplex) visor(visor_radar) anim_rotate(radar_loop) anim_lift(radar_lift) marker(antirad_generator_rus))	

	{on spawn	
		{add_view	 "startsmoke_big"	"shooter00"	"tail00"}			
		{add_view	 "startsmoke_big"	"shooter01"	"tail01"}			
		{add_view	 "startsmoke_big"	"shooter02"	"tail02"}		
		{add_view	 "startsmoke_big"	"shooter03"	"tail03"}		
		{add_view	 "startsmoke_big"	"shooter04"	"tail04"}		
		{add_view	 "startsmoke_big"	"shooter05"	"tail05"}			
	}
		
	{on fire "gun2" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "9m33_missile_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42						{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)				  else ("fire_barrel" args 01)				  else ("fire_barrel" args 02)				  else ("fire_barrel" args 03)				  else ("fire_barrel" args 04)				  else ("fire_barrel" args 05)		
		}		
	}			
}

{"2k12_kub"
	("Shilka_sound")	  	
	{on spawn			
	{add_view	 "flash_gun_big"	"shooter00"	"shooter00"}	{add_view	 "flash_gun_big"	"shooter01"	"shooter01"}
	{add_view	 "flash_gun_big"	"shooter02"	"shooter02"}

	{add_view	 "startsmoke_big"	"shooter00"	"shooter00"}			
	{add_view	 "startsmoke_big"	"shooter01"	"shooter01"}
	{add_view	 "startsmoke_big"	"shooter02"	"shooter02"}			 	
	}		
	{on fire "ptur" 			
	(define "fire_barrel"				name "%0"					
	{delay 0.1 
	{spawn "3m9_kub_carrier" "shooter%0"   x}
	}					
	{ani_play "fire"}					
	{view start "shooter%0"}					
	{delay 0.42					
	{view pause "shooter%0"}					
	}			
	)				
	{if    ("fire_barrel" args 00)			
	  else ("fire_barrel" args 01)			
	  else ("fire_barrel" args 02)				 			
	}		
	}	
	}

	{"2k12_kub"
	

	("radar_lifting90_params" triplex(additional_triplex) visor(visor2) anim_rotate(radar) anim_lift(radar) marker(antirad_generator_usa))	  
	
	}



{"2s7_pion"	  
	("Shilka_sound")	

	{on fire "gun" 
	     		{spawn "dust_shot_big_2" "basis"}
			{ani_play "fire"}
			{view start "flashbarrel_gun"}
			{view start "spawn_shell"}
	{delay 1
			{ani_play "reload"}}

	}	
}



{"saab_j39"
("air_multibarrel_launcher" weapon(ptur2) shooter(shooter)missile(aim-120c7) flashbarrel(shooter))				}

{"a4_skyhawk"
("air_multibarrel_launcher" weapon(ptur1) shooter(shooter_) missile(agm-65g) flashbarrel(shooter_))				}

{"su24_x59"
("air_multibarrel_launcher" weapon(ptur4) shooter(Shooter_x59_) missile(x59m) flashbarrel(Shooter_x59_))				
}
{"mig-21bis_x59"
("air_multibarrel_launcher" weapon(nar1) shooter(Shooter_0) missile(x59m) flashbarrel(Shooter_x59_))				
}		
{"su24_x31"
("air_multibarrel_launcher" weapon(ptur4) shooter(Shooter_r31_) missile(x31p) flashbarrel(Shooter_r31_))			
}	
{"su24_x25"
("air_multibarrel_launcher" weapon(ptur) shooter(shooter_) missile(x_25ml_su25_ammo) flashbarrel(shooter_))				
}
{"su24_agm88"
("air_multibarrel_launcher" weapon(ptur4) shooter(AGM-86-88_shooter_) missile(agm88) flashbarrel(AGM-86-88_shooter_))			
}
{"mig-21bis_agm88" 
("air_multibarrel_launcher" weapon(ptur2) shooter(Shooter_0) missile(x31p) flashbarrel(Shooter_r31_))					
}
{"harrier_support"
("air_multibarrel_launcher" weapon(ptur_agm) shooter(shooter_) missile(agm-65g) flashbarrel(shooter_))				}



{"m113a_ser"
	{On spawn
		{Delay 0.2
			{tex_mod "un"}
		}
	}
}
{"t34-85_ser"
	{On spawn
		{Delay 0.2
			{tex_mod "balkans"}
		}
	}
}
{"mig-21bis_harm"
	{On spawn
		{Delay 0.2
			{tex_mod "serb"}
		}
	}
}
{"mig-21bis_support"
	{On spawn
		{Delay 0.2
			{tex_mod "serb"}
		}
	}
}
{"mig-21bis_bomber"
	{On spawn
		{Delay 0.2
			{tex_mod "serb"}
		}
	}
}
{"mtlb_vmk_ogon"
	{On spawn
		{Delay 0.2
			{tex_mod "medic_ua"}
		}
	}
}