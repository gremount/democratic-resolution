#include "resources.h"



CEdge::CEdge(int a, int b, int c, int d){
	tail=a;
	head=b;
	weight=c;
	capacity=d;
}

CEdge::CEdge(int a, int b, int c){
	head=b;
	tail=a;
	weight=c;
}

CEdge::CEdge(CEdge & x){
	tail=x.getTail();
	head=x.getHead();
	weight=x.getWeight();
	capacity=x.getCap();
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

CGraph FTM_propose(list<pair<int,int>> requests, CGraph g)
{
	CGraph ng = g;
	int numVMs;
	int numOpenSlots;//record the rest space in racks
	int openRackIndex,rackIndex,length;
	list<pair<int,int>>::iterator it,iend;
	iend = requests.end();
	for(it = requests.begin();it!=iend;it++)
		numVMs = (*it).first;
		numOpenSlots = ng.getNumOpenSlots();
		if(numOpenSlots < numVMs)
			return ng;
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
	return ng;
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
	//g.p1();
	//g.p2();
	g.p3();//adjacency matrix
	g.p4();
	//for(i=26;i<=153;i++)
		//g.DijkstraAlg(g,i);
	list<pair<int,int>> requests;
	pair<int,int> p(129,100);
	requests.push_back(p);
	g = FTM_propose(requests,g);
	
	for(i=26;i<=50;i++)
		printf("rack[%d]: %d\n", i,g.rack[i]);
	getchar();
	return 0;
}
