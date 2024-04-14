{selector
	{type "missile"}

	{group
		{sort {class decoy_chaff} time_to_aim}
	    {sort {class decoy_flare} time_to_aim}
	    {sort {class decoy_optic}}
		{sort {class proj_usa_ir}}
		{sort {class proj_rus_ir}}
		{sort {class airborne} time_to_aim}
		{sort {class Helicopter} time_to_aim}
		{sort {class small_UAV} time_to_aim}
		{sort {class proj_cwps3} time_to_aim}
		{sort {class antirad_missile} distance}
		{sort {class antiship_missile} distance}
		{sort {class bomb} distance}
		
		{sort time_to_aim}
	}
}
{selector
	{type "antimissile"}
	{group
		{sort {in_range 150} {class proj_cwps3}}
		{sort {class antirad_missile} distance}
		{sort {class antiship_missile} distance}
		{sort {class bomb} distance}
		{sort {class proj_cwps3} time_to_aim}
		
		{sort distance}
	}
}
{selector
	{type "corr"}
	{group
	   {sort {class proj_cwps3}} 
	   {sort time_to_aim}
	}
}
{selector
	{type "laser_guided_shell"}
	{group
	   {sort {class proj_cwps3}}
	   ;{sort {class proj_rus_laser_uas}}
       ;{sort distance}	   
	   ;{sort {class proj_rus_laser_guide}} 
	}
}
{selector
	{type "missile_antirad"}

	{group
		{sort time_to_aim}
	}
}

(define "gbu39_selector"
{selector
	{type "gbu39_%x"}
	{group
		{sort {in_range 5000} {class proj_gbu39_gps_%x}}
		{sort {in_range 10} {class proj_gbu39_gps}}
		{ignore {class proj_gbu39_gps_%a}}
		{ignore {class proj_gbu39_gps_%b}}
		{ignore {class proj_gbu39_gps_%c}}
		{ignore {class proj_gbu39_gps_%d}}
		{ignore {class proj_gbu39_gps_%e}}
		{ignore {class proj_gbu39_gps_%f}}
		{ignore {class proj_gbu39_gps_%g}}
		{ignore {class proj_gbu39_gps_%h}}
		{ignore {class proj_gbu39_gps_%i}}
		{ignore {class proj_gbu39_gps_%j}}
		{ignore {class proj_gbu39_gps_%k}}
		{ignore {class proj_gbu39_gps_%l}}
		{ignore {class proj_gbu39_gps_%m}}
		{ignore {class proj_gbu39_gps_%n}}
		{ignore {class proj_gbu39_gps_%o}}
	}
}
)
("gbu39_selector" x(00) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(01) a(00) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(02) a(01) b(00) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(03) a(01) b(02) c(00) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(04) a(01) b(02) c(03) d(00) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(05) a(01) b(02) c(03) d(04) e(00) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(06) a(01) b(02) c(03) d(04) e(05) f(00) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(07) a(01) b(02) c(03) d(04) e(05) f(06) g(00) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(08) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(00) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(09) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(00) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(10) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(00) k(11) l(12) m(13) n(14) o(15))
("gbu39_selector" x(11) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(00) l(12) m(13) n(14) o(15))
("gbu39_selector" x(12) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(00) m(13) n(14) o(15))
("gbu39_selector" x(13) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(00) n(14) o(15))
("gbu39_selector" x(14) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(00) o(15))
("gbu39_selector" x(15) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(00))

(define "gbu53b_selector"
{selector
	{type "gbu53b_%x"}
	{group
;		{sort {class proj_usa_active}}
;		{sort {class proj_rus_active}}
		{sort {in_range 5000} {class proj_gbu53b_gps_%x}}
		{sort {in_range 10} {class proj_gbu53b_gps}}
		{ignore {class proj_gbu53b_gps_%a}}
		{ignore {class proj_gbu53b_gps_%b}}
		{ignore {class proj_gbu53b_gps_%c}}
		{ignore {class proj_gbu53b_gps_%d}}
		{ignore {class proj_gbu53b_gps_%e}}
		{ignore {class proj_gbu53b_gps_%f}}
		{ignore {class proj_gbu53b_gps_%g}}
		{ignore {class proj_gbu53b_gps_%h}}
		{ignore {class proj_gbu53b_gps_%i}}
		{ignore {class proj_gbu53b_gps_%j}}
		{ignore {class proj_gbu53b_gps_%k}}
		{ignore {class proj_gbu53b_gps_%l}}
		{ignore {class proj_gbu53b_gps_%m}}
		{ignore {class proj_gbu53b_gps_%n}}
		{ignore {class proj_gbu53b_gps_%o}}
	}
}
)
("gbu53b_selector" x(00) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(01) a(00) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(02) a(01) b(00) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(03) a(01) b(02) c(00) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(04) a(01) b(02) c(03) d(00) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(05) a(01) b(02) c(03) d(04) e(00) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(06) a(01) b(02) c(03) d(04) e(05) f(00) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(07) a(01) b(02) c(03) d(04) e(05) f(06) g(00) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(08) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(00) i(09) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(09) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(00) j(10) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(10) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(00) k(11) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(11) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(00) l(12) m(13) n(14) o(15))
("gbu53b_selector" x(12) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(00) m(13) n(14) o(15))
("gbu53b_selector" x(13) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(00) n(14) o(15))
("gbu53b_selector" x(14) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(00) o(15))
("gbu53b_selector" x(15) a(01) b(02) c(03) d(04) e(05) f(06) g(07) h(08) i(09) j(10) k(11) l(12) m(13) n(14) o(00))

(define "jdam_er_selector"
{selector
	{type "jdam_er_%x"}
	{group
		{sort {in_range 5000} {class proj_jdam_er_gps_%x}}
		{sort {in_range 10} {class proj_jdam_er_gps}}
		{ignore {class proj_jdam_er_gps_%a}}
		{ignore {class proj_jdam_er_gps_%b}}
		{ignore {class proj_jdam_er_gps_%c}}
	}
}
)
("jdam_er_selector" x(00) a(01) b(02) c(03))
("jdam_er_selector" x(01) a(00) b(02) c(03))
("jdam_er_selector" x(02) a(01) b(00) c(03))
("jdam_er_selector" x(03) a(01) b(02) c(00))

(define "umpk_500_selector"
{selector
	{type "umpk_500_%x"}
	{group
		{sort {in_range 5000} {class proj_umpk_500_gps_%x}}
		{sort {in_range 10} {class proj_umpk_500_gps}}
		{ignore {class proj_umpk_500_gps_%a}}
		{ignore {class proj_umpk_500_gps_%b}}
		{ignore {class proj_umpk_500_gps_%c}}
	}
}
)
("umpk_500_selector" x(00) a(01) b(02) c(03))
("umpk_500_selector" x(01) a(00) b(02) c(03))
("umpk_500_selector" x(02) a(01) b(00) c(03))
("umpk_500_selector" x(03) a(01) b(02) c(00))

(define "ls6_selector"
{selector
	{type "ls6_%x"}
	{group
		{sort {in_range 5000} {class proj_ls6_gps_%x}}
		{sort {in_range 10} {class proj_ls6_gps}}
		{ignore {class proj_ls6_gps_%a}}
		{ignore {class proj_ls6_gps_%b}}
		{ignore {class proj_ls6_gps_%c}}
	}
}
)
("ls6_selector" x(00) a(01) b(02) c(03))
("ls6_selector" x(01) a(00) b(02) c(03))
("ls6_selector" x(02) a(01) b(00) c(03))
("ls6_selector" x(03) a(01) b(02) c(00))

(define "csbbm2_selector"
{selector
	{type "csbbm2_%x"}
	{group
		{sort {in_range 5000} {class proj_csbbm2_gps_%x}}
		{sort {in_range 10} {class proj_csbbm2_gps}}
		{ignore {class proj_csbbm2_gps_%a}}
		{ignore {class proj_csbbm2_gps_%b}}
		{ignore {class proj_csbbm2_gps_%c}}
	}
}
)
("csbbm2_selector" x(00) a(01) b(02) c(03))
("csbbm2_selector" x(01) a(00) b(02) c(03))
("csbbm2_selector" x(02) a(01) b(00) c(03))
("csbbm2_selector" x(03) a(01) b(02) c(00))
