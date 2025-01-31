/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "MS51_32K.h"


void Timer0_ISR(void) interrupt 1            /*interrupt address is 0x000B */
{
    _push_(SFRS);
    TF0 = 0;
    _pop_(SFRS);
}

//-------------------------------------------------------------------------
void Timer0_Interrupt_Init(unsigned long u32SYSCLK, unsigned int u16CNT, unsigned int u16DLYUnit)
{
    unsigned int i;
    BIT_TMP = EA;
    ENABLE_TIMER0_MODE1;
    TIMER0_FSYS_DIV12;
    ENABLE_TIMER0_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

    for (i = 0; i < u16CNT; i++)
    {
        TL0 = LOBYTE(65535 - ((u32SYSCLK / 1000000) * u16DLYUnit / 12));
        TH0 = HIBYTE(65535 - ((u32SYSCLK / 1000000) * u16DLYUnit / 12));
        set_TCON_TR0;                                    //Start Timer0

        while (!TF0);

        clr_TCON_TR0;
    }

    DISABLE_TIMER0_INTERRUPT;
    EA = BIT_TMP;
}

void Timer0_Interrupt_Disable(void)
{
    clr_TCON_TR0;
    DISABLE_TIMER0_INTERRUPT;
}
/*
//------------------------------------------------------------------------------
void Timer0_Delay1ms(UINT32 u32CNT)
{
    clr_CKCON_T0M;                                    //T0M=0, Timer0 Clock = Fsys/12
    TMOD |= 0x01;                               //Timer0 is 16-bit mode

    while (u32CNT != 0)
    {
        TL0 = LOBYTE(TIMER_DIV12_VALUE_1ms);     //Find  define in "Function_define.h" "TIMER VALUE"
        TH0 = HIBYTE(TIMER_DIV12_VALUE_1ms);
         set_TCON_TR0;                                    //Start Timer0
        while (TF0 != 1);                       //Check Timer0 Time-Out Flag
        clr_TCON_TF0;
        u32CNT --;
    }
    clr_TCON_TR0;                                    //Stop Timer0
}
//------------------------------------------------------------------------------
void Timer1_Delay10ms(UINT32 u32CNT)
{
    clr_CKCON_T1M;                                    //T1M=0, Timer1 Clock = Fsys/12
    TMOD |= 0x10;                                //Timer1 is 16-bit mode
    set_TCON_TR1;                                    //Start Timer1
    while (u32CNT != 0)
    {
        TL1 = LOBYTE(TIMER_DIV12_VALUE_10ms);    //Find  define in "Function_define.h" "TIMER VALUE"
        TH1 = HIBYTE(TIMER_DIV12_VALUE_10ms);
        while (TF1 != 1);                        //Check Timer1 Time-Out Flag
        clr_TCON_TF1;
        u32CNT --;
    }
    clr_TCON_TR1;                                     //Stop Timer1
}
//------------------------------------------------------------------------------
void Timer2_Delay500us(UINT8 u8CNT)
{
    SFRS = 0;
    T2MOD&=0x8F;T2MOD|=0x10;                                   //Timer2 Clock = Fsys/4
    clr_T2CON_CMRL2;
    set_T2MOD_LDEN;
    set_T2MOD_CMPCR;

    while (u8CNT != 0)
    {
        TL2 = LOBYTE(TIMER_DIV4_VALUE_500us);    //Find  define in "Function_define.h" "TIMER VALUE"
        TH2 = HIBYTE(TIMER_DIV4_VALUE_500us);
        set_T2CON_TR2;
        while (TF2 == 0);                       //Check Timer2 Time-Out Flag
        clr_T2CON_TF2;
        u8CNT --;
    }
    clr_T2CON_TR2;                                    //Stop Timer2
}
void Timer2_Delay1ms(unsigned char u8CNT)
{
    SFRS = 0;
    T2MOD&=0x8F;T2MOD|=0x10;                                   //Timer2 Clock = Fsys/4
    clr_T2CON_CMRL2;
    set_T2MOD_LDEN;
    set_T2MOD_CMPCR;

    while (u8CNT != 0)
    {        TL2 = LOBYTE(TIMER_DIV4_VALUE_1ms);    //Find  define in "Function_define.h" "TIMER VALUE"
        TH2 = HIBYTE(TIMER_DIV4_VALUE_1ms);
        set_T2CON_TR2;
        while (TF2 == 0);                       //Check Timer2 Time-Out Flag
        clr_T2CON_TF2;
        u8CNT --;
    }
    clr_T2CON_TR2;                                    //Stop Timer2
}
//------------------------------------------------------------------------------
void Timer3_Delay100ms(UINT32 u32CNT)
{
    T3CON = 0x07;                               //Timer3 Clock = Fsys/128
    set_T3CON_TR3;                                    //Trigger Timer3
    while (u32CNT != 0)
    {
        RL3 = LOBYTE(TIMER_DIV128_VALUE_100ms); //Find  define in "Function_define.h" "TIMER VALUE"
        RH3 = HIBYTE(TIMER_DIV128_VALUE_100ms);
        while ((T3CON&SET_BIT4) != SET_BIT4);    //Check Timer3 Time-Out Flag
        clr_T3CON_TF3;
        u32CNT --;
    }
    clr_T3CON_TR3;                                    //Stop Timer3
}
//------------------------------------------------------------------------------
void Timer3_Delay10us(UINT32 u32CNT)
{
    T3CON = 0x02;                               //Timer3 Clock = Fsys/4
    set_T3CON_TR3;                                    //Trigger Timer3
    while (u32CNT != 0)
    {
        RL3 = LOBYTE(TIMER_DIV4_VALUE_10us); //Find  define in "Function_define.h" "TIMER VALUE"
        RH3 = HIBYTE(TIMER_DIV4_VALUE_10us);
        while ((T3CON&SET_BIT4) != SET_BIT4);    //Check Timer3 Time-Out Flag
        clr_T3CON_TF3;
        u32CNT --;
    }
    clr_T3CON_TR3;                                    //Stop Timer3
}
*/