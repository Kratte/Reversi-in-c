#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "funktionen.h"



#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"


#define Weiss       2
#define Schwarz     1
#define Leer        0
#define Spielbar    3

struct directions is_playable(int x, int y, int brett[8][8], int lastplay)
{
    struct directions directions={0,0,0,0,0,0,0,0};
    directions.playable = FALSE;
    if ( !is_valid_position( x, y ) ) return directions;
    if ( brett[x][y] != Leer && brett[x][y] != Spielbar) return directions;
    int current_player=0;

if (lastplay == 1)
{
    current_player = 2;
}
else
{
    current_player = 1;
}
    // Test UL diagonal
    int y_pos = y-1, x_pos = x-1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
    {
        y_pos --;
        x_pos --;
    }
    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.UL = 1;
        directions.playable = TRUE;
    }

    // Test UP path
    y_pos = y-1, x_pos = x;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        y_pos --;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.U = 1;
        directions.playable = TRUE;
    }

    // Test UR diagonal
    y_pos = y-1, x_pos = x+1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
    {
        y_pos --;
        x_pos ++;
    }
    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.UR = 1;
        directions.playable = TRUE;
    }

    // Test LEFT path
    y_pos = y, x_pos = x-1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        x_pos --;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.L = 1;
        directions.playable = TRUE;
    }

    // Test RIGHT path
    y_pos = y, x_pos = x+1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        x_pos ++;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.R = 1;
        directions.playable = TRUE;
    }

    // Test DL diagonal
    y_pos = y+1, x_pos = x-1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
    {
        y_pos ++;
        x_pos --;
    }
    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.DL = 1;
        directions.playable = TRUE;
    }

    // Test DOWN path
    y_pos = y+1, x_pos = x;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        y_pos ++;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player  )
    {
        directions.D = 1;
        directions.playable = TRUE;
    }

    // Test DR diagonal
    y_pos = y+1, x_pos = x+1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
    {
        y_pos ++;
        x_pos ++;
    }
    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.DR = 1;
        directions.playable = TRUE;
    }
    return directions;
}

void capture_pieces( int x, int y, int brett[8][8],int lastplay, int playable_tiles_direction[8][8][8] )
{
int current_player;
int opponent_player;
if (lastplay == 1)
{
    current_player = 2;
    opponent_player = 1;
}
else
{
    current_player = 1;
    opponent_player = 2;
}
    int x_pos, y_pos;

    // Capture UL diagonal
    if ( playable_tiles_direction[x][y][0] )
    {
        y_pos = y-1, x_pos = x-1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos --;
            x_pos --;
        }
    }

    // Capture UP path
    if ( playable_tiles_direction[x][y][1] )
    {
        y_pos = y-1, x_pos = x;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos --;
        }
    }

    // Capture UR diagonal
    if ( playable_tiles_direction[x][y][2] )
    {
        y_pos = y-1, x_pos = x+1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos --;
            x_pos ++;
        }
    }

    // Capture LEFT path
    if ( playable_tiles_direction[x][y][3] )
    {
        y_pos = y, x_pos = x-1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            x_pos --;
        }
    }

    // Capture RIGHT path
    if ( playable_tiles_direction[x][y][4] )
    {
        y_pos = y, x_pos = x+1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            x_pos ++;
        }
    }

    // Capture DL diagonal
    if ( playable_tiles_direction[x][y][5] )
    {
        y_pos = y+1, x_pos = x-1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos ++;
            x_pos --;
        }
    }

    // Capture DOWN path
    if ( playable_tiles_direction[x][y][6] )
    {
        y_pos = y+1, x_pos = x;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos ++;
        }
    }

    // Capture DR diagonal
    if ( playable_tiles_direction[x][y][7] )
    {
        y_pos = y+1, x_pos = x+1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos ++;
            x_pos ++;
        }
    }
}

int distance( int X1, int y1, int x1, int y2 )
{
    int dx = abs( X1 - x1 ), dy = abs( y1 - y2 );
    if ( dx > 0 ) return dx;
    return dy;
}

int is_valid_position( int x, int y )
{
    if ( x < 0 || x >= 8 || y < 0 || y >= 8 ) return FALSE;
    return TRUE;
}

void white_tile (int x, int y)
{
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
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x],y_cursor[y]);
    SetConsoleTextAttribute(hConsole, 8);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+1);
    printf (smallrow);
    set_cursor (x_cursor[x],y_cursor[y]+2);
    printf (smallrow);
}
void Playable_tile (int x, int y,int lastplay)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lastplay == 1) SetConsoleTextAttribute(hConsole, 7);
    else   SetConsoleTextAttribute(hConsole, 8);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};

    set_cursor (x_cursor[x]+3,y_cursor[y]+1);

    printf ("\xDB");
}
void Cursor_tile (int x, int y,int lastplay)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lastplay == 1) SetConsoleTextAttribute(hConsole, 7);
    else   SetConsoleTextAttribute(hConsole, 8);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};
    int y_cursor[8] = {1,5,9,13,17,21,25,29};
        for (size_t i = 0; i < 8; i++)
    {
        set_cursor  (0,y_cursor[i]-1);
        printf ("\33[2K");
    }
        set_cursor  (0,32);
        printf ("\33[2K");
    if (y<8){





    set_cursor (x_cursor[x]-1,y_cursor[y]-1);
    printf ("\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    set_cursor (x_cursor[x]-1,y_cursor[y]+3);
    printf ("\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    set_cursor (x_cursor[x]+3,y_cursor[y]+2);
    }
    else{
    int x_cursor2[5] = {2,10,22,30,39};
    set_cursor (x_cursor2[x],34);
    }
}
void empty_tile (int x, int y)
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

int save_game ( int brett[8][8], long long starttime, int lastplay, int x, int y, int savegame)
{
    int timeplayed = time(NULL) - starttime;
    FILE *fp;
    if (savegame == 1) fp = fopen ("savegame1.txt","w");
    else if(savegame == 2 ) fp = fopen ("savegame2.txt","w");
    else if(savegame == 3 ) fp = fopen ("savegame3.txt","w");
    else if(savegame == 4 ) fp = fopen ("savegame4.txt","w");
    else if(savegame == 5 ) fp = fopen ("savegame5.txt","w");
    else if(savegame == 6 ) fp = fopen ("savegame6.txt","w");
    else if(savegame == 7 ) fp = fopen ("savegame7.txt","w");
    else if(savegame == 8 ) fp = fopen ("savegame8.txt","w");
    else if(savegame == 9 ) fp = fopen ("savegame9.txt","w");
    else if(savegame == 10 ) fp = fopen ("savegame10.txt","w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            fprintf(fp, "%d ", brett[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "%d %d %d %d %d\n", timeplayed ,lastplay, x, y, 0);
    fclose(fp);
    return 0;
}

int load_game (int brett[8][8], long long *starttime, int *lastplay, int *x, int *y, int savegame)
{
    int timeplayed;
    FILE *fp;
    if (savegame == 1) fp = fopen ("savegame1.txt","r");
    else if(savegame == 2 ) fp = fopen ("savegame2.txt","r");
    else if(savegame == 3 ) fp = fopen ("savegame3.txt","r");
    else if(savegame == 4 ) fp = fopen ("savegame4.txt","r");
    else if(savegame == 5 ) fp = fopen ("savegame5.txt","r");
    else if(savegame == 6 ) fp = fopen ("savegame6.txt","r");
    else if(savegame == 7 ) fp = fopen ("savegame7.txt","r");
    else if(savegame == 8 ) fp = fopen ("savegame8.txt","r");
    else if(savegame == 9 ) fp = fopen ("savegame9.txt","r");
    else if(savegame == 10 ) fp = fopen ("savegame10.txt","r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    printf ("test");
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            fscanf(fp, "%d ", &brett[i][j]);
        }
    }
    printf ("test2");
    fscanf(fp, "%d %d %d %d\n", &timeplayed, lastplay, x, y);
    printf ("test3");
    *starttime = time(NULL) - timeplayed;
    fclose(fp);
    return 0;
}

int select_save (int *savegame)
{
    struct cursor cursorsave = {0,0};
    int cursory[11] = {6,8,10,12,14,16,18,20,22,24,26};
    for (size_t i = 0; i < 32; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,3);
    printf("Select savegame to Save:");
    set_cursor (20,6);
    printf ("savegame 1");\
    set_cursor (20,8);
    printf ("savegame 2");
    set_cursor (20,10);
    printf ("savegame 3");
    set_cursor (20,12);
    printf ("savegame 4");
    set_cursor (20,14);
    printf ("savegame 5");
    set_cursor (20,16);
    printf ("savegame 6");
    set_cursor (20,18);
    printf ("savegame 7");
    set_cursor (20,20);
    printf ("savegame 8");
    set_cursor (20,22);
    printf ("savegame 9");
    set_cursor (20,24);
    printf ("savegame 10");
    set_cursor (20,26);
    printf ("back");
    while (1)
    {
    set_cursor (20,cursory[cursorsave.y]);
        switch(getch()){
            case 72:
                if (cursorsave.y >0)
                    cursorsave.y--;
                break;
            case 80:
                if (cursorsave.y <10)
                    cursorsave.y++;
                break;
            case 13:
                *savegame = cursorsave.y+1;
                    for (size_t i = 0; i < 32; i++)
                        {
                            set_cursor (1,i+1);
                            printf ("\33[2K");
                        }
                return cursorsave.y+1;
            }
    }
}

int select_load (int *savegame)
{
    struct cursor cursorsave = {0,0};
    int cursory[11] = {6,8,10,12,14,16,18,20,22,24,26};
    for (size_t i = 0; i < 32; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,3);
    printf("Select savegame to Load:");
    set_cursor (20,6);
    printf ("savegame 1");\
    set_cursor (20,8);
    printf ("savegame 2");
    set_cursor (20,10);
    printf ("savegame 3");
    set_cursor (20,12);
    printf ("savegame 4");
    set_cursor (20,14);
    printf ("savegame 5");
    set_cursor (20,16);
    printf ("savegame 6");
    set_cursor (20,18);
    printf ("savegame 7");
    set_cursor (20,20);
    printf ("savegame 8");
    set_cursor (20,22);
    printf ("savegame 9");
    set_cursor (20,24);
    printf ("savegame 10");
    set_cursor (20,26);
    printf ("back");
    while (1)
    {
    set_cursor (20,cursory[cursorsave.y]);
        switch(getch()){
            case 72:
                if (cursorsave.y >0)
                    cursorsave.y--;
                break;
            case 80:
                if (cursorsave.y <10)
                    cursorsave.y++;
                break;
            case 13:
                *savegame = cursorsave.y+1;
                    for (size_t i = 0; i < 32; i++)
                        {
                            set_cursor (1,i+1);
                            printf ("\33[2K");
                        }
                return cursorsave.y+1;
            }
    }
}

void win_screen (struct time_played time_played, int winner, int white_tiles, int black_tiles)
{
      for (size_t i = 0; i < 35; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,5);
    if (winner == Schwarz) printf ("Schwarz hat gewonnen!");
    else if (winner == Weiss) printf ("Weiss hat gewonnen!");
    else printf ("Unentschieden!");
    set_cursor (20,7);
    printf ("Spieldauer");
    set_cursor (20,8);
    printf ("%ih : %im : %is",time_played.h,time_played.m,time_played.s);

    set_cursor (20,10);
    printf ("Endspielstand");
    set_cursor (20,11);
    printf ("Weiss: %2i", white_tiles);
    set_cursor (20,12);
    printf ("Schwarz: %2i", black_tiles);
    set_cursor (20,14);
    printf ("Taste druecken um ein neues Spiel zu starten");
    getch();
    getch();
    for (size_t i = 0; i < 35; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");

    }


}

void exit_game ( int brett[8][8], long long starttime, int lastplay, int x, int y)
{
    int savegame, i=0,cursor=0;
    for (size_t i = 0; i < 35; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    while (i == 0 )
    {
        i=0;
            set_cursor (20,5);
                printf ("Wollen Sie das Spiel vorher Speichern?");
            set_cursor (35,7);
                printf ("ja    /   nein");
            if(cursor==0) set_cursor (35,7);
            else if(cursor==1) set_cursor (45,7);
switch(getch()){
            break;
        case 77:
                cursor=1;
            break;
        case 75:
                cursor=0;
            break;
        case 13:
        if (cursor==0)
        {
            select_save(&savegame);
            if (savegame == 11)
            {
            break;
            }
            else
            {
            save_game(brett,starttime,lastplay,x,y,savegame);
            i=1;
            }
        break;
        }
        else if (cursor==1)
        {
        i=1;
        break;
        }
    }
    for (size_t i = 0; i < 35; i++)
            {
            set_cursor (1,i+1);
            printf ("\33[2K");
            }
}
i=0;
    while (i == 0 )
    {
        i=0;
            set_cursor (20,5);
                printf ("Wollen Sie das Spiel Wirklioh beenden?");
            set_cursor (35,7);
                printf ("ja    /   nein");
                if(cursor==0)
                    set_cursor (35,7);
                    else
                    set_cursor (45,7);
    switch(getch()){
            break;
        case 77:
                cursor=1;
            break;
        case 75:
                cursor=0;
            break;
        case 13:
        if (cursor==0)
        {
            exit(0);
        break;
        }
        else if (cursor==1)
        {
        return;
        }
        break;

        }
    for (size_t i = 0; i < 35; i++)
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }

    }
}


/*
counts the number of tiles of a player

*/
int Count_Tiles (int brett[8][8],int tile)
{
    int k=0;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (brett[i][j]==tile)
            {
                k++;
            }
        }
    }
    return k;
}
/*
takes the UNIX timestamp when the game was started
and returns a struct with the time in hours, minutes and seconds
*/

struct time_played caculate_time_played(long long starttime)
{
    struct time_played time_played_since;
    long long time_played_in_seconds = time(NULL)-starttime;
    time_played_since.s = time_played_in_seconds % 60;
    time_played_since.m = (time_played_in_seconds / 60) % 60;
    time_played_since.h = (time_played_in_seconds / 3600);
    return time_played_since;
}
long long pause (long long starttime)
{
    long long pausestart = time(NULL);

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    set_cursor (78,1);
    printf ("||");
    set_cursor (25,10);
    printf ("Das Spiel ist Pausiert!");
    set_cursor (10,11);
    printf ("Druecken sie eine Beliebige Taste zum Fortfahren");
    getch();
    set_cursor (78,1);
    printf ("  ");
    set_cursor (70,10);
    printf ("\33[2K");
    set_cursor (70,11);
    printf ("\33[2K");

    return starttime+time(NULL)-pausestart;
    }





//funktionen geklaut von wichmann

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


