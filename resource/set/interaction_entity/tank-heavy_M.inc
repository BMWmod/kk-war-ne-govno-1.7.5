(define "secondary_damage"
{
	if hit_side front
	{
		if  stuff "autocannon_small"
		{
			blastwave c4 0.5 r0 1.0 r1 1.1 position
		}
		{
			spawn "metal_pierce_small"
		}
		else stuff "rok"
		{
			blastwave c4 3 r0 1.0 r1 1.6 position
		}
		{
			blastwave c4 0.5 r0 1.6 r1 1.7 position
		}
		{
			spawn "metal_pierce"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "ptrk"
		{
			blastwave c4 3 r0 1.0 r1 1.9 position
		}
		{
			blastwave c4 0.5 r0 2.0 r1 2.1 position
		}
		{
			spawn "metal_pierce"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "cm"
		{
			blastwave c4 3 r0 1.0 r1 1.9 position
		}
		{
			blastwave c4 0.5 r0 1.8 r1 2.0 position
		}
		{
			spawn "metal_pierce_small"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "fg"
		{
			blastwave c4 5 r0 1.8 r1 3.9 position
		}
		{
			blastwave c4 2.5 r0 2.0 r1 4.1 position
		}
		else stuff "ap"
		{
			blastwave c4 3 r0 1.2 r1 1.2 position
		}
		{
			blastwave c4 0.5 r0 1.3 r1 1.4 position
		}
		{
			spawn "metal_pierce_small"
		}
		else stuff "hesh"
		{
			bullet_detonate
		}
		{
			blastwave c4 6.5 r0 1.2 r1 1.2 position
		}
		{
			spawn "metal_pierce_small"
		}
		else stuff "apcr"
		{
			blastwave c4 3 r0 1.1 r1 1.2 position
		}
		{
			blastwave c4 0.5 r0 1.3 r1 1.3 position
		}
		{
			spawn "metal_pierce"
		}
		else stuff "apcr_h"
		{
			blastwave c4 3 r0 1.1 r1 1.2 position
		}
		{
			blastwave c4 0.5 r0 1.3 r1 1.3 position
		}
		{
			spawn "metal_pierce"
		}
		else  stuff "bullet"
		{
			blastwave c4 3 r0 1.0 r1 1.0 position
		}
		{
			blastwave c4 0.5 r0 1.2 r1 1.2 position
		}
		else
		{
			if "efp_core"
			{
				blastwave c4 3 r0 1.2 r1 1.2 position
			}
			{
				blastwave c4 0.5 r0 1.3 r1 1.4 position
			}
			{
				spawn "metal_pierce_small"
			}
			("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))
			{
				set "efp_core" 0
			}
			else
			{
				blastwave c4 3 r0 1.7 r1 1.9 position
			}
			{
				blastwave c4 0.5 r0 1.8 r1 2.0 position
			}
			{
				spawn "metal_pierce_small"
			}
			("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))
		}
	}
	else
	{
		if  stuff "autocannon_small"
		{
			blastwave c4 0.5 r0 1.0 r1 1.1 position
		}
		{
			spawn "metal_pierce_small"
		}
		else stuff "rok"
		{
			blastwave c4 3 r0 0.5 r1 1.1 position
		}
		{
			blastwave c4 0.5 r0 1.1 r1 1.2 position
		}
		{
			spawn "metal_pierce"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "ptrk"
		{
			blastwave c4 3 r0 0.5 r1 1.4 position
		}
		{
			blastwave c4 0.5 r0 1.5 r1 1.6 position
		}
		{
			spawn "metal_pierce"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "cm"
		{
			blastwave c4 3 r0 0.5 r1 1.4 position
		}
		{
			blastwave c4 0.5 r0 1.3 r1 1.5 position
		}
		{
			spawn "metal_pierce_small"
		}
		("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))			else stuff "fg"
		{
			blastwave c4 5 r0 1.8 r1 3.9 position
		}
		{
			blastwave c4 2.5 r0 2.0 r1 4.1 position
		}
		else stuff "ap"
		{
			blastwave c4 3 r0 0.7 r1 0.7 position
		}
		{
			blastwave c4 0.5 r0 0.8 r1 0.9 position
		}
		else stuff "hesh"
		{
			bullet_detonate
		}
		{
			blastwave c4 11 r0 1.2 r1 1.2 position
		}
		{
			blastwave c4 6.5 r0 3.3 r1 4.4 position
		}
		{
			spawn "metal_pierce_small"
		}
		else stuff "apcr"
		{
			blastwave c4 3 r0 0.6 r1 0.7 position
		}
		{
			blastwave c4 0.5 r0 0.8 r1 0.8 position
		}
		{
			spawn "metal_pierce"
		}
		else stuff "apcr_h"
		{
			blastwave c4 3 r0 0.6 r1 0.7 position
		}
		{
			blastwave c4 0.5 r0 0.8 r1 0.8 position
		}
		{
			spawn "metal_pierce"
		}
		else stuff  "hmgun"
		{
			blastwave c4 0.5 r0 0.1 r1 0.2 position
		}
		{
			spawn "metal_pierce_small"
		}
		else  stuff "bullet"
		{
			blastwave c4 3 r0 0.5 r1 0.5 position
		}
		{
			blastwave c4 0.5 r0 0.7 r1 0.7 position
		}
		else
		{
			if "efp_core"
			{
				blastwave c4 3 r0 0.7 r1 0.7 position
			}
			{
				blastwave c4 0.5 r0 0.8 r1 0.9 position
			}
			{
				spawn "metal_pierce_small"
			}
			("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))
			{
				set "efp_core" 0
			}
			else
			{
				blastwave c4 3 r0 0.5 r1 1.4 position
			}
			{
				blastwave c4 0.5 r0 1.3 r1 1.5 position
			}
			{
				spawn "metal_pierce_small"
			}
			("pierce_damage_contusion" blast_rand_contusion(1)	blast_crew_shock_time(6))
		}
	}
}
{
	if stuff "ic hmgun"
	{
		fire radius 0.5 time 0.3 heating 30
	}
	else stuff "ic autocannon_small"
	{
		fire radius 0.5 time 0.3 heating 60
	}
}
)
{
	on pierce
	{
		if not stuff "proj_pointer"
		{
			if component "driver_panel"
			{
				components "driver_panel" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "transmission"
			{
				components "transmission" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "driver_place"
			{
				if crew_in_place "driver"
				{
					damage_report "body" "component/armored/driver_dead"
				}
			}
			{
				kill_crew "driver"
			}
			{
				crew_enable place "driver" 0
			}
			{
				delay 10
				{
					crew_enable place "driver" 1
				}
			}
			else component "driver1_place"
			{
				if crew_in_place "driver1"
				{
					damage_report "body" "component/armored/driver_dead"
				}
			}
			{
				kill_crew "driver1"
			}
			{
				crew_enable place "driver1" 0
			}
			{
				delay 10
				{
					crew_enable place "driver1" 1
				}
			}
			else component "gunner_place"
			{
				if crew_in_place "gunner"
				{
					damage_report "body" "component/armored/gunner_dead"
				}
			}
			{
				kill_crew "gunner"
			}
			{
				crew_enable place "gunner" 0
			}
			{
				delay 10
				{
					crew_enable place "gunner" 1
				}
			}
			else component "gunner1_place"
			{
				if crew_in_place "gunner1"
				{
					damage_report "body" "component/armored/shooter_dead"
				}
			}
			{
				kill_crew "gunner1"
			}
			{
				crew_enable place "gunner1" 0
			}
			{
				delay 10
				{
					crew_enable place "gunner1" 1
				}
			}
			else component "gunner2_place"
			{
				if crew_in_place "gunner2"
				{
					damage_report "body" "component/armored/shooter_dead"
				}
			}
			{
				kill_crew "gunner2"
			}
			{
				crew_enable place "gunner2" 0
			}
			{
				delay 10
				{
					crew_enable place "gunner2" 1
				}
			}
			else component "charger_place"
			{
				if crew_in_place "charger"
				{
					damage_report "body" "component/armored/charger_dead"
				}
			}
			{
				kill_crew "charger"
			}
			{
				crew_enable place "charger" 0
			}
			{
				delay 10
				{
					crew_enable place "charger" 1
				}
			}
			else component "commander_place"
			{
				if crew_in_place "commander"
				{
					damage_report "body" "component/armored/commander_dead"
				}
			}
			{
				kill_crew "commander"
			}
			{
				crew_enable place "commander" 0
			}
			{
				delay 10
				{
					crew_enable place "commander" 1
				}
			}
			else component "commander1_place"
			{
				if crew_in_place "commander1"
				{
					damage_report "body" "component/armored/commander_dead"
				}
			}
			{
				kill_crew "commander1"
			}
			{
				crew_enable place "commander1" 0
			}
			{
				delay 10
				{
					crew_enable place "commander1" 1
				}
			}
			else component "seat1_place"
			{
				kill_crew "seat1"
			}
			else component "seat2_place"
			{
				kill_crew "seat2"
			}
			else component "seat3_place"
			{
				kill_crew "seat3"
			}
			else component "seat4_place"
			{
				kill_crew "seat4"
			}
			else component "seat5_place"
			{
				kill_crew "seat5"
			}
			else component "seat6_place"
			{
				kill_crew "seat6"
			}
			else component "seat7_place"
			{
				kill_crew "seat7"
			}
			else component "seat8_place"
			{
				kill_crew "seat8"
			}
			else component "seat9_place"
			{
				kill_crew "seat9"
			}
			else component "seat10_place"
			{
				kill_crew "seat10"
			}
			else component "seat11_place"
			{
				kill_crew "seat11"
			}
			else component "seat12_place"
			{
				kill_crew "seat12"
			}
			else component "seat13_place"
			{
				kill_crew "seat13"
			}
			else component "seat14_place"
			{
				kill_crew "seat14"
			}
			else component "seat15_place"
			{
				kill_crew "seat15"
			}
			else component "seat16_place"
			{
				kill_crew "seat16"
			}
			else component "seat17_place"
			{
				kill_crew "seat17"
			}
			else component "seat18_place"
			{
				kill_crew "seat18"
			}
			else component "seat19_place"
			{
				kill_crew "seat19"
			}
			else component "seat20_place"
			{
				kill_crew "seat20"
			}
			else component "seat21_place"
			{
				kill_crew "seat21"
			}
			else component "seat22_place"
			{
				kill_crew "seat22"
			}
			else component "seat23_place"
			{
				kill_crew "seat23"
			}
			else component "seat24_place"
			{
				kill_crew "seat24"
			}
			else component "seat25_place"
			{
				kill_crew "seat25"
			}
			else component "driver_triplex"
			{
				components "driver_triplex" break
			}
			{
				spawn "glass_hit"
			}
			else component "commander_triplex"
			{
				components "commander_triplex" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex"
			{
				components "additional_triplex" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex1"
			{
				components "additional_triplex1" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex2"
			{
				components "additional_triplex2" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex3"
			{
				components "additional_triplex3" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex4"
			{
				components "additional_triplex4" break
			}
			{
				spawn "glass_hit"
			}
			else component "additional_triplex5"
			{
				components "additional_triplex5" break
			}
			{
				spawn "glass_hit"
			}
			else component "ammo_storage_main"
			{
				damage_report "ammo_storage_main" "component/armored/ammo_storage_damaged"
			}
			{
				spawn "metal_hit_bul"
			}
			{
				if  explosive_amount 130
				{
					if rand 0.95
					{
						components "ammo_storage_main" break
					}
				}
				else  explosive_amount 100
				{
					if rand 0.8
					{
						components "ammo_storage_main" break
					}
				}
				else  explosive_amount 50
				{
					if rand 0.65
					{
						components "ammo_storage_main" break
					}
				}
				else  explosive_amount 30
				{
					if rand 0.50
					{
						components "ammo_storage_main" break
					}
				}
			}
			else component "ammo_storage_autocannon"
			{
				damage_report "ammo_storage_autocannon" "component/armored/ammo_storage_damaged"
			}
			{
				spawn "metal_hit_bul"
			}
			{
				if rand 0.55
				{
					components "ammo_storage_autocannon" break
				}
			}
			else component "ammo_storage_mgun"
			{
				damage_report "ammo_storage_mgun" "component/armored/ammo_storage_damaged"
			}
			{
				spawn "metal_hit_bul"
			}
			{
				if rand 0.45
				{
					components "ammo_storage_mgun" break
				}
			}
			else component "autoloader"
			{
				components "autoloader" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "fuel_tank_internal_a"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_a" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_a" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_internal_a" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_internal_a" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_a" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_a" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_internal_a" break
					}
				}
			}
			else component "fuel_tank_internal_b"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_b" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_b" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_internal_b" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_internal_b" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_b" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_b" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_internal_b" break
					}
				}
			}
			else component "fuel_tank_internal_c"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_c" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_c" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_internal_c" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_internal_c" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_c" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_c" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_internal_c" break
					}
				}
			}
			else component "fuel_tank_internal_d"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_d" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_internal_d" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_internal_d" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_internal_d" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_d" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_internal_d" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_internal_d" break
					}
				}
			}
			else component "fuel_tank_external_a"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_external_a" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_external_a" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_external_a" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_external_a" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_external_a" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_external_a" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_external_a" break
					}
				}
			}
			else component "fuel_tank_external_b"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_external_b" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_external_b" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_external_b" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_external_b" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_external_b" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_external_b" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_external_b" break
					}
				}
			}
			else component "fuel_tank_external_c"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_external_c" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_external_c" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_external_c" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_external_c" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_external_c" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_external_c" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_external_c" break
					}
				}
			}
			else component "fuel_tank_external_d"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				if stuff "cm"
				{
					if rand 0.85
					{
						components "fuel_tank_external_d" break
					}
				}
				else stuff "rok"
				{
					if rand 0.85
					{
						components "fuel_tank_external_d" break
					}
				}
				else stuff "fg"
				{
					if rand 0.8
					{
						components "fuel_tank_external_d" break
					}
				}
				else stuff "ap"
				{
					if rand 0.25
					{
						components "fuel_tank_external_d" break
					}
				}
				else stuff "apcr"
				{
					if rand 0.2
					{
						components "fuel_tank_external_d" break
					}
				}
				else stuff "apcr_h"
				{
					if rand 0.2
					{
						components "fuel_tank_external_d" break
					}
				}
				else
				{
					if rand 0.5
					{
						components "fuel_tank_external_d" break
					}
				}
			}
			else component "gun2"
			{
				components "gun2" break
			}
			else component "gun3"
			{
				components "gun3" break
			}
			else component "mgun"
			{
				components "mgun" break
			}
			else component "mgun1"
			{
				components "mgun1" break
			}
			else component "mgun2"
			{
				components "mgun2" break
			}
			else component "mgun3"
			{
				components "mgun3" break
			}
			else component "mgun4"
			{
				components "mgun4" break
			}
			else component "mgun5"
			{
				components "mgun5" break
			}
			else component "mgun6"
			{
				components "mgun6" break
			}
			else component "mgun20"
			{
				components "mgun20" break
			}
			else component "mgun21"
			{
				components "mgun21" break
			}
			else component "turret_ring"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				components "turret_ring" break
			}
			else  component "panel_engine_connectors"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				components "panel_engine_connectors" break
			}
			else  component "turret_move_engine"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				components "turret_move_engine" break
			}
			else component "front_wheels"
			{
				burn fx "smoke_dead_tank2" fake
			}
			{
				components "front_wheels" break
			}
			else component "stabilizer"
			{
				components "stabilizer" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "gunner_panel"
			{
				components "gunner_panel" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "PPU"
			{
				components "PPU" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "APU"
			{
				components "APU" break
			}
			{
				burn fx "smoke_dead_tank2" fake
			}
			else component "body"
			{
				if not tagged "destroyed"
				{
					damage_report "body" "component/armored/body_pierced"
				}
			}
			("secondary_damage")		 else component "turret"
			{
				if not tagged "destroyed"
				{
					damage_report "turret" "component/armored/turret_pierced"
				}
			}
			("secondary_damage")		else  component "trackleft"
			{
				if stuff "cm" 				("track_hit" max_rand(0.8) min_rand(0.4))			else stuff "rok"				("track_hit" max_rand(0.9) min_rand(0.5))			else stuff "fg"				("track_hit" max_rand(0.9) min_rand(0.9))			else stuff "ap"				("track_hit" max_rand(0.8) min_rand(0.3))			else stuff "apcr"				("track_hit" max_rand(0.6) min_rand(0.2))			else stuff "apcr_h"				("track_hit" max_rand(0.6) min_rand(0.2))			else 				("track_hit" max_rand(0.8) min_rand(0.4))
			}
			else component "trackright"
			{
				if stuff "cm" 				("track_hit" max_rand(0.8) min_rand(0.4))			else stuff "rok"				("track_hit" max_rand(0.9) min_rand(0.5))			else stuff "fg"				("track_hit" max_rand(0.9) min_rand(0.9))			else stuff "ap"				("track_hit" max_rand(0.8) min_rand(0.3))			else stuff "apcr"				("track_hit" max_rand(0.6) min_rand(0.2))			else stuff "apcr_h"				("track_hit" max_rand(0.6) min_rand(0.2))			else 				("track_hit" max_rand(0.8) min_rand(0.4))
			}
			else component "d_a" 			("DPS_Effect" dps_apcr(0) dps_cm(1) dps_ap(0))
		}
	}
}
{
	on bullet_hit
	{
		if  stuff "rus_IR_ff_beam ammo"
		{
			tags add "rus_target_IR_ff"
		}
		{
			delay 10
			{
				tags remove "rus_target_IR_ff"
			}
		}
		else stuff "usa_IR_ff_beam ammo"
		{
			tags add "usa_target_IR_ff"
		}
		{
			delay 10
			{
				tags remove "usa_target_IR_ff"
			}
		}
	}
	{
		if component "d_a"
		{
			if not stuff "proj_pointer"
			{
				if stuff "cm" 				("DPS_Effect" dps_apcr(0) dps_cm(1) dps_ap(0))			else stuff "radar_ammo"			else stuff "laser_ammo"			else stuff "IR_ff_ammo"			else stuff "rok"				("DPS_Effect" dps_apcr(0) dps_cm(1) dps_ap(0))			else stuff "fg"				("DPS_Effect" dps_apcr(0) dps_cm(0.2) dps_ap(0))			else stuff "ap"				("DPS_Effect" dps_apcr(0) dps_cm(0) dps_ap(1))			else stuff "apcr"				("DPS_Effect" dps_apcr(0) dps_cm(0) dps_ap(1))			else stuff "apcr_h"				("DPS_Effect" dps_apcr(0) dps_cm(0) dps_ap(1))			else stuff "big fg"				("DPS_Effect" dps_apcr(0) dps_cm(1) dps_ap(0))			else 				("DPS_Effect" dps_apcr(0) dps_cm(0) dps_ap(1))
			}
		}
	}
	("blast")
	{
		if stuff "size2"	                                                                                     	    else stuff "size3"	                                                                                     	    else stuff "size4"
	}
	("damage_process_bullet_hit"	       staff(150to152fg)		        hit_body__explosive(0)	        hit_body__engine_burn(0.2)	        hit_body__body_destroy(0)	        hit_body__body_brake(0)	                                   	        hit_engine__engine_brake(0)	                                   	        hit_turret__explosive(0)	        hit_turret_front__gun_brake(0)	        hit_turret__turret_destroy(0)	        hit_turret__turret_brake(0.8)	        imp(0)	    )
}
{
	on ik begin "turret"
	{
		if tagged "no_power"
		{
			if tagged "cw_turr_speed_reduced"
			{
				ik_enable "turret" 0
			}
			else
			{
				delay 0.3
				{
					ik_enable "turret" 0
				}
				{
					tags remove "cw_turr_speed_reduced"
				}
			}
		}
		{
			tags add "cw_turr_speed_reduced"
		}
	}
}
{
	on ik end "turret"
	{
		delay 0.5 "turret_no_power"
		{
			call "update_turret"
		}
	}
}
{
	on blast                             	    ("blast_damage_contusion"		blast_rand_contusion(1)		blast_energy(18)		blast_crew_shock_time(15)	    )	    ("blast_damage_contusion"		blast_rand_contusion(0.7)		blast_energy(13)		blast_crew_shock_time(12)	    )	    ("blast_damage_contusion"		blast_rand_contusion(0.4)		blast_energy(10)		blast_crew_shock_time(6)	    )	    ("blast_damage_contusion"		blast_rand_contusion(0.3)		blast_energy(9)		blast_crew_shock_time(5)	    )	    ("blast_damage_contusion"		blast_rand_contusion(0.2)		blast_energy(8)		blast_crew_shock_time(4)	    )	    ("blast_damage_contusion"		blast_rand_contusion(0.15)		blast_energy(7)		blast_crew_shock_time(3)	    )
	{
		if stuff "antitrack"
		{
			if volume "track"
			{
				if min_energy 3
				{
					component break
				}
			}
		}
	}
}