#include <cstdint>
#include <cstdlib>
#include <ios>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
//#include <algorithm>
using namespace std;


//4 自定义函数
float getMIN(float a,float b)
{
    if(a>b)
        return b;
    else 
        return a;
}

float getMAX(float a,float b)
{
    if(a<b)
        return b;
    else 
        return a;
}

float getABS(float a)
{
    if(a<0)
        return -a;
    else 
        return a;
}

//2024.4.23
//length = 101 即 Length = 2*Rwindow+1
int getMedian(int * a,int length = 101)
{
    int median = 0;
    for (int i = 0; i < length - 1; i++)//冒泡排序
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
             if (a[j] > a[j + 1])
             {
                 int temp = a[j];
                 a[j] = a[j + 1];
                 a[j + 1] = temp;}}}
        return a[50];
}
//2024.4.26
int Not(int Num)
{
    if(Num)
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}


//2024.4.27 12-BITS UP-COUNTER

//2024.4.26

int binout0[12] = {0};
int * dec2bin0(int B)
{
        int r[12] = {0};
        int i, j = 0;
        //对十进制数进行除以二取余并以此存放到列表中
        for ( i = 0;B > 0; i++)
        {
            r[i] = B % 2;
            B = B / 2;
            j++;
        }
        //依次取出从列表的最后一位到第一位余数
        for (j=0;j <12 ; j++)
        {
            binout0[j] = r[j];
        }
        return binout0;
}
int binout[12] = {0};
int * dec2bin(int B)
{
        int r[12] = {0};
        int i, j = 0;
        //对十进制数进行除以二取余并以此存放到列表中
        for ( i = 0;B > 0; i++)
        {
            r[i] = B % 2;
            B = B / 2;
            j++;
        }
        //依次取出从列表的最后一位到第一位余数
        for (j=0;j <12 ; j++)
        {
            binout[j] = r[j];
        }
        return binout;
}
int upcount = 0;
int * upCounter()
{
    int *array=NULL;
    array = dec2bin0(upcount++);
    return array;
}

int downcount = 4095;
//2024.4.27 12-BITS DOWN-COUNTER
int * downCounter()
{
    int *array=NULL;
    array = dec2bin0(downcount--);
    return array;
}

//2024.4.26 WBG-SNG 随机数生成器
int WBGX_down[4096] = {0};
int * WBG_SNG_down(int B)
{
    int *array ;
    int W[12] = {0};
    int Wx[12] = {0};
    int * BN = dec2bin(B);
    /*//test1
    for(int u = 0 ;u<12;u++)
    {cout<<BN[u]<<endl;}
    //test1 end*/
    for(int i =0;i<4096;i++)
    {
        //int R = RNG_LD(2, i);
        array = downCounter();//12-bits RNs
        //array = RN();
        //cout<<R<<","<<bin2dec(array)<<endl;
        //step1 solve Wi
        W[0] = array[0];
        W[1] = Not(array[0])&array[1];
        W[2] = Not(array[0])&Not(array[1])&array[2];
        W[3] = Not(array[0])&Not(array[1])&Not(array[2])&array[3];
        W[4] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&array[4];
        W[5] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&array[5];
        W[6] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&array[6];
        W[7] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&array[7];
        W[8] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&array[8];
        W[9] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&array[9];
        W[10] =Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&Not(array[9])&array[10];
        W[11] =Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&Not(array[9])&Not(array[10])&array[11];
       
        //step2 solve Wxi
        for(int j = 0;j<12;j++)
        { Wx[j] = W[j] & BN[11-j]; }
       
        //step3 solve SNX
        WBGX_down[i] = Wx[0]|Wx[1]|Wx[2]|Wx[3]|Wx[4]|Wx[5]|Wx[6]|Wx[7]|Wx[8]|Wx[9]|Wx[10]|Wx[11];
    }
    return WBGX_down;
}


//2024.5.1 CAPE实现
int WBGX_up[4096] = {0};
int * WBG_SNG_up(int B)
{
    int *array ;
    int W[12] = {0};
    int Wx[12] = {0};
    int * BN = dec2bin(B);
    /*//test1
    for(int u = 0 ;u<12;u++)
    {cout<<BN[u]<<endl;}
    //test1 end*/
    for(int i =0;i<4096;i++)
    {
        //int R = RNG_LD(2, i);
        array = upCounter();//12-bits RNs
        //array = RN();
        //cout<<R<<","<<bin2dec(array)<<endl;
        //step1 solve Wi
        W[0] = array[0];
        W[1] = Not(array[0])&array[1];
        W[2] = Not(array[0])&Not(array[1])&array[2];
        W[3] = Not(array[0])&Not(array[1])&Not(array[2])&array[3];
        W[4] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&array[4];
        W[5] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&array[5];
        W[6] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&array[6];
        W[7] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&array[7];
        W[8] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&array[8];
        W[9] = Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&array[9];
        W[10] =Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&Not(array[9])&array[10];
        W[11] =Not(array[0])&Not(array[1])&Not(array[2])&Not(array[3])&Not(array[4])&Not(array[5])&Not(array[6])&Not(array[7])&Not(array[8])&Not(array[9])&Not(array[10])&array[11];
       
        //step2 solve Wxi
        for(int j = 0;j<12;j++)
        { Wx[j] = W[j] & BN[11-j]; }
       
        //step3 solve SNX
        WBGX_up[i] = Wx[0]|Wx[1]|Wx[2]|Wx[3]|Wx[4]|Wx[5]|Wx[6]|Wx[7]|Wx[8]|Wx[9]|Wx[10]|Wx[11];
    }
    return WBGX_up;
}


//参数定义
/*
//12位量化
const int coe[31] = {
592,576,544,528,560,656,752,736,512,176,0,288,1184,2480,3616,4080,3616,2480,1184,288,0,176,512,736,752,656,560,528,	544,576,592};
*/

//8位量化
const int coe[31] = {70,68,66,64,64,67,70,64,45,18,0,14,70,152,226,256,226,152,70,14,0,18,45,64,70,67,64,64,66,68,70};
//变量初始化
//static int seed1[12]={1,0,1,1,1,0,1,0,1,0,1,0};
static int seed1[12]={0,0,0,0,0,0,0,0,0,0,0,1};
static int seed2[12]={1,0,0,1,0,0,0,0,0,0,0,0};
static int seed3[12]={0,0,0,0,0,1,0,0,0,0,0,0};

int scX1[4096]={0};
int scX2[4096]={0};
int scX3[4096]={0};
int output[4096]={0};
int ADD_result[4096]={0};
int result_coe[31] = {0};

//二进制转十进制 2024.1.28
int bin2dec(int * bin)
{
    int output_bin2dec = bin[0]+bin[1]*2+bin[2]*4+bin[3]*8+bin[4]*16+bin[5]*32+bin[6]*64+bin[7]*128+bin[8]*256+bin[9]*512+bin[10]*1024+bin[11]*2048;
    return output_bin2dec;
}

//随机序列转十进制 2024.1.28
int sc2dec(int * scX)
{
    int output_sc2dec = 0;
    for(int i=0;i<4096;i++)
    {
        if(scX[i]==1)
            output_sc2dec = output_sc2dec+1;
    }
    return output_sc2dec;
}

//数组求和 2024.4.26
int arraySum(int * array,int length)
{
    int res = 0;
    for(int i = 0;i<length;i++)
    {
        res = res + array[i];
    }
    return res;
}
//2024.1.27 SC部分模块

//2024.4.26
//添加全零反馈的LFSR随机数源 共4096个状态
int zeroNum = 0;
int * RN_Generator_zeroFB()
{
    int output_RN = 0;
    int new_bits = 0;
    int zeroFB = 1;
    zeroFB = arraySum(seed1, 12);
    if(!zeroFB && zeroNum == 0)
    {
        zeroNum++;
        return seed1;
    }
    else if(!zeroFB && zeroNum == 1)
    {
        seed1[0] = 1;
    }
    new_bits = seed1[0]^seed1[6]^seed1[8]^seed1[11];
    output_RN  = seed1[11];
    seed1[11] = seed1[10];
    seed1[10] = seed1[9];
    seed1[9] = seed1[8];
    seed1[8] = seed1[7];
    seed1[7] = seed1[6];
    seed1[6] = seed1[5];
    seed1[5] = seed1[4];
    seed1[4] = seed1[3];
    seed1[3] = seed1[2];
    seed1[2] = seed1[1];
    seed1[1] = seed1[0];
    seed1[0] = new_bits;
    zeroNum = 0;
    return seed1;
}

//LFSR随机数源
int * RN_Generator1()
{
    int output_RN = 0;
    int new_bits = 0;
    new_bits = seed1[0]^seed1[6]^seed1[8]^seed1[11];
    output_RN  = seed1[11];
    seed1[11] = seed1[10];
    seed1[10] = seed1[9];
    seed1[9] = seed1[8];
    seed1[8] = seed1[7];
    seed1[7] = seed1[6];
    seed1[6] = seed1[5];
    seed1[5] = seed1[4];
    seed1[4] = seed1[3];
    seed1[3] = seed1[2];
    seed1[2] = seed1[1];
    seed1[1] = seed1[0];
    seed1[0] = new_bits;
    return seed1;
}

//循环右移bits位
int * ArrayShift( int *a, int n, int m )
{
	int i,j,temp;
    for(i=0;i<m;i++)
    {
        temp=a[n-1];
        for(j=n-2;j>=0;j--)
        {
            a[j+1]=a[j];
        }
        a[0]=temp;
    }
    return a;
}

int * RN_Generator2()
{

    int output_RN = 0;
    int new_bits = 0;
    // m sequence 8/6/5/4

        new_bits = seed2[0]^seed2[6]^seed2[8]^seed2[11];
        output_RN  = seed2[11];
        seed2[11] = seed2[10];
        seed2[10] = seed2[9];
        seed2[9] = seed2[8];
        seed2[8] = seed2[7];
        seed2[7] = seed2[6];
        seed2[6] = seed2[5];
        seed2[5] = seed2[4];
        seed2[4] = seed2[3];
        seed2[3] = seed2[2];
        seed2[2] = seed2[1];
        seed2[1] = seed2[0];
        seed2[0] = new_bits;

    return seed2;

}

int * RN_Generator3()
{

    int output_RN = 0;
    int new_bits = 0;
    // m sequence 8/6/5/4

        new_bits = seed3[0]^seed3[6]^seed3[8]^seed3[11];
        output_RN  = seed3[11];
        seed3[11] = seed3[10];
        seed3[10] = seed3[9];
        seed3[9] = seed3[8];
        seed3[8] = seed3[7];
        seed3[7] = seed3[6];
        seed3[6] = seed3[5];
        seed3[5] = seed3[4];
        seed3[4] = seed3[3];
        seed3[3] = seed3[2];
        seed3[2] = seed3[1];
        seed3[1] = seed3[0];
        seed3[0] = new_bits;

    return seed3;

}


//随机数生成器
int * SN_Generator1(int B)
{

    int R=0;
    int * array;

    for(int i =0;i<4096;i++)
    {

        array = RN_Generator1();
        //array = ArrayShift(array, 12, 6);
        R = bin2dec(array);
        if(R<B)
            scX1[i] = 1;
        else
            scX1[i] = 0;
    }
    return scX1;
}

int * SN_Generator2(int B)
{
    int R=0;
    int * array;

    for(int i =0;i<4096;i++)
    {

        array = RN_Generator2();
        R = bin2dec(array);
        if(R<B)
            scX2[i] = 1;
        else
            scX2[i] = 0;
    }
    return scX2;
}

int * SN_Generator3(int B)
{

    int R=0;
    int * array;

    for(int i =0;i<4096;i++)
    {

        array = RN_Generator3();
        //array = ArrayShift(array, 12, 11);
        R = bin2dec(array);
        if(R<B)
            scX3[i] = 1;
        else
            scX3[i] = 0;
    }
    return scX3;
}


//与门乘法器，输入不相关，SCC=0
int * MUL(int*op1,int*op2)
{
    for(int i =0;i<4096;i++)
    {
        output[i] = op1[i]&op2[i];
    }
    return output;
}


//复用加法器，输入数据SCC任意，地址端与输入数据端不相关
int * ADD(int * op1,int * op2)
{
    int * control = WBG_SNG_down(2048);//概率为0.5的随机码流
    //control = ArrayShift(control, 12, 11);
    for(int i = 0;i<4096;i++)
    {
        if(control[i]==0)
            ADD_result[i] = op1[i];
        else if(control[i]==1)
            ADD_result[i] = op2[i];
    }
    return ADD_result;
}


//2024.1.29 coe参数处理  共31个   coe转随机码流SN作为乘数
int * coe_process(const int coe)
{
    int * coe_sc = SN_Generator1(coe);
    return coe_sc;
}


//2024.1.29  将十进制ECG信号转为4096位随机码流
int * ecg_process2(int ecg_data_input)
{
    int * result_ecg = SN_Generator2(ecg_data_input);
    return result_ecg;
}
//2024.1.29  同上，将十进制ECG信号转为4096位随机码流，但两组码流不相关，即SCC=0
int * ecg_process3(int ecg_data_input)
{
    int * result_ecg = SN_Generator2(ecg_data_input);
    return result_ecg;
}

//2023.12.30  FIR
//2024.1.29 update 1.0
void Fir_Test(int Input,int *LowPass)
{

    int data_buffer[31] ={};
    int a = 1;
    int * p = &a;
	int *result = p;
	int *temp = p;
    int *temp0 = p;

	for (int i = 30; i > 0; i--)
	{
		data_buffer[i] = data_buffer[i-1];
        int * coe_1 = coe_process(coe[i]);
        
        int * data_sc = ecg_process2(data_buffer[i]);
        temp = MUL(data_sc,coe_1);

        result = ADD(result, temp);
	}

    int * input_sc = ecg_process3(Input);
	data_buffer[0] = sc2dec(input_sc);

    temp0 = MUL(input_sc, coe_process(coe[0]));
    result = ADD(result, temp0);

    int output = sc2dec(result);
	*LowPass = output;
}


//2024.1.30 update 2.0
int data_buffer[31] = { 0 }; 
void Fir_Test_new(int Input,int *LowPass)
{
    int a = 1;
    int * p = &a;

    int result_fir = 0;
    int *temp = p;
    int *mul_sc= p;
    int mul_buffer[31] = { 0 };

    //先计算N+1次乘法
    for(int i = 0;i < 31; i++ )
    {
        int * coe_1 = coe_process(coe[i]);
        int * data_sc = ecg_process2(data_buffer[i]);
        temp = MUL(data_sc,coe_1);
        mul_buffer[i] = sc2dec(temp);
    }

    //再计算N次加法
    for(int k = 0;k<31;k++)
    {
        result_fir = result_fir + mul_buffer[k];
    }

    //更新数据
    for(int j = 30;j>0;j--)
    {
        data_buffer[j] = data_buffer[j-1];
    }

    data_buffer[0] = Input;
    *LowPass = result_fir;
}



//2024.2.6 共享随机数源测试用的SNG函数 测试函数不可用于ECG信号处理
//SHIFT_BITS 即共享随机数源所移位数 范围是0~11
int SN1[4096]={0};
int SN2[4096]={0};
static int seedT1[12]={1,0,1,1,1,0,1,0,1,0,1,0};
static int seed1T[12]={1,0,1,1,1,0,1,0,1,0,1,0};

int * RNG1_T()
{
    int output_RN = 0;
    int new_bits = 0;
    // m sequence 8/6/5/4
    // m sequence 12/6/4/1
    new_bits = seedT1[0]^seedT1[6]^seedT1[8]^seedT1[11];
    output_RN  = seedT1[11];
    seedT1[11] = seedT1[10];
    seedT1[10] = seedT1[9];
    seedT1[9] = seedT1[8];
    seedT1[8] = seedT1[7];
    seedT1[7] = seedT1[6];
    seedT1[6] = seedT1[5];
    seedT1[5] = seedT1[4];
    seedT1[4] = seedT1[3];
    seedT1[3] = seedT1[2];
    seedT1[2] = seedT1[1];
    seedT1[1] = seedT1[0];
    seedT1[0] = new_bits;
    return seedT1;
}

int * RNG2_T()
{
    int output_RN = 0;
    int new_bits = 0;
    // m sequence 8/6/5/4
    // m sequence 12/6/4/1
    new_bits = seed1T[0]^seed1T[6]^seed1T[8]^seed1T[11];
    output_RN  = seed1T[11];
    seed1T[11] = seed1T[10];
    seed1T[10] = seed1T[9];
    seed1T[9] = seed1T[8];
    seed1T[8] = seed1T[7];
    seed1T[7] = seed1T[6];
    seed1T[6] = seed1T[5];
    seed1T[5] = seed1T[4];
    seed1T[4] = seed1T[3];
    seed1T[3] = seed1T[2];
    seed1T[2] = seed1T[1];
    seed1T[1] = seed1T[0];
    seed1T[0] = new_bits;
    return seed1T;
}


int * SNG1_T(int B,int SHIFT_BITS){
    int R=0;
    int * array;
    for(int i =0;i<4096;i++)
    {
        array = RNG1_T();
        array = ArrayShift(array, 12, SHIFT_BITS);
        R = bin2dec(array);
        //cout<<R<<endl;
        if(R<B)
            SN1[i] = 1;
        else
            SN1[i] = 0;
    }
    return SN1;
}

int * SNG2_T(int B,int SHIFT_BITS){
    int R=0;
    int * array;
    for(int i =0;i<4096;i++)
    {
        array = RNG2_T();
        array = ArrayShift(array, 12, SHIFT_BITS);
        R = bin2dec(array);
        if(R<B)
            SN2[i] = 1;
        else
            SN2[i] = 0;}
    return SN2;
}

//随机码流转概率 2024.2.6
float sn2prob(int *sn)
{
    float counter = 0;
    for(int i=0;i<4096;i++)
    {
        if(sn[i]==1)
            counter=counter+1;
    }
    counter=counter/4096;
    return counter;
}

float sn2prob12(int *sn)
{
    float counter = 0;
    for(int i=0;i<12;i++)
    {
        if(sn[i]==1)
            counter=counter+1;
    }
    counter=counter/12;
    return counter;
}
//计算两组码流之间的随机相关性SCC 2024.2.6
float getSCC(int * snx,int * sny)
{
    float SCC = 0;
    int xandy[4096]={0};

    for(int i=0;i<4096;i++)
    {
        xandy[i] = snx[i]&sny[i];
    }

    float op1 = sn2prob(snx);
    float op2 = sn2prob(sny);

    float flag1 = op1*op2;// Px * Py
    float flag2 = sn2prob(xandy);  //Px&y

    //公式（2.4）
    if(flag1 < flag2)
        {
            if((getMIN(op1,op2)-flag1)!=0)
                SCC = (flag2-flag1)/(getMIN(op1,op2)-flag1);
            else
                SCC = 0;
        }
    else
        {
            if(( flag1-getMAX((op1+op2-1),0)  )!=0)
                SCC = (flag2-flag1)/( flag1-getMAX((op1+op2-1),0)  );
            else
                SCC = 0;
        }

return SCC;
}


float getSCC12(int * snx,int * sny)
{
    float SCC = 0;
    int xandy[12]={0};

    for(int i=0;i<12;i++)
    {
        xandy[i] = snx[i]&sny[i];
    }

    float op1 = sn2prob12(snx);
    float op2 = sn2prob12(sny);

    float flag1 = op1*op2;// Px * Py
    float flag2 = sn2prob12(xandy);  //Px&y

    //公式（2.4）
    if(flag1 < flag2)
        {
            if((getMIN(op1,op2)-flag1)!=0)
                SCC = (flag2-flag1)/(getMIN(op1,op2)-flag1);
            else
                SCC = 0;
        }
    else
        {
            if(( flag1-getMAX((op1+op2-1),0)  )!=0)
                SCC = (flag2-flag1)/( flag1-getMAX((op1+op2-1),0)  );
            else
                SCC = 0;
        }

return SCC;
}
//*****************************************************************************************
//Halton序列实现 2024.2.11
double RadicalInverse(int Base, int i)
{
	double Digit, Radical, Inverse;
	Digit = Radical = 1.0 / (double) Base;
	Inverse = 0.0;
	while(i){
		Inverse += Digit * (double) (i % Base);
		Digit *= Radical;
		i /= Base;
	}
	return Inverse;
}
double Halton(int Dimension, int Index)
{
	return RadicalInverse(Dimension, Index);
}

//2024.2.11 基于Halton低差异序列的改写
int RNG_LD(int D,int I)
{
    return int(Halton(D, I)*4096);
}

//2024.2.11 基于Halton低差异序列的改写
int scX1_LD[4096]={0};
int * SN_Generator1_LD(int B)
{

    int R=0;
    int * array;

    for(int i =0;i<4096;i++)
    {

        //array = RN_Generator1();
        //array = ArrayShift(array, 12, 6);
        //R = bin2dec(array);
        R = RNG_LD(2,i);
        if(R<B)
            scX1_LD[i] = 1;
        else
            scX1_LD[i] = 0;
    }
    return scX1_LD;
}

//2024.2.11 基于Halton低差异序列的改写
int * ecg_process_LD(int ecg_data_input)
{
    int * result_ecg = SN_Generator1_LD(ecg_data_input);
    return result_ecg;
}

//2024.2.11 coe参数处理  共31个  基于Halton低差异序列的改写
int * coe_process_LD(const int coe)
{
    int * coe_sc = SN_Generator3(coe);
    return coe_sc;
}

//2024.2.11  基于Halton低差异序列的改写
int data_buffer_LD[31] = { 0 };
void Fir_Test_new_LD(int Input,int *LowPass)
{
    int a = 1;
    int * p = &a;

    int result_fir = 0;
    int *temp = p;
    int *mul_sc= p;
    int output = 0;
    int mul_buffer[31] = { 0 };

    //先计算N+1次乘法
    for(int i = 0;i < 31; i++ )
    {
        int * coe_1 = coe_process_LD(coe[i]);
        int * data_sc = ecg_process_LD(data_buffer_LD[i]);
        temp = MUL(data_sc,coe_1);
        mul_buffer[i] = sc2dec(temp);
    }

    //再计算N次加法
    for(int k = 0;k<31;k++)
    {
        //mul_sc = ecg_process_SB(mul_buffer[k]);
        result_fir = result_fir + mul_buffer[k];

    }

    //更新数据
    for(int j = 30;j>0;j--)
    {
        data_buffer_LD[j] = data_buffer_LD[j-1];
    }

    data_buffer_LD[0] = Input;
    output = result_fir;
    *LowPass = output;
}
//*************************************************************************************************


//2024.4.10  新的移位共享LFSR实现

//2024.1.29 coe参数处理  共31个   coe转随机码流SN作为乘数
int * coe_process_new(const int coe)
{
    int * coe_sc = SNG1_T(coe,0);
    return coe_sc;
}


//2024.1.29  将十进制ECG信号转为4096位随机码流
int * ecg_process2_new(int ecg_data_input)
{
    int * result_ecg = SN_Generator3(ecg_data_input);
    return result_ecg;
}
//2024.1.29  同上，将十进制ECG信号转为4096位随机码流，但两组码流不相关，即SCC=0
int * ecg_process3_new(int ecg_data_input)
{
    int * result_ecg = SNG2_T(ecg_data_input,11);
    return result_ecg;
}


int data_buffer_CEPT[31] = { 0 };
void Fir_Test_new_LFSR(int Input,int *LowPass)
{
    int a = 1;
    int * p = &a;

    int result_fir = 0;
    int *temp = p;
    int *mul_sc= p;
    int output = 0;
    int mul_buffer[31] = { 0 };

    //先计算乘法
    for(int i = 0;i < 31; i++ )
    {
        int * coe_1 = coe_process_new(coe[i]);
        int * data_sc = ecg_process2_new(data_buffer_CEPT[i]);//7
        temp = MUL(data_sc,coe_1);
        mul_buffer[i] = sc2dec(temp);
    }

    //再计算N次加法
    for(int k = 0;k<31;k++)
    {
        //mul_sc = ecg_process_SB(mul_buffer[k]);
        result_fir = result_fir + mul_buffer[k];

    }


    //更新数据
    for(int j = 30;j>0;j--)
    {
        data_buffer_CEPT[j] = data_buffer_CEPT[j-1];
    }

    data_buffer_CEPT[0] = Input;
    output = result_fir;
    *LowPass = output;
}


//传统二进制滤波 2024.2.14  
const int coe_TR[31] = {
		849,-701,-2758,-3860,-1168,6350,14087,
		12595,-4649,-31377,-46117,-23101,48447,
		150680,241671,278103,241671,150680,48447,
		-23101,-46117,-31377,-4649,12595,14087,
		6350,-1168,-3860,-2758,-701,849};

void Fir_Test_TR(int Input,int *LowPass)
{
	static int data_buffer[31] = {0};
	int result = 0;
	for (int i = 31 - 1; i > 0; i--)
	{
		data_buffer[i] = data_buffer[i - 1];
		result += data_buffer[i] * coe_TR[i];
	}

	data_buffer[0] = Input;
	result += data_buffer[0] * coe_TR[0];

	*LowPass = result;
}


//2024.5.6  递减计数器作SNG 实现CAPE乘法
int SNout[4096] = {0};
int * downC(int BN)
{
    for(int i = 0;i < BN ;i++)
    {
        SNout[i] = 1;
    }
    return SNout;
}

int MulForCAPE(int*op1,int*op2,int clk)
{
    for(int i =0;i<clk;i++)
    {
        output[i] = op1[i]&op2[i];
    }
    int a = arraySum(output, 4096);
    int out = a*4096;
    return out;
}

int main(void)
{
 
 /*
	int out;
    // 逐词读取，按照空格进行分隔
    ofstream ofs; 
    ifstream fin("test_12bit_ecg.txt");
    //ifstream fin("11.txt");
    ofs.open("INDENP_LFSR_RESULT.txt",ios::out);
    int s;
    int data[3604];
    int i=0;
// 移位共享LFSR 3、7、11  最好的是7和11
    while(fin>>s)
    {
    	data[i] = s;
        //cout<<i<<endl;
    	Fir_Test_new(data[i],&out);
        ofs <<(out)<< endl;  //endl用于换行
        //printf("%d\n",data[i]);
        //printf("%d\n",out);
    	i=i+1;
        cout<<"The current calculation progress is located at "<<i<<" bits!"<<endl;
    }
    fin.close();
    ofs.close();
    i=0;
*/


//2024.5.14 CAPE + DownCounter → 乘法器 误差分析
/*
ofstream ofs; 
ofs.open("CAPE_error.txt",ios::out);
int SN_width = 4096;
int lengthStrip = 32;
for(int i = 0;i<SN_width/lengthStrip;i++)
{
    for(int j = 0;j<SN_width/lengthStrip;j++)
    {
        int * SN1 = WBG_SNG_up(i*lengthStrip);
        int * SN2 = downC(j*lengthStrip);
        int res = MulForCAPE(SN1, SN2, j*lengthStrip);
        int real = i*j*lengthStrip*lengthStrip;
        int diff  =getABS(real-diff);
        ofs <<diff<< endl;
    }
}
ofs.close();
*/


ofstream ofs; 
ofs.open("LFSR_error_4096.txt",ios::out);
int SN_width = 4096;
int lengthStrip = 1;
for(int i = 0;i<SN_width/lengthStrip;i++)
{
    int * SN1 = SN_Generator1(256);
    int * SN2 = SN_Generator2(i*lengthStrip);
    int res = MulForCAPE(SN1, SN2, SN_width);
    int real = i*256*lengthStrip;
    int diff  =getABS(real-res);
    ofs <<diff<< endl;
}
ofs.close();






/*
 //测试随机数生成器的均匀性 2024.1.30
for(int i =0;i<4096;i++)
{
    int *aa = RN_Generator1();
    int num = bin2dec(aa);
    cout<<num<<endl;
}
*/




/*
ofstream ofs; 
ofs.open("ECG_data_2.txt",ios::out);
 //测试随机数生成器的均匀性 2024.1.30
for(int i =0;i<4000;i++)
{
    int *aa = RN_Generator1();
    int num = bin2dec(aa);
    //cout<<num<<endl;
    ofs <<num<< endl; 
}
    ofs.close();
*/




/*
//测试随机序列的误差 2024.1.31
ofstream ofs; 
ofs.open("ECG_data_2.txt",ios::out);
for(int i =0;i<4096;i++)
{   
    int *p = SN_Generator2(i);
    int num = sc2dec(p);
    ofs <<num<< endl;
}
ofs.close();
*/



/*
//Testing the link between the number of shifts and 
//the correlation of the 12-bit shared random number source 
// 【2024.2.6】 original
// 【2024.2.17】 update 1.0 double SNG used
// 【2024.4.13】 update 2.0 256*256 random Downsampling
ofstream ofs; 
ofs.open("TEST_K_4_256*256.txt",ios::out);
for(int i =0;i<256;i++)
{   
    for(int j = 0;j<256;j++)
    {
    int * SNX = SNG1_T(i,0);
    int * SNY = SNG2_T(j,4);
    float SCC_X_Y = getSCC(SNX,SNY);
    SCC_X_Y = getABS(SCC_X_Y);
    ofs <<SCC_X_Y<< endl;
    //cout<<"The current calculation progress is located at:Round ["<<i<<"] "<<"Position ["<<j<<"] bits!"<<endl;
    //cout<<i<<"  "<<j<<endl;
    }
    cout<<"current calculation progress is located at "<<i<<endl;
}
ofs.close();
*/

/*
// 2024.04.23  VDC sequence Test
double VDC[4096] = {0};
ofstream ofs; 
ofs.open("VDC4096.txt",ios::out);
for(int i = 1 ; i<=4096 ;i++ )
{   
    VDC[i-1] = RadicalInverse(2, i);
    ofs <<VDC[i-1]<< endl;
}
ofs.close();
*/

/*
    int  SNX[12] = {0,0,0,1,0,0,0,0,1,0,1,0};
    int  SNY[12] = {1,1,0,0,1,1,0,0,1,1,0,0};
    float SCC_X_Y = getSCC12(SNX,SNY);
    //SCC_X_Y = getABS(SCC_X_Y);
    cout<<SCC_X_Y<<endl;
*/
/*
//2024.2.11 LFSR随机数源分布测试 周期4000
ofstream ofs; 
ofs.open("dispution_LFSR.txt",ios::out);
for(int i =0;i<4000;i++)
{   
    int * LFSR_array = RN_Generator1();
    int LFSR_num = bin2dec(LFSR_array);
    ofs <<LFSR_num<< endl;
}
ofs.close();
*/

/*
//halton低差异序列分布测试 2024.2.11
ofstream ofs; 
ofs.open("dispution_sobol.txt",ios::out);
for(uint j = 0;j<4000;j++)
{
    double LD2 = Halton(2, j);
    ofs <<int(LD2*4096)<< endl;
}
ofs.close();
*/

/*
    int out;
    // 逐词读取，按照空格进行分隔
    ofstream ofs; 
    //ifstream fin("ECG_data_1.txt");
    ifstream fin("test_12bit_ecg.txt");
    ofs.open("LD_Trans.txt",ios::out);
    int s;
    int data[3604];
    int i=0;

    while(fin>>s)
    {
    	data[i] = s;
        int *p = SN_Generator1_LD(data[i]);
        int num = sc2dec(p);
        ofs <<num<< endl;  
        //printf("%d\n",data[i]);
        //printf("%d\n",out);
    	i=i+1;
    }
    fin.close();
    ofs.close();
    i=0;
*/

return 0;

}


