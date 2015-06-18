#pragma once
#include "FTM_small_map.h"
#include "CBM_small_map.h"
#include "GBM_small_map.h"
#include "SRM_small_map.h"
#include "Voting.h"

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
	for (i=0;i<=N;i++)
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

	//CGraph g(listEdge);
	//g.matrix();
	//g.p4();
	//for (i = 26; i <= 153; i++)
		//g.DijkstraAlg(g, i);
	pair<int, int> req1(33, 100);
	pair<int, int> req2(16, 100);
	pair<int, int> req3(17, 100);
	
	FTM f;
	CBM c;
	GBM gg;
	SRM s;
	
	//req1 
	c.propose(req1, all_links_bw2, rack2);
	float co,fo,so;
	float ggo;
	f.req_num++;
	co=c.evaluate(req1, c.all_links_bw, c.rack, c.implement);
	fo = f.evaluate(req1, c.all_links_bw, c.rack, c.implement);
	ggo = gg.evaluate(c.all_links_bw);
	so = s.evaluate(c.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;
	
	//second request
	c.propose(req2, c.all_links_bw, c.rack);
	f.req_num++;
	co=c.evaluate(req2, c.all_links_bw, c.rack, c.implement);
	fo = f.evaluate(req2, c.all_links_bw, c.rack, c.implement);
	ggo = gg.evaluate(c.all_links_bw);
	so = s.evaluate(c.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;

	//third request
	c.propose(req3, c.all_links_bw, c.rack);
	f.req_num++;
	co=c.evaluate(req3, c.all_links_bw, c.rack, c.implement);
	fo = f.evaluate(req3, c.all_links_bw, c.rack, c.implement);
	ggo = gg.evaluate(c.all_links_bw);
	so = s.evaluate(c.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;

	
	//c.propose(req1, all_links_bw2, rack2);
	//gg.propose(req1, all_links_bw2, rack2);
	
	/*  FTM test
	//req1
	f.propose(req1, all_links_bw2, rack2);
	float co,fo,so;
	float ggo;
	f.req_num++;
	co=c.evaluate(req1, f.all_links_bw, f.rack, f.implement);
	fo = f.evaluate(req1, f.all_links_bw, f.rack, f.implement);
	ggo = gg.evaluate(f.all_links_bw);
	so = s.evaluate(f.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;
	
	//second request
	f.propose(req2, f.all_links_bw, f.rack);
	f.req_num++;
	co=c.evaluate(req2, f.all_links_bw, f.rack, f.implement);
	fo = f.evaluate(req2, f.all_links_bw, f.rack, f.implement);
	ggo = gg.evaluate(f.all_links_bw);
	so = s.evaluate(f.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;

	//third request
	f.propose(req3, f.all_links_bw, f.rack);
	f.req_num++;
	co=c.evaluate(req3, f.all_links_bw, f.rack, f.implement);
	fo = f.evaluate(req3, f.all_links_bw, f.rack, f.implement);
	ggo = gg.evaluate(f.all_links_bw);
	so = s.evaluate(f.implement);
	printf("cbm result: %f and ftm result: %f \n and gbm: %f  and srm: %f\n", co, fo,ggo,so);
	f.wcs_record += f.wcs;
	the end of FTM test*/

	int tmp[3][4] = { { 1, 3, 2, 3 }, { 2, 2, 1, 1 }, { 3, 1, 3, 2 } };
	Table tt(tmp);
	int finalWinner;
	Vote vv;
	finalWinner = vv.Voting(tt, 3);  // scenario 3
	cout <<"final winner is "<<finalWinner << endl;

	/*
	f.propose(req2, c.all_links_bw, c.rack);
	c.propose(req2, c.all_links_bw, c.rack);
	f.req_num++;
	cc = c.evaluate(req2, f.all_links_bw, f.rack, f.implement);
	ff = f.evaluate(req2, f.all_links_bw, f.rack, f.implement);
	printf("cbm result: %f and ftm result: %f\n",cc,ff);
	*/

	/*
	f.propose(req2,all_links_bw2,rack2);
	f.evaluate(req2, f.all_links_bw, f.rack, f.implement);
	f.wcs_record += f.wcs;
	f.propose(req3, f.all_links_bw, f.rack);
	f.evaluate(req3, f.link_bw, f.rack, f.implement);
	*/

	//for (i = 8; i <= 15; i++)
		//printf("rack[%d]: %d\n", i, f.rack[i]);
	//printf("wcs: %f\n",f.evaluate(req2,f.all_links_bw,f.rack,f.implement));

	/*
	for (i = 26; i <= 30; i++)
	printf("the utli_bw of link %d is %d \n", i,f.ng.mline_all[i]);
	printf("%d,%d,%f\n", f.bw_core_links, f.bw_all_links,f.wcs);
	*/

	getchar();
	return 0;
}