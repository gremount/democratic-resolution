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
	IncidentList=listEdge;
	numVertex=N;
	numEdge=listEdge.size()*2;
	//add the back edge
	list<CEdge*>::iterator it,iend;
	iend=IncidentList.end();
	for(it=IncidentList.begin();it!=iend;it++)
	{
		CEdge* e=new CEdge((*it)->getHead(),(*it)->getTail(),1,10);
		IncidentList.push_back(e);
	}
}

int main()
{
	list<CEdge*> listEdge;
	int i,j;
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
	}
	//the third level
	j=10;//father beginning with 10
	flag=1;//j++ per 8 loops
	for(i=26;i<=153;i++)
	{
		CEdge* e3=new CEdge(j,i,1,10);
		listEdge.push_back(e3);
		if(flag%8==0) j++;
	}

	CGraph g(listEdge);
	g.p1();
	g.p2();
	g.p3();
	g.p4();
	g.DijkstraAlg(g,1);
	printf("hehe,wangsc student\n");
	getchar();
	return 0;
}
