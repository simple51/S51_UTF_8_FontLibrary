/**
 * @file s51_fontlib.c
 * @author yinxiang2207(yinxiang2207@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2020-03-13
 * 
 * @copyright Copyright (c) 2020 
 * 
 */

#include "s51_fontlib.h"

/**
 * @brief Interface function
 * 
 * @param _data data
 * @return uint8_t Read the returned value
 */
uint8_t Simple51_FontLib_Interface(uint8_t _data, uint8_t _ss)
{
    uint8_t _getdata = 0x00;
    extern SPI_HandleTypeDef hspi1;

    pin_fontss = _ss;
    Simple51_SPI_TransmitReceive(&hspi1, &_data, &_getdata, 1);
    return _getdata;
}

/**
 * @brief This function is a character pointer, 
 *        which is converted into the data address in the word library through a formula
 * 
 * @param _str Address pointer of character to be converted
 * @param _fonttype The font type of the character to be converted
 * @return uint32_t Returns the address of the character
 */
uint32_t Simple51_FontLib_FindFirstAddress(uint8_t *_str, Font_type _fonttype)
{
    uint32_t _fontaddress = 0x000000;
    /*显示长度*/
    if (_fonttype == Font_8)
    {
        if (*_str >= 0x20 && *_str <= 0x7E)
        {
            _fontaddress = (uint32_t)(*_str) - 0x20;
            _fontaddress = (uint32_t)(_fontaddress * 0x05);
            return _fontaddress;
        }
    }
    if (_fonttype == Font_16)
    {
        if (*_str >= 0x20 && *_str <= 0x7E)
        {
            _fontaddress = (uint32_t)((*_str) - 0x20);
            _fontaddress = (uint32_t)(_fontaddress * 0x10);
            _fontaddress = (uint32_t)(_fontaddress + 0x1DB);
            return _fontaddress;
        }
        if (((*_str) >= 0xC2) && ((*_str) <= 0xD1) &&
            (*(_str + 1) >= 0x80) && (*(_str + 1) <= 0xBF))
        {
            _fontaddress = (uint32_t)((*_str) - 0xC2) * 0x800;
            _fontaddress += (uint32_t)(*(_str + 1) - 0x80) * 0x20;
            _fontaddress = (uint32_t)(_fontaddress + 0x7CB);
            return _fontaddress;
        }
        if (((*_str) >= 0xE2) && ((*_str) <= 0xEF) &&
            (*(_str + 1) >= 0x80) && (*(_str + 1) <= 0xBF) &&
            (*(_str + 2) >= 0x80) && (*(_str + 2) <= 0xBF))
        {
            _fontaddress = (uint32_t)((*_str) - 0xE2) * 0x20000;
            _fontaddress += (uint32_t)(*(_str + 1) - 0x80) * 0x800;
            _fontaddress += (uint32_t)(*(_str + 2) - 0x80) * 0x20;
            _fontaddress = (uint32_t)(_fontaddress + 0x87CB);
            return _fontaddress;
        }
    }
    return 0x000000;
}

/**
 * @brief Send address to library and return data
 * 
 * @param _fontaddress Font encoding first address
 * @param _pdata Data pointer returned
 * @param _len Data pointer length returned
 */
void Simple51_FontLib_ReadAddress(uint32_t _fontaddress, uint8_t *_pdata, uint8_t _len)
{
    Simple51_FontLib_Interface(0x03, RESET);
    Simple51_FontLib_Interface((uint8_t)(_fontaddress >> 16), RESET);
    Simple51_FontLib_Interface((uint8_t)(_fontaddress >> 8), RESET);
    Simple51_FontLib_Interface((uint8_t)(_fontaddress), RESET);
    for (; _len > 0; _len--)
    {
        *_pdata = Simple51_FontLib_Interface(0x00, RESET);
        _pdata++;
    }
    Simple51_FontLib_Interface(0x00, SET);
}
