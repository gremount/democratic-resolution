#pragma once
#include "FTM_small_map.h"

CEdge::CEdge(int a, int b, int c, int d){
	tail = a;
	head = b;
	weight = c;
	capacity = d;
	bw_utli = 0;
}

CEdge::CEdge(int a, int b, int c){
	head = b;
	tail = a;
	weight = c;
	bw_utli = 0;
}

CEdge::CEdge(CEdge & x){
	tail = x.getTail();
	head = x.getHead();
	weight = x.getWeight();
	capacity = x.getCap();
	bw_utli = x.bw_utli;
}

CGraph::CGraph(list<CEdge*> listEdge){
	list<CEdge*> IncidentList2;
	IncidentList2 = listEdge;//the initial edges
	IncidentList = listEdge;
	numVertex = N;
	numEdge = listEdge.size() * 2;
	//add the back edge
	list<CEdge*>::iterator it, iend;
	iend = IncidentList2.end();
	for (it = IncidentList2.begin(); it != iend; it++)
	{
		CEdge* e = new CEdge((*it)->getHead(), (*it)->getTail(), 1, 10);
		IncidentList.push_back(e);
	}
}

int main()
{
	list<CEdge*> listEdge;
	int i, j;
	int all_links_bw2[N+10];
	int rack2[N+10];
	for (i=1;i<=N;i++)
	{
		all_links_bw2[i]=0;
		rack2[i]=0;
	}
	/*Our experiments emulate a network with a single-rooted, three-level tree topology:
	*specifically, a 1-2-4 tree with 8 top-of-rack (ToR) switches.
	*/

	//the edge between the root and the first level of the tree
	for (i = 2; i <= 3; i++)
	{
		CEdge* e1 = new CEdge(1, i, 1, 10);
		listEdge.push_back(e1);
	}
	//the second level
	j = 2;//father beginning with 2
	int flag = 1;//j++ per 2 loops
	for (i = 4; i <= 7; i++)
	{
		CEdge* e2 = new CEdge(j, i, 1, 10);
		listEdge.push_back(e2);
		if (flag % 2 == 0) j++;
		flag++;
	}
	//the third level
	j = 4;//father beginning with 4
	flag = 1;//j++ per 2 loops
	for (i = 8; i <= 15; i++)
	{
		CEdge* e3 = new CEdge(j, i, 1, 10);
		listEdge.push_back(e3);
		if (flag % 2 == 0) j++;
		flag++;
	}

	CGraph g(listEdge);
	//g.matrix();
	g.p4();
	//for (i = 26; i <= 153; i++)
		//g.DijkstraAlg(g, i);
	pair<int, int> req2(16,100);
	FTM f;
	//CBM c;
	f.propose(req2,all_links_bw2,rack2);

	for (i = 8; i <= 15; i++)
		printf("rack[%d]: %d\n", i, f.rack[i]);

	/*
	for (i = 26; i <= 30; i++)
	printf("the utli_bw of link %d is %d \n", i,f.ng.mline_all[i]);
	printf("%d,%d,%f\n", f.bw_core_links, f.bw_all_links,f.wcs);
	*/

	getchar();
	return 0;
}