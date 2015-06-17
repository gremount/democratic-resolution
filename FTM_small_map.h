#pragma once
#include "resources.h"

class FTM{
public:
	float wcs;//record the wcs at this step
	float wcs_record;//record the sum of wcs

	int req_num;//record the num of req

	int implement[N+10];//in one step, record the rack
	int rack[N+10];// After accumulations, 0<=rack[i]<=16 
	
	int link_bw[N+10];//in one step, record the utilization of links
	int all_links_bw[N+10];//the sum of link_bw in all steps
	FTM()
	{ 
		for(int i=1;i<=N;i++){all_links_bw[i]=0;rack[i]=0;}
		wcs_record = 0;
		req_num = 0;
	}

	void propose(pair<int, int> req, int all_links_bw2[], int rack2[])
	{
		int numVMs, bw;
		int rackIndex, length;
		for (int i = 1; i <= N; i++)
		{
			all_links_bw[i] = all_links_bw2[i];
			rack[i] = rack2[i];
			link_bw[i] = 0;
			implement[i] = 0;
		}
		numVMs = req.first;
		bw = req.second;
		length = 8;
		rackIndex = 8;
		int i, j;
		for (i = 1; i <= numVMs; i++)
		{
			// if the rack space is not enough, use the next rack
			while (1)
			{
				if (rack[rackIndex] == 16) { rackIndex++; if (rackIndex >= 16)rackIndex = 8; }
				else break;
			}
			rack[rackIndex]++;
			implement[rackIndex]++;
			link_bw[rackIndex] += req.second;//modify the util_bw of third level of links
			rackIndex++;
			if (rackIndex >= 16)rackIndex = 8;
		}
		//modify the util_bw of second level of links
		i = 4;
		int count = 1;
		for (j = 8; j <= 15; j++)
		{
			link_bw[i] += link_bw[j];
			implement[i] += implement[j];
			if (count % 2 == 0)
			{
				if (implement[i] > (req.first - implement[i])) link_bw[i] = (req.first - implement[i])*bw;
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
			implement[i] += implement[j];
			if (count % 2 == 0)
			{
				if (implement[i] > (req.first - implement[i])) link_bw[i] = (req.first - implement[i])*bw;
				i++;
			}
			count++;
		}
		for (i = 2; i <= N; i++)
		{
			all_links_bw[i] += link_bw[i];
			printf("ftm link %d: %d\n",i,all_links_bw[i]);
		}
		
		
	}
	float evaluate(pair<int,int> req, int all_links_bw2[], int rack2[],int implement2[])
	{
		int numone=8;//record the rack number with the biggest capacity
		int i,j;
		for(i=8;i<=15;i++)
		{
			if(implement2[i]<implement2[i+1]) numone=i+1;
		}
		wcs = (float)(req.first-implement2[numone])/(float)req.first;
		return  (wcs_record + wcs) / (float)(req_num);
	}
};