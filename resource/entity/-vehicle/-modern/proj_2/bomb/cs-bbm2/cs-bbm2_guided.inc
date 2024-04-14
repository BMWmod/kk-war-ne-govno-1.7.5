
    (include "/properties/projectile_impulse.ext")
	{extender "stuff"
		{item "cs-bbm2_impactor"}
	}
	{props "cs-bbm2_guided"}
	
	("impulse_engine" missile("cs-bbm2")
	fore_offset(35) cont_offset(-70)
	calibre(250) length(2470)
	)
	("impulse_glide_bomb")
	("guidance_double" country(rus) type(gps) typeaj(gps) guidance(long_gbu) guidanceaj(short_gbu))
	("impulse_missile_armor" thickness(7) durability(50))	;стенка ФАБ-500 около 10мм


