#include "common.h"
#include "resources.h"

class FTM{
private:
		
public:
	FTM(){};

	CGraph propose(list<pair<int,int>> requests, CGraph g)
	{
		CGraph ng = g;
		int numVMs;
		int numOpenSlots;//record the rest space in racks
		int openRackIndex,rackIndex,length;
		int openRack[N+10];// 0<=openRacks[i]<=16 
		list<pair<int,int>>::iterator it,iend;
		iend = requests.end();
		for(it = requests.begin();it!=iend;it++)
		{
			numVMs = (*it).first;
			numOpenSlots = ng.getNumOpenSlots();
			if(numOpenSlots < numVMs)
				return ng;
			openRackIndex = 0;
			length = ng.rack.size();
			for(int i=1;i<=numVMs;i++)
			{
				rackIndex = openRackIndex%length;
				ng.rack[rackIndex]++;
				openRackIndex++;
			}
			ng.NumOpenSlots = ng.NumOpenSlots - numVMs;
		}
		return ng;
	}
};