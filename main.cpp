#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

#define MaxWindowSize 11

int R[MaxBMPSizeX][MaxBMPSizeY];
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

void medianFilter(int inputR[][MaxBMPSizeY], int inputG[][MaxBMPSizeY], int inputB[][MaxBMPSizeY], int outputR[][MaxBMPSizeY], int outputG[][MaxBMPSizeY], int outputB[][MaxBMPSizeY], int width, int height)
{
    int windowSize = 3;
    int halfWindow = windowSize ;
    int windowLength = windowSize * windowSize;
    int window[MaxWindowSize * MaxWindowSize];

    while (windowSize <= MaxWindowSize) {
        for (int j = halfWindow; j < height - halfWindow; j++) {
            for (int i = halfWindow; i < width - halfWindow; i++) {
                int index = 0;

                // �������f�d�򤺪�������
                for (int y = -halfWindow; y <= halfWindow; y++) {
                    for (int x = -halfWindow; x <= halfWindow; x++) {
                        window[index] = inputR[i + x][j + y];
                        index++;
                    }
                }

                // �ﵡ�f���������ȶi��Ƨ�
                for (int k = 0; k < windowLength - 1; k++) {
                    for (int l = 0; l < windowLength - k - 1; l++) {
                        if (window[l] > window[l + 1]) {
                            int temp = window[l];
                            window[l] = window[l + 1];
                            window[l + 1] = temp;
                        }
                    }
                }

                // �N������x�s���X������
                outputR[i][j] = window[windowLength / 2];
                outputG[i][j] = window[windowLength / 2];
                outputB[i][j] = window[windowLength / 2];
            }
        }

        windowSize += 2;
        halfWindow = windowSize / 2;
    }
}

int main()
{
    int width, height;
    int i, j;

    // �}�Ҩ�Ū��bmp����
    open_bmp("cameraman.bmp", R, G, B, width, height);

    // ���椤���o�i�B�z
    medianFilter(R, G, B, r, g, b, width, height);

    // �x�s�B�z���G�ܷs�����ɤ�
    save_bmp("cameraman_new_mid.bmp", r, g, b);

    printf("Job Finished!\n");

    // ���� bmp �v������
    close_bmp();

    system("pause");
    return 0;
}

