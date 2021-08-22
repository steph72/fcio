

#ifndef __FCIO
#define __FCIO

#include "memory.h"
#include <stdbool.h>

#ifndef __FCIO_VARS
#define __FCIO_VARS
#define SCREENBASE 0x12000l  // 16 bit screen
#define EXTCHARBASE 0x14000l // 'reserved' graphics for extended characters
#define SYSPAL 0x15000l      // system palette
#define PALBASE 0x15300l     // palettes for loaded images
#define GRAPHBASE 0x40000l   // bitmap characters
#define COLBASE 0xff81000l   // colours
#endif

#define FCBUFSIZE 0xff

#ifndef byte
typedef unsigned char byte;
#endif

#ifndef himemPtr
typedef unsigned long himemPtr;
#endif

#ifndef word
typedef unsigned int word;
#endif

extern char *fcbuf;

// --------------- graphics ------------------

typedef struct _fciInfo
{
    himemPtr baseAdr;
    himemPtr paletteAdr;
    byte paletteSize;
    byte reservedSysPalette;
    byte columns;
    byte rows;
    word size;
} fciInfo;

typedef struct _textwin
{
    byte xc;
    byte yc;
    byte x0;
    byte y0;
    byte width;
    byte height;
    byte textcolor;
    byte extAttributes;
} textwin;

extern byte gScreenColumns;  // number of screen columns (in characters)
extern byte gScreenRows;     // number of screen rows (in characters)
extern textwin *gCurrentWin; // current window

// --- general & initializations ---

void fc_init(byte h640, byte v400, byte rows, char *bordersFilename);
void fc_go16bit(byte h640, byte v400, byte rows);
void fc_go8bit();
void fc_fatal(const char *format, ...);

// --- borders, columns and titles ---

void fc_block(byte x0, byte y0, byte x1, byte y1, byte character, byte col);
void fc_hlinexy(byte x0, byte y, byte x1, byte lineChar);
void fc_vlinexy(byte x, byte y0, byte y1, byte lineChar);
void fc_line(byte x, byte y, byte width, byte character, byte col);

// --- keyboard input ---

void fc_emptyBuffer(void);
unsigned char fc_cgetc(void);
char fc_getkey(void);
char fc_getkeyP(byte x, byte y, const char *prompt);
char *fc_input(byte maxlen);
int fc_getnum(byte maxlen);
int fc_kbhit();

// --- string and character output ---

void fc_clrscr();
void fc_putc(char c);
void fc_puts(const char *s);
void fc_putsxy(byte x, byte y, char *s);
void fc_putcxy(byte x, byte y, char c);
void fc_printf(const char *format, ...);
void fc_gotoxy(byte x, byte y);
byte fc_wherex();
byte fc_wherey();
void fc_setwin(textwin *aWin);
textwin *fc_makeWin(byte x0, byte y0, byte width, byte height);
void fc_resetwin();
void fc_cursor(byte onoff);
void fc_center(byte x, byte y, byte width, char *text);
void fc_scrollUp();
void fc_scrollDown();

// colour, attributes and palette handling

void fc_revers(byte f);
void fc_flash(byte f);
void fc_bold(byte f);
void fc_underline(byte f);

void fc_loadPalette(himemPtr adr, byte size, byte reservedSysPalette);
void fc_setPalette(byte num, byte red, byte green, byte blue);
void fc_zeroPalette(byte reservedSysPalette);
void fc_fadePalette(himemPtr adr, byte size, byte reservedSysPalette, byte steps, bool fadeOut);
void fc_resetPalette();

void fc_textcolor(byte c);
#define fc_bordercolor(C) POKE(0xd020u, C)
#define fc_bgcolor(C) POKE(0xd021u, C)

// graphic areas
void fc_freeGraphAreas(void);
void fc_addGraphicsRect(byte x0, byte y0, byte width, byte height,
                        himemPtr bitmapData);
fciInfo *fc_loadFCI(char *filename, himemPtr address, himemPtr paletteAddress);
void fc_displayFCI(fciInfo *info, byte x0, byte y0);
void fc_fadeFCI(fciInfo *info, byte x0, byte y0, byte steps);
fciInfo *fc_displayFCIFile(char *filename, byte x0, byte y0);
void fc_plotExtChar(byte x, byte y, byte c);
void fc_plotPetsciiChar(byte x, byte y, byte c, byte color, byte exAttr);

// convenience stuff
void fc_clearFromTo(byte start, byte end);

#endif