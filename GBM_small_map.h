#pragma once
#include "resources.h"
#include <math.h>
#include <functional>
class GBM{
    public:
    int layer_num;
    int rack_num;
    int joint_num;
    int layer_joint_num[4];

    int block_num[16];

    int gbm_implement[16];
    int gbm_rack[16];
    int gbm_link_bw[16];
    int gbm_all_link_bw[16];

    GBM(){
		layer_num = 4;
		rack_num = 8;
		joint_num = 15;
		layer_joint_num[0]=1;
		layer_joint_num[1]=2;
		layer_joint_num[2]=4;
		layer_joint_num[3]=8;
	}



    void imp(int req_num,int x,int y)
    {
        gbm_implement[y] = req_num;
        if(x != layer_num - 1)
        {
            if(block_num[2*y] > block_num[2*y+1])
            {
                if(block_num[2*y] < req_num)
                {
                    imp(block_num[2*y],x+1,2*y);
                    imp(req_num-block_num[2*y],x+1,2*y+1);
                }
                else
                {
                    imp(req_num,x+1,2*y);
                }

            }
            else
            {
                if(block_num[2*y+1] < req_num)
                {
                    imp(block_num[2*y+1],x+1,2*y+1);
                    imp(req_num-block_num[2*y+1],x+1,2*y);
                }
                else
                {
                    imp(req_num,x+1,2*y+1);
                }
            }
        }
    }





    void propose(pair<int, int> req, int all_link_bw[], int rack[])
    {
        for(int i = 0;i <= joint_num;i++)
        {
            gbm_implement[i] = 0;
            gbm_link_bw[i] = 0;
            gbm_all_link_bw[i] = all_link_bw[i];
            gbm_rack[i] = rack[i];
        }///initialize

        int req_num = req.first;
        int req_bw = req.second;


        for(int i = 8;i<= joint_num;i++)
        {
            block_num[i] = 16 - rack[i];
        }
        for(int i = 7; i >= 1;i--)
        {
            block_num[i] = block_num[2*i]+block_num[2*i+1];
        }
        block_num[0] = 0;

        int beginnum;
        int endnum = 15;
        int room = 0;
        int x,y;

        for(int i = 3;i >= 0;i--)
        {
            beginnum = endnum;
            endnum -= layer_joint_num[i];

            for(int j = beginnum;j > endnum;j--)
            {
                if(block_num[j] >= req_num )
                {
                    room = block_num[j];
                    x = i;
                    y = j;
					break;
                }
            }
        }
        if(room >= req_num)
        {
            //cout<<x<<" "<<y<<endl;
            imp(req_num,x,y);


            for(int i = 7;i>=1;i--)
                gbm_implement[i] = gbm_implement[2*i] + gbm_implement[2*i+1];

            for(int i = 1;i <= joint_num;i++)
            {
                if(gbm_implement[i] > req_num - gbm_implement[i])
                    gbm_link_bw[i] = req_bw*(req_num - gbm_implement[i]);
                else
                    gbm_link_bw[i] = req_bw*gbm_implement[i];

                gbm_all_link_bw[i] += gbm_link_bw[i];
                gbm_rack[i] += gbm_implement[i];

            }



        }
		/*
        cout<<"link_bw"<<endl;
        for(int i = 1;i <= joint_num;i++)
        {

            cout<<gbm_link_bw[i]<<"  ";
        }
        cout<<endl;

        cout<<"all_link_bw"<<endl;
        for(int i = 1;i <= joint_num;i++)
        {

            cout<<gbm_all_link_bw[i]<<"  ";
        }
        cout<<endl;

        cout<<"implement"<<endl;
        for(int i = 1;i <= joint_num;i++)
        {

            cout<<gbm_implement[i]<<"  ";
        }
        cout<<endl;

        cout<<"rack"<<endl;
        for(int i = 1;i <= joint_num;i++)
        {

            cout<<gbm_rack[i]<<"  ";
        }
        cout<<endl;
		*/
    }
    float evaluate(int all_link_bw[])
    {
        float aver;
        float sum = 0;
        for(int i =2;i<= 15;i++)
        {
			sum+= all_link_bw[i];
        }
        aver = sum / 14;
        return aver;
    }





};
