/*
 * =====================================================================================
 *
 *       Filename:  urlCode.c
 *
 *    Description:  url encode and decode cfunc;
 *
 *        Version:  1.0
 *        Created:  2010年12月30日 14时27分25秒
 *       Revision:  0.1
 *       Compiler:  gcc
 *
 *         Author:  bigdog()
 *        Company:  
 *
 * =====================================================================================
 */

#include "urlCode.h"


inline char Char2Num(char ch){
    if(ch>='0' && ch<='9')return (char)(ch-'0');
    if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
    if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
    return NON_NUM;
}

/* ***********************************************
 * * 把字符串进行URL编码。
 * * 输入：
 * * str: 要编码的字符串
 * * strSize: 字符串的长度。这样str中可以是二进制数据
 * * result: 结果缓冲区的地址
 * * resultSize:结果地址的缓冲区大小(如果str所有字符都编码，该值为strSize*3)
 * * 返回值：
 * * >0: result中实际有效的字符长度，
 * * 0: 编码失败，原因是结果缓冲区result的长度太小
 * ************************************************/
int urlEncode(const char* str, const int strSize, char* result, const int resultSize) {
    int i;
    int j = 0; /*  for result index */
    char ch;

    if ((str == NULL) || (result == NULL) || (strSize <= 0) || (resultSize <= 0)) {
        return 0;
    }

    for (i=0; (i<strSize) && (j<resultSize); i++) {
        ch = str[i];
        if ((ch >= 'A') && (ch <= 'Z')) {
            result[j++] = ch;
        } else if ((ch >= 'a') && (ch <= 'z')) {
            result[j++] = ch;
        } else if ((ch >= '0') && (ch <= '9')) {
            result[j++] = ch;
        } else if(ch == ' '){
            result[j++] = '+';
        } else {
            if (j + 3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}


/* ***********************************************
 * * 把字符串进行URL解码。
 * * 输入：
 * * str: 要解码的字符串
 * * strSize: 字符串的长度。
 * * result: 结果缓冲区的地址
 * * resultSize:结果地址的缓冲区大小，可以<=strSize
 * * 返回值：
 * * >0: result中实际有效的字符长度，
 * * 0: 解码失败，原因是结果缓冲区result的长度太小
 * ************************************************/
int urlDecode(const char* str, const int strSize, char* result, const int resultSize) {
    char ch, ch1, ch2;
    int i;
    int j = 0; /*  for result index */

    if ((str == NULL) || (result == NULL) || (strSize <= 0) || (resultSize <= 0)) {
        return 0;
    }

    for (i=0; (i<strSize) && (j<resultSize); i++) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;

            case '%':
                if (i+2 < strSize) {
                    ch1 = Char2Num(str[i+1]);
                    ch2 = Char2Num(str[i+2]);
                    if ((ch1 != NON_NUM) && (ch2 != NON_NUM)) {
                        result[j++] = (char)((ch1<<4) | ch2);

                        i += 2;
                        break;
                    }
                }

            /*  goto default */
            default:
                result[j++] = ch;
                break;
        }
    }

    result[j] = '\0';
    return j;
} 


//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;

    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
    iconv_close(cd);
    return 0;
}

//UNICODE码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
    return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
    return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}



#ifdef  _TEST_URL

#include <string.h>

int main(int argc, char **argv) {
    //char *home = "www.baidu.com";
    char *home2 = "q=%E4%B8%AD%E5%9B%BD%E4%BA%BA%E6%B0%91zhang";
    //char *home = "中国zhadifg网络";
    char *home = "张三";
    char buf[256] = {0};
    char puf[256] = {0};

    int ret = u2g(home,strlen(home),buf,256);
    if(ret < 0) {
        printf ( "Error\n" );
    }
    ret = urlEncode(buf, strlen(buf), puf, 256);
    printf("gbk-urlencoded : %s\n", puf);

    printf("defined : home = %s\n", home);
    ret = urlEncode(home, strlen(home), buf, 256);
    printf ( "encode : buf = %s\n", buf );
    ret = urlDecode(buf, strlen(buf), puf, 256);
    printf ( "decode : puf = %s\n", puf );

    memset(puf, 0, 256);
    ret = urlDecode(home2, strlen(home2), puf, 256 );
    printf ( "decode puf2  = %s\n", puf );
    return 0;
}
#endif 
