struct Result {
    float min;
    float max;
};

struct Data {
    float v[500000];
    int start;
    int end;
};

program PROG {
    version VERSAO {
        Result findNumbers(Data) = 1;
    } = 100;
} = 55555555;
