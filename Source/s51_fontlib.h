#ifndef __S51_FONTLIB_H__
#define __S51_FONTLIB_H__

#include "Simple51Core.h"
// #include "s51_spi.h"

typedef enum
{
    Font_8,
    Font_16,
    Font_24,
} Font_type;

uint32_t Simple51_FontLib_FindFirstAddress(uint8_t *_str, Font_type _fonttype);
void Simple51_FontLib_ReadAddress(uint32_t _fontaddress, uint8_t *_pdata, uint8_t _len);

#endif