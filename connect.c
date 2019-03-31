#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(void){
	printf("\e[?25l");
	bool animation_on = false;
	int rValue = 0;
	while(1){
		rValue = dispMenu(animation_on);
		if(rValue == -1) break;
		if(rValue == 1) animation_on = true;
		if(rValue == 2) animation_on = false;
	}
	return 0;
}
