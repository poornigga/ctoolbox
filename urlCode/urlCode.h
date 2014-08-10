/*
 * =====================================================================================
 *
 *       Filename:  urlCode.h
 *
 *    Description:  url decode and encode header file.
 *
 *        Version:  1.0
 *        Created:  2010年12月30日 14时34分01秒
 *       Revision:  0.1
 *       Compiler:  gcc
 *
 *         Author:  bigdog()
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _URLCODE_H_
#define _URLCODE_H_

#include <stdio.h>
#include <string.h>

#include <iconv.h>

#define NON_NUM '0'

int urlEncode(const char* str, const int strSize, char* result, const int resultSize) ;
int urlDecode(const char* str, const int strSize, char* result, const int resultSize) ;

int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);

//UNICODE码转为GB2312码 (used)
int u2g(char *inbuf,int inlen,char *outbuf,int outlen);

//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

#endif
