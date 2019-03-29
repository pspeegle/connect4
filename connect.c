#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(void){
	while(dispMenu() == 0){
		;
	}
	return 0;
}
