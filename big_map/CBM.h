#pragma once
#include "resources.h"

class CBM{
public:
	CGraph ng;
	int bw_core_links, bw_all_links;
	float wcs;
	int sum16[10];
	CBM(){ for(int i=1;i<=8;i++)sum16[10]=256; }

	void propose(list<pair<int, int>> requests, CGraph g)
	{
		ng = g;
		int numVMs,numVMs_step;
		int numOpenSlots;//record the rest space in racks
		int openRackIndex,rackIndex,length;
		list<pair<int,int>>::iterator it,iend;
		iend = requests.end();
		numVMs_step=0;
		//for (int i = 1; i <= N; i++)
			//ng.mline_step[i] = 0;
		for(it=requests.begin();it!=iend;it++)
		{
			numVMs = (*it).first;
			numVMs_step += numVMs;
			numOpenSlots = ng.getNumOpenSlots();
			if(numOpenSlots < numVMs)
			{
				break;
				printf("!!!!there is not enough space for the VMs\n");
			}
			openRackIndex = 0;
			length = 128;
			int i, j;
			int flag=0;// modify to 1 if this request has been placed
			for(i=1;i<=8;i++)
			{
				if(sum16[i]>=numVMs) 
				{
					for(j=i+26;j<=i+26+7;j++)
					{
						if((ng.rack[j]<16) && ((16-ng.rack[j])<numVMs)) {numVMs=numVMs-(16-ng.rack[j]);sum16[i]=sum16[i]-(16-ng.rack[j]);ng.rack[j]=16;}
						else if((ng.rack[j]<16) && ((16-ng.rack[j])>=numVMs)){ng.rack[j]+=numVMs;sum16[i]=sum16[i]-numVMs;numVMs=0;flag=1;break;}
						else if(ng.rack[j]==16) continue;
					}
				}
				if(flag==1) break;
			}
			// if one 16 ToR domain can't provide enough space for this request
			if(flag==0) 
			{
				for(j=26;j<=153;j++)
				{
					if((ng.rack[j]<16) && ((16-ng.rack[j])<numVMs)) {numVMs=numVMs-(16-ng.rack[j]);sum16[i]=sum16[i]-(16-ng.rack[j]);ng.rack[j]=16;}
					else if((ng.rack[j]<16) && ((16-ng.rack[j])>=numVMs)){ng.rack[j]+=numVMs;sum16[i]=sum16[i]-numVMs;numVMs=0;flag=1;break;}
					else if(ng.rack[j]==16) continue;
				}
			}
			if(flag==0) printf("error exists, please check\n");
			
		}
	}
};