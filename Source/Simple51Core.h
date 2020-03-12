/**
 * @file Simple51.h
 * @author yinxiang (yinxiang2207@qq.com)
 * @brief This is a core header file of the Simple51 framework, 
 *        including part of the stdint file content and macro 
 *        definitions, please do not change it at will.
 * @version v1.1
 * @date 2019-12-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SIMPLE51CORE_H__
#define __SIMPLE51CORE_H__

typedef signed char int8_t;  /*-128 to +127*/
typedef signed int int16_t;  /*-32768 to +32767*/
typedef signed long int32_t; /*-2147483648 to 2147483647*/

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

/*
The XBYTE macro accesses individual bytes in the external data memory of the 8051. You may use this macro in your programs as follows:.
rval = XBYTE [0x0002];
XBYTE [0x0002] = 57;

This example reads and writes the contents of the byte in external data memory at address 0002h.

The range of valid index values for this macro is 0-65535.
*/
#define CBYTE ((unsigned char volatile code *)0)
#define DBYTE ((unsigned char volatile data *)0)
#define PBYTE ((unsigned char volatile pdata *)0)
#define XBYTE ((unsigned char volatile xdata *)0)
#define CWORD ((unsigned int volatile code *)0)
#define DWORD ((unsigned int volatile data *)0)
#define PWORD ((unsigned int volatile pdata *)0)
#define XWORD ((unsigned int volatile xdata *)0)

/*位操作,使用方法为sfr&=BITxRESET*/
#define BIT0RESET 0xFE /*位0置0*/
#define BIT1RESET 0xFD /*位1置0*/
#define BIT2RESET 0xFB /*位2置0*/
#define BIT3RESET 0xF7 /*位3置0*/
#define BIT4RESET 0xEF /*位4置0*/
#define BIT5RESET 0xDF /*位5置0*/
#define BIT6RESET 0xBF /*位6置0*/
#define BIT7RESET 0x7F /*位7置0*/

/* @brief 位操作,使用方法为sfr|=BITxRESET*/
#define BIT0SET 0x01 /*位0置1*/
#define BIT1SET 0x02 /*位1置1*/
#define BIT2SET 0x04 /*位2置1*/
#define BIT3SET 0x08 /*位3置1*/
#define BIT4SET 0x10 /*位4置1*/
#define BIT5SET 0x20 /*位5置1*/
#define BIT6SET 0x40 /*位6置1*/
#define BIT7SET 0x80 /*位7置1*/

#define ENABLE 1  /*使能*/
#define DISABLE 0 /*失能*/

#define TRUE 1  /**/
#define FALSE 0 /**/

#define SET 1   /*置位*/
#define RESET 0 /*清除*/

#define TRANSMIT 1 /*发送*/
#define RECEIVE 0  /*接收*/

#endif
