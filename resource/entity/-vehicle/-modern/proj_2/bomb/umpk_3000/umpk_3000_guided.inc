
    (include "/properties/projectile_impulse.ext")
	{extender "stuff"
		{item "umpk_3000_impactor"}
	}
	{props "umpk_3000_guided"}
	
	("impulse_engine" missile("umpk_3000")
	fore_offset(50) cont_offset(-100)
	calibre(820) length(3300)
	)
	("impulse_glide_bomb")
	("guidance_double" country(rus) type(gps) typeaj(gps) guidance(long_gbu) guidanceaj(short_gbu))
	("impulse_missile_armor" thickness(20) durability(160))	;FAB-3000 M-54, thick-walled body
