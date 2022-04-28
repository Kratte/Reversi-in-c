#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
struct cursor
{
    int x;
    int y;
};


int set_console_width(const int width);
int set_console_size(const int width, const int height);
int set_code_page(const int code_page);
int set_cursor(const int x, const int y);
int set_color(const char color);

void white_tile (int x, int y)
{
#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x],y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 7);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+1);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+2);
    printf (smallrow);
}
void Black_tile (int x, int y)
{
#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x],y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 4);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+1);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+2);
    printf (smallrow);
}
void Playable_tile (int x, int y)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x]+6,y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 8);
    printf ("\xDB");
}
void Cursor_tile (int x, int y)
{
    if (y<8){
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x]+3,y_cursor[y]+1);
    }
    else{
    int x_cursor2[5] = {2,10,22,30,46};
    set_cursor (x_cursor2[x],34);
    }
}
void Empty_tile (int x, int y)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x],y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 2);
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    set_cursor (x_cursor[x],y_cursor[y]+1);
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    set_cursor (x_cursor[x],y_cursor[y]+2);
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
}


#define row                 "\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB"
#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"


#define Weiss       2
#define Schwarz     1
#define Leer        0
#define Spielbar    3

int main()
{
    struct cursor cursor = {0,0};
    unsigned int brett[8][8] ={0};
    int lastplay = Schwarz;
    brett [3] [4] = Weiss;
    brett [4] [3] = Weiss;
    brett [3] [3] = Schwarz;
    brett [4] [4] = Schwarz;
    brett [2] [3] = Spielbar;
    //set_code_page (437);
    set_console_size(80, 36);
     HANDLE  hConsole;

 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
while (1)
{

SetConsoleTextAttribute(hConsole, 2);

/*
set_cursor(2,1);
printf (row);
set_cursor(2,2);
printf (row);
set_cursor(2,3);
printf (row);
set_cursor(2,5);
printf (row);
set_cursor(2,6);
printf (row);
set_cursor(2,7);
printf (row);
set_cursor(2,9);
printf (row);
set_cursor(2,10);
printf (row);
set_cursor(2,11);
printf (row);
set_cursor(2,13);
printf (row);
set_cursor(2,14);
printf (row);
set_cursor(2,15);
printf (row);
set_cursor(2,17);
printf (row);
set_cursor(2,18);
printf (row);
set_cursor(2,19);
printf (row);
set_cursor(2,21);
printf (row);
set_cursor(2,22);
printf (row);
set_cursor(2,23);
printf (row);
set_cursor(2,25);
printf (row);
set_cursor(2,26);
printf (row);
set_cursor(2,27);
printf (row);
set_cursor(2,29);
printf (row);
set_cursor(2,30);
printf (row);
set_cursor(2,31);
printf (row);
*/
SetConsoleTextAttribute(hConsole, 8);
set_cursor (2,34);
printf ("Laden");
set_cursor (10,34);
printf ("Speichern");
set_cursor (22,34);
printf ("Pause");
set_cursor (30,34);
printf ("Ueberspringen");
set_cursor (46,34);
printf ("Aufgeben");

for (size_t i = 0; i < 8; i++)
{
    for (size_t j = 0; j < 8; j++)
    {
        if (brett[i][j] == Leer)
        {
            Empty_tile (i,j);
        }
        else if (brett[i][j] == Weiss)
        {
            white_tile (i,j);
        }
        else if (brett[i][j] == Schwarz)
        {
            Black_tile (i,j);
        }
        else if (brett[i][j] == Spielbar)
        {
            Empty_tile (i,j);
            Playable_tile (i,j);
        }
    }
}
Cursor_tile (cursor.x, cursor.y);

 switch(getch()){
        case 72:
            if (cursor.y >0)
                cursor.y--;
            break;
        case 80:
            if (cursor.y <8)
                cursor.y++;
            break;
        case 77:
            if (cursor.x <7)
                cursor.x++;
            break;
        case 75:
            if (cursor.x >0)
                cursor.x--;
            break;
        case 13:
            if (lastplay == Schwarz)
            {
            brett [cursor.x] [cursor.y] = Weiss;
            lastplay = Weiss;
            }
            else if (lastplay == Weiss)
            {
            brett [cursor.x] [cursor.y] = Schwarz;
            lastplay = Schwarz;
            }
            break;
        }
        if (cursor.y >= 8 && cursor.x >= 4)
        {
            cursor.x = 4;
        }
}
return 0;
}


/**
 * \ingroup KonsolenDemo
 * \brief Sets code page for current console to allow printing of special
 * characters. See also "C-Programmieren von Anfang an", page 307ff.
 *
 * \param code_page number identifying code page to be set
 * \return 0 if code page was set, else 1
 */
int set_code_page(const int code_page)
{
    int set_code_page_failed = 0;

    set_code_page_failed = SetConsoleOutputCP(code_page);

    // reverse "wrong" return value from Windows API
    return set_code_page_failed ? 0 : 1;
}


/**
 * \ingroup KonsolenDemo
 * \brief Sets width of console window.
 *
 * \param width width of console window as number of characters
 * \return 0 if console width was set, else 1
 */
int set_console_width(int width)
{
    int return_value = 0;
    char temp[255];

    // Prepare command string and send it to OS
    sprintf(temp, "mode CON: COLS=%i", width);
    return_value = system(temp);

    return return_value;
}


/**
 * \ingroup KonsolenDemo
 * \brief Sets size of console window.
 *
 * \param width width of console window as number of characters
 * \param height height of console window as number of characters
 * \return 0 if console size was set, else 1
 */
int set_console_size(const int width, const int height)
{
    int return_value = 0;
    char temp[255];

    // Prepare command string and send it to OS
    sprintf(temp, "mode %i, %i", width, height);
    return_value = system(temp);

    return return_value;
}


/**
 * \ingroup KonsolenDemo
 * \brief Sets cursor to a given position on the current console.
 *
 * \param x x-coordinate to be set
 * \param y y-coordinate to be set
 * \return 0 if cursor was set, 1 if failed
 */
int set_cursor(const int x, const int y)
{
    int set_position_failed = 0;
    int return_value = 0;
    HANDLE hstdout;

    COORD coordinates;
    coordinates.X= x;
    coordinates.Y= y;

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    set_position_failed = SetConsoleCursorPosition(hstdout, coordinates);

    // reverse "wrong" return value from Windows API
    if (set_position_failed)
    {
        return_value = 0;
    }
    else
    {
        return_value = 1;
    }

    return return_value;
}


/**
 * \ingroup KonsolenDemo
 * \brief Sets color of current console
 *
 * \param color color to be set (see comment)
 * \return 0 if code page was set, else 1
 */
int set_color(const char color)
{
    int set_color_failed = 0;

    /* Colors are defined by two hexadecimal numbers. First number sets
     * background color, the second number sets foreground color. Each one
     * be one of the following values:
     *     0 = black         8 = dark grey
     *     1 = dark blue     9 = blue
     *     2 = drk green     A = green
     *     3 = blue green    B = cyan
     *     4 = dark red      C = red
     *     5 = purple        D = magenta
     *     6 = ocher         E = yellow
     *     7 = light grey    F = white
     */

    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstdout, &csbi);

    set_color_failed = SetConsoleTextAttribute(hstdout, color);

    // reverse "wrong" return value from Windows API
    return set_color_failed ? 0 : 1;
}