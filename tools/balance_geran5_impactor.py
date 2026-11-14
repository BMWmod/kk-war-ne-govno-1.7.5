"""Keep Geran-5's game warhead below the Su-35's Kh-59M cruise missile."""
import sys
sys.dont_write_bytecode=True
from build_an196_config import ROOT,write

def install():
    # Game balance, not a physical warhead model. Slightly wider than Shahed-136,
    # substantially below Kh-59M (outer radius 31, central layer energy 69).
    profile='''{from "pattern proj_impactor"
    {entity "geran5_base_impactor"}
    {inventory {weight 100} {size 5 1}}
    {tag "no_ricochet" "fg" "fragmentary" "big" "size4" "fx_upto50kg" "he_over30"}
    ; UAV warhead: no cruise-missile penetration or FAB-500 blast envelope.
    {damage blastwave {energy 0.7} {area 20 23}}
    {damage add blastwave {energy 1.2} {area 16 18.4}}
    {damage add blastwave {energy 2.5} {area 10 11.5}}
    {damage add blastwave {energy 6.5} {area 7.5 8.6}}
    {damage add blastwave {energy 11} {area 3.5 4}}
    {damage add blastwave {energy 25} {area 0.2 0.4}}
    {damage add fire {radius 3} {heating 10} {time 1.5}}
}
'''
    for name in ['geran5_base_impactor','geran5_base_impactor_direct_hit.fg.ammo']:
        write(ROOT/'resource/set/stuff/air_stuff'/name,profile)
    print('Geran-5 impact and direct hit use one reduced warhead profile: outer radius 23, central layer energy 25.')

if __name__=='__main__':install()
