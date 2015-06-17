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

the standard interface:

req-----request(one propose has one request)
link_bw[i]-----After accumulations, the bw utilization of link[i]
rack[i]-----After accumulations, 0<=rack[i]<=16 
implement[i]----- in one step, the VMs in each rack
proposal-----control module provide this to be voted
(int link_bw[], int rack[], int implement[]);

Athens.FTM.propose(pair<int, int> req, int link_bw[], int rack[] );
propose()-->return proposal-->(int link_bw[], int rack[], int implement[]);

Athens.FTM.evaluate(int req, struct proposal);
evaluate()-->return value-->int

Athens.make_table()
return table;

Athens.Voting(struct table, int k);(k represents the k kind of voting method scenario)
return winner(int)

tasks distribution:
make table--wang: Athens+FTM+CBM
make table--tang: Athens+GBM+SRM
use tabel--jian: Athens+Voting

the topo of Athens, for test convenience, we use the 1-2-4-8 structure of binary tree and each rack can store 16 VMs  

