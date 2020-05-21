#include <math.h>
#include "wgs2gcj.h"
#include <stdio.h>

 double x_pi = (3.14159265358979324 * 3000.0) / 180.0;
 double pi = 3.1415926535897932384626;
 double a = 6378245.0;
 double ee = 0.00669342162296594323;

 /*dd.dddd*/
static int transformlat(double lng, double lat)
{
	double ret = 0;
	ret = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * sqrt(fabs(lng));

	ret = ret + ( (20.0 * sin(6.0 * lng * pi) + 20.0 *sin(2.0 * lng * pi)) * 2.0 / 3.0 );


	ret = ret + ( (20.0 * sin(lat * pi) + 40.0 * sin(lat / 3.0 * pi)) * 2.0 / 3.0 );


	ret = ret + ( (160.0 * sin(lat / 12.0 * pi) + 320 *sin(lat * pi / 30.0)) * 2.0 / 3.0 );

	printf("transformlat lat %6.9f ==> %6.9f\n", lat, ret);
	return ret;
}

 /*dd.dddd*/
static double transformlng(double lng, double lat)
{
	double ret = 0;
	ret = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * sqrt(fabs(lng));


	ret = ret + ( (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0 );


	ret = ret + ( (20.0 * sin(lng * pi) + 40.0 * sin(lng / 3.0 * pi)) * 2.0 / 3.0 );


	ret = ret + ( (150.0 * sin(lng / 12.0 * pi) + 300.0 * sin(lng / 30.0 * pi)) * 2.0 / 3.0 );


	return ret;
}

 /*dd.dddd*/
static int out_of_china(double lng, double lat)
{
	return !((lng > 73.66) && (lng < 135.05) && (lat > 3.86) && (lat < 53.55));
}

 /*dd.dddd*/
 /*double lat = 30.5095416666*/
 /*double lng = 114.334656666*/
lng_lat wgs84_to_gcj02(double lng, double lat)
{
	lng_lat na;
	na.lat = lat;
	na.lng = lng;

	if (out_of_china(lng,lat) )
	{
		return na;
	}

	double dlat = transformlat(lng - 105.0, lat - 35.0);
	double dlng = transformlng(lng - 105.0, lat - 35.0);
	double radlat = lat / 180.0 * pi;
	double magic = sin(radlat);
	magic = 1 - ee * magic * magic;
	double sqrtmagic = sqrt(magic);
	dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi);
	dlng = (dlng * 180.0) / (a / sqrtmagic * cos(radlat) * pi);
	na.lat = lat + dlat;
	na.lng = lng + dlng;
	return na;
}
