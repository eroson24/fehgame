#ifndef FEHSD_H
#define FEHSD_H
// #include "SDHC.h"
// #include "ff.h"
// #include "ffconf.h"
// #include "diskio.h"
#include "FEHFile.h"
#include "FEHUtility.h"

#define SD_DEPRECATED() std::cout << CONSOLE_WARN("") << CONSOLE_BLUE("(FEHSD)") << " The FEHSD library is not recommended for use with the Proteus Simulator; Consider using C ("<< CONSOLE_BLUE("fprintf") << " / " << CONSOLE_BLUE("fscanf") << ") or C++ (" << CONSOLE_BLUE("std::fstream") << ") file I/O"<< std::endl;


class FEHSD
{
public:
    FEHSD();
    FEHFile *FOpen(const char *str, const char *mode);
    int FClose(FEHFile *fptr);
    int FCloseAll();
    int FPrintf(FEHFile *fptr, const char *format,
                /* Pointer to the format string */...);
    int FScanf(FEHFile *fptr, const char *format, ...);
    int FEof(FEHFile *fptr);
    //int FSeek(FEHFile *fptr, long int offset, int position);

private:
    int Initialize();
    int isInitialized;
    int numberOfFiles;
};

extern FEHSD SD;
#endif
