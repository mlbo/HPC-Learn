#include <stdio.h>

void cpu() {
    printf("Hello cpu\n");
}

__global__ void gpu() {
    printf("Hello gpu\n");
}

int main() {
    cpu();
    gpu<<< 1, 1>>>();
    cudaDeviceSynchronize();

    return 0;

}