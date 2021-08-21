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
    char i, j;
    fciInfo *img0, *img1;
    textwin *w0, *w1;

    fc_init(0, 0, 25, NULL); // init fcio

    fc_bordercolor(5);
    fc_textcolor(8); // orange

    for (j=0;j<12;j++)
    {
        fc_go16bit(0,0,25+j);
        for (i = 0; i < 25+j; ++i)
        {
            fc_gotoxy(0, i);
            fc_printf("%d", i);
        }
        fc_getkey();
    }

    img0 = fc_loadFCI("once.fci", 0, 0);         // load title image
    fc_center(0, 25, 40, "once upon a time..."); // display prompt at lower center
    fc_fadeFCI(img0, 0, 0, 128);                 // fade in title image
    jiffySleep(60);

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
    fc_go16bit(1, 0, 26); // activate H640
    fc_freeGraphAreas();
    fc_textcolor(15);
    fc_center(0, 12, 80, "\"Horses fly without wings,");
    fc_center(0, 13, 80, " and conquer without swords\"");
    fc_center(0, 15, 80, "       -- Bedouin proverb");
    jiffySleep(60);

    fc_displayFCIFile("lucky1.fci", 0, 0);
    fc_displayFCIFile("luna.fci", 55, 12);
    fc_displayFCIFile("scarlett.fci", 0, 12);
    img0 = fc_displayFCIFile("lsc.fci", 50, 0);
    jiffySleep(120);

    fc_fadePalette(img0->paletteAdr, img0->paletteSize, true, 128, true);
    fc_freeGraphAreas();

    fc_clrscr();
    fc_displayFCIFile("luna2.fci", 40, 0);

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
            "* palette fading\n");
    fc_textcolor(4);
    fc_flash(1);
    fc_revers(1);
    fc_center(0, 22, 40, "Enjoy!");
    while (1)
        ;
}