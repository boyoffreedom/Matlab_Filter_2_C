#include <stdio.h>
#include "filter.h"

#define LENGTH 5001
int main()
{
    FILE *data,*dout;
    int i;
    float in_data[LENGTH],filter_out[LENGTH];
    struct IIR_Filter_State state1;
    if((data = fopen("lowpass_input.txt","r")) == NULL)         //打开测试数据文件
    {
        printf("lowpass_input.txt file does not exist!\n");     //文件打开失败
        if((data = fopen("lowpass_input.txt","w+")) == NULL)    //生成测试数据文件
        {
            printf("cannot create file lowpass_input.txt!\n");  //数据文件生成失败，退出
            getchar();
        }
        else                                                    //文件打开成功
        {
            fclose(data);
            getchar();
        }
        return 0;
    }
    if((dout = fopen("lowpass_out.txt","w+"))==NULL)
    {
        printf("Cannot open lowpass_out.txt!\n");
        fclose(dout);
        return 0;
    }

                                                                //读取数据
    for(i = 0; i < LENGTH;i++)
    {
        fscanf(data,"%f ",&in_data[i]);
    }
    printf("Data read success!\n");
    //滤波进行时
    //初始化低通滤波器状态结构体
    for(i = 0; i < FILTER_ORDER+1;i++)
    {
        state1.x[i] = 0;
        state1.y[i] = 0;
    }
    //iir滤波函数
    for(i = 0; i < LENGTH;i++)
    {
        filter_out[i] = iir_filter(&state1,IIR_A,IIR_B,in_data[i]);
    }
    printf("Lowpass Filter compute finish!\n");
    //保存滤波结果
    for(i = 0; i < LENGTH;i++)
    {
        fprintf(dout,"%f ",filter_out[i]);
    }
    printf("Save finish!\n");
                                                                //保存滤波结果
                                                                //关闭文件
    fclose(data);
    fclose(dout);
    //getchar();
    return 0;
}

float iir_filter(struct IIR_Filter_State* filter_state, float* a, float* b, float x_0)
{
	int i;
	float tmp = 0;

     //x值更新
	for(i = FILTER_ORDER; i > 0 ;i--)
    {
        filter_state->x[i] = filter_state->x[i-1];
    }
	filter_state->x[0] = x_0;
	//更新y
	for(i = FILTER_ORDER; i > 0 ;i--)
    {
        filter_state->y[i] = filter_state->y[i-1];
    }

	//计算输出滤波数值
	for(i = 0; i <= FILTER_ORDER;i++)
    {
        tmp += (b[i]* filter_state->x[i]);
    }
    for(i = 1; i <= FILTER_ORDER;i++)
    {
        tmp -= (a[i]* filter_state->y[i]);
    }
    tmp /= a[0];

	filter_state->y[0] = tmp;

	return tmp;
}
