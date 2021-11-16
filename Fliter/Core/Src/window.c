//
// Created by 10633 on 2021/11/4.
//
#include "window.h"

void WinInit(axishander *axis, uint16_t o_x, uint16_t o_y, uint16_t v_step) {

    axis->h_origin = o_x;
    axis->v_origin = o_y;
    axis->v_step = v_step;

};

void MeshOn(axishander *axis) {

/*    char label[15] = {};
    sprintf(label, "U/100mv");
    LCD_SetColor(LCD_BLACK);
    LCD_DisplayString(10, 10, label);*/

    LCD_SetColor(LIGHT_GREY);
    LCD_DrawLine(axis->h_origin, axis->v_origin - 1, axis->h_origin + 480, axis->v_origin - 1);
    LCD_DrawLine(axis->h_origin, axis->v_origin - 2, axis->h_origin + 480, axis->v_origin - 2);

    LCD_SetColor(LIGHT_GREY);
    for (int i = 0; i < 6; i++) {
        LCD_DrawLine(axis->h_origin, axis->v_origin - i * (axis->v_step), axis->h_origin + 480,
                     axis->v_origin - i * (axis->v_step));
        LCD_DrawLine(axis->h_origin, axis->v_origin + i * (axis->v_step), axis->h_origin + 480,
                     axis->v_origin + i * (axis->v_step));
    }
    for (int i = 0; i < 12; i++) {
        LCD_DrawLine(axis->h_origin + i * 40, 0 , axis->h_origin + i * 40,
                     272 );
    }

}

void Painting(axishander *axis, float *buffer, uint32_t *freqDst, float *phase, float THDx, float *normal) {

    float Line[480] = {0.0};
    char order[20] = {};

    /*for (int i = 0; i < 5; ++i) {
        printf("phase: %f\r\n",phase[i]);
    }*/

    for (int i = 1; i < 5; ++i) {
        phase[i] -= phase[0];
    }
    for (int i = 0; i < 480; ++i) {
        for (int f = 0; f < 5; f++) {
            Line[i] += 75 * normal[f] * sin(2 * 3.1415926 * i / 480 * (f + 1) + phase[f]+3.1415926);
        }
        /*printf("%f\r\n",Line[i]);*/
    }

    LCD_Clear();
    MeshOn(axis);
    LCD_SetColor(LCD_YELLOW);

    for (int cnt = 0, next; cnt < 480; cnt++) {
        next = cnt + 1;
        LCD_DrawLine(cnt, axis->v_origin - Line[cnt],
                     next,axis->v_origin - Line[next]);
        LCD_DrawLine(cnt, axis->v_origin - Line[cnt] -1,
                     next,axis->v_origin - Line[next] -1 );
    }

    LCD_SetFont(&Font16);
    LCD_SetColor(LIGHT_MAGENTA);
    sprintf(order, "THX=%f", THDx);
    LCD_DisplayString(360, 10, order);

    sprintf(order, "harmonic1=%.4f", normal[0]);
    LCD_DisplayString(360, 30, order);

    sprintf(order, "harmonic2=%.4f", normal[1]);
    LCD_DisplayString(360, 50, order);

    sprintf(order, "harmonic3=%.4f", normal[2]);
    LCD_DisplayString(360, 70, order);

    sprintf(order, "harmonic4=%.4f", normal[3]);
    LCD_DisplayString(360, 90, order);

    sprintf(order, "harmonic5=%.4f", normal[4]);
    LCD_DisplayString(360, 110, order);

    return;
}

void Packageup(float *buffer, float THDx, float *normal) {
    static uint8_t temp[31] = {0};
    uint8_t *pos = temp + 1;
    uint8_t judge;
    temp[0] = 0xa5;
    temp[30] = 0x5a;
//    *((float *)pos) = THDx;
//    for (int i = 0; i < 5; ++i) {
//        *((float *)pos) = normal[i];
//        pos += 4;
//    }
    for (int i = 0; i < 1; ++i) {
        pos = temp + 6 * 4 + 1;
        //*((float *) pos) = 0;
        pos = temp + 1;
        judge = 0;
        for (int j = 1; j < 29; ++j) {
            judge += temp[i];
        }
        temp[29] = judge;
        HAL_UART_Transmit(&huart2, temp, 31, 100);
    }
}
