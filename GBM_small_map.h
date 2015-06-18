#pragma once
#include "resources.h"
#include <math.h>
#include <functional>

class GBM{
    public:
    int layer_num = 4;
    int rack_num = 8;
    int block_num[15];

    int flow_size[15];
    int gbm_implement[8];
    int gbm_link_bw[15];
    int gbm_rack[8];
    int subnet_vmnum[15];
    GBM(){;}

    void implement(int req_num, int x, int y)
    {
        if(x != layer_num -1)
        {
            int step = pow(2,layer_num -1 - x);
            multimap<int,int,greater<int> > sort_map;
            for(int k = (y+1)*2 - 1;k<(y+2)*2 -1;k++)
            {
                sort_map.insert(pair<int,int>(block_num[k],k));
            }
            multimap<int,int,greater<int> >::iterator it;
            for(it = sort_map.begin();it!= sort_map.end();it++)
            {
                if(req_num > it->first)
                {
                    req_num -= it->first;
                    for(int i = (y+1)*step -1;i <(y +2)*step -1 - step /2;i++)
                    {
                        gbm_implement[i-7] = block_num[i];
                    }
                }
                else
                {
                    int a = x + 1;
                    int b = it->second;
                    implement(req_num,a,b);
                        break;
                }
            }
        }
        else
        {
            gbm_implement[y - 7] = req_num;
        }
    }

    void propose(pair<int, int> req, int link_bw[], int rack[])
    {

        for(int i = 0;i < 8;i++)
        {
            gbm_implement[i] = 0;
            gbm_rack[i] = rack[i];
        }
        for(int i = 0;i <15;i++)
        {
            gbm_link_bw[i] = link_bw[i];
            flow_size[i] = 0;
        }
        ///initialize

        int bw = req.second;
        int vm_num = req.first;

        for(int i = 0;i<rack_num;i++)
        {
            block_num[i+7] = 16 - rack[i];
        }

        for(int i = 15 - rack_num -1;i >= 0;i--)
        {
            block_num[i] = block_num[2*i+1] + block_num[2*i+2];
        }
		/*
        for(int i = 0;i<15;i++)
        {
            cout<<block_num[i]<<"  ";
        }
		*/
        int x,y;
        int room = 0;
        int begin_num = 14;
        int end_num = 14;
        for(int i = layer_num -1;i >= 0;i--)
        {
            int step = pow(2,i);
            begin_num = end_num;
            end_num = begin_num - step;
            for(int j = begin_num;j> end_num;j--)
            {
                if(block_num[j] >= vm_num && block_num[j] > room)
                {
                    room = block_num[j];
                    x=i;y=j;
                }
            }

            if(room >= vm_num)
                break;
        }
        if(room >= vm_num)
        {
            implement(vm_num,x,y);
            //for(int i = 0;i<8;i++)
              //  cout<<gbm_implement[i]<<"  ";

            for(int i = 0;i < rack_num;i++)
                gbm_rack[i] += gbm_implement[i];

            for(int i = 0;i<rack_num;i++)
            {
                subnet_vmnum[i+7] = gbm_implement[i];
            }

            for(int i = 15 - rack_num -1;i >= 0;i--)
            {
                subnet_vmnum[i] = subnet_vmnum[2*i+1] + subnet_vmnum[2*i+2];
            }

            for(int i = 1;i < 15;i++)
            {
                if(vm_num - subnet_vmnum[i] < subnet_vmnum[i])
                    flow_size[i] = bw * (vm_num - subnet_vmnum[i]);
                else
                    flow_size[i] = bw * subnet_vmnum[i];
            }
            for(int i = 1;i < 15;i++)
                gbm_link_bw[i] += flow_size[i];
        }

       // cout<<endl;
       // for(int i = 1;i < 15;i++)
           // cout<<gbm_link_bw[i]<<"  ";

    }
    int evaluate(int link_bw[])
	{
	    int bw_sum = 0;
	    int i;
	    for(i = 0;i<15;i++)
	    {
	        bw_sum =bw_sum + link_bw[i];
	    }
        return bw_sum;
	}
};
