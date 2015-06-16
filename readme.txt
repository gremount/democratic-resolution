readme

Democratic Resolution of Resource Conflicts Between SDN Control Programs

core: Athens

control: 
FTM(Fault-Tolerance Module) 
CBM(Core-Bandwidth Module) --- CBM and GBM are very similar with each other, so we omit the CBM.
GBM(Guaranteed-Bandwidth Module) 
SRM(Switch Resource Module)

input: request injection module

output: winning proposal

topo: 1-8-16-128
1:   1
8:   2 3 4 5 ... 9
16:  10 11 12 ... 25
128: 26 27 28 ... 153

the index of rack and the index of ToR switch is consistent. For example, rack[30] <---> s[30]

small_map:
1:  1
2:  2 3
4:  4 5 6 7
8:  8 9 10 11 12 13 14 15