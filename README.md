# S51_UTF_8_FontLibrary
UTF-8 font dot matrix data is saved through external FLASH  
s51 UTF-8 font is an open source font based on the simple51 framework.   This library is mainly used to display Chinese ASCII codes or other   Chinese characters on a monochrome dot matrix display module. Read through SPI FLASH.


# Why is UTF-8 ?
The first point is that UTF-8 is the currently popular encoding set.  Compared with GB2312 and GBK, it supports more characters.  
The second point is that on Keil, some GB2312 characters use the / xFD encoding. Since Keil does not support the compilation of / xFD, additional measures are required.  
Such as: "code char RussianString [] =" My Text "" \ xFD ";"  
See details:[GENERAL: COMPILER IGNORES 0XFD, 0XFE, 0XFF VALUES IN STRINGS](http://www.keil.com/support/docs/2618.htm)  

# Supported characters
ASCII 5x8  
ASCII 16x8  
The Chinese Compatible GB2312 16x16  
 
# Getting Started

1. First burn the fontbin file into the flash, the flash capacity must be greater than 16Mbits (2MBytes)
16Mbits SPI FLASH is used in the example

2. Copy s51_fontlib.c and s51_fontlib.h to the project file

3. Write the interface function of the file, here the interface function is the SPI bus interface  
   
        uint8_t Simple51_FontLib_Interface(uint8_t _data, uint8_t _ss) 
        {
            uint8_t _getdata = 0x00;
            extern SPI_HandleTypeDef hspi1;

            pin_fontss = _ss;
            Simple51_SPI_TransmitReceive(&hspi1, &_data, &_getdata, 1);
            return _getdata;
        } 

4. Write your own LCD display function and call, reference test function  

        S51_GUI_Display_Str(Font_8,0,0,"ASCII Test",0,0);
        S51_GUI_Display_Str(Font_16, 2, 0, "A!@中文测试", 0, 0);
        S51_GUI_Display_Str(Font_16, 4, 0, "三升锡", 0, 1);

5. Display effect

    [display effect](Resources/Snipaste_1.png)

# License

Apache License  
Version 2.0, January 2004