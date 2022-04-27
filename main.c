#include <stdio.h>
#include <stdlib.h>
#include <windows.h>




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
    x--;
    y--;

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
    x--;
    y--;

    set_cursor (x_cursor[x],y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 4);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+1);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+2);
    printf (smallrow);
}

#define row                 "\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB"
#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"


#define Weiss       2
#define Schwarz     1
#define Leer        0
#define Spielbar    3

int main()
{
    unsigned int brett[8][8] ={0};
    int cursor_position_x, cursor_position_y;
    set_code_page (437);
    //set_console_width(67);
    set_console_size(75, 35);
    int i, j, y = 1;


     HANDLE  hConsole;
    int k;

  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // you can loop k higher to see more color choices
/*  for(k = 1; k < 255; k++)
  {
    SetConsoleTextAttribute(hConsole, k);
    printf("%3d  %s\n", k, "I want to be nice today!");
  }
*/
SetConsoleTextAttribute(hConsole, 2);
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
white_tile (4,5);
white_tile (5,4);
Black_tile (4,4);
Black_tile (5,5);


printf ("\n");
getchar();
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
