#include "memory.h"
#include "fcio.h"
#include <stdio.h>
#include <stdlib.h>


#ifndef himemPtr
typedef unsigned long himemPtr;
#endif

unsigned int readExt(FILE *inFile, himemPtr addr, byte skipCBMAddressBytes) {

    unsigned int readBytes;
    unsigned int overallRead;
    unsigned long insertPos;

    insertPos= addr;
    overallRead= 0;

    if (skipCBMAddressBytes) {
        fread(drbuf, 1, 2, inFile);
    }

    do {
        readBytes= fread(drbuf, 1, FCBUFSIZE, inFile);
        if (readBytes) {
            overallRead+= readBytes;
            lcopy((long)drbuf, insertPos, readBytes);
            insertPos+= readBytes;
        }
    } while (readBytes);

    return overallRead;
}

unsigned int loadExt(char *filename, himemPtr addr, byte skipCBMAddressBytes) {

    FILE *inFile;
    word readBytes;

    inFile= fopen(filename, "r");
    readBytes= readExt(inFile, addr, skipCBMAddressBytes);
    fclose(inFile);

    if (readBytes==0) {
        fc_fatal("0 bytes from %s",filename);
    }

    return readBytes;
}
