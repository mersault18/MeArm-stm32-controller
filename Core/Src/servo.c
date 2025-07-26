//
// Created by 21043 on 2025/7/24.
//
#include "servo.h"
void Servo_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); //left
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); //bottom
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); //right

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 75);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 65);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 75);

    HAL_GPIO_WritePin(MAGNET_GPIO_Port,MAGNET_Pin, GPIO_PIN_RESET);

    HAL_Delay(500);

}

void Servo_Wave(void) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 50);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 50);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 50);
    HAL_Delay(500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 100);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
    HAL_Delay(500);
}

void Magnet_On(void) {
    HAL_GPIO_WritePin(MAGNET_GPIO_Port, MAGNET_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
}

void Magnet_Off(void) {
    HAL_GPIO_WritePin(MAGNET_GPIO_Port, MAGNET_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
}

void Servo_Duty(int left, int bottom, int right) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, left);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, bottom);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, right);
    HAL_Delay(500);
}

//input original left, right, bottom servo duty
void Mid_Position(int left, int bottom, int right) {
    MoveServoSlow(right, 75, 'r' );
    MoveServoSlow(left, 75, 'l' );
    MoveServoSlow(bottom, 65, 'b' );
    HAL_Delay(500);
    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 75);
    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 65);
    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 75);
    // HAL_Delay(500);
}

void MoveServoSlow(uint8_t current, uint8_t target, char name) {
    while (current != target) {
        if (current < target)
            current++;
        else
            current--;

        Servo_Duty2(current, name);  // 实际运动
        HAL_Delay(15);           // 每次延时，调节速度
    }
}

void Servo_Duty2(const int duty, char name) {
    switch (name) {
        case 'l':
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty);
            break;

        case 'b':
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
            break;
        case 'r':
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
            break;


    }

}

void Example(void) {
    MoveServoSlow(65, 80, 'b');
    MoveServoSlow(75, 25, 'l');
    MoveServoSlow(75, 88, 'r');
    Magnet_On();
    Mid_Position(25, 80, 88);
    //MoveServoSlow(65, 65, 'b');
    MoveServoSlow(75, 25, 'l');
    MoveServoSlow(75, 105, 'r');
    Magnet_Off();
    Mid_Position(40, 65, 95);
}