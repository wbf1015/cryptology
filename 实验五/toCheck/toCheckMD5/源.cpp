#include <string.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

/***********************************
* �����Ժ���
* (&����,|�ǻ�,~�Ƿ�,^�����)
*
* ��Щ������������Ƶģ�
*   ���X��Y��Z�Ķ�Ӧλ�Ƕ����;��ȵģ�
*   ��ô�����ÿһλҲӦ�Ƕ����;��ȵġ�
*
* ����F�ǰ���λ��ʽ���������X����ôY������Z��
* ����H����λ��ż������
**********************************/
#define F(x,y,z) ((x & y) | (~x & z))  
#define G(x,y,z) ((x & z) | (y & ~z))  
#define H(x,y,z) (x^y^z)  
#define I(x,y,z) (y ^ (x | ~z))  


/**************************************
*������(�һ���)n����λ
* ************************************/
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))  
/****************************************************
* ÿ�β�����a��b��c��d�е�����������һ�η����Ժ�������
*  F(b,c,d)   G(b,c,d)   H(b,c,d)   I(b,c,d)
*
* Ȼ�����ý������ ���ĸ�����(a)��
* F(b,c,d)+a
*
* �ı���һ���ӷ���(x)
* F(b,c,d)+a+x
*
* ��һ������(ac)��
* F(b,c,d)+a+x+ac
*
* �ٽ����ý�����һ���һ����������(s)��
* ROTATE_LEFT( F(b,c,d)+a+x+ac , s )
*
* ������a��b��c��d��֮һ(b)��
* ROTATE_LEFT( F(b,c,d)+a+x+ac , s )+b
*
* ����øý��ȡ��a��b��c��d��֮һ(a)��
* a=ROTATE_LEFT( F(b,c,d)+a+x+ac , s )+b
*
* ***************************************************/
#define FF(a,b,c,d,x,s,ac) { a += F(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define GG(a,b,c,d,x,s,ac) { a += G(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define HH(a,b,c,d,x,s,ac) { a += H(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define II(a,b,c,d,x,s,ac) { a += I(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
//����һ��MD5 text��Ϣ 
typedef struct
{
    unsigned int count[2];
    //��¼��ǰ״̬��������λ��   
    unsigned int state[4];
    //4������һ��32λ ��¼���ڱ����512bits��Ϣ���ܵ��м����������ս��  
    unsigned char buffer[64];
    //һ��64�ֽڣ�512λ      
}MD5_CTX;
//��һλ1 ������ɸ�0,����MD5Final����ʱ�Ĳ���
unsigned char PADDING[] = { 0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//��������
void MD5Init(MD5_CTX* context);
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);
void MD5Final(MD5_CTX* context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);
/************************
* �������ܣ���ʼ��һ��MD5 text
* ����������MD5 text ָ��
* ***********************/
//��ʼ��
void MD5Init(MD5_CTX* context)
{
    context->count[0] = 0;
    context->count[1] = 0;
    //�ֱ𸳹̶�ֵ  
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
}
/************************************************
* �������ܣ���һ��MD5 text,����������ݽ��з��飬�����м���
* δ�õ������ݰ��䴢����MD5 text�С�
*
* ����������
* MD5_CTX *context       ��һ��MD5 text
* unsigned char *input   ������ӵ�����
* unsigned int inputlen  ����������ݵĳ���(�ֽ�)
*
***********************************************/
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen)
{
    unsigned int i = 0, index = 0, partlen = 0;
    //index����ǰ״̬��λ����64ȡ�࣬�䵥λ���ֽ�
    //Ҳ����д����  index=(context->count[0]/8)%64
    index = (context->count[0] >> 3) & 0x3F;
    //partlen:���Բ���64�ֽڵ��ֽ���
    partlen = 64 - index;
    //��������ǽ��һ��unsignde int �޷����漫�����ݵ������������
    //��ǰλ����������ӵ�λ��������inputlen�����ֽ�Ϊ��λ��������ת��Ϊλ��
    //�൱��context->count[0] += inputlen*8;  
    context->count[0] += inputlen << 3;
    //���������������ʱ��ͨ�����²���������16λ��������һ�飬����һ��
    //32λ�Ķ������������Ӷ������䴢�淶Χ
    if (context->count[0] < (inputlen << 3))
    {
        context->count[1]++;
    }
    //�������滻Ϊ context->count[1]+=(inputlen<<3)>>32;
    //�������
    context->count[1] += inputlen >> 29;
    //���������ֽ����Ĵ�������Բ���64�ֽڵ��ֽ��������в���
    if (inputlen >= partlen)
    {
        //��buffer�в���partlen���ֽڣ�ʹ�䵽��64�ֽ�
        memcpy(&context->buffer[index], input, partlen);
        //buffer�ﵽ64�ֽ�512λ���������Ϊһ���������
        MD5Transform(context->state, context->buffer);
        //�����������ݻ�������ɶ��64�ֽڣ������������
        //����Ϊ�������������
        for (i = partlen; i + 64 <= inputlen; i += 64)
            MD5Transform(context->state, &input[i]);
        //�ָ�0ֵ����Ӧ ���� ������ ʣ���ֽ�(�������64�ֽ���) ����Ĳ���
        index = 0;
    }
    //���򣬰���������ݰ�˳�����ԭ�����ݺ���
    else
    {
        i = 0;
    }
    //����ʣ������
    memcpy(&context->buffer[index], &input[i], inputlen - i);
}
/*************************************************
* �������ܣ������ݽ��в��㣬����������λ����Ϣ������һ������
*
* ����������
* MD5_CTX *context          :һ��MD5 text
* unsigned char digest[16]  :������ܽ��������
*************************************************/
void MD5Final(MD5_CTX* context, unsigned char digest[16])
{
    unsigned int index = 0, padlen = 0;
    //bits�� 8���ֽڣ�64λ
    unsigned char bits[8];
    //index:��64ȡ����
    index = (context->count[0] >> 3) & 0x3F;
    //��ΪҪ�������ʹ��λ����512����Ľ������448��56λ��
    //���Ե�����ʣ�����С��56�ֽڣ������56-index�ֽڣ�
    //�������120-index�ֽ�
    //����padlen���������������ֽ�
    padlen = (index < 56) ? (56 - index) : (120 - index);
    //Ȼ�������������渽��һ����64λ�����Ʊ�ʾ�����ǰ���ݳ��ȡ�
    //�����ǰ�������ݳ���ת����ŵ�bit�ַ�������
    MD5Encode(bits, context->count, 8);
    //�����Ѿ��洢�õ�����PADDING������Ϣ�ĺ������һ��1��������0��
    //ֱ���������������ʱ��ֹͣ��0����Ϣ�����
    //�����������һϵ�еļ��ܲ������䶨ʣ��48���ֽ�
    MD5Update(context, PADDING, padlen);
    //�������ӽ�8���ֽڵ����ݳ�����Ϣ�����ճ�һ�飬����һ�μ��ܴ���
    MD5Update(context, bits, 8);
    //�����յõ��ļ�����Ϣ����ַ��������16�ֽ�
    MD5Encode(digest, context->state, 16);
}
/**********************************************************
* �������ܣ�����λ��������1->4��ʽ�����ַֽ���ַ�
*
* ����������
* unsigned char  *output ��������ַ�������
* unsigned int   *input  ���������ֵ�����
* unsigned int   len     : ������������ĳ��ȣ���λ��λ��
* *********************************************************/
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len)
{
    unsigned int i = 0, j = 0;
    while (j < len)
    {
        //����& 0xFFΪȡ��8λ
        //i�������������±�
        //j�����ַ������±�
        //�����ֵ�8��8-16��16-24��24-32�ֱ�ֵ���ַ�
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
        i++;
        j += 4;
    }
}
/**********************************************************
* �������ܣ�����λ��������4->1��ʽ���ַ��ϳ�����
*
* ����������
* unsigned int  *output ����������ֵ�����
* unsigned char *input  �������ַ�������
* unsigned int  len     : �����ַ��ĳ��� ����λ��λ��
* *********************************************************/
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len)
{
    unsigned int i = 0, j = 0;
    while (j < len)
    {
        //����λ���������ĸ���λΪ1�ֽڵ��ַ����ϳ�һ����λΪ4�ֽڵ�����
        //��ΪFF GG HH II�ͷ����Ժ�����ֻ�ܶ����ֽ��д���
        //��һ���ַ�ռǰ8λ���ڶ���ռ8-16λ��������ռ16-24λ�����ĸ�ռ
        //24-32λ��
        //i�������������±�
        //j�����ַ������±�
        output[i] = (input[j]) |
            (input[j + 1] << 8) |
            (input[j + 2] << 16) |
            (input[j + 3] << 24);
        i++;
        j += 4;
    }
}
/**************************************************************
* �������ܣ���512λ��block���ݽ��м��ܣ����Ѽ��ܽ������state������
* ��512λ��Ϣ(��block�ַ�����)����һ�δ���ÿ�δ����������
*state[4]��md5�ṹ�е�state[4]�����ڱ����512bits��Ϣ���ܵ��м����������ս��
* block[64]�������ܵ�512bits��Ϣ�����м�����
***************************************************************/
void MD5Transform(unsigned int state[4], unsigned char block[64])
{
    //a b c d�̳���һ�����ܵĽ������������м̳���
    unsigned int a = state[0];
    unsigned int b = state[1];
    unsigned int c = state[2];
    unsigned int d = state[3];
    //����ֻ���õ�16�����Ұ�ԭ����unsiged int x[64]  ��Ϊ�� x[16]
    unsigned int x[16];
    //���ַ�ת�������֣���������
    MD5Decode(x, block, 64);
    //���庯����ʽ�̶�������׸��
    /*************��һ��******************/
    FF(a, b, c, d, x[0], 7, 0xd76aa478);
    printf("��һ�ֵ�һ�����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    printf("��һ�ֵ�һ�����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);
    /*************�ڶ���*****************/
    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    printf("�ڶ��ֵ�һ�����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    printf("�ڶ��ֵڶ������Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    printf("�ڶ��ֵ��������Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    printf("�ڶ��ֵ��Ĳ����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);
    printf("�ڶ��ֵ�ʮ�������Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    /*************������*****************/
    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    printf("�����ֵ�һ�����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);
    /*************������******************/
    II(a, b, c, d, x[0], 6, 0xf4292244);
    printf("�����ֵ�һ�����Ϊ\n");
    printf("%02x \n", a);
    printf("%02x \n", b);
    printf("%02x \n", c);
    printf("%02x \n", d);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    //����ԭ���Ľ��
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
int main(int argc, char* argv[])
{
    MD5_CTX md5;  //����һ��MD5 text
    MD5Init(&md5);//��ʼ��
    int i;
    //unsigned char encrypt[] ="admin";//Ҫ��������
    //���ܽ����21232f297a57a5a743894a0e4a801fc3
    unsigned char encrypt[1000];//Ҫ��������
    printf("������Ҫ���ܵ��ַ�����");
    gets_s((char*)encrypt,999);
    unsigned char decrypt[16]; //���ܽ��
    MD5Update(&md5, encrypt, strlen((char*)encrypt));//���г����������
    MD5Final(&md5, decrypt);   //���к���Ĳ��㣬������ 
    printf("����ǰ:%s\n���ܺ�16λ:", encrypt);
    for (i = 4; i < 12; i++)
    {
        printf("%02x", decrypt[i]);
    }
    printf("\n����ǰ:%s\n���ܺ�32λ:", encrypt);
    for (i = 0; i < 16; i++)
    {
        printf("%02x", decrypt[i]);
    }
    printf("\n");
    return 0;
}