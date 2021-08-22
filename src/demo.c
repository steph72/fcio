#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fcio.h"

void jiffySleep(int num)
{
    unsigned int t;

    t = clock();
    while ((clock() - t) < num)
        ;
}

void main(void)
{
    char i;
    fciInfo *img0;
    textwin *w0, *w1;

    fc_init(0, 0, 26, "borders.fci"); // init fcio with low res, 26 rows
    
    fc_textcolor(8);                  // orange

    img0 = fc_loadFCI("once.fci", 0, 0);         // load title image
    fc_center(0, 25, 40, "once upon a time..."); // display prompt at lower center
    fc_fadeFCI(img0, 0, 0, 128);                 // fade in title image
    jiffySleep(60);

    // we can easily scroll graphic areas...
    w0 = fc_makeWin(0, 0, 20, 25);
    w1 = fc_makeWin(20, 0, 20, 25);
    for (i = 0; i < 25; ++i)
    {
        fc_setwin(w0);
        fc_scrollDown();
        fc_setwin(w1);
        fc_scrollUp();
        jiffySleep(3);
    }

    jiffySleep(60);
    fc_screenmode(1, 0, 26); // activate H640 with 26 rows
    fc_freeGraphAreas();
    fc_textcolor(15);
    fc_center(0, 12, 80, "\"Horses fly without wings,");
    fc_center(0, 13, 80, " and conquer without swords\"");
    fc_center(0, 15, 80, "       -- Bedouin proverb");
    jiffySleep(60);

    // load a few files and display them directly
    fc_displayFCIFile("lucky1.fci", 0, 0);
    fc_displayFCIFile("luna.fci", 55, 14);
    fc_displayFCIFile("scarlett.fci", 0, 14);
    img0 = fc_displayFCIFile("lsc.fci", 50, 0);
    jiffySleep(120);

    fc_fadePalette(img0->paletteAdr, img0->paletteSize, true, 128, true);
    fc_freeGraphAreas();


    img0 = fc_loadFCI("luna2.fci", 0, 0);
    fc_screenmode(1, 0, 30);          // demonstrate tall 80columns display
    fc_setPalette(15, 12, 42, 12); // really dark gray/green
    fc_bordercolor(5);
    fc_bgcolor(15);

    fc_clrscr();
    for (i = 0; i < 30; ++i)
    {
        fc_gotoxy(78, i);
        fc_printf("%2d", i);
    }

    fc_gotoxy(0, 3);
    fc_textcolor(5);
    fc_underline(1);
    fc_puts("fcio features:\n\n");
    fc_underline(0);
    fc_puts("* standard io in 16 bit character mode\n"
            "  - fc_putc\n"
            "  - fc_puts\n"
            "  - fc_printf\n"
            "  - fc_gotoxy\n"
            "  - fc_putsxy\n"
            "  ... and much more\n\n"
            "* text windows\n"
            "* character attributes\n"
            "* extended screen sizes (PAL&NTSC)\n"
            "* scrolling\n"
            "* line and block fill commands\n"
            "* up to 16 independant bitmap areas\n"
            "* mix text and graphics easily\n"
            "* loading images from disc\n"
            "* protected palette and bitmap areas\n"
            "* palette fading\n\n");
    fc_textcolor(4);
    fc_flash(1);
    fc_revers(1);
    fc_center(0, fc_wherey(), 40, "Press any key!");
    fc_getkey();
    fc_displayFCI(img0, 40, 3, true);
    fc_line(0,fc_wherey(),40,32,5);
    fc_center(0,fc_wherey(),40,"Enjoy :)");

    while (1)
        ;
}