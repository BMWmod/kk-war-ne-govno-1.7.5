	{commonmissile
		{"trophy"}
		{"smoke_atgm" {ground}}
		{"smoke_kzvp"}
		{"ir_soep_ammo"}
	}
	{laser_using_missile
	    {"smoke_atgm" {ground}}
		{"smoke_shtora"}
		{"trophy"}
		{"smoke_kzvp"}
	}
	{antiship_missile	;antiship and cruise
	    {"usa_radpassive cwps2"  {volume "targ_for_missile"}}
		{"rus_radpassive cwps2"  {volume "targ_for_missile"}}
		
		{"usa_radpassive_aj cwps2"  {volume "targ_for_missile"}}
		{"rus_radpassive_aj cwps2"  {volume "targ_for_missile"}}
		
		{"anti_smallmissile_gs" {volume "targ_for_missile"}}	
		{"radiowave" {volume "body"}}
		{"anti_smallmissile" {volume "body"}}	
		{"antimissile" {volume "targ_for_missile"}}	
	
		;{"trophy"}	;ПКР обычно плохо пробиваются в лоб
		{"smoke_kzvp"}
		;{"zenite" {volume "target_front"}}
		;{"zenite_ap" {volume "target_front"}}
		;{"autocannon_small ap" {volume "target_front"}}
		;{"autocannon_small fragmentary" {volume "target_front"}}
		;{"autocannon_small" {volume "target_front"}}
		{"shell_antimissile" {volume "target_front"}}
		;пуск ракеты по самому первому волуму, а вот наведение уже на более близкий.
		
		

	}
	{antirad_missile	;antiradiation
		{"rad_aa_passive" {volume "targ_for_missile"}}
	    {"rad_aa" {volume "targ_for_missile"}}
		{"rus_radpassive cwps2"  {volume "target_front"}}
		{"rus_radpassive_aj cwps2"  {volume "target_front"}}
		{"rus_radpassive_missile_aj" {volume "target_front"}}
		{"rus_active cwps2"  {volume "target_front"}}
		{"rus_active_aj cwps2"  {volume "target_front"}}
		{"rus_active_asm_aj cwps2"  {volume "target_front"}}
		{"usa_active cwps2"  {volume "target_front"}}
		{"usa_active_aj cwps2"  {volume "target_front"}}
		{"usa_active_asm_aj cwps2"  {volume "target_front"}}
		{"usa_radpassive cwps2"  {volume "target_front"}}
		{"usa_radpassive_aj cwps2"  {volume "target_front"}}
		{"usa_radpassive_missile_aj" {volume "target_front"}}
	}
	{small_targ_missile	;air-to-ground and ATGM
	    {"anti_smallmissile" {volume "target_front"}}	
		{"anti_smallmissile_gs" {volume "target_front"}}	
	   
		{"trophy"}
		{"smoke_kzvp"}
		{"smoke_atgm"}
		;{"zenite" {volume "target_front"}}
		;{"zenite_ap" {volume "target_front"}}
		;{"autocannon_small ap" {volume "target_front"}}
		;{"autocannon_small fragmentary" {volume "target_front"}}
		;{"autocannon_small" {volume "target_front"}}
		{"shell_antimissile" {volume "target_front"}}
		;пуск ракеты по самому первому волуму, а вот наведение уже на более близкий.
		

	}	
	{proj_rus_active
		{"rus_active cwps2"  }
		{"rus_active_aj cwps2"  }
		{"rus_active_asm_aj cwps2"  }
	}
	{proj_rus_ir
		{"rus_ir cwps2"  }
		{"rus_ir_aj cwps2"  }
		{"rus_ir_asm_aj cwps2"}
	}
	{proj_rus_antirad
		{"missile_antirad_usa"}
		{"usa_antirad cwps2" {volume "body"}}
		
		{"missile_antirad_usa_aj"}
		{"usa_antirad_aj cwps2" {volume "body"}}
	}
	{proj_rus_laser
		{"rus_laser cwps2"  }
		{"rus_laser_aj cwps2"  }
		{"rus_laser_asm_aj cwps2"  }
	}
	{proj_rus_laser_guide
		{"rus_laser_spot cwps2"  }
		{"rus_laser_spot_aj cwps2"  }
	}
	{proj_rus_laser_uas
		{"rus_laser_spot cwps2"  }
		{"rus_laser_spot_aj cwps2"  }
	}
	{proj_rus_other
		{"rus_other cwps2"  }
		{"rus_other_aj cwps2"  }
		{"rus_other_asm_aj cwps2"  }
	}
	{proj_rus_antiship
		{"rus_antiship cwps2"  }
		{"rus_antiship_aj cwps2"  }
	}
	{proj_rus_radpassive
		{"rus_radpassive cwps2"  }
		{"rus_radpassive_missile"}
		
		{"rus_radpassive_aj cwps2"  }
		{"rus_radpassive_missile_aj"}
	}
	{proj_usa_active
		{"usa_active cwps2"  }
		{"usa_active_aj cwps2"  }
		{"usa_active_asm_aj cwps2"  }
	}
	{proj_usa_ir
		{"usa_ir cwps2"  }
		{"usa_ir_aj cwps2"  }
		{"usa_ir_asm_aj cwps2"}
	}
	{proj_usa_antirad
		{"missile_antirad_rus"}
		{"rus_antirad cwps2" {volume "body"}}
		
		{"missile_antirad_rus_aj"}
		{"rus_antirad_aj cwps2" {volume "body"}}
	}
	{proj_usa_laser
		{"usa_laser cwps2"  }
		{"usa_laser_aj cwps2"  }
		{"usa_laser_asm_aj cwps2"  }
	}
	{proj_usa_laser_guide
		{"usa_laser_spot cwps2"  }
		{"usa_laser_spot_aj cwps2"  }
	}
	{proj_usa_laser_uas
		{"usa_laser_spot cwps2"  }
		{"usa_laser_spot_aj cwps2"  }
	}
	{proj_usa_other
		{"usa_other cwps2"  }
		{"usa_other_aj cwps2"  }
		{"usa_other_asm_aj cwps2"  }
	}
	{proj_usa_antiship
		{"usa_antiship cwps2"  }
		{"usa_antiship_aj cwps2"  }
	}
	{proj_usa_radpassive
		{"usa_radpassive cwps2"  }
		{"usa_radpassive_missile"}
		
		{"usa_radpassive_aj cwps2"  }
		{"usa_radpassive_missile_aj"}
	}
	{proj_ballistic_missile
	    {"anti_ballistic_missile_usa" {volume "targ_for_missile"}}
		{"anti_ballistic_missile_rus" {volume "targ_for_missile"}}
		
	    {"usa_active cwps2"  }
		{"usa_active_aj cwps2"  }
		{"usa_active_asm_aj cwps2"  }
	
		{"usa_radpassive cwps2"  }
		{"usa_radpassive_missile"}
		
		{"usa_radpassive_aj cwps2"  }
		{"usa_radpassive_missile_aj"}
		
		{"rus_radpassive cwps2"  }
		{"rus_radpassive_missile"}
		
		{"rus_radpassive_aj cwps2"  }
		{"rus_radpassive_missile_aj"}
		
		{"rus_active cwps2"  }
		{"rus_active_aj cwps2"  }
		{"rus_active_asm_aj cwps2"  }
		
	}
	{proj_ballistic_missile_rus
	    {"anti_ballistic_missile_usa" {volume "targ_for_missile"}}
	    {"usa_active cwps2"  }
		{"usa_active_aj cwps2"  }
		{"usa_active_asm_aj cwps2"  }
		{"usa_radpassive cwps2"  }
		{"usa_radpassive_missile"}
		{"usa_radpassive_aj cwps2"  }
		{"usa_radpassive_missile_aj"}
		
	}
	{proj_ballistic_missile_usa
		{"anti_ballistic_missile_rus" {volume "targ_for_missile"}}
		{"rus_radpassive cwps2"  }
		{"rus_radpassive_missile"}
		{"rus_radpassive_aj cwps2"  }
		{"rus_radpassive_missile_aj"}
		{"rus_active cwps2"  }
		{"rus_active_aj cwps2"  }
		{"rus_active_asm_aj cwps2"  }
		
	}

	
	{proj_cwps3

		{"rus_active cwps2" {volume "target_rus_active"}}
		{"rus_ir cwps2" {volume "target_rus_ir"}}
		{"rus_laser cwps2" {volume "target_rus_laser"}}
		{"rus_laser_spot cwps2" {volume "target_rus_laser_spot"}}
		{"rus_other cwps2" {volume "target_rus_other"}}
		{"rus_antiship cwps2" {volume "target_rus_antiship"}}
		{"rus_radpassive cwps2" {volume "target_rus_radpassive"}}
		{"rus_radpassive_missile" {volume "target_rus_radpassive"}}
		{"usa_active cwps2" {volume "target_usa_active"}}
		{"usa_ir cwps2" {volume "target_usa_ir"}}
		{"usa_laser cwps2" {volume "target_usa_laser"}}
		{"usa_laser_spot cwps2" {volume "target_usa_laser_spot"}}
		{"usa_other cwps2" {volume "target_usa_other"}}
		{"usa_antiship cwps2" {volume "target_usa_antiship"}}
		{"usa_radpassive cwps2" {volume "target_usa_radpassive"}}
		{"usa_radpassive_missile" {volume "target_usa_radpassive"}}
		
		
		{"rus_active cwps2" {volume "rus_active"}}
		{"rus_ir cwps2" {volume "rus_ir"}}
		{"rus_laser cwps2" {volume "rus_laser"}}
		{"rus_other cwps2" {volume "rus_other"}}
		{"rus_antiship cwps2" {volume "rus_antiship"}}
		{"rus_radpassive cwps2" {volume "rus_radpassive"}}
		{"rus_radpassive_missile" {volume "rus_radpassive"}}
		{"usa_active cwps2" {volume "usa_active"}}
		{"usa_ir cwps2" {volume "usa_ir"}}
		{"usa_laser cwps2" {volume "usa_laser"}}
		{"usa_other cwps2" {volume "usa_other"}}
		{"usa_antiship cwps2" {volume "usa_antiship"}}
		{"usa_radpassive cwps2" {volume "usa_radpassive"}}
		{"usa_radpassive_missile" {volume "usa_radpassive"}}
		
; AJ	======================================================	
		{"rus_active_aj cwps2" {volume "target_rus_active"}}
		{"rus_active_asm_aj cwps2" {volume "target_rus_active"}}
		{"rus_ir_aj cwps2" {volume "target_rus_ir"}}
		{"rus_ir_asm_aj cwps2" {volume "target_rus_ir"}}
		{"rus_laser_aj cwps2" {volume "target_rus_laser"}}
		{"rus_laser_spot_aj cwps2" {volume "target_rus_laser_spot"}}
		{"rus_laser_asm_aj cwps2" {volume "target_rus_laser"}}
		{"rus_other_aj cwps2" {volume "target_rus_other"}}
		{"rus_other_asm_aj cwps2" {volume "target_rus_other"}}
		{"rus_antiship_aj cwps2" {volume "target_rus_antiship"}}
		{"rus_radpassive_aj cwps2" {volume "target_rus_radpassive"}}
		{"rus_radpassive_missile_aj" {volume "target_rus_radpassive"}}
		{"usa_active_aj cwps2" {volume "target_usa_active"}}
		{"usa_active_asm_aj cwps2" {volume "target_usa_active"}}
		{"usa_ir_aj cwps2" {volume "target_usa_ir"}}
		{"usa_ir_asm_aj cwps2" {volume "target_usa_ir"}}
		{"usa_laser_aj cwps2" {volume "target_usa_laser"}}
		{"usa_laser_spot_aj cwps2" {volume "target_usa_laser_spot"}}
		{"usa_laser_asm_aj cwps2" {volume "target_usa_laser"}}
		{"usa_other_aj cwps2" {volume "target_usa_other"}}
		{"usa_other_asm_aj cwps2" {volume "target_usa_other"}}
		{"usa_antiship_aj cwps2" {volume "target_usa_antiship"}}
		{"usa_radpassive_aj cwps2" {volume "target_usa_radpassive"}}
		{"usa_radpassive_missile_aj" {volume "target_usa_radpassive"}}
		
		
		{"rus_active_aj cwps2" {volume "rus_active"}}
		{"rus_active_asm_aj cwps2" {volume "rus_active"}}
		{"rus_ir_aj cwps2" {volume "rus_ir"}}
		{"rus_ir_asm_aj cwps2" {volume "rus_ir"}}
		{"rus_laser_aj cwps2" {volume "rus_laser"}}
		{"rus_laser_asm_aj cwps2" {volume "rus_laser"}}
		{"rus_other_aj cwps2" {volume "rus_other"}}
		{"rus_other_asm_aj cwps2" {volume "rus_other"}}
		{"rus_antiship_aj cwps2" {volume "rus_antiship"}}
		{"rus_radpassive_aj cwps2" {volume "rus_radpassive"}}
		{"rus_radpassive_missile_aj" {volume "rus_radpassive"}}
		{"usa_active_aj cwps2" {volume "usa_active"}}
		{"usa_active_asm_aj cwps2" {volume "usa_active"}}
		{"usa_ir_aj cwps2" {volume "usa_ir"}}
		{"usa_ir_asm_aj cwps2" {volume "usa_ir"}}
		{"usa_laser_aj cwps2" {volume "usa_laser"}}
		{"usa_laser_asm_aj cwps2" {volume "usa_laser"}}
		{"usa_other_aj cwps2" {volume "usa_other"}}
		{"usa_other_asm_aj cwps2" {volume "usa_other"}}
		{"usa_antiship_aj cwps2" {volume "usa_antiship"}}
		{"usa_radpassive_aj cwps2" {volume "usa_radpassive"}}
		{"usa_radpassive_missile_aj" {volume "usa_radpassive"}}
	}
	{decoy_chaff
		{"usa_active cwps2" {volume "body"}}
		{"rus_active cwps2" {volume "body"}}
		{"usa_antiship cwps2" {volume "body"}}
		{"rus_antiship cwps2" {volume "body"}}
		{"usa_radpassive cwps2" {volume "body"}}
		{"rus_radpassive cwps2" {volume "body"}}
	}
	{decoy_flare
		{"usa_ir cwps2" {volume "body"}}
		{"rus_ir cwps2" {volume "body"}}
	}
	{decoy_optic
		{"usa_laser cwps2" {volume "body"}}
		{"rus_laser cwps2" {volume "body"}}
		{"usa_other cwps2" {volume "body"}}
		{"rus_other cwps2" {volume "body"}}
	}
	
	{proj_gbu39_gps
		{"usa_gps cwps2" {volume "target_gbu"}}	
	}
(define "gbu39_selector"	
	{proj_gbu39_gps_%n
		{"usa_gps cwps2" {volume "target_gorka"}}
		{"usa_gps cwps2" {ground}}
		
	}
)
("gbu39_selector" n(00))
("gbu39_selector" n(01))
("gbu39_selector" n(02))
("gbu39_selector" n(03))
("gbu39_selector" n(04))
("gbu39_selector" n(05))
("gbu39_selector" n(06))
("gbu39_selector" n(07))
("gbu39_selector" n(08))
("gbu39_selector" n(09))
("gbu39_selector" n(10))
("gbu39_selector" n(11))
("gbu39_selector" n(12))
("gbu39_selector" n(13))
("gbu39_selector" n(14))
("gbu39_selector" n(15))

	{proj_gbu53b_gps
		{"usa_gps cwps2" {volume "target_gbu"}}	
	}

(define "gbu53b_selector"	
	{proj_gbu53b_gps_%n
		{"usa_gps cwps2" {volume "target_gorka"}}
		{"usa_gps cwps2" {ground}}
	
	}
)
("gbu53b_selector" n(00))
("gbu53b_selector" n(01))
("gbu53b_selector" n(02))
("gbu53b_selector" n(03))
("gbu53b_selector" n(04))
("gbu53b_selector" n(05))
("gbu53b_selector" n(06))
("gbu53b_selector" n(07))
("gbu53b_selector" n(08))
("gbu53b_selector" n(09))
("gbu53b_selector" n(10))
("gbu53b_selector" n(11))
("gbu53b_selector" n(12))
("gbu53b_selector" n(13))
("gbu53b_selector" n(14))
("gbu53b_selector" n(15))

	{proj_jdam_er_gps
		{"usa_gps cwps2" {volume "target_gbu"}}	
	}

(define "jdam_er_selector"	
	{proj_jdam_er_gps_%n
		{"usa_gps cwps2" {volume "target_gorka"}}
		{"usa_gps cwps2" {ground}}
		
	}
)
("jdam_er_selector" n(00))
("jdam_er_selector" n(01))
("jdam_er_selector" n(02))
("jdam_er_selector" n(03))

	{proj_umpk_500_gps
		{"rus_gps cwps2" {volume "target_gbu"}}	
	}

(define "umpk_500_selector"	
	{proj_umpk_500_gps_%n
		{"rus_gps cwps2" {volume "target_gorka"}}
		{"rus_gps cwps2" {ground}}
		
	}
)
("umpk_500_selector" n(00))
("umpk_500_selector" n(01))
("umpk_500_selector" n(02))
("umpk_500_selector" n(03))

	{proj_ls6_gps
		{"rus_gps cwps2" {volume "target_gbu"}}	
	}

(define "ls6_selector"	
	{proj_ls6_gps_%n
		{"rus_gps cwps2" {volume "target_gorka"}}
		{"rus_gps cwps2" {ground}}
		
	}
)
("ls6_selector" n(00))
("ls6_selector" n(01))
("ls6_selector" n(02))
("ls6_selector" n(03))

(define "csbbm2_selector"	
	{proj_csbbm2_gps_%n
		{"rus_gps cwps2" {volume "target_gorka"}}
		{"rus_gps cwps2" {ground}}
		
	}
)
("csbbm2_selector" n(00))
("csbbm2_selector" n(01))
("csbbm2_selector" n(02))
("csbbm2_selector" n(03))

