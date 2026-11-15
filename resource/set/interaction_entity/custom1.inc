{"toyota_radar"		
	("btr80_sound")	  

	("radar_lifting90_params" triplex(additional_triplex) visor(visor_radar) anim_rotate(radar_loop) anim_lift(radar_lift) marker(antirad_generator_usa))				
}


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
		{add_view	"flash_gun_big"		"flash00"	"shooter00"}
		{add_view	"flash_gun_big"		"flash01"	"shooter01"}
		{add_view	"flash_gun_big"		"flash02"	"shooter02"}
		{add_view	"startsmoke_big"	"smoke00"	"shooter00"}
		{add_view	"startsmoke_big"	"smoke01"	"shooter01"}
		{add_view	"startsmoke_big"	"smoke02"	"shooter02"}
	}
	;3M9 is semi-active: 3m9_kub_carrier homes only on a target illuminated by 1s91_kub_radar
	{on fire "ptur"
		(define "fire_barrel"	name "%0"
			{delay 0.1
				{spawn "3m9_kub_carrier" "shooter%0" x}
			}
			{view start "flash%0"}
			{view start "smoke%0"}
			{delay 0.42
				{view pause "flash%0"}
				{view pause "smoke%0"}
			}
		)
		{if    ("fire_barrel" args 00)
		  else ("fire_barrel" args 01)
		  else ("fire_barrel" args 02)
		}
	}
}

{"1s91_kub_radar"
	("Shilka_sound")
	("radar_lifting90_params" triplex(additional_triplex) visor(visor2) anim_rotate(radar) anim_lift(radar) marker(antirad_generator_large_rus))
	;illumination radar works only while stationary, powered and intact (same rules as buk_launcher)
	{on move on
		{delay 0.1
			{call "update_radar"}
		}
	}
	{on move off
		{delay 0.1
			{call "update_radar"}
		}
	}
	{on "update_radar"
		{if tagged "radar_off"
			{weapon_work "laser" 0}
		else not work "additional_triplex"
			{weapon_work "laser" 0}
		else tagged "no_power"
			{weapon_work "laser" 0}
		else velocity 0
			{weapon_work "laser" 0}
		else
			{weapon_work "laser" 1}
		}
	}
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
{"su24m_storm_ukr"
("air_multibarrel_launcher" weapon(ptur4) shooter(Shooter_r31_) missile(storm_shadow) flashbarrel(Shooter_r31_))
	{on spawn
		{delay 0.2
			{tex_mod "ukr_pix"}
		}
	}
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