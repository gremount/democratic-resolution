#pragma once
#include "FTM.h"
#include "CBM.h"

CEdge::CEdge(int a, int b, int c, int d){
	tail=a;
	head=b;
	weight=c;
	capacity=d;
	bw_utli=0;
}

CEdge::CEdge(int a, int b, int c){
	head=b;
	tail=a;
	weight=c;
	bw_utli=0;
}

CEdge::CEdge(CEdge & x){
	tail=x.getTail();
	head=x.getHead();
	weight=x.getWeight();
	capacity=x.getCap();
	bw_utli=x.bw_utli;
}

CGraph::CGraph(list<CEdge*> listEdge){
	list<CEdge*> IncidentList2;
	IncidentList2=listEdge;//the initial edges
	IncidentList=listEdge;
	numVertex=N;
	numEdge=listEdge.size()*2;
	//add the back edge
	list<CEdge*>::iterator it,iend;
	iend=IncidentList2.end();
	for(it=IncidentList2.begin();it!=iend;it++)
	{
		CEdge* e=new CEdge((*it)->getHead(),(*it)->getTail(),1,10);
		IncidentList.push_back(e);
	}
	NumOpenSlots = 128*8;
	for(int i=1;i<=N;i++)
		rack[i]=0;
}

int main()
{
	list<CEdge*> listEdge;
	int i,j;

	/*Our experiments emulate a network with a single-rooted, three-level tree topology:
	 *specifically, a 1-8-16 tree with 128 top-of-rack (ToR) switches.
	 */

	//the edge between the root and the first level of the tree
	for(i=2;i<=9;i++)
	{
		CEdge* e1=new CEdge(1,i,1,10);
		listEdge.push_back(e1);
	}
	//the second level
	j=2;//father beginning with 2
	int flag=1;//j++ per 2 loops
	for(i=10;i<=25;i++)
	{
		CEdge* e2=new CEdge(j,i,1,10);
		listEdge.push_back(e2);
		if(flag%2==0) j++;
		flag++;
	}
	//the third level
	j=10;//father beginning with 10
	flag=1;//j++ per 8 loops
	for(i=26;i<=153;i++)
	{
		CEdge* e3=new CEdge(j,i,1,10);
		listEdge.push_back(e3);
		if(flag%8==0) j++;
		flag++;
	}

	CGraph g(listEdge);
	g.matrix();//adjacency matrix
	g.p4();
	for(i=26;i<=153;i++)
		g.DijkstraAlg(g,i);
	list<pair<int,int>> requests;
	pair<int,int> p1(257,100);
	//pair<int, int> p2(3, 100);
	requests.push_back(p1);
	//requests.push_back(p2);
	//FTM f;
	CBM c;
	c.propose(requests,g);

	for(i=26;i<=50;i++)
		printf("rack[%d]: %d\n", i,c.ng.rack[i]);
	
	/*
	for (i = 26; i <= 30; i++)
		printf("the utli_bw of link %d is %d \n", i,f.ng.mline_all[i]);
	printf("%d,%d,%f\n", f.bw_core_links, f.bw_all_links,f.wcs);
	*/

	getchar();
	return 0;
}