;Лис пустыни
;====Тест мод=====  
(define "unit_limits"
{unitLimits ";9k72=1;tankman=6;strike=1;rogatka=1;vs=4;p=2;t14=2;max5=5;max6=6;susemx59=2"}
)
(define "instant_test"
	{common
		{unitset
			{value "%unitset"}
		}
				{commandPoints "*=1;vvs=1;artbr=1;vdv=1;mot=1;armbr=1;specbr=1;usaf=1;usart=1;idf=1;usarmy=1;usmc=1;nrf=1;abn=1;bund=1;gb=1;fra=1;cnair=1;cnart=1;cnheavy=1;cnmed=1;cnsco=1;iregular_mot=1;iregular_specbr=1;srbs_mot=1;srbs_vdv=1;srbs_art=1;srbs_pmc=1;avia_odkb=1;ukr_odkb=1;bel_odkb=1;art_odkb=1 ;kz_odkb =1 ;isis_vvs =1; ;ngu_ua=1; brt_ua=1; vsu_ua=1; art_ua=1; ppo_ua=1;avia_ua=1 ;iran=1 "} 
		{unitLimits ""}
		{balancingFactorBonus {cp 55000.0} {mp 1.0}}
		{chargeFactors
			{value "*=0"}
			;{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				{mode "without_update"}
				{resource 
					{start 		%start}
					{finish 	100000}
					{speed 		0}
					{limitmin	1000}
					{limitmax	100000}
					{speedset 	"100000"}
				} 
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar  srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
				;gb_hqcar fra_hqcar
			}
			{extra
				{resource 
					{start 		50000}
				}
				{buttons "extra"}
				{tag "special"}
			}
			{hqcar
				{mode "standard"}
				{resource
					{start		110}
					{finish		110}
					{growTime	70}		; in seconds
					{growTable	"0.45"}
					{payback
						{cp			"0		50		100		150		200"}
						{restore	"0.35	0.30	0.20	0.05	0.05"}
					}
				}
				{buttons "hqcar"}
			}
		} 
	}
	{bots
		(include "bots_generic_brig.inc")
	}
)

(define "instant_test_nobrigades"
	{common
		{unitset
			{value "%unitset"}
		}
		{commandPoints "*=55000"} 
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=0"}
			;{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				{mode "without_update"}
				{resource 
					{start 		%start}
					{finish 	100000}
					{speed 		0}
					{limitmin	1000}
					{limitmax	100000}
					{speedset 	"100000"}
				} 
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			{extra
				{resource 
					{start 		50000}
				}
				{buttons "extra"}
				{tag "special"}
			}
			("no_hq_cars")
		} 
	}
	{bots
		(include "bots_generic.inc")
	}
)

;====Стандарт====
(define "extra_units"
			{extra
				{resource 
					{start 		500}
				}
				{buttons "extra"}
				{tag "special"}
			}
)
(define "hq_cars"
			{hqcar
				{mode "standard"}
				{resource
					{start		%size}
					{finish		%size}
					{growTime	70}		; in seconds
					{growTable	"0.45"}
					{payback
						{cp			"0		50		100		150		200"}
						{restore	"0.35	0.25	0.15	0.05	0.05"}
					}
				}
				{buttons "hqcar"}
			}
)
(define "no_hq_cars"
			{hqcardummy
				{mode "standard"}
				{resource
					{start		1}
					{finish		5}
					{growTime	70}		; in seconds
					{growTable	"0.45"}
					{payback
						{cp			"0		50		100		150		200"}
						{restore	"0.35	0.30	0.20	0.05	0.05"}
					}
				}
				
			}
)
(define "without_update"
				{mode "without_update"}
				{resource 
					{start 		%start}
					{finish 	%finish}
					{speed 		0}
					{limitmin	100}
					{limitmax	10000}
					{speedset 	"100 200 300 400 500 600 800 900 1000 1200 1500 1800 2000 4000 6000 8000 10000"}
				} 
)
(define "with_payback"
				{mode "with_payback"}
				{resource 
					{start 		%start}
					{finish 	%finish}
;					{growTime	3623} ; чем меньше тем быстрее идут очки, 0.25 при 10 минутах примерно раз в 1 сек, при 20 в 2
;					{growTable 	"0.6 0.6 0.7 0.7 0.8 0.8 0.9 0.9 0.9 1.0 1.0 1.0"} ; скорость роста относительно кол-ва очков, если 
;					{restoreBegin 	1.25}	; points per sec  Скорость возврата очков за погибших юнитов
;					{restoreEnd 	1.25}	; points per sec 
;					{speedset "300 400"}


					{growTime	9311}		; in seconds
					{limitmin	500}
					{limitmax	5000}
					{speedset 	"500 1000 2000 3000 4000 5000"}
					
					
					{growTable	"0.45"}
					{payback
						{cp			"0		50		100		150		200"}
						{restore	"0.35	0.30	0.20	0.05	0.05"}
					}
					
					
				}   
)
(define "periodical_update"
				{mode "custom"}
				{resource 
					{start 		%start}
					{finish 	%finish}
					{growTime	9311}		; in seconds
					{growTable 	"0.50 0.50 0.50	0.50 0.60 0.60 0.60	0.60 0.60 0.60 0.65	0.65 0.65 0.65 0.70	0.70 0.70 0.70 0.75	0.75 0.75 0.8 0.8	0.8 0.85 0.85 0.85 0.9 0.9 1.0"} ; реальное число(1.0)=(%finish-%start)/(60*сумма из набора чисел growTable) Формула для 30 чисел growTable и {growTime	1800}
					            ;1m   2m   3m   4m   5m   6m   7m   8m   9m   10m  11m  12m  13m  14m  15m  16m  17m  18m  19m  20m  21m  22m  23m  24m  25m  26m  27m  28m  29m  30m
					{payback
						{cp			"-200 -150 -100 -50		0	50	200"}
						{restore	"0.3  0.2	0.1  0.07	0.05 0.05	0.05"}
					}
					{limitmin	%start}
					{limitmax	50000}
					{speedset 	"2000 4000 6000 8000 12000 16000"}
				} 
)

(define "game_brigade_without_update"
	{common
		{unitset
			{value "%unitset"}
		}
				{commandPoints "*=1;vvs=1;artbr=1;vdv=1;mot=1;armbr=1;specbr=1;usaf=1;usart=1;idf=1;usarmy=1;usmc=1;nrf=1;abn=1;bund=1;gb=1;fra=1;cnair=1;cnart=1;cnheavy=1;cnmed=1;cnsco=1 ;iregular_mot=1;iregular_specbr=1;srbs_mot=1 ;srbs_vdv=1 ;srbs_art=1;srbs_pmc=1;avia_odkb=1 ;ukr_odkb=1;bel_odkb=1;art_odkb=1 ;kz_odkb =1 ;isis_vvs =1; ;ngu_ua=1; brt_ua=1; vsu_ua=1; art_ua=1; ppo_ua=1; avia_ua=1"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				("without_update" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar avia_odkb_hqcar art_odkb_hqcar"}
			}
			("hq_cars" hq_restore_speed(%hq_restore_speed) size(%size))
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic_brig.inc")
	}
)
(define "game_brigade_with_payback"
	{common
		{unitset
			{value "%unitset"}
		}
				{commandPoints "*=1;vvs=1;artbr=1;vdv=1;mot=1;armbr=1;specbr=1;usaf=1;usart=1;idf=1;usarmy=1;usmc=1;nrf=1;abn=1;bund=1;gb=1;fra=1;cnair=1;cnart=1;cnheavy=1;cnmed=1;cnsco=1;iregular_mot=1;iregular_specbr=1;srbs_mot=1 ;srbs_vdv=1 ;srbs_art=1;srbs_pmc=1;avia_odkb=1 ;ukr_odkb=1;bel_odkb=1;art_odkb=1 ;kz_odkb =1 ;isis_vvs =1; ;ngu_ua=1; brt_ua=1; vsu_ua=1; art_ua=1; ppo_ua=1; avia_ua=1"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				("with_payback" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("hq_cars" hq_restore_speed(%hq_restore_speed) size(%size))
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic_brig.inc")
	}
)
(define "game_brigade_with_periodical_update"
	{common
		{unitset
			{value "%unitset"}
		}
				{commandPoints "*=1;vvs=1;artbr=1;vdv=1;mot=1;armbr=1;specbr=1;usaf=1;usart=1;idf=1;usarmy=1;usmc=1;nrf=1;abn=1;bund=1;gb=1;fra=1;cnair=1;cnart=1;cnheavy=1;cnmed=1;cnsco=1;iregular_mot=1;iregular_specbr=1;srbs_mot=1 ;srbs_vdv=1 ;srbs_art=1;srbs_pmc=1;avia_odkb=1 ;ukr_odkb=1;bel_odkb=1;art_odkb=1 ;kz_odkb =1 ;isis_vvs =1; ;ngu_ua=1; brt_ua=1; vsu_ua=1; art_ua=1; ppo_ua=1; avia_ua=1"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.25 *=0.5 *=0.7 *=1.0 *=1.2 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle 
                               ("periodical_update" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("hq_cars" hq_restore_speed(%hq_restore_speed) size(%size))
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic_brig.inc")
	}
)

(define "game_brigade_with_lowperiodical_update"
	{common
		{unitset
			{value "%unitset"}
		}
				{commandPoints "*=1;vvs=1;artbr=1;vdv=1;mot=1;armbr=1;specbr=1;usaf=1;usart=1;idf=1;usarmy=1;usmc=1;nrf=1;abn=1;bund=1;gb=1;fra=1;cnair=1;cnart=1;cnheavy=1;cnmed=1;cnsco=1;iart=1;iregular_mot=1;iregular_specbr=1;srbs_mot=1 ;srbs_vdv=1 ;srbs_art=1;srbs_pmc=1;avia_odkb=1 ;ukr_odkb=1;bel_odkb=1;art_odkb=1 ;kz_odkb =1 ;isis_vvs =1; ;ngu_ua=1; brt_ua=1; vsu_ua=1; art_ua=1; ppo_ua=1; avia_ua=1"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 0.6}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle 
                               ("periodical_update" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("hq_cars" hq_restore_speed(%hq_restore_speed) size(%size))
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic_brig.inc")
	}
)
(define "game_normal_without_update"
	{common
		{unitset
			{value "%unitset"}
		}
		{commandPoints "*=%cp"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				("without_update" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("no_hq_cars")
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic.inc")
	}
)
(define "game_normal_with_payback"
	{common
		{unitset
			{value "%unitset"}
		}
		{commandPoints "*=%cp"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle
				("with_payback" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("no_hq_cars")
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic.inc")
	}
)

(define "game_normal_with_periodical_update"
	{common
		{unitset
			{value "%unitset"}
		}
		{commandPoints "*=%cp"} 
;		{chargeFactors "*=%cf"}
 ("unit_limits")
		{balancingFactorBonus {cp 1.0} {mp 1.0}}
		{chargeFactors
			{value "*=1.0"}
			{available "*=0 *=0.5 *=1.0 *=1.5 *=2.0 *=2.5 *=5.0 *=10.0"}
		}
		{budgets
			{vehicle 
                 ("periodical_update" start(%start) finish(%finish))
				{buttons "common supl vvs_hqcar artbr_hqcar vdv_hqcar mot_hqcar armbr_hqcar specbr_hqcar usaf_hqcar usart_hqcar idf_hqcar usarmy_hqcar usmc_hqcar nrf_hqcar abn_hqcar bund_hqcar gb_hqcar fra_hqcar cnair_hqcar cnart_hqcar cnheavy_hqcar cnmed_hqcar cnsco_hqcar iart_hqcar iregular_mot_hqcar iregular_specbr_hqcar srbs_mot_hqcar srbs_vdv_hqcar cnsam_hqcar srbs_art_hqcar srbs_pmc_hqcar avia_odkb_hqcar art_odkb_hqcar ukr_odkb_hqcar bel_odkb_hqcar kz_odkb_hqcar isis_vvs_hqcar ngu_ua_hqcar brt_ua_hqcar vsu_ua_hqcar art_ua_hqcar ppo_ua_hqcar avia_ua_hqcar iran_hqcar"}
			}
			("no_hq_cars")
			("extra_units")
		} 
	}
	{bots
		(include "bots_generic.inc")
	}
)

(define "brigade_presets"
    {"p:brigade_200_periodical_update_%gametype"	{gameMode "periodical_update"}		{unitMode "brigades%desc"}	{specMode "army_200"}
		("game_brigade_with_periodical_update" unitset(%unitset_brigade) cf(1) start(550) finish(6000) size(110))
		{ranked}
	}
	 {"p:brigade_200_lowperiodical_update_%gametype"	{gameMode "periodical_update"}		{unitMode "lowbrigades%desc"}	{specMode "army_200"}
		("game_brigade_with_lowperiodical_update" unitset(%unitset_brigade) cf(1) start(550) finish(6000) size(220))
		{ranked}
	}
	{"p:brigade_200_with_payback_%gametype"	{gameMode "with_payback"}		{unitMode "brigades%desc"}	{specMode "army_200"}
		("game_brigade_with_payback" unitset(%unitset_brigade) cf(1) start(550) finish(6000) size(110))
	}
	{"p:brigade_200_without_update_%gametype"	{gameMode "without_update"}		{unitMode "brigades%desc"}	{specMode "army_200"}
		("game_brigade_without_update" unitset(%unitset_brigade) cf(1) start(550) finish(6000) size(110))
	}
)
(define "normal_presets"
	{"p:normal_200_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "army_200"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(400) cf(1) start(400) finish(6000))
	}
	{"p:normal_160_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "division_160"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(360) cf(1) start(320) finish(6000))
	}
	{"p:normal_140_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "regiment_140"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(340) cf(1) start(280) finish(6000))
	}
	{"p:normal_120_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "battalion_120"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(320) cf(1) start(240) finish(6000))
	}
	{"p:normal_100_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "company_100"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(300) cf(1) start(200) finish(6000))
	}
	{"p:normal_80_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "platoon_80"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(280) cf(1) start(80) finish(6000))
	}
	{"p:normal_60_periodical_update_%gametype"		{gameMode "periodical_update"}		{unitMode "Vnormal%desc"}	{specMode "squad_60"}
		("game_normal_with_periodical_update" unitset(%unitset) cp(260) cf(1) start(60) finish(6000))
	}
;============================
	{"p:normal_200_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "army_200"}
		("game_normal_with_payback" unitset(%unitset) cp(400) cf(1) start(400) finish(6000))
	}
	{"p:normal_160_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "division_160"}
		("game_normal_with_payback" unitset(%unitset) cp(360) cf(1) start(320) finish(6000))
	}
	{"p:normal_140_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "regiment_140"}
		("game_normal_with_payback" unitset(%unitset) cp(340) cf(1) start(280) finish(6000))
	}
	{"p:normal_120_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "battalion_120"}
		("game_normal_with_payback" unitset(%unitset) cp(320) cf(1) start(240) finish(6000))
	}
	{"p:normal_100_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "company_100"}
		("game_normal_with_payback" unitset(%unitset) cp(300) cf(1) start(200) finish(6000))
	}
	{"p:normal_80_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "platoon_80"}
		("game_normal_with_payback" unitset(%unitset) cp(280) cf(1) start(80) finish(6000))
	}
	{"p:normal_60_with_payback_%gametype"		{gameMode "with_payback"}		{unitMode "Vnormal%desc"}	{specMode "squad_60"}
		("game_normal_with_payback" unitset(%unitset) cp(260) cf(1) start(60) finish(6000))
	}
;============================
	{"p:normal_200_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "army_200"}
		("game_normal_without_update" unitset(%unitset) cp(200) cf(1) start(400) finish(6000))
	}
	{"p:normal_160_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "division_160"}
		("game_normal_without_update" unitset(%unitset) cp(160) cf(1) start(320) finish(6000))
	}
	{"p:normal_140_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "regiment_140"}
		("game_normal_without_update" unitset(%unitset) cp(140) cf(1) start(280) finish(6000))
	}
	{"p:normal_120_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "battalion_120"}
		("game_normal_without_update" unitset(%unitset) cp(120) cf(1) start(240) finish(6000))
	}
	{"p:normal_100_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "company_100"}
		("game_normal_without_update" unitset(%unitset) cp(100) cf(1) start(200) finish(6000))
	}
	{"p:normal_80_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "platoon_80"}
		("game_normal_without_update" unitset(%unitset) cp(80) cf(1) start(80) finish(6000))
	}
	{"p:normal_60_without_update_%gametype"		{gameMode "without_update"}		{unitMode "Vnormal%desc"}	{specMode "squad_60"}
		("game_normal_without_update" unitset(%unitset) cp(60) cf(1) start(60) finish(6000))
	}
;============================

)

;==================================================================================================================
(define "custom_presets"
     {presets
	("brigade_presets" gametype(%gametype) desc(%desc) unitset_brigade(%unitset_brigade))
	("normal_presets" gametype(%gametype) desc(%desc) unitset(%unitset))
     }
)



("custom_presets" gametype() desc() unitset_brigade(all_nz^hqcarhqcardummy) unitset(all_nz^hqcar))

;Тестовые
{presets
	{"wu:without_update_timers"
		{gameMode "without_update"}
		{unitMode "test"}
		{specMode "test_a"}
		("instant_test" cf(0) start(100000) unitset(all_nz))
	}
	{"wu:without_update_notimers"
		{gameMode "without_update"}
		{unitMode "test"}
		{specMode "test_b"}
		("instant_test" cf(1) start(100000) unitset(all_nz))
	}
	{"wu:without_update_timers_nobrig"
		{gameMode "without_update"}
		{unitMode "test_nobrig"}
		{specMode "test_a"}
		("instant_test_nobrigades" cf(0) start(100000) unitset(all_nz^hqcar))
	}
	{"wu:without_update_notimers_nobrig"
		{gameMode "without_update"}
		{unitMode "test_nobrig"}
		{specMode "test_b"}
		("instant_test_nobrigades" cf(1) start(100000) unitset(all_nz^hqcar))
	}
}