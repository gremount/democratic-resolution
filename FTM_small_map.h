#pragma once
#include "resources.h"

class FTM{
public:
	CGraph ng;
	int bw_core_links, bw_all_links;
	float wcs;
	int rack[N+10];// 0<=rack[i]<=16 
	int link_bw[N+10];//in one step, record the utilization of links
	int all_links_bw[N+10];//the sum of link_bw in all steps
	FTM(){ for(int i=1;i<=N;i++){all_links_bw[i]=0;rack[i]=0;} }

	void propose(pair<int, int> req, int all_links_bw2[], int rack2[])
	{
		int numVMs, numVMs_step;
		int openRackIndex, rackIndex, length;
		for (int i = 1; i <= N; i++)
		{
			all_links_bw[i] = all_links_bw2[i];
			rack[i] = rack2[i];
			link_bw[i] = 0;
		}
		numVMs_step = 0;
		numVMs = req.first;
		numVMs_step += numVMs;
		openRackIndex = 0;
		length = 8;
		int i, j;
		for (i = 1; i <= numVMs; i++)
		{
			rackIndex = 8 + openRackIndex%length;
			// if the rack space is not enough, use the next rack
			while (1)
			{
				if (rack[rackIndex] == 16) rackIndex++;
				else break;
			}
			rack[rackIndex]++;
			link_bw[rackIndex] += req.second;//modify the util_bw of third level of links
			openRackIndex++;
		}
		//modify the util_bw of second level of links
		i = 4;
		int count = 1;
		for (j = 8; j <= 15; j++)
		{
			link_bw[i] += link_bw[j];
			if (count % 2 == 0)
			{
				if (link_bw[i] > (numVMs*req.second - link_bw[i])) link_bw[i] = numVMs - link_bw[i];
				i++;
			}
			count++;
		}
		//modify the util_bw of core links
		i = 2;
		count = 1;
		for (j = 4; j <= 7; j++)
		{
			link_bw[i] += link_bw[j];
			if (count % 2 == 0)
			{
				if (link_bw[i] > (numVMs*req.second - link_bw[i])) link_bw[i] = numVMs - link_bw[i];
				i++;
			}
			count++;
		}
		for (i = 2; i <= N; i++)
		{
			all_links_bw[i] += link_bw[i];
			printf("link %d: %d\n",i,all_links_bw[i]);
		}
		ng.NumOpenSlots = ng.NumOpenSlots - numVMs;
		
	}
	void evaluate()
	{

	}
};