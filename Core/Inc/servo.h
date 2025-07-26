//
// Created by 21043 on 2025/7/24.
//

#ifndef SERVO_H
#define SERVO_H

#include "main.h"
#include "tim.h"

#define leftServoChannel 0x0000000CU
#define bottomServoChannel 0x00000008U
#define rightServoChannel 0x00000004U

void Servo_Init(void);
void Servo_Wave(void);
void Magnet_On(void);
void Magnet_Off(void);
void Servo_Duty(int left, int bottom, int right);
void Mid_Position(int left, int bottom, int right);
void MoveServoSlow(uint8_t current, uint8_t target, char name);
void Servo_Duty2(const int duty, char name);
void Example(void);

#endif //SERVO_H
