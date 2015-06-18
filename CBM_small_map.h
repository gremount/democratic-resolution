#pragma once
#include "resources.h"

class CBM{
public:
	float wcs;//in one step, record the wcs
	float wcs_record;//record the sum of wcs

	int req_num;//record the num of req

	int implement[N + 10];//in one step, record the rack
	int rack[N + 10];// After accumulations, 0<=rack[i]<=16 

	int link_bw[N + 10];//in one step, record the utilization of links
	int all_links_bw[N + 10];//the sum of link_bw in all steps
	
	int subnet_one, subnet_two;

	CBM()
	{
		for (int i = 1; i <= N; i++){ all_links_bw[i] = 0; rack[i] = 0; }
		wcs_record = 0;
		req_num = 0;
		subnet_one = 16 * 4;
		subnet_two = 16 * 4;
	}

	void propose(pair<int, int> req, int all_links_bw2[], int rack2[])
	{
		int numVMs,bw;
		int openRackIndex, rackIndex, length;
		for (int i = 1; i <= N; i++)
		{
			all_links_bw[i] = all_links_bw2[i];
			rack[i] = rack2[i];
			link_bw[i] = 0;
			implement[i] = 0;
		}
		numVMs = req.first;
		bw = req.second;
		openRackIndex = 0;
		length = 8;
		int i, j;
		if (subnet_one >= numVMs){
			for (i = 8; i <= 11; i++)
			{
				if (rack[i] == 16)continue;
				if (rack[i] + numVMs > 16){ numVMs = numVMs - (16 - rack[i]); implement[i] += 16 - rack[i]; rack[i] = 16; }
				if (rack[i] + numVMs <= 16){ rack[i] = rack[i] + numVMs; implement[i] += numVMs; numVMs = 0; }
				if (numVMs == 0) break;
			}
		}
		else if (subnet_two >= numVMs)
		{
			for (i = 12; i <= 15; i++)
			{
				if (rack[i] == 16)continue;
				if (rack[i] + numVMs > 16){ numVMs = numVMs - (16 - rack[i]); implement[i] += 16 - rack[i]; rack[i] = 16; }
				else if (rack[i] + numVMs <= 16){ rack[i] = rack[i] + numVMs; implement[i] += numVMs; numVMs = 0; }
				if (numVMs == 0) break;
			}
		}
		else
		{
			if (subnet_one >= subnet_two)
			{
				numVMs = numVMs - subnet_one;
				for (i = 8; i <= 11; i++)
				{
					implement[i] += (16 - rack[i]);
					rack[i] = 16;
				}
				for (i = 12; i <= 15; i++)
				{
					if (rack[i] == 16)continue;
					if (rack[i] + numVMs > 16){ numVMs = numVMs - (16 - rack[i]);  implement[i] += 16 - rack[i]; rack[i] = 16; }
					else if (rack[i] + numVMs <= 16){ rack[i] = rack[i] + numVMs;  implement[i] += numVMs; numVMs = 0; }
					if (numVMs == 0) break;
				}
			}
			else
			{
				numVMs = numVMs - subnet_one;
				for (i = 12; i <= 15; i++)
				{
					implement[i] += (16 - rack[i]);
					rack[i] = 16;
				}
				for (i = 8; i <= 11; i++)
				{
					if (rack[i] == 16)continue;
					if (rack[i] + numVMs > 16){ numVMs = numVMs - (16 - rack[i]); implement[i] += 16 - rack[i]; rack[i] = 16; }
					else if (rack[i] + numVMs <= 16){ rack[i] = rack[i] + numVMs; implement[i] += numVMs; numVMs = 0; }
					if (numVMs == 0) break;
				}
			}
		}
		//have already implemented, and then modify the bw of all links
		//the third floor
		for (j = 8; j <= 15; j++)
		{
			if (implement[j] == 0) continue;
			if ((implement[j] > (req.first - implement[j])) && (req.first - implement[j])!=0)
				link_bw[j] = link_bw[j] + req.second*(req.first - implement[j]);
			else if ((implement[j] > (req.first - implement[j])) && (req.first - implement[j]) == 0)
				break;
			else	
				link_bw[j] = implement[j] * bw;
		}
		//the second floor
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
		//the first floor
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
			//printf("cbm link %d: %d\n", i, all_links_bw[i]);
		}
	}

	float evaluate(pair<int, int> req, int all_links_bw2[], int rack2[], int implement2[])
	{
		float core_bw;
		core_bw = (float)(all_links_bw2[2] + all_links_bw2[3]) / 2;
		return  core_bw;
	}
};