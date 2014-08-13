/*
 * =====================================================================================
 *
 *       Filename:  inet_tr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年08月02日 15时24分08秒
 *       Revision:  0.1
 *       Compiler:  gcc
 *
 *         Author:  bigdog()
 *        Company:  
 *
 * =====================================================================================
 */



#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<stdint.h>

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>

uint32_t ip_atoi(char *ipstr)
{
    if(ipstr == NULL) {
        return 0;
    }
    // in_addr_t ret = inet_network(ipstr);
    in_addr_t ret = inet_addr(ipstr);
    return (uint32_t)ret;
}

int ip_itoa(uint32_t ip, char *ipstr, size_t strlen)
{
    if(ipstr == NULL || strlen < 17 || ip < 1)
        return -1;

    struct in_addr in;
    in.s_addr = ip;
    strcpy(ipstr, inet_ntoa(in));
    return 0;
}


int main()
{
    char *ip = "192.168.1.102";
    printf("IP : [%u]\n", ip_atoi(ip));
    char mac[18];
    memset(mac, 0, 18);
    if (ip_itoa(ip_atoi(ip), mac, 18) < 0)
        printf ( "error\n" );

    printf("IPSTR : [%s]\n", mac);
    return 0;
}
