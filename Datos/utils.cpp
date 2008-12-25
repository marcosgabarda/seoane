#include "utils.h"
#include <cstdio>

char *itoa(int i) {
	char *a = new char[1024];
	sprintf(a,"%d",i);
	return a;

}
char *ftoa(float f) {
	char *a = new char[1024];
	sprintf(a,"%f",f);
	return a;
}
