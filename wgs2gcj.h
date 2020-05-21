#ifndef __WGS2GCJ_H
#define __WGS2GCJ_H
typedef struct lng_lat{
	double lng;
	double lat;
}lng_lat;

lng_lat wgs84_to_gcj02(double, double);

#endif
