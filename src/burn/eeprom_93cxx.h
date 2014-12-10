// 93Cxx EEPROM module

void EEPROMWrite(char SK, char CS, char DI);
int EEPROMRead();
void EEPROMFill(unsigned char* pData, int nOffset, int nSize);
void EEPROMReset();
void EEPROMScan(int nAction, int* pnMin);
void EEPROMExit();
int EEPROMInit(int nSize, int nWidth);


