
#ifndef __BME280__
#define __BME280__

int bme280Init(int iChannel, int iAddr);
int bme280ReadValues(int *T, int *P, int *H);


int BME280_compensate();
int bme280Temperature(int *T);
int bme280Pressure(int *P);
int bme280Humidity(int *H);


#endif // __BME280__
