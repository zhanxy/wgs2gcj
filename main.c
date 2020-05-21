#include <stdio.h>
#include <stdlib.h>
#include "wgs2gcj.h"
char *double2string(double d,char *str);

char *double2string(double d,char *str)
{
	char str1[40];
	int j = 0,k,i;
	i = (int)d;//浮点数的整数部分
	while(i > 0)
	{
		str1[j++] = i % 10 + '0';
		i = i / 10;
	}
	for(k = 0;k < j;k++)
	{
		str[k] = str1[j-1-k];//被提取的整数部分正序存放到另一个数组
	}


	str[j++] = '.';

	d = d - (int)d;//小数部分提取
	for(i = 0;i < 10;i++)
	{
		d = d*10;
		str[j++] = (int)d + '0';
		d = d - (int)d;
	}
	while(str[--j] == '0');
	str[++j] = '\0';
	return str;
}

int main()
{
    lng_lat na;
    char str[50] = {0};
//    double lat = 30.50950;//3030.5724;
//    double lng = 114.33488;//11420.0793;

    int lat = 3050950;//3030.5724;
    int lng = 11433488;//11420.0793;

    double lat_double = (lat/100000) + (1.0*(lat%100000))/100000;
    printf("lat_double = %.9f\n", lat_double);
    printf("double2string(%.9f) = %s\n", lat_double, double2string(lat_double, str));

    double lng_double = (lng/100000) + (1.0*(lng%100000))/100000;
    printf("lng_double = %.9f\n", lng_double);

    na = wgs84_to_gcj02(lng_double, lat_double);

    printf("lat=%.9f,lng=%.9f\n", na.lat, na.lng);

    printf("double2string(%.9f) = %s\n", na.lat, double2string(na.lat, str));
    printf("double2string(%.9f) = %s\n", na.lng, double2string(na.lng, str));

    return 0;
}
