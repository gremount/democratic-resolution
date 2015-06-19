#pragma once
//#include "FTM_small_map.h"
#include "CBM_small_map.h"
#include "GBM_small_map.h"
#include "SRM_small_map.h"
#include "FTM_small_map.h"
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

float test_record[3][4];

void test(pair<int, int> req,FTM& f,CBM& c,GBM& gg, SRM& s)
{
	//the initialization of the test_record[][]
	memset(test_record,0,sizeof(test_record));
	//evaluate the FTM
	test_record[0][0] = f.evaluate(req, f.all_links_bw, f.rack, f.implement,1);
	test_record[0][1] = c.evaluate(req, f.all_links_bw, f.rack, f.implement);
	test_record[0][2] = gg.evaluate(f.all_links_bw);
	test_record[0][3] = s.evaluate(f.implement);
	//evaluate the CBM
	test_record[1][0] = f.evaluate(req, c.all_links_bw, c.rack, c.implement,2);
	test_record[1][1] = c.evaluate(req, c.all_links_bw, c.rack, c.implement);
	test_record[1][2] = gg.evaluate(c.all_links_bw);
	test_record[1][3] = s.evaluate(c.implement);
	//evaluate the GBM
	test_record[2][0] = f.evaluate(req, gg.gbm_all_link_bw, gg.gbm_rack, gg.gbm_implement,3);
	test_record[2][1] = c.evaluate(req, gg.gbm_all_link_bw, gg.gbm_rack, gg.gbm_implement);
	test_record[2][2] = gg.evaluate(gg.gbm_all_link_bw);
	test_record[2][3] = s.evaluate(gg.gbm_implement);
}

int main()
{
	list<CEdge*> listEdge;
	int i, j;
	int all_links_bw2[N + 10];
	int rack2[N + 10];
	for (i = 0; i <= N; i++)
	{
		all_links_bw2[i] = 0;
		rack2[i] = 0;
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
	int rack[20] = { 0 };
	int all_links_bw[20] = { 0 };

	pair<int, int> req1(33, 100);
	pair<int, int> req2(16, 100);
	pair<int, int> req3(17, 100);

	FTM f;
	CBM c;
	GBM gg;
	SRM s;
	Vote vv;

	/*****************  Standard Test   *****************/

	printf("      WCS        CB        GB        FTE\n");

	/*****************the first request*****************/
	cout << "the first request:" << endl;
	//req1 propose()
	f.propose(req1, all_links_bw2, rack2);
	c.propose(req1, all_links_bw2, rack2);
	gg.propose(req1, all_links_bw2, rack2);
	f.req_num++;

	/*
	cout << endl;
	for (i = 1; i <= 15; i++)
	cout << rack[i] << " ";
	cout << endl;
	*/

	//req1 evaluate()
	test(req1, f, c, gg, s);
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 3; j++)
			printf("%10.3f ", test_record[i][j]);
		printf("\n");
	}

	//voting methods
	int winner;//the winner choosed by the voting methods
	Table tt1(test_record);
	winner = vv.Voting(tt1, 2);
	cout << "the winner is: " << winner << endl;

	//data update
	if (winner == 1)
	{
		s.his_sum = s.evaluate(f.implement);
		f.wcs_record += f.wcs_FTM;
	}
	else if (winner == 2)
	{
		s.his_sum = s.evaluate(c.implement); 
		f.wcs_record += f.wcs_CBM;
	}
	else if (winner == 3)
	{
		s.his_sum = s.evaluate(gg.gbm_implement);
		f.wcs_record += f.wcs_GBM;
	}
	else
		cout << "error" << endl;
	if (winner == 1 || winner == 2 || winner == 3)
	{
		for (i = 1; i<16; i++)
		{
			s.FTE_his[i] += s.flow_count[i];
		}
	}
	/*****************the second request*****************/
	cout << endl;
	cout << "the second request:" << endl;
	//req2 propose()
	if (winner == 1)
		for (i = 1; i <= 15; i++)
		{
			rack[i] = f.rack[i];
			all_links_bw[i] = f.all_links_bw[i];
		}
	else if (winner==2)
		for (i = 1; i <= 15; i++)
		{
			rack[i] = c.rack[i];
			all_links_bw[i] = c.all_links_bw[i];
		}
	else
		for (i = 1; i <= 15; i++)
		{
			rack[i] = gg.gbm_rack[i];
			all_links_bw[i] = gg.gbm_all_link_bw[i];
		}
	
	for (i = 1; i <= 15; i++)
		cout << rack[i] << " ";
	cout << endl;
	
	f.propose(req2, all_links_bw, rack);
	c.propose(req2, all_links_bw, rack);
	gg.propose(req2, all_links_bw, rack);
	f.req_num++;

	//req2 evaluate()
	test(req2,f,c,gg,s);
	for(i=0;i<=2;i++)
	{
		for(j=0;j<=3;j++)
			printf("%10.3f ",test_record[i][j]);
		printf("\n");
	}
	
	//voting methods
	Table tt2(test_record);
	winner = vv.Voting(tt2, 2);
	cout << "the winner is: " << winner << endl;

	//data update
	if (winner == 1)
	{
		s.his_sum = s.evaluate(f.implement);
		f.wcs_record += f.wcs_FTM;
	}
	else if (winner == 2)
	{
		s.his_sum = s.evaluate(c.implement);
		f.wcs_record += f.wcs_CBM;
	}
	else if (winner == 3)
	{
		s.his_sum = s.evaluate(gg.gbm_implement);
		f.wcs_record += f.wcs_GBM;
	}
	else
		cout << "error" << endl;
	if (winner == 1 || winner == 2 || winner == 3)
	{
		for (i = 1; i<16; i++)
		{
			s.FTE_his[i] += s.flow_count[i];
		}
	}

	/*****************the third request*****************/
	cout << endl;
	cout << "the third request:" << endl;
	//req3 propose()
	if (winner == 1)
		for (i = 1; i <= 15; i++)
		{
			rack[i] = f.rack[i];
			all_links_bw[i] = f.all_links_bw[i];
		}
	else if (winner == 2)
		for (i = 1; i <= 15; i++)
		{
			rack[i] = c.rack[i];
			all_links_bw[i] = c.all_links_bw[i];
		}
	else
		for (i = 1; i <= 15; i++)
		{
			rack[i] = gg.gbm_rack[i];
			all_links_bw[i] = gg.gbm_all_link_bw[i];
		}
	
	f.propose(req3, all_links_bw, rack);
	c.propose(req3, all_links_bw, rack);
	gg.propose(req3, all_links_bw, rack);
	f.req_num++;
	
	test(req3, f, c, gg, s);
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 3; j++)
			printf("%10.3f ", test_record[i][j]);
		printf("\n");
	}

	//voting methods
	Table tt3(test_record);
	winner = vv.Voting(tt3, 2);
	cout << "the winner is: " << winner << endl;

	//data update
	if (winner == 1)
	{
		s.his_sum = s.evaluate(f.implement);
		f.wcs_record += f.wcs_FTM;
	}
	else if (winner == 2)
	{
		s.his_sum = s.evaluate(c.implement);
		f.wcs_record += f.wcs_CBM;
	}
	else if (winner == 3)
	{
		s.his_sum = s.evaluate(gg.gbm_implement);
		f.wcs_record += f.wcs_GBM;
	}
	else
		cout << "error" << endl;
	if (winner == 1 || winner == 2 || winner == 3)
	{
		for (i = 1; i<16; i++)
		{
			s.FTE_his[i] += s.flow_count[i];
		}
	}

	getchar();
	return 0;
}
