/**
 * @brief For interface functions displayed by GUI, 
 *        different interfaces need to be adapted differently.
 *        Sacrifice Speed to Improve Compatibility
 * 
 * @param _page Number of pages displayed In the 12864 is 0-7
 * @param _column Number of rows displayed In the 12864 is 0-127
 */
void S51_GUI_Interface(uint8_t _page, uint8_t _column, uint8_t _data)
{
    KS0108_SetAddress(_page, _column);
    if (_column <= 63)
    {
        KS0108_Interface(TRANSMIT, KS0108_DATA, _data, LCD_SCREEN_0);
    }
    else
    {
        KS0108_Interface(TRANSMIT, KS0108_DATA, _data, LCD_SCREEN_1);
    }
}

/**
 * @brief 
 * 
 * @param _page Number of pages displayed In the 12864 is 0-7
 * @param _column Number of rows displayed In the 12864 is 0-127
 * @param _pagenum The number fo row to display
 * @param _columnnum The number of column to display
 * @param _displaydata The data to be display ,8bits
 * @param _inverse 0 is not inverted and 1 is inverted.
 */
void S51_GUI_Display_nxn(uint8_t _page, uint8_t _column,
                         uint8_t _pagenum, uint8_t _columnnum,
                         uint8_t *_displaydata, uint8_t _inverse)
{
    uint8_t i, j;
    for (j = 0; j < _pagenum; j++)
    {
        for (i = 0; i < _columnnum; i++)
        {
            (_inverse == SET) ? (~(*_displaydata)) : (*_displaydata = *_displaydata);
            S51_GUI_Interface(_page + j, _column + i, *_displaydata);
            _displaydata++;
        }
    }
}

/**
 * @brief The output of characters on the screen currently 
 *        supports ASCII and Chinese codes compatible with GB2312, 
 *        and more characters will be supported later on. 
 *        Currently supported fonts are 5*8 ASCII fonts, 
 *        8*16 ASCII fonts, and 16*16 fonts
 * 
 * @param _type Font type,use Font_type struct enum
 * @param _page Number of pages displayed In the 12864 is 0-7
 * @param _column Number of rows displayed In the 12864 is 0-127
 * @param _pdata The character to be entered
 * @param _strlen Enter the length of the character
 * @param _inverse 0 is not inverted and 1 is inverted.
 */
void S51_GUI_Display_Str(Font_type _type, uint8_t _page, uint8_t _column,
                         uint8_t *_pdata, uint8_t _strlen, uint8_t _inverse)
{
    uint8_t i, k;
    uint8_t _codebuf[32];

    (_strlen == 0) ? (k = 255) : (k = _strlen);

    for (i = 0; i < k; i++)
    {
        if (*_pdata >= 0x20 && *_pdata <= 0x7E)
        {
            if (_type == Font_8)
            {
                Simple51_FontLib_ReadAddress(Simple51_FontLib_FindFirstAddress(_pdata, _type), _codebuf, 5);
                S51_GUI_Display_nxn(_page, _column, 1, 5, _codebuf, _inverse);
                _column += 5;
            }
            if (_type == Font_16)
            {
                Simple51_FontLib_ReadAddress(Simple51_FontLib_FindFirstAddress(_pdata, _type), _codebuf, 16);
                S51_GUI_Display_nxn(_page, _column, 2, 8, _codebuf, _inverse);
                _column += 8;
            }
            _pdata++;
        }
        if (((*_pdata) >= 0xC2) && ((*_pdata) <= 0xD1) &&
            (*(_pdata + 1) >= 0x80) && (*(_pdata + 1) <= 0xBF))
        {
            if (_type == Font_16)
            {
                Simple51_FontLib_ReadAddress(Simple51_FontLib_FindFirstAddress(_pdata, _type), _codebuf, 32);
                S51_GUI_Display_nxn(_page, _column, 2, 16, _codebuf, _inverse);
                _column += 16;
            }
            _pdata += 2;
        }
        if (((*_pdata) >= 0xE2) && ((*_pdata) <= 0xEF) &&
            (*(_pdata + 1) >= 0x80) && (*(_pdata + 1) <= 0xBF) &&
            (*(_pdata + 2) >= 0x80) && (*(_pdata + 2) <= 0xBF))
        {
            if (_type == Font_16)
            {
                Simple51_FontLib_ReadAddress(Simple51_FontLib_FindFirstAddress(_pdata, _type), _codebuf, 32);
                S51_GUI_Display_nxn(_page, _column, 2, 16, _codebuf, _inverse);
                _column += 16;
            }
            _pdata += 3;
        }

        if (_strlen == 0 && *_pdata == 0)
        {
            break;
        }
    }
}