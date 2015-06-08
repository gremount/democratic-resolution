#pragma once
#include "common.h"

class CEdge{
private:
	int tail, head;
	int weight, capacity;
public:
	int bw_utli;//用来记录link当前所用带宽
	CEdge(int a, int b, int c, int d);
	CEdge(int a, int b, int c);
	CEdge(CEdge &x);
	int getHead(){return head;}
	int getTail(){return tail;}
	int getWeight(){return weight;}
	int getCap(){return capacity;}
	bool operator<(CEdge& x){
		if(weight<x.weight)
			return 1;
		else 
			return 0;
	}
};

class CGraph{
private:
	int numVertex;
	int numEdge;
	list<CEdge*> IncidentList;//图的所有边组成的链表
public:
	set<int> S[N+10];
	set<int> V[N+10];
	int d[N+10][N+10];
	int p[N+10][N+10];
	int NumOpenSlots;
	int rack[N+10];// 0<=rack[i]<=16 
	int mline[N + 10];// record all the utlization of links in the graph

	//matrix  邻接矩阵
	int adjmatrix[N+10][N+10];
	//p4  给定一个顶点，求一个list，该list中存储了与该顶点关联的所有边
	map<int,list<CEdge*>> nelist;
	
	CGraph(){;}
	CGraph(char* inputFile);
	CGraph(list<CEdge*> listEdge);
	//CGraph(CGraph &);
	int getNumOpenSlots(){
		return NumOpenSlots;
	}
	int getNumVertex(){
		return numVertex;
	}
	int getNumEdge(){
		return numEdge;
	}
	int cmp(const pair<int,int> &x, const pair<int, int> &y){
		return x.second > y.second;
	}

	void matrix(){
		int i,j;
		for (i = 1; i <= N; i++)
			mline[i] = 0;
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
				adjmatrix[i][j]=0;
	}

	void p4(){
		list<CEdge*>::iterator it,iend;
		
		iend=IncidentList.end();
		for(it=IncidentList.begin();it!=iend;it++){
			nelist[(*it)->getTail()].push_back(*it);
		}
		list<CEdge*>::iterator it2,iend2;
		iend2=nelist[3].end();
	}
	
	void Update(int s,int i){
		list<CEdge*>::iterator it,iend;
		it=nelist[i].begin();
		iend=nelist[i].end();
		for(;it!=iend;it++)
			if((*it)->getWeight()+d[s][i]<d[s][(*it)->getHead()]){
				d[s][(*it)->getHead()]=(*it)->getWeight()+d[s][i];
				p[s][(*it)->getHead()]=i;
			}
	}

	int FindMin(int s){
		set<int>::iterator vi,vend;
		vend=V[s].end();
		int mini=10000000;
		int loc=0;
		for(vi=V[s].begin();vi!=vend;vi++)
			if(mini>=d[s][*vi])
				{mini=d[s][*vi];loc=*vi;}
		return loc;
	}

	void DijkstraAlg(CGraph &g,int s){
		int i,j;
		for(i=1;i<=N;i++)
			V[s].insert(i);
		for(i=1;i<=N;i++)
			{d[s][i]=INF;p[s][i]=-2;}
		S[s].insert(s);
		V[s].erase(s);
		d[s][s]=0;
		p[s][s]=-1;
		Update(s,s);
		while (V[s].size()!=0){
			j=FindMin(s);
			S[s].insert(j);
			V[s].erase(j);
			Update(s,j);
		}
		//printf("\n %d->153:%d  p=%d \n",s,d[s][153],p[s][153]);
	}
};
