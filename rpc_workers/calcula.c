#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define X 30

typedef struct Result {
    float min;
    float max;
} Result;

int f_aleat() {
    int aleat = rand() % X;
    return aleat;
}

void generateNumbers(float *v) {
    for(int i = 0; i < X; i++) {
        v[i] = sqrt(pow(i - (f_aleat()/2.0), 2));
    }
}

Result findNumbers(float *v, int start, int end) {
    Result res = {-1, -1};
    for(int i = start; i <= end; i++) {
        if(res.min == -1 || res.min > v[i]) {
            res.min = v[i];
        }
        if(res.max < v[i] ){
            res.max = v[i];
        }
    }
    return res;
}

int main() {
    srand(time(NULL));
    float v[X];
    generateNumbers(v);

    for(int i=0; i<X; i++){
        printf("%.2f ", v[i]);
    }

    Result result = findNumbers(v, 0, X - 1);
    printf("\n%.2f, %.2f\n", result.max, result.min);
    return 0;
}
