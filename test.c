#include <stdio.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
	int n = atoi(argv[1]),rpn = atoi(argv[2]);

	if((n== 0)?(rpn < 0) : (rpn > 0)){
		printf("%d %d IF\n",n,rpn);
	}
	else {
		printf("%d %d ELSE\n",n,rpn);
	}
	return 0;
}
