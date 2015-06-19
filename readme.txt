readme

Democratic Resolution of Resource Conflicts Between SDN Control Programs

core: Athens

control: 
FTM(Fault-Tolerance Module) 
CBM(Core-Bandwidth Module)
GBM(Guaranteed-Bandwidth Module) 
SRM(Switch Resource Module)

input: request injection module

output: winning proposal

big_map: 1-8-16-128
1:   1
8:   2 3 4 5 ... 9
16:  10 11 12 ... 25
128: 26 27 28 ... 153

small_map: 1-2-4-8
1:  1
2:  2 3
4:  4 5 6 7
8:  8 9 10 11 12 13 14 15

the topo of Athens, for test convenience, we use the 1-2-4-8 structure of binary tree and each rack can store 16 VMs  

