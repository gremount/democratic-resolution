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
	numEdge=listEdge.size();
}



int main()
{
	list<CEdge*> listEdge;
	CEdge* e1=new CEdge(1,2,1,10);
	CEdge* e2=new CEdge(2,1,1,10);
	CEdge* e3=new CEdge(1,7,1,10);
	CEdge* e4=new CEdge(7,1,1,10);
	CEdge* e5=new CEdge(7,10,1,10);
	CEdge* e6=new CEdge(10,7,1,10);
	CEdge* e7=new CEdge(3,2,1,10);
	CEdge* e8=new CEdge(2,3,1,10);
	CEdge* e9=new CEdge(3,4,1,10);
	CEdge* e10=new CEdge(4,3,1,10);
	CEdge* e11=new CEdge(4,10,1,10);
	CEdge* e12=new CEdge(10,4,1,10);
	CEdge* e13=new CEdge(1,5,1,10);
	CEdge* e14=new CEdge(5,1,1,10);
	CEdge* e15=new CEdge(6,5,1,10);
	CEdge* e16=new CEdge(5,6,1,10);
	CEdge* e17=new CEdge(6,10,1,10);
	CEdge* e18=new CEdge(10,6,1,10);
	CEdge* e19=new CEdge(8,10,1,10);
	CEdge* e20=new CEdge(10,8,1,10);
	CEdge* e21=new CEdge(9,10,1,10);
	CEdge* e22=new CEdge(10,9,1,10);
	listEdge.push_back(e1);
	listEdge.push_back(e2);
	listEdge.push_back(e3);
	listEdge.push_back(e4);
	listEdge.push_back(e5);
	listEdge.push_back(e6);
	listEdge.push_back(e7);
	listEdge.push_back(e8);
	listEdge.push_back(e9);
	listEdge.push_back(e10);
	listEdge.push_back(e11);
	listEdge.push_back(e12);
	listEdge.push_back(e13);
	listEdge.push_back(e14);
	listEdge.push_back(e15);
	listEdge.push_back(e16);
	listEdge.push_back(e17);
	listEdge.push_back(e18);
	listEdge.push_back(e19);
	listEdge.push_back(e20);
	listEdge.push_back(e21);
	listEdge.push_back(e22);
	CGraph g(listEdge);
	g.p1();
	g.p2();
	g.p3();
	g.p4();
	g.DijkstraAlg(g,1);
	getchar();
	return 0;
}