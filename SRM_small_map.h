#pragma once
#include "resources.h"

class SRM{
    public:
	int n;
    int FTE_his[16];
    int flow_count[16];
    int his_sum;
    int FTE_limit[16];
    SRM(){
		n=16;
		for(int i=0;i<=15;i++)
		{
			FTE_his[i]=0;
			FTE_limit[i]=9999;
		}
		his_sum=0;
	}

    float evaluate(int implement[])
    {

        for(int i = 8;i<16;i++)
        {
            flow_count[i] = implement[i]*(implement[i] -1);
        }
        for(int i = 0;i<8;i++)
        {
            flow_count[i] = 0;
        }

        for(int i = 8;i<n;i++)
        {
            for(int j = i+1;j<n;j++)
            {
                int num = implement[i] * implement[j]*2;
                int fi,fj;
                fi = (i)/2;
                fj = (j)/2;
                while(fi != fj)
                {
                    flow_count[fi] += num;
                    flow_count[fj] += num;
                    fi = fi /2;
                    fj = fj / 2;
                }
                flow_count[fj] += num;
            }
        }



        for(int i = 1;i < n;i++)
        {
            if(FTE_his[i]+flow_count[i]>FTE_limit[i])
                return 99999999;
        }
        int sum = 0;

        for(int i = 1; i< n;i++)
        {
            sum += flow_count[i];
        }

        return sum+his_sum;


    }




};
