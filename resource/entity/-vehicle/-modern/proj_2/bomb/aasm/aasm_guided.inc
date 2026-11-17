
    (include "/properties/projectile_impulse.ext")
	{extender "stuff"
		{item "aasm_impactor"}
	}
	{props "aasm_guided"}

	("impulse_engine" missile("aasm")
	fore_offset(30) cont_offset(-60)
	calibre(330) length(3100)
	)
	("impulse_glide_bomb")
	("guidance_double" country(usa) type(gps) typeaj(gps) guidance(long_gbu) guidanceaj(short_gbu))
	("impulse_missile_armor" thickness(10) durability(80))
