#pragma once
#include "resources.h"

class FTM{
public:
	CGraph ng;
	FTM();

	void propose(list<pair<int,int>> requests, CGraph g)
	{
		ng = g;
		int numVMs;
		int numOpenSlots;//record the rest space in racks
		int openRackIndex,rackIndex,length;
		list<pair<int,int>>::iterator it,iend;
		iend = requests.end();
		for(it = requests.begin();it!=iend;it++)
		{
			numVMs = (*it).first;
			numOpenSlots = ng.getNumOpenSlots();
			if(numOpenSlots < numVMs)
			{
				break;
				printf("!!!!there is not enough space for the VMs\n");
			}
			openRackIndex = 0;
			length = 128;
			for(int i=1;i<=numVMs;i++)
			{
				rackIndex = openRackIndex%length;
				ng.rack[26+rackIndex]++;
				openRackIndex++;
			}
			ng.NumOpenSlots = ng.NumOpenSlots - numVMs;
		}
	}
};