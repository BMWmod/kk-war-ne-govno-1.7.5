    	(include "terra-interactive_stuff.inc")	{"rock"	  {on hit		{if effector "wind"			{spawn "heli_dust_ground"}		else			{if min_mass 100				{if effector "tree"					{spawn "tree_crush"}				else					{spawn "spheredust_small"}				}			else min_mass 10				{if not effector "tree"					{spawn "spheredust_small_short"}				}			}		}	  }		{on detonate	("terra-interactive_stuff") ("terra-interactive_stuff_ground")	("expl_ground")	("debris_road")	("shellhole_ground_nocrater")		  }	}	