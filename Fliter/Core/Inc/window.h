//
// Created by 10633 on 2021/11/4.
//

#ifndef SHOW_WINDOW_H
#define SHOW_WINDOW_H

#include "stm32f4xx.h"
#include "ltdc.h"
#include "usart.h"
#include "math.h"

typedef struct axis {

    uint16_t h_origin;
    uint16_t v_origin;
    uint16_t v_step;

} axishander;

typedef struct {
    uint8_t head;
    float THD;
    float normal[5];
    float waveform;
    uint8_t judge;
    uint8_t tail;
} datahander;


void WinInit(axishander * axis,uint16_t o_x,uint16_t o_y,uint16_t v_step);
void MeshOn(axishander * axis);
void Painting(axishander *axis, float *buffer,uint32_t *freqDst,float *phase, float THDx, float *normal);
void Packageup(float * buffer,float THDx,float * normal);


#endif //SHOW_WINDOW_H
