#pragma once
#include "resources.h"

class GBM{
public:
	CGraph ng;
	int bw_core_links, bw_all_links;
	float wcs;
	GBM(){ ; }

	void propose(list<pair<int, int>> requests, CGraph g)
	{
		ng = g;

	}
};