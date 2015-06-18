#pragma once
#include"common.h"
#define P 3   // P is the number of proposals
#define M 4   // M is the number of modules
#define None 0;


//table[3][4] ,the 4 kinds vuale and 3 proposals
//4:(wcs,cb(core bandwidth),ab(all bandwidth),ft(flow table entry))

struct Table{
 vector<vector<float> > table; //in our experiment:table[3][4],3 proposals,4 modules
 
 Table(){ ; }
  Table(float tmp[P][M]) 
  {  table.resize(P*M);
	  for(int i=0;i<P;i++)
		for(int j=0;j<M;j++)
         table[i].push_back(tmp[i][j]);
  }

  //scenario 3
  vector<vector<int> > table2;
  Table(int tmp[P][M]){
	   table2.resize(P*M);
	  for(int i=0;i<P;i++)
		for(int j=0;j<M;j++)
         table2[i].push_back(tmp[i][j]);
  }
   // void insert(float value);//make_table
  // need the information:which proposal,which module,in order to insert into the right palce of table
};

class Vote{
public:
	Table tb;
	float finalVotes[P];//p1,p2,p3
	float TotalVotes[M];//FTM,CBM,GBM,SRM
	int flag;//
	int wins[P+1][P+1];  //scenario 3
	int finalwin[P+1];
	int winner;
	Vote(){;}

	int Voting(Table t,int k){
	if(k==2)
		return Cumulative_Voting(t);//Scenario 2
	else if(k==3)
		return Condorcet_Voting(t);//Scenario 3
	else
	{
		cout<<"the k is the wrong number,make sure k is 2 or 3"<<endl;
		return 0;
	}

	}

//Scenario 2
   int Cumulative_Voting(Table t){
	tb.table=t.table;
	//initialization
	memset(finalVotes,0,sizeof(finalVotes));
	memset(TotalVotes,0,sizeof(TotalVotes));
	winner=0;
	
	// count totalVotes
	int i=0;
	while(i<M){
	for(int j=0;j<M;j++)
	{
		TotalVotes[i]=tb.table[0][j]+tb.table[1][j]+tb.table[2][j];
		i++;
	}}
	
	// count votes for every proposal
	for(int k=0;k<P;k++)
	for(int m=0;m<M;m++)
	{
		finalVotes[k]+=tb.table[k][m]/TotalVotes[m];
	}

	//select winner
	float sum=0;
	flag=0;
	for(int i=0;i<P;i++)
	{
	 if(finalVotes[i]>sum) 
	 {sum=finalVotes[i];
	  winner=i+1;
	 }
	 else if(finalVotes[i]==sum) flag+=1;//there are two or more proposal having same votes
     }
	 /*
	if(flag>=1)
		{ cout<<"there is not only one winner,try another Scenario or vote again"<<endl;
	     // return None;
	    return winner;// the first one winner
	   }
	else  */
    return winner;
}

//Scenario 3
   int Condorcet_Voting(Table t){
    tb.table2=t.table2;
	//initialization
	winner=0;
	memset(wins,0,sizeof(wins));
	
	// count pairwise Votes
	for(int k=0;k<P-1;k++)
    for(int m=0;m<M;m++)
		for(int j=1;j+k<P;j++)
			wins[tb.table2[k][m]][tb.table2[k+j][m]]+=1;
	
	// count votes for every proposal
	memset(finalwin,0,sizeof(finalwin));
	for(int k=0;k<P+1;k++)
		for(int i=0;i<P+1;i++)
	{
      finalwin[k]+=wins[k][i];
	}

	//select winner
	int sum=0;
	flag=0;
	for(int i=1;i<P+1;i++)
	{
	 if(finalwin[i]>sum)
	  {
		 sum=finalwin[i];
		 winner=i; 
	  }
	 else if(finalwin[i]==sum) flag+=1;//there are two or more proposal having same votes
     }
	/* 
	if(flag>=1)
	{ cout<<"there is not only one winner,try another Scenario or vote again"<<endl;
	 // return None;
	 return winner;// the first one winner
	}
	else */
    return winner;
}

};