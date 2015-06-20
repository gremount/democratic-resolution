#pragma once
#include"common.h"
#define P 3   // P is the number of proposals
#define M 4   // M is the number of modules
#define None 0;

class Vote{
public:
	//Table tb;
	float finalVotes[P];//p1,p2,p3
	float TotalVotes[M];//FTM,CBM,GBM,SRM
	int flag;//
	int wins[P + 1][P + 1];  //scenario 3
	int finalwin[P + 1];
	int winner;
	Vote(){ ; }

	//Scenario 2
	int Voting(float table[P][M], int k){
		//initialization
		memset(finalVotes, 0, sizeof(finalVotes));
		memset(TotalVotes, 0, sizeof(TotalVotes));
		winner = 0;

		/////convert 0 to 1
		for (int k = 0; k<P; k++)
			for (int m = 0; m<M; m++)
			{
				if (table[k][m] == 0)
					table[k][m] = 1;
			}
		///// ½«CB  GB  FTEÈ¡µ¹Êý
		for (int k = 0; k<P; k++)
			for (int m = 1; m<M; m++)
				table[k][m] = 1 / table[k][m];

		// count totalVotes
		int i = 0;
		while (i<M){
			for (int j = 0; j<M; j++)
			{
				TotalVotes[i] = table[0][j] + table[1][j] + table[2][j];
				i++;
			}
		}

		// count votes for every proposal
		for (int k = 0; k<P; k++)
			for (int m = 0; m<M; m++)
			{
				finalVotes[k] += table[k][m] / TotalVotes[m];
			}

		//select winner
		float sum = 0;
		flag = 0;
		for (int i = 0; i<P; i++)
		{
			if (finalVotes[i]>sum)
			{
				sum = finalVotes[i];
				winner = i + 1;
			}
			else if (finalVotes[i] == sum) flag += 1;//there are two or more proposal having same votes
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
	int Voting(int table[P][M], int k){
		//initialization
		winner = 0;
		memset(wins, 0, sizeof(wins));

		// count pairwise Votes
		for (int k = 0; k<P - 1; k++)
			for (int m = 0; m<M; m++)
				for (int j = 1; j + k<P; j++)
					wins[table[k][m]][table[k + j][m]] += 1;

		// count votes for every proposal
		memset(finalwin, 0, sizeof(finalwin));
		for (int k = 0; k<P + 1; k++)
			for (int i = 0; i<P + 1; i++)
			{
				finalwin[k] += wins[k][i];
			}

		//select winner
		int sum = 0;
		flag = 0;
		for (int i = 1; i<P + 1; i++)
		{
			if (finalwin[i]>sum)
			{
				sum = finalwin[i];
				winner = i;
			}
			else if (finalwin[i] == sum) flag += 1;//there are two or more proposal having same votes
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