#pragma once
#include "resources.h"

class FTM{
public:
	CGraph ng;
	FTM(){;}

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
			int i, j;
			for(i=1;i<=numVMs;i++)
			{
				rackIndex = 26 + openRackIndex%length;
				if (ng.rack[rackIndex] == 16) continue;// if the rack space is not enough, use the next rack
				ng.rack[rackIndex]++;
				ng.mline[rackIndex] += (*it).second;//modify the util_bw of third level of links
				openRackIndex++;
			}
			//modify the util_bw of second level of links
			i = 10;
			int count = 1;
			for (j = 26; j <= 153; j++)
			{
				ng.mline[i] += ng.mline[j];
				if (count % 8 == 0) 
				{ 
					if (ng.mline[i] > (numVMs*(*it).second - ng.mline[i])) ng.mline[i] = numVMs - ng.mline[i];
					i++; 
				}
				count++;
			}
			//modify the util_bw of core links
			i = 2;
			count = 1;
			for (j = 10; j <= 25; j++)
			{
				ng.mline[i] += ng.mline[j];
				if (count % 2 == 0)
				{
					if (ng.mline[i] > (numVMs*(*it).second - ng.mline[i])) ng.mline[i] = numVMs - ng.mline[i];
					i++;
				}
				count++;
			}
			ng.NumOpenSlots = ng.NumOpenSlots - numVMs;
		}
	}
};