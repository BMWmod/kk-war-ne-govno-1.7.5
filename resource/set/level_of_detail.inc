;{levelofdetail
;	{"test"
;		{distance 1000}		; LOD1
;		{distance 1500		; LOD2
;			{NoFog}
;			{NoGetShadow}
;			{NoCastShadow}
;			{off}
;		}
;	}
	(define "scale"
		(* 1.0 %d)
	)
	(mod "mp"
		(define "scale"
			(* 1.0 %d)
		)
	)
	(mod "coop"
		(define "scale"
			(* 1.0 %d)
		)
	)
	{"human"
		{distance ("scale" d(1000))
			; LOD1
		}
		{distance ("scale" d(1500))
			; LOD2
		}
		{distance ("scale" d(2000))
			; LOD3
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")
		}
	}
	{"vehicle_civilian"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")
		}
	}
	{"vehicle_small"
		{distance ("scale" d(2000))
			; LOD1
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")
		}
	}
	{"vehicle_big"
		{distance ("scale" d(2000))
			; LOD1
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")
		}
	}
	{"stuff_small"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off_small")
		}
	}
	{"part_small"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off_small")
		}
	}
	{"part_big"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")
		}
	}
	{"decor_tiny"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off_small")
		}
	}
	{"decor_small"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off_small")
		}
	}
	{"decor_medium"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(2000))
			; LOD2
		}
		{distance ("scale" d(2500))
			; LOD3
		}
		{distance ("scale" d(3000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			("off")		
		}
	}
	{"decor_big"
		{distance ("scale" d(1500))
			; LOD1
		}
		{distance ("scale" d(3000))
			; LOD2
		}
		{distance ("scale" d(8000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
	}
	{"decor_tree"
		{distance ("scale" d(2000))
			; LOD1
		}
		{distance ("scale" d(2500))
			; LOD2
		}
		{distance ("scale" d(3000))
			; LOD3
		}
		{distance ("scale" d(5000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			; LOD5
		}
	}

	{"decor_cap"
		{distance ("scale" d(2000))
			; LOD1
		}
		{distance ("scale" d(3000))
			; LOD2
		}
		{distance ("scale" d(4000))
			; LOD3
		}
		{distance ("scale" d(5000))
			{NoGetShadow}
			{NoFog}
			{NoCastShadow}
		}
		{distance ("scale" d(8000))
			; LOD5
		}
	}
	{GrassDistance ("scale" d(5000))}
	{GrassFadeDepth ("scale" d(3000))}
;}