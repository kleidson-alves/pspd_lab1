#include "calcula.h"
#include <time.h>
#include <math.h>

#define X 500000

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int f_aleat() {
    int aleat = rand() % X;
    return aleat;
}

void generateNumbers(float *v) {
    for(int i = 0; i < X; i++) {
        v[i] = sqrt(pow(i - (f_aleat()/2.0), 2));
    }
}

int main(int argc, char* argv[]) {
	CLIENT *clnt, *clnt2;
    Data data;
    Result msg, msg2;
   
    srand(time(NULL));

	if (argc!=3) {
		fprintf(stderr,"Uso: %s hostname1 hostname2\n",argv[0]);
	exit(0); 
	}

	clnt = clnt_create(argv[1], PROG, VERSAO, "tcp");
	clnt2 = clnt_create(argv[2], PROG, VERSAO, "tcp");

	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

    if (clnt2 == (CLIENT *) NULL) {
		clnt_pcreateerror(argv[2]);
		exit(1);
	}
    
    generateNumbers(data.v);

    data.start = 0;
    data.end = X/2 - 1;

	msg = *findnumbers_100(&data, clnt);
    
    data.start = X/2;
    data.end = X - 1;

	msg2 = *findnumbers_100(&data, clnt2);

    float min = MIN(msg.min, msg2.min);
    float max = MAX(msg.max, msg2.max);

    printf("min = %.2f\nmax = %.2f\n", min, max);

    return 0;
}
