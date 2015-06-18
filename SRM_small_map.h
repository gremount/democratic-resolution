#pragma once
#include "resources.h"

class SRM{
    public:
    SRM(){;}

    int n = 8;
    int evaluate(int implement[])
    {
        int flow_count[15];
        for(int i = 0;i<8;i++)
        {
            flow_count[i+7] = implement[i+8]*(implement[i+8
			] -1);
        }
        for(int i = 0;i<7;i++)
        {
            flow_count[i] = 0;
        }

        for(int i = 0;i<n;i++)
        {
            for(int j = i+1;j<n;j++)
            {
                int num = implement[i+8] * implement[j+8];
                int fi,fj;
                fi = (i+6)/2;
                fj = (j+6)/2;
                while(fi != fj)
                {
                    flow_count[fi] += num;
                    flow_count[fj] += num;
                    fi = (fi-1) /2;
                    fj = (fj - 1) / 2;
                }
                flow_count[fj] += num;
            }
        }
        int flow_sum =0;
        for(int i = 0;i < 15;i++)
        {
            flow_sum += flow_count[i];
            //cout<<flow_count[i]<<endl;
        }


        return flow_sum;
    }




};
