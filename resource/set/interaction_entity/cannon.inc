(define "handle_ik"
{
	on ik begin "basis"
}
{
	on ik end "basis"
}
{
	on ik begin "turret"
	{
		play_sound "rotate_turret" 1
	}
}
{
	on ik end "turret"
	{
		stop_sound "rotate_turret"
	}
}
{
	on ik begin "gun_rot"
}
{
	on ik end "gun_rot"
}
{
	on ik begin "turret_rotator"
}
{
	on ik end "turret_rotator"
}
)		(define "damage_cannon_process_pierce"
{
	if stuff "%staff"
	{
		if volume "standl"	                   	    else volume "standr"	                   	    else volume "wheell"	                   	    else volume "wheelr"	                   	    else volume "gun"
		{
			components "gun" break
		}
		else
		{
			burn fx "smoke_dead_tank3" fake
		}
		{
			if rand %pierce_turret__crew_die
			{
				kill_crew "commander"
			}
			{
				kill_crew "driver1"
			}
			else rand %pierce_turret__crew_die
			{
				kill_crew "driver2"
			}
			{
				kill_crew "gunner"
			}
			else rand %pierce_turret__crew_die
			{
				kill_crew "commander1"
			}
		}
		{
			if rand %pierce_turret__crew_contusion
			{
				crew_throw_off up 2 1 dir 2 1 turn 0 180 forward 2 force
			}
			{
				if operatable
				{
					weapon_work "gun" 0
				}
				{
					tags add "contused"
				}
				{
					delay 2
					{
						if not tagged "gun_brake"
						{
							weapon_work "gun" 1
						}
					}
					{
						tags remove "contused"
					}
				}
			}
		}
		{
			if rand %pierce_turret__gun_brake
			{
				components "gun" break
			}
		}
	}
}
)
{
	"cannon"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on "leave_unit" overload
		{
			if operatable
			{
				call "cwsh_switch_hatch"
			}
		}
	}
	{
		on pierce	            ("damage_cannon_process_pierce"	                staff(ptr)	                pierce_turret__crew_die(0)	                pierce_turret__gun_brake(0)	                pierce_turret__crew_contusion(0)	            )	            ("damage_cannon_process_pierce"	                staff(shell ap)	                pierce_turret__crew_die(0.5)	                pierce_turret__gun_brake(0.3)	                pierce_turret__crew_contusion(1)	            )
	}
	{
		on break_armor
		{
			call "do_armor_break"
		}
	}
	{
		on break_armor_again
		{
			call "do_armor_break"
		}
	}
	{
		on "do_armor_break"
		{
			if name "blast"
			{
				if volume "body"
				{
					components "body" destroy
				}
				{
					call "stat_break"
				}
				{
					kick_entity_manager
				}
				{
					reset_manual_control
				}
				{
					able select 0
				}
				{
					able repaired 0
				}
				{
					unlink_trailer
				}
				{
					tags add "destroyed"
				}
				else volume "turret"
				{
					components "turret" destroy
				}
				{
					call "stat_break"
				}
				{
					kick_entity_manager
				}
				{
					reset_manual_control
				}
				{
					able select 0
				}
				{
					able repaired 0
				}
				{
					unlink_trailer
				}
				{
					tags add "destroyed"
				}
			}
		}
	}
	{
		on blast_hit
		{
			if min_energy 5
			{
				if not linked
				{
					impulse up 0.5 0.2 dir 1 0.2
				}
			}
			{
				if simulating
				{
					attack_save
				}
				{
					delay_ex 0.3
					{
						attack_load
					}
					{
						crew_throw_off up 4 1 dir 5 1 turn 0 180 forward 2 force
					}
				}
			}
			{
				call "explosion"
			}
			else min_energy 1.2
			{
				if not linked
				{
					impulse up 0.3 0.2 dir 0.7 0.2
				}
			}
			{
				if simulating
				{
					attack_save
				}
				{
					delay_ex 0.3
					{
						attack_load
					}
					{
						crew_throw_off up 4 1 dir 5 1 turn 0 180 forward 2 force
					}
				}
			}
			else min_energy 0.6
			{
				ani_play "hit"
			}
		}
	}
	{
		on "explosion"
		{
			components "body" destroy
		}
		{
			components "turret" destroy
		}
		{
			call "stat_break"
		}
		{
			kick_entity_manager
		}
		{
			reset_manual_control
		}
		{
			able select 0
		}
		{
			able repaired 0
		}
		{
			unlink_trailer
		}
	}
	{
		on "cut_parts"
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "part5")			("cut_part" args "part6")			("cut_part" args "part7")			("cut_part" args "part8")			("cut_part" args "part9")			("cut_part" args "part10")			("cut_part" args "part11")			("cut_part" args "part12")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
	{
		on fire "gun"
		{
			ani_play "recoil"
		}
		{
			view start "flashbarrel1"
		}
		{
			view start "flashbarrel1s"
		}
		{
			delay 0.15
			{
				view pause "flashbarrel1"
			}
		}
		{
			delay 0.3
			{
				view pause "flashbarrel1s"
			}
		}
		{
			call "spawn_shell"
		}
	}
	{
		on "spawn_shell"
		{
			start_sound "weapon/shot/shell"
		}
		{
			add_view "smoke_zenit" "smoke_shell" "fx_invers"
		}
		{
			view start "smoke_shell"
		}
		{
			delay 2.5 0.5
			{
				view stop "smoke_shell"
			}
		}
		{
			spawn "shell_cannon" "fx_invers" x
			{
				impulse up 1.5 0.5 dir -4.5 0.7 cz 0.2 0.1 com
			}
			{
				add_view "smoke_zenit" "smoke_shell" "fx_shellsmoke"
			}
			{
				view start "smoke_shell"
			}
			{
				delay_effect 3 1 "stop"
			}
			{
				delay 3 0.5
				{
					hide 3
				}
			}
		}
	}
	{
		on contact
		{
			if not impregnable
			{
				if not effector "armored_car"
				{
					if effector "tank"
					{
						if effector_velocity 10
						{
							component destroy
						}
						{
							set "crush" 1
						}
						{
							call "explosion"
						}
					}
					else effector "big part"
					{
						if effector_velocity 5
						{
							component break
						}
					}
				}
			}
		}
	}
	("handle_ik")
	{
		on "check_water_level" overload
		{
			if not linked
			{
				if water_level 1.2
				{
					able "sinking" 1
				}
			}
		}
	}
	{
		on "tear_wheel" overload
	}
	{
		on "diagnostics"
		{
			if not work "mgun"
			{
				damage_report "mgun" "component/armored/mgun_damaged"
			}
			else not work "mgun1"
			{
				damage_report "mgun1" "component/armored/mgun_damaged"
			}
			else not work "mgun2"
			{
				damage_report "mgun2" "component/armored/mgun_damaged"
			}
			else not work "mgun3"
			{
				damage_report "mgun3" "component/armored/mgun_damaged"
			}
			else not work "mgun4"
			{
				damage_report "mgun4" "component/armored/mgun_damaged"
			}
			else not work "mgun5"
			{
				damage_report "mgun5" "component/armored/mgun_damaged"
			}
			else not work "mgun6"
			{
				damage_report "mgun6" "component/armored/mgun_damaged"
			}
		}
		{
			if not work "gun"
			{
				damage_report "gun" "component/armored/gun1_damaged"
			}
		}
		{
			if not work "gun1"
			{
				damage_report "gun1" "component/armored/gun1_damaged"
			}
		}
		{
			if not work "gun2"
			{
				damage_report "gun2" "component/armored/ptur_damaged"
			}
			else not work "gun3"
			{
				damage_report "gun3" "component/armored/ptur_damaged"
			}
		}
		{
			if not work "driver_triplex"
			{
				damage_report "driver_triplex" "component/armored/driver_triplex_damaged"
			}
		}
		{
			if not work "commander_triplex"
			{
				damage_report "commander_triplex" "component/armored/commander_triplex_damaged"
			}
		}
		{
			if not work "additional_triplex"
			{
				damage_report "additional_triplex" "component/armored/additional_triplex_damaged"
			}
			else not work "additional_triplex1"
			{
				damage_report "additional_triplex1" "component/armored/additional_triplex_damaged"
			}
			else not work "additional_triplex2"
			{
				damage_report "additional_triplex2" "component/armored/additional_triplex_damaged"
			}
			else not work "additional_triplex3"
			{
				damage_report "additional_triplex3" "component/armored/additional_triplex_damaged"
			}
			else not work "additional_triplex4"
			{
				damage_report "additional_triplex4" "component/armored/additional_triplex_damaged"
			}
			else not work "additional_triplex5"
			{
				damage_report "additional_triplex5" "component/armored/additional_triplex_damaged"
			}
		}
		{
			if not work "body"
			{
				damage_report "body" "component/body_broken"
			}
		}
		{
			if not work "turret"
			{
				damage_report "turret" "component/turret_broken"
			}
		}
		{
			if not work "engine"
			{
				damage_report "engine" "component/engine_broken"
			}
		}
		{
			if not work "wheelleft1"
			{
				damage_report "wheelleft1" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelright1"
			{
				damage_report "wheelright1" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelleft2"
			{
				damage_report "wheelright2" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelright2"
			{
				damage_report "wheelright2" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelleft3"
			{
				damage_report "wheelright3" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelright3"
			{
				damage_report "wheelright3" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelleft4"
			{
				damage_report "wheelright4" "component/airborne_M/wheels_damaged"
			}
			else not work "wheelright4"
			{
				damage_report "wheelright4" "component/airborne_M/wheels_damaged"
			}
		}
	}
}
{
	"ATGM"
	{
		on spawn overload
		{
			add_view 	"rok_tail"	                            "rok_tail"			"tail"
		}
		{
			add_view 	"startsmoke"	                            "startsmoke"			"foresight1"
		}
		{
			add_view 	"smoke_zenit" 	"zenite_smoke2" 		"tail"
		}
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload			("low_speed_bullet")
		{
			view start "rok_tail"
		}
		{
			view start "startsmoke"
		}
		{
			volumes "gun" disable bullet blast
		}
		{
			if terrain_fx "ground"
			{
				spawn "dust_shot_norm" "basis"
			}
			else terrain_fx "country_road"
			{
				spawn "dust_shot_norm" "basis"
			}
			else terrain_fx "sand"
			{
				spawn "dust_shot_big" "basis"
			}
		}
		{
			delay 0.4
			{
				view pause "rok_tail"
			}
		}
		{
			delay 0.12
			{
				view start "zenite_smoke2"
			}
			{
				delay 25 15
				{
					view pause "zenite_smoke2"
				}
			}
		}
		{
			delay 30
			{
				volumes "gun" enable bullet blast
			}
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on fire "gun2" overload			("low_speed_bullet")
		{
			view start "rok_tail"
		}
		{
			view start "startsmoke"
		}
		{
			volumes "gun" disable bullet blast
		}
		{
			if terrain_fx "ground"
			{
				spawn "circledust_norm" "basis"
			}
			else terrain_fx "country_road"
			{
				spawn "circledust_norm" "basis"
			}
			else terrain_fx "sand"
			{
				spawn "circledust_norm" "basis"
			}
		}
		{
			delay 0.4
			{
				view pause "rok_tail"
			}
		}
		{
			delay 0.12
			{
				view start "zenite_smoke2"
			}
			{
				delay 25 15
				{
					view pause "zenite_smoke2"
				}
			}
		}
		{
			delay 30
			{
				volumes "gun" enable bullet blast
			}
		}
		("cw_check_shooting" weap_id(gun2))
	}
	{
		on pierce
		{
			if volume "gun"
			{
				components "gun" break
			}
			else volume "gun2"
			{
				components "gun2" break
			}
		}
	}
	{
		on break
		{
			if component "gun"
			{
				if not tagged "destroyed"
				{
					damage_report "turret" "component/other/ptur_damaged"
				}
				{
					spawn "metal_hit_bul"
				}
				{
					tags add "gun_damaged"
				}
				{
					weapon_work "gun" 0
				}
				{
					weapon_work "gun2" 0
				}
				{
					if explosive_amount 10
					{
						spawn "ex_air_big"
					}
					{
						blastwave c4 6 r0 0.5 r1 1 position
					}
					{
						blastwave c4 2 r0 3 r1 4 position
					}
					else explosive_amount 5
					{
						spawn "ex_air_big"
					}
					{
						blastwave c4 2 r0 3 r1 4 position
					}
				}
			}
			else component "gun2"
			{
				if not tagged "destroyed"
				{
					damage_report "turret" "component/other/ptur_damaged"
				}
				{
					spawn "metal_hit_bul"
				}
				{
					tags add "gun_damaged"
				}
				{
					weapon_work "gun" 0
				}
				{
					weapon_work "gun2" 0
				}
				{
					if explosive_amount 30
					{
						spawn "ex_air_big"
					}
					{
						blastwave c4 6 r0 0.5 r1 1 position
					}
					{
						blastwave c4 2 r0 3 r1 4 position
					}
					else explosive_amount 10
					{
						spawn "ex_air_big"
					}
					{
						blastwave c4 2 r0 3 r1 4 position
					}
				}
			}
		}
	}
	{
		on repair
		{
			if component "gun"
			{
				damage_report "gun" "component/other/ptur_repaired"
			}
			{
				tags remove "gun_damaged"
			}
			{
				weapon_work "gun" 1
			}
			{
				weapon_work "gun2" 1
			}
			else component "gun2"
			{
				damage_report "gun2" "component/other/ptur_repaired"
			}
			{
				tags remove "gun2_damaged"
			}
			{
				tags remove "gun_damaged"
			}
			{
				weapon_work "gun2" 1
			}
			{
				weapon_work "gun" 1
			}
		}
		{
			if component "body"
		}
	}
	{
		on blast_hit
		{
			if min_energy 2
			{
				call "explosion"
			}
		}
	}
	{
		on move on
		{
			tags add "no_missile_control"
		}
	}
	{
		on move off
		{
			tags remove "no_missile_control"
		}
	}
	{
		on "update_power"
		{
			tags remove "no_missile_control"
		}
	}
}
{
	"laser_designator"
	{
		on spawn overload				(mod not "mp"
		{
			add_view "laser_designator" "laser_designator" "foresight1"
		}
		)
		{
			view hide "laser_designator"
		}
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload
		{
			view show "laser_designator"
		}
		{
			delay 0.6
			{
				view hide "laser_designator"
			}
		}
		("cw_check_shooting" weap_id(gun))
	}
}
{
	"eleron_catapult"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "fire" callback
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on animation_end "fire"
		{
			spawn "eleron3sv" "foresight1" x
		}
	}
}
{
	"lancet3m_catapult"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
		{
			tags remove "lancet3m_fg"
		}
		{
			tags remove "lancet3m_cm"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "fire" callback
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on animation_end "fire"
		{
			if tagged "lancet3m_fg"
			{
				spawn "lancet3m_fg" "foresight1" x
			}
			else
			{
				spawn "lancet3m_cm" "foresight1" x
			}
		}
		{
			tags remove "lancet3m_fg"
		}
		{
			tags remove "lancet3m_cm"
		}
	}
}
{
	"switchblade300_catapult"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "fire" callback
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on animation_end "fire"
		{
			spawn "switchblade300" "foresight1" x
		}
	}
}
{
	"switchblade600_catapult"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "fire" callback
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on animation_end "fire"
		{
			spawn "switchblade600" "foresight1" x
		}
	}
}
{
	"ch901_catapult"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "fire" callback
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on animation_end "fire"
		{
			spawn "ch901" "foresight1" x
		}
	}
}
{
	"ptur_konkurs"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "Foresight1"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "ptur_rot")			("cut_part" args "turret")			("cut_part" args "ptur")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"metis_m"
	{
		on fire "gun2"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "Foresight1"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"kornet_stan"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "Foresight1"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part5")			("cut_part" args "gun")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"malytka_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "9k14m_carrier" "Foresight1_spawn" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "gun")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"hj73_stan"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "foresight1_spawn"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "gun")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"ptur_tow"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "Foresight1"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "gun")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"hj8_stan"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
			{
				tags add "Foresight1"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"milan_stan"
	{
		on fire "gun"
		{
			spawn "proj_probe" "foresight1_spawn" x
			{
				tags add "foresight1_spawn"
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"spike_lr_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "spike-lr_carrier" "foresight1" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"spike_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "spike-er_carrier" "foresight1" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"mmp_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "mmp_missile_carrier" "foresight1" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"mistral_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "mistral_missile_carrier" "foresight1" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part5")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"starstreak_stan"		("custom_multi_launcher"	weapon(gun) tail(taill_) shooter(shooter) missile(starstreak_ammo))
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "part5")			("cut_part" args "part6")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"shershen_d_stan"		("atgm_multi_launcher" weapon(gun) foresight(foresight1) tail(tail))
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 1 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 5 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "gun")			("cut_part" args "turret")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"tl-4_stan"
	{
		on fire "gun"
		{
			delay 0.1
			{
				spawn "tl4_cm_carrier" "foresight1" x
			}
		}
	}
	{
		on "cut_parts" overload
		{
			add_view "smoke_dead_norm" "deathfx" "FXfire1"
		}
		{
			view start "deathfx"
		}
		(define "cut_part"
		{
			tear "piece_medium_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")
		{
			delay 14
			{
				view stop "deathfx"
			}
		}
	}
}
{
	"spg_9"
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
		}
		{
			spawn "startsmoke" "tail" x
		}
	}
}
{
	"cannon_small"
	{
		on spawn
		{
			tags add "cannon_proj"
		}
	}
	{
		on contact overload
		{
			if not impregnable
			{
				if effector "tank"
				{
					if effector_velocity 7
					{
						component destroy
					}
					{
						set "crush" 1
					}
					{
						call "explosion"
					}
				}
				else effector "armored_car"
				{
					if effector_velocity 10
					{
						component destroy
					}
					{
						set "crush" 1
					}
					{
						call "explosion"
					}
				}
			}
		}
	}
}
{
	"mg_stan"
	{
		on spawn
		{
			add_view	"flash_gun_big"	"flashbarrel2"	"Foresight3"
		}
	}
	{
		on fire "mgun"
		{
			view start "flashbarrel2"
		}
	}
	{
		on "explosion_blastwave" overload
		{
			impulse up 0.2 dir 0.3
		}
	}
	{
		on break
		{
			if component "shield"
			{
				call "explosion"
			}
		}
	}
}
{
	"no_exp_blast"
	{
		on "explosion_blastwave" overload
	}
	{
		on "explosion_sound" overload
	}
}
{
	"heavy cannon"
	{
		on spawn
		{
			add_view	"flash_cannon_medium"	"flashbarrel1"	"Foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "dust_shot_norm" "basis"
		}
		{
			spawn "tank_canon_fire" "Foresight1" x
		}
	}
}
{
	"medium cannon"
	{
		on spawn
		{
			add_view	"flash_cannon_small"	"flashbarrel1"	"Foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "dust_shot_small" "basis"
		}
		{
			spawn "tank_canon_fire_small" "Foresight1" x
		}
	}
}
{
	"truck_mortar"
	{
		on fire "gun"
		{
			spawn "startsmoke" inv_normal
		}
		{
			spawn "circledust_norm2" "basis"
		}
		{
			ani_play "recoil"
		}
		{
			call "spawn_shell"
		}
		("cw_check_shooting" weap_id(gun))
	}
}
{
	"mortar"
	{
		on spawn overload
		{
			link_sound "rotate_turret" "vehicle/turret/mortar"
		}
		{
			link_sound "rotate_gun" "vehicle/turret/medium"
		}
		{
			add_view	"flash_cannon_big"		"flashbarrel1"	"Foresight1"
		}
		{
			add_view	"spheredust_big"	"dust"			"turret"
		}
	}
	{
		on fire "gun" overload
		{
			ani_play "recoil"
		}
		{
			spawn "canon_gaub_fire" "Foresight1" x
		}
		{
			view start "flashbarrel1"
		}
		{
			view start "flashbarrel1s"
		}
		{
			view start "dust"
		}
		{
			delay 1
			{
				view pause "dust"
			}
		}
		{
			delay 2
			{
				view pause "flashbarrel1"
			}
		}
		{
			blastwave c4 0.6 r0 3 r1 5 bone "Foresight1" offset 40 0 0
		}
		{
			call "spawn_shell"
		}
		("cw_check_shooting" weap_id(gun))
	}
	{
		on "cut_parts" overload
		{
			spawn "tank_die" "Basis"
		}
		{
			add_view "smoke_aero_big" "deathfx1" "fx_smoke1"
		}
		{
			add_view "smoke_black" "deathfx2" "fx_smoke2"
		}
		{
			view start "deathfx1"
		}
		{
			view start "deathfx2"
		}
		(define "cut_part"
		{
			tear "piece_big_steel" bone %0
			{
				impulse up 8 1 dir 5 2 cx 5 2 cy 5 2 rnd_dir 10 no_position
			}
			{
				call "check_delete_part"
			}
		}
		)			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "part5")			("cut_part" args "part6")
		{
			delay 10 2
			{
				view stop "deathfx1"
			}
		}
		{
			delay 6 2
			{
				view stop "deathfx2"
			}
		}
	}
	{
		on ik begin "gun_rot"
		{
			play_sound "rotate_gun" 1
		}
	}
	{
		on ik end "gun_rot"
		{
			stop_sound "rotate_gun"
		}
	}
	{
		on contact overload
	}
}
{
	"l16_mortar"
	{
		on "cut_parts"			("cut_part" args "gun")
		{
			bone cut "stan"
		}
	}
}
{
	"mortarfr"
	{
		on "cut_parts"			("cut_part" args "Body1")			("cut_part" args "WheelR")			("cut_part" args "WheelL")			("cut_part" args "gun")
	}
}
{
	"mo_81_llr_f1"
	{
		on "cut_parts"			("cut_part" args "part1")			("cut_part" args "part2")
	}
}
{
	"l118"
	{
		on "cut_parts"			("cut_part" args "standl")			("cut_part" args "standr")			("cut_part" args "turret")			("cut_part" args "wheelr")			("cut_part" args "wheelr")			("cut_part" args "wheell1")			("cut_part" args "gun")
	}
}
{
	"m119"
	{
		on "cut_parts"			("cut_part" args "standl")			("cut_part" args "standr")			("cut_part" args "turret")			("cut_part" args "wheelr")			("cut_part" args "wheelr")			("cut_part" args "wheell1")			("cut_part" args "gun")
	}
}
{
	"cannon flak"
	{
		on spawn overload
		{
			call "init_gun"
		}
		{
			call "add_movement_sound"
		}
	}
}
{
	"flak"		("handle_ik")
	{
		on "init_gun"
		{
			add_view "ofzt_fire" 		"ofzt_fire" 				"foresight1"
		}
		{
			add_view "light_flash_zenit"	"flashbarrel"	"foresight1"
		}
		{
			add_view "flash_zenit"			"flashbarrel00"	"shooter00"
		}
		{
			add_view "flash_zenit"			"flashbarrel01"	"shooter01"
		}
		{
			add_view "flash_zenit"			"flashbarrel02"	"shooter02"
		}
		{
			add_view "flash_zenit"			"flashbarrel03"	"shooter03"
		}
		{
			add_view "smoke_zenit"			"smoke00"		"shooter00"
		}
		{
			add_view "smoke_zenit"			"smoke01"		"shooter01"
		}
		{
			add_view "smoke_zenit"			"smoke02"		"shooter02"
		}
		{
			add_view "smoke_zenit"			"smoke03"		"shooter03"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell1"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell2"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell3"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell4"
		}
		{
			add_view "circledust_norm2"	"dust"			"basis"
		}
		{
			call "update_gun"
		}
	}
	{
		on "add_movement_sound"
		{
			link_sound "rotate_turret" "vehicle/turret/light"
		}
	}
	{
		on fire "gun" overload			(define "fire_barrel"				name "%0"
		{
			call "fire_barrel%0"
		}
		{
			view start "flashbarrel%0"
		}
		{
			delay 0.05
			{
				view stop "ofzt_fire"
			}
		}
		{
			delay 0.42
			{
				view pause "flashbarrel%0"
			}
		}
		{
			ani_play "fire%0"
		}
		{
			delay 0.12
			{
				view start "smoke%0"
			}
			{
				delay 5
				{
					view pause "smoke%0"
				}
			}
		}
		)
		{
			if    ("fire_barrel" args 00)			  else ("fire_barrel" args 01)			  else ("fire_barrel" args 02)			  else ("fire_barrel" args 03)
		}
		{
			if name "00"
			{
				call "fire_gun_common"
			}
		}
	}
	{
		on "fire_gun_common"
		{
			view start "flashbarrel"
		}
		{
			ani_play "recoil"
		}
		{
			kill_delay "shell_off"
		}
		{
			view start "shell"
		}
		{
			view start "dust"
		}
		{
			delay 0.12 "shell_off"
			{
				view pause "shell"
			}
			{
				view pause "dust"
			}
		}
	}
}
{
	"small cannon"
	{
		on spawn overload
		{
			link_sound "rotate_turret" "turret.flak"
		}
		{
			add_view "light_flash_zenit"	"flashbarrel"	"foresight1"
		}
		{
			add_view "flash_zenit"			"flashbarrel1"	"foresight1"
		}
		{
			add_view "smoke_zenit"			"smoke"			"foresight1"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell1"
		}
		{
			call "update_gun"
		}
		{
			add_view	"human_linked_selection" "linked_selection" "visor"
		}
		{
			view hide "linked_selection"
		}
	}
	{
		on fire "gun" overload
		{
			view start "flashbarrel"
		}
		{
			view start "flashbarrel1"
		}
		{
			ani_play "fire"
		}
		{
			ani_play "recoil"
		}
		{
			kill_delay "shell_off"
		}
		{
			view start "shell"
		}
		{
			delay 0.12 "shell_off"
			{
				view pause "shell"
			}
			{
				view start "smoke"
			}
			{
				delay 0.3
				{
					view pause "flashbarrel1"
				}
			}
			{
				delay 5
				{
					view pause "smoke"
				}
			}
		}
	}
}
{
	"lg_40"
	{
		on fire "gun"
		{
			spawn "bazooka_shot" "fxshot" x
		}
	}
}
{
	"zenite"                            		("handle_ik")
	{
		on spawn
		{
			add_view "light_flash_zenit"	"zenite_flash"	"foresight1"
		}
		{
			add_view "flash_zenit"			"zenite_flash"	"foresight1"
		}
		{
			add_view "smoke_zenit"			"zenite_smoke"	"foresight1"
		}
		{
			add_view "zenit_gilz"			"zenite_shell"	"FXshell1"
		}
		{
			add_view "circledust_norm2"	"zenite_dust"	"turret"
		}
	}
	{
		on fire "gun" overload
		{
			view start "zenite_flash"
		}
		{
			ani_play "fire"
		}
		{
			kill_delay "shell_off"
		}
		{
			view start "zenite_shell"
		}
		{
			view start "zenite_dust"
		}
		{
			delay 0.12 "shell_off"
			{
				view pause "zenite_shell"
			}
			{
				view pause "zenite_dust"
			}
			{
				view pause "zenite_dust"
			}
			{
				view start "zenite_smoke"
			}
			{
				delay 0.3
				{
					view pause "zenite_flash"
				}
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
}
{
	"searchlight"
	{
		on blast_hit
		{
			if min_energy 0.4
			{
				call "light_break"
			}
		}
	}
	{
		on "light_break"
		{
			call "lamp_broken"
		}
	}
	{
		on bullet_hit
		{
			if volume "lamp1"
			{
				call "lamp_broken"
			}
		}
	}
	{
		on "lamp_broken"
		{
			tags add "lamp_broken"
		}
	}
	{
		on ground_hit
		{
			call "explosion"
		}
	}
	{
		on "_explosion"
		{
			drop_orders
		}
		{
			call "light_break"
		}
	}
	{
		on operatable on
	}
	{
		on operatable off
	}
}
{
	"cannon zu23-2"
	{
		on "add_movement_sound"  overload
		{
			link_sound "rotate_turret" "vehicle/turret/light_m1"
		}
	}
	("handle_ik")
	{
		on "init_gun"
		{
			add_view "light_flash_zenit"	"flashbarrel"		"foresight1"
		}
		{
			add_view "flash_zenit"			"flashbarrel00"	"shooter00"
		}
		{
			add_view "flash_zenit"			"flashbarrel01"	"shooter01"
		}
		{
			add_view "smoke_zenit"			"smoke00"		"shooter00"
		}
		{
			add_view "smoke_zenit"			"smoke01"		"shooter01"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell"
		}
		{
			add_view "zenit_gilz"			"shell"			"FXshell1"
		}
		{
			add_view "circledust_norm2"	"dust"			"basis"
		}
		{
			call "update_gun"
		}
	}
	{
		on "fire_gun_common"
		{
			view start "flashbarrel"
		}
		{
			ani_play "recoil"
		}
		{
			kill_delay "shell_off"
		}
		{
			view start "shell"
		}
		{
			view start "dust"
		}
		{
			delay 0.12 "shell_off"
			{
				view pause "shell"
			}
			{
				view pause "dust"
			}
		}
	}
}
(define "automatic_grenade_launcher"
{
	on fire "mgun"
}
)
{
	"cannon Ags30_stan"		("automatic_grenade_launcher")
}
{
	"cannon ags17"		("automatic_grenade_launcher")
}
{
	"cannon qlz04"		("automatic_grenade_launcher")
}
{
	"cannon mk19"		("automatic_grenade_launcher")
	{
		on "cut_parts"
		{
			tear "piece_medium_steel" bone "gun_rot"
			{
				impulse up 1 0.5
			}
			{
				call "check_delete_part"
			}
		}
	}
}
{
	"cannon D30"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "cut_parts"			("cut_part" args "wheell1")			("cut_part" args "wheelr")			("cut_part" args "turret")			("cut_part" args "standr")			("cut_part" args "standl")
	}
}
{
	"cannon mt12_rapira"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "proj_probe" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				start_sound "weapon/shot/shell"
			}
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "cut_parts"			("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "turret")			("cut_part" args "standr")			("cut_part" args "standl")
	}
}
{
	"cannon 2a65_msta_b"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "canon_gaub_fire" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "cut_parts"			("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "turret")			("cut_part" args "standr")			("cut_part" args "standl")
	}
}
{
	"cannon pl-66"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "canon_gaub_fire" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "cut_parts"			("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "turret")			("cut_part" args "standr")			("cut_part" args "standl")
	}
}
{
	"fh-70"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "canon_gaub_fire" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "cut_parts"			("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "turret")			("cut_part" args "standr")			("cut_part" args "standl")			("cut_part" args "standl1")
	}
}
{
	"cannon m777"
	{
		on spawn
		{
			add_view 	"smoke_zenit" 	"zenite_smoke" 		"foresight1"
		}
	}
	{
		on fire "gun"
		{
			spawn "tank_canon_fire_small" "smoke_gun1"   x
		}
		{
			spawn "tank_canon_fire_small" "smoke_gun2"   x
		}
		{
			spawn "canon_gaub_fire" "Foresight1" x
		}
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			view start "smoke_add"
		}
		{
			delay 0.16 "shell_off"
			{
				view start "zenite_smoke"
			}
			{
				view pause "smoke_add"
			}
			{
				view pause "flashbarrel_gun"
			}
			{
				delay 5
				{
					view pause "zenite_smoke"
				}
			}
		}
	}
	{
		on "spawn_shell" overload
		{
			start_sound "weapon/shot/shell"
		}
		{
			add_view "smoke_zenit" "smoke_shell" "fx_invers"
		}
		{
			view start "smoke_shell"
		}
		{
			delay 2.5 0.5
			{
				view stop "smoke_shell"
			}
		}
		{
			spawn "shell_cannon_big" "fx_invers" x
			{
				impulse up 1.5 0.5 dir -4.5 0.7 cz 0.2 0.1 com
			}
			{
				add_view "smoke_zenit" "smoke_shell" "fx_shellsmoke"
			}
			{
				view start "smoke_shell"
			}
			{
				delay_effect 3 1 "stop"
			}
			{
				delay 3 0.5
				{
					hide 3
				}
			}
		}
	}
	{
		on "cut_parts"
		{
			bone cut "hydraulics_1"
		}
		{
			bone cut "hydraulics_2"
		}
		{
			bone cut "hydraulics_3"
		}
		{
			bone cut "hydraulics_4"
		}
		{
			bone cut "hydraulics_5"
		}
		{
			bone cut "rail_1"
		}
		("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "turret")			("cut_part" args "part1")			("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "part5")			("cut_part" args "part6")
	}
}
{
	"vasilek"
	{
		on "cut_parts"			("cut_part" args "wheelleft")			("cut_part" args "wheelright")			("cut_part" args "part1")					("cut_part" args "part2")			("cut_part" args "part3")			("cut_part" args "part4")			("cut_part" args "part5")			("cut_part" args "turret")
	}
}
{
	"p-37"
	{
		on "check_rotation"
		{
			if crew_in_place "gunner"
			{
				if crew_in_place "gunner2"
				{
					if work "turret"
					{
						if not tagged "radar_off"
						{
							ani_play "turret" callback
						}
						{
							delay 0.1
							{
								ani_play "visor1" -1
							}
							{
								ani_play "visor2" -1
							}
						}
						{
							with_linked_entity "vehicle9"
							{
								call "start"
							}
						}
						else
						{
							ani_stop "turret"
						}
						{
							delay 0.1
							{
								ani_play "visor1" 1
							}
							{
								ani_play "visor2" 1
							}
						}
						{
							with_linked_entity "vehicle9"
							{
								call "stop"
							}
						}
					}
					else
					{
						ani_stop "turret"
					}
					{
						delay 0.1
						{
							ani_play "visor1" 1
						}
						{
							ani_play "visor2" 1
						}
					}
					{
						with_linked_entity "vehicle9"
						{
							call "stop"
						}
					}
				}
				else
				{
					ani_stop "turret"
				}
				{
					delay 0.1
					{
						ani_play "visor1" 1
					}
					{
						ani_play "visor2" 1
					}
				}
				{
					with_linked_entity "vehicle9"
					{
						call "stop"
					}
				}
			}
			else
			{
				ani_stop "turret"
			}
			{
				delay 0.1
				{
					ani_play "visor1" 1
				}
				{
					ani_play "visor2" 1
				}
			}
			{
				with_linked_entity "vehicle9"
				{
					call "stop"
				}
			}
		}
	}
	{
		on animation_end "turret"
		{
			if linked
			{
				call "check_unlink"
			}
			else
			{
				if not tagged "radar_off"
				{
					ani_play "turret" callback
				}
			}
		}
	}
	{
		on "check_unlink"
		{
			delay 3
			{
				if not linked
				{
					call "check_rotation"
				}
				else
				{
					call "check_unlink"
				}
			}
		}
	}
	{
		on crew in
		{
			kill_delay "check_rotation"
		}
		{
			delay 3 "check_rotation"
			{
				call "check_rotation"
			}
		}
	}
	{
		on crew out
		{
			kill_delay "check_rotation"
		}
		{
			delay 3 "check_rotation"
			{
				call "check_rotation"
			}
		}
	}
	{
		on "cwsh_radar_on"
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
	{
		on "cwsh_radar_off"
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
	{
		on pierce overload
		{
			if volume "radar_bottom"
			{
				components "radar_bottom" break
			}
			else volume "radar_top"
			{
				components "radar_top" break
			}
			else volume "visor1"
			{
				components "visor1" break
			}
			else volume "visor2"
			{
				components "visor2" break
			}
			else volume "turret"
			{
				components "turret" break
			}
		}
	}
	{
		on "check_destroy"
	}
	{
		on break
		{
			if component "visor1"
			{
				if not tagged "visor1_break"
				{
					tags add "visor1_break"
				}
				{
					damage_report "visor1" "component/other/radar_damaged"
				}
				{
					tear "piece_medium_steel" bone "visor1"
					{
						impulse up 2 1 dir 2 1
					}
				}
				else
				{
					call "explosion"
				}
			}
			{
				spawn "glass_hit"
			}
		}
		{
			if component "visor2"
			{
				if not tagged "visor2_break"
				{
					tags add "visor2_break"
				}
				{
					damage_report "visor2" "component/other/radar_damaged"
				}
				{
					tear "piece_medium_steel" bone "visor2"
					{
						impulse up 2 1 dir 2 1
					}
				}
				else
				{
					call "explosion"
				}
			}
			{
				spawn "glass_hit"
			}
		}
		{
			if component "radar_bottom"
			{
				if tagged "radar_break"
				{
					call "explosion"
				}
				else tagged "turret_break"
				{
					call "explosion"
				}
			}
			{
				tags add "radar_break"
			}
			{
				spawn "tank_die_particle" "radar_bottom"
			}
			{
				damage_report "visor1" "component/other/radar_array_damaged"
			}
		}
		{
			if component "radar_top"
			{
				if tagged "radar_break"
				{
					call "explosion"
				}
				else tagged "turret_break"
				{
					call "explosion"
				}
			}
			{
				tags add "radar_break"
			}
			{
				spawn "tank_die_particle" "radar_top"
			}
			{
				damage_report "visor2" "component/other/radar_array_damaged"
			}
		}
		{
			if component "turret"
			{
				if tagged "radar_break"
				{
					call "explosion"
				}
				else tagged "turret_break"
				{
					call "explosion"
				}
			}
			{
				tags add "turret_break"
			}
			{
				call "check_rotation"
			}
			{
				spawn "tank_die_particle" "turret"
			}
		}
	}
	{
		on repair
		{
			if component "radar_bottom"
			{
				tags remove "radar_break"
			}
		}
		{
			if component "radar_top"
			{
				tags remove "radar_break"
			}
		}
		{
			if component "turret"
			{
				tags remove "turret_break"
			}
			{
				call "check_rotation"
			}
		}
	}
}
{
	"radar_stan"
	{
		on break
		{
			if component "visor1"
			{
				tags add "visor1_break"
			}
			{
				damage_report "visor1" "component/other/radar_damaged"
			}
			{
				call "check_rotation"
			}
		}
	}
	{
		on repair
		{
			if component "visor1"
			{
				tags remove "visor1_break"
			}
			{
				call "check_rotation"
			}
		}
	}
	{
		on "check_rotation"
		{
			if crew_in_place "gunner"
			{
				if crew_in_place "commander"
				{
					if work "visor1"
					{
						if not tagged "radar_off"
						{
							delay 0.1
							{
								ani_play "visor1" -1
							}
						}
						{
							with_linked_entity "vehicle9"
							{
								call "start"
							}
						}
						else
						{
							delay 0.1
							{
								ani_play "visor1" 1
							}
						}
						{
							with_linked_entity "vehicle9"
							{
								call "stop"
							}
						}
					}
					else
					{
						delay 0.1
						{
							ani_play "visor1" 1
						}
					}
					{
						with_linked_entity "vehicle9"
						{
							call "stop"
						}
					}
				}
				else
				{
					delay 0.1
					{
						ani_play "visor1" 1
					}
				}
				{
					with_linked_entity "vehicle9"
					{
						call "stop"
					}
				}
			}
			else
			{
				delay 0.1
				{
					ani_play "visor1" 1
				}
			}
			{
				with_linked_entity "vehicle9"
				{
					call "stop"
				}
			}
		}
	}
	{
		on crew in
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
	{
		on crew out
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
	{
		on "cwsh_radar_on"
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
	{
		on "cwsh_radar_off"
		{
			delay 0.1
			{
				call "check_rotation"
			}
		}
	}
}
{
	"tank_add_container"
	{
		on spawn
		{
			physics_work 0
		}
	}
	{
		on blast_hit overload
	}
	{
		on blast overload
	}
	{
		on break_armor overload
	}
	{
		on break_armor_again overload
	}
	{
		on break overload
		{
			if component "nisha"
			{
				burn fx "smoke_dead_tank2" fake
			}
		}
	}
	{
		on pierce
		{
			if component "nisha"
			{
				if explosive_amount 800
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 16 r0 7 r1 14 position
				}
				{
					delay 0.2 0.3
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 14 r0 6 r1 12 position
					}
				}
				{
					delay 0.3 0.4
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 12 r0 5 r1 10 position
					}
				}
				{
					delay 0.4 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 10 r0 5 r1 10 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 400
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 12 r0 7 r1 14 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 10 r0 6 r1 12 position
					}
				}
				{
					delay 0.6 1
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 8 r0 5 r1 10 position
					}
				}
				{
					delay 1 1.2
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 4 r1 8 position
					}
				}
				{
					delay 1.3 1.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 4 r1 8 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 200
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 9 r0 5 r1 10 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 8 r0 5 r1 10 position
					}
				}
				{
					delay 0.6 1
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 8 r0 5 r1 10 position
					}
				}
				{
					delay 1 1.2
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 4 r1 8 position
					}
				}
				{
					delay 1.3 1.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 4 r1 8 position
					}
				}
				{
					delay 1.6 1.7
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 130
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 8 r0 5 r1 10 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 5 r1 10 position
					}
				}
				{
					delay 0.6 1
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 7 r0 5 r1 10 position
					}
				}
				{
					delay 1 1.2
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 1.3 1.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 1.6 1.7
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 100
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 6 r0 4 r1 8 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 0.6 1
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 1 1.2
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 1.3 1.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 70
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 6 r0 4 r1 8 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 6 r0 4 r1 8 position
					}
				}
				{
					delay 0.6 1
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 5 r0 3 r1 6 position
					}
				}
				{
					delay 1 1.2
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 5 r0 3 r1 6 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 30
				{
					spawn "ex_air_big2"
				}
				{
					blastwave c4 4 r0 3 r1 6 position
				}
				{
					delay 0.2 0.5
					{
						spawn "ex_air_big2"
					}
					{
						blastwave c4 4 r0 3 r1 6 position
					}
				}
				{
					clear_inventory
				}
				{
					call "cut_parts"
				}
				else explosive_amount 10
				{
					if rand 0.5
					{
						clear_inventory
					}
					{
						call "cut_parts"
					}
				}
			}
		}
	}
	{
		on "cut_parts"
		{
			components "nisha" break
		}
	}
}
{
	"ur_83p"
	{
		on fire "gun"
		{
			spawn "dust_shot_big_2" "basis"
		}
		{
			spawn "startsmoke_big" "basis"
		}
		{
			spawn "ur83p_charge" "basis" x
		}
	}
	{
		on "cut_parts"			("cut_part" args "gun")
	}
}
{
	"ur83p_charge"
	{
		on spawn
		{
			ani_play "wire_fly" callback
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine1"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine2"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine3"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine4"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine5"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine6"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine7"
		}
		{
			add_view	"rocket_smoke"		"ur_engine"				"engine8"
		}
		{
			view start "ur_engine"
		}
		{
			view show "ur_engine"
		}
		{
			delay 2
			{
				bone cut "engine1"
			}
			{
				bone cut "engine2"
			}
			{
				bone cut "engine3"
			}
			{
				bone cut "engine4"
			}
			{
				bone cut "engine5"
			}
			{
				bone cut "engine6"
			}
			{
				bone cut "engine7"
			}
			{
				bone cut "engine8"
			}
		}
	}
	{
		on animation_end "wire_fly"
		{
			physics_work 0
		}
		{
			delay 0.1
			{
				set_skeleton "_x"
			}
			{
				delay 2
				{
					spawn "ur_83p_detector" "expl1"
				}
				{
					spawn "ur_83p_detector" "expl2"
				}
				{
					spawn "ur_83p_detector" "expl3"
				}
				{
					spawn "ur_83p_detector" "expl4"
				}
				{
					spawn "ur_83p_detector" "expl5"
				}
				{
					spawn "ur_83p_detector" "expl6"
				}
				{
					spawn "ur_83p_detector" "expl7"
				}
				{
					spawn "ur_83p_detector" "expl8"
				}
				{
					spawn "ur_83p_detector" "expl9"
				}
			}
			{
				delay 12
				{
					delete
				}
			}
		}
	}
}
{
	"ur_83p_detector"
	{
		on spawn
		{
			impulse up 0.1 com
		}
		{
			gravity 0.5
		}
		{
			constrain_velocity 4.5
		}
		{
			delay 0.1
			{
				call "loop_detect"
			}
		}
		{
			delay 10
			{
				stuff_detonate
			}
		}
	}
	{
		on "loop_detect"
		{
			impulse up -0.1 com
		}
		{
			if not altitude 1
			{
				constrain_velocity 7.5
			}
			{
				delay 0.2
				{
					call "loop_detect"
				}
			}
			else altitude 0
			{
				physics_work 0
			}
			else
			{
				constrain_velocity 1.5
			}
		}
	}
}
{
	"vant_vm_shield"
	{
		on spawn
		{
			add_view "smg_gilz" "shell" "FXshell"
		}
		{
			add_view "flash_gun_small" "flashbarrel" "foresight3"
		}
		{
			add_view "we_smoke" "smoke_or" "foresight3"
		}
		{
			if operatable
			{
				ani_wind "down" end
			}
			else
			{
				ani_wind "down" begin
			}
		}
	}
	{
		on operatable on
		{
			ani_play "down" 1
		}
	}
	{
		on operatable off
		{
			ani_play "down" -1
		}
	}
	{
		on fire "pistol"
		{
			view show	"flashbarrel"
		}
		{
			view start	"flashbarrel"
		}
		{
			view show	"smoke_or"
		}
		{
			view start	"smoke_or"
		}
		{
			view show	"shell"
		}
		{
			view start	"shell"
		}
		{
			kill_delay "fire"
		}
		{
			kill_delay "shells_we"
		}
		{
			delay 0.2 "shells_we"
			{
				view pause	"shells_we"
			}
			{
				view pause	"shell"
			}
		}
		{
			delay 0.45 "fire"
			{
				view hide	"flashbarrel"
			}
			{
				view pause	"flashbarrel"
			}
			{
				view pause	"smoke_or"
			}
			{
				view hide	"smoke_or"
			}
			{
				view pause	"flashbarrell"
			}
		}
	}
}
{
	"2start"
	{
		on spawn
		{
			tags remove "already_fired"
		}
		{
			tags remove "2start_off"
		}
		{
			call "update_weaponry"
		}
	}
	{
		on fire "gun2"
		{
			if not tagged "already_fired"
			{
				tags add "already_fired"
			}
			{
				if tagged "2start_off"
				{
					weapon_work "gun2" 0
				}
				{
					delay 1
					{
						weapon_work "gun2" 0
					}
				}
				{
					delay 10
					{
						call "update_weaponry"
					}
				}
			}
			{
				delay 3
				{
					tags remove "already_fired"
				}
			}
			else
			{
				tags remove "already_fired"
			}
			{
				weapon_work "gun2" 0
			}
			{
				delay 6
				{
					call "update_weaponry"
				}
			}
		}
	}
	{
		on "single_launch"
		{
			tags remove "already_fired"
		}
		{
			weapon_work "gun2" 0
		}
		{
			delay 6
			{
				call "update_weaponry"
			}
		}
	}
	{
		on "leave_unit" overload
		{
			call "cwsh_switch_hatch"
		}
	}
	{
		on "cwsh_switch_hatch" overload
		{
			if tagged "2start_off"
			{
				components "zpu_indicator" repair
			}
			{
				tags remove "2start_off"
			}
			{
				damage_report "body" "component/salvo_launch"
			}
			else
			{
				tags add "2start_off"
			}
			{
				components "zpu_indicator" break
			}
			{
				damage_report "body" "component/single_launch"
			}
			{
				if tagged "already_fired"
				{
					tags remove "already_fired"
				}
				{
					weapon_work "gun2" 0
				}
				{
					delay 1
					{
						weapon_work "gun2" 0
					}
				}
				{
					delay 6
					{
						call "update_weaponry"
					}
				}
			}
		}
	}
}