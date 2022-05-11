#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Funktionen.h"





#define smallrow            "\xDB\xDB\xDB\xDB\xDB\xDB\xDB"


#define Weiss       2
#define Schwarz     1
#define Leer        0
#define Spielbar    3

int main()
{
    struct cursor cursor = {0,0};
    struct directions direction;
    int brett[8][8] = {0};
    int playable_tiles_direction[8][8][8] = {0};
    int lastplay = Schwarz, white_tiles, black_tiles,savegame,playable,reset;
    long long starttime = time(NULL);
    struct time_played time_played;
    HANDLE  hConsole;



    //setzen der startsteine
    brett [3] [4] = Weiss;
    brett [4] [3] = Weiss;
    brett [3] [3] = Schwarz;
    brett [4] [4] = Schwarz;
    //einstellen der konsolengröße
    set_console_size(100, 36);

    //handle für farbeinstellungen
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    //main loop
    while (1)
    {

        //textfarbe zu hellgrau wechseln
        SetConsoleTextAttribute(hConsole, 8);

        //drucken der spieloptionen
        set_cursor (2,34);
        printf ("Laden");
        set_cursor (10,34);
        printf ("Speichern");
        set_cursor (22,34);
        printf ("Pause");
        set_cursor (30,34);
        printf ("Passen");
        set_cursor (39,34);
        printf ("Beenden");

        //zählen und anzeigen der momentan gespielten felder
        white_tiles=Count_Tiles (brett,Weiss);
        black_tiles=Count_Tiles (brett,Schwarz);
        set_cursor (80,5);
        printf ("Weiss: %2i", white_tiles);
        set_cursor (80,7);
        printf ("Schwarz: %2i", black_tiles);

        //anzeigen des spielers der grade am zug ist
        set_cursor (80,11);
        if (lastplay==Schwarz) printf ("Spieler: Weiss    ");
        else printf ("Spieler: Schwarz");


        //anzeigen eines timers der die zeit zählt seit spielstart
        set_cursor (80,1);
        time_played= caculate_time_played(starttime);
        if (time_played.s%2==0) printf ("%i : %i : %i ", time_played.h, time_played.m, time_played.s);  //wenn grade zahl dopplepunkte zwischen den zahlen
        else printf ("%i   %i   %i ", time_played.h, time_played.m, time_played.s);                     //wenn ungerade doppelpunkte nicht anzeigen



        //drucken und prÜfen des Spielfelds
        for (size_t x = 0; x < 8; x++)
        {
            for (size_t y = 0; y < 8; y++)
            {
                direction = is_playable(x,y,brett,lastplay);            //überprüfen des feldes auf spielbarkeit
                if (brett [x][y] ==  Leer||brett [x][y] == Spielbar)    //nur schreiben wenn feld spielbar oder leer ist
                {                                                       //auslesen der direction Struktur und setzen der bits im playables_tiles_direction array passend zu der ausgabe von der is_playable funktion
                    if (direction.playable==1) brett[x][y]=Spielbar;
                    if (direction.playable==0) brett[x][y]=Leer;
                    if (direction.UL == 1) playable_tiles_direction[x][y][0] = 1;
                    else playable_tiles_direction[x][y][0] = 0;
                    if (direction.U == 1) playable_tiles_direction[x][y][1] = 1;
                    else playable_tiles_direction[x][y][1] = 0;
                    if (direction.UR == 1) playable_tiles_direction[x][y][2] = 1;
                    else playable_tiles_direction[x][y][2] = 0;
                    if (direction.L == 1) playable_tiles_direction[x][y][3] = 1;
                    else playable_tiles_direction[x][y][3] = 0;
                    if (direction.R == 1) playable_tiles_direction[x][y][4] = 1;
                    else playable_tiles_direction[x][y][4] = 0;
                    if (direction.DL == 1) playable_tiles_direction[x][y][5] = 1;
                    else playable_tiles_direction[x][y][5] = 0;
                    if (direction.D == 1) playable_tiles_direction[x][y][6] = 1;
                    else playable_tiles_direction[x][y][6] = 0;
                    if (direction.DR == 1) playable_tiles_direction[x][y][7] = 1;
                    else playable_tiles_direction[x][y][7] = 0;
                }                                                       //aus brett array die belegung auslesen und diese dann auf dem bildschirm ausgeben
                if (brett[x][y] == Leer)
                {
                    empty_tile (x,y);
                }
                else if (brett[x][y] == Weiss)
                {
                    white_tile (x,y);
                }
                else if (brett[x][y] == Schwarz)
                {
                    Black_tile (x,y);
                }
                else if (brett[x][y] == Spielbar)
                {
                    empty_tile (x,y);
                    Playable_tile (x,y,lastplay);
                }
            }
        }
        /*
        brett auf spielbarkeit überprüfen
        wenn spielbar playable=1 wenn kein zug mehr möglich playable=0
        */
        playable=0;
        for (size_t x = 0; x < 8; x++)
        {
            for (size_t y = 0; y < 8; y++)
            {
                direction = is_playable(x,y,brett,Schwarz); //orüfen für schwarz
                if (direction.playable==1)
                {
                    playable = 1;
                    x=8;
                    y=8;
                }
                direction = is_playable(x,y,brett,Weiss);   //prüfen für weiss
                if (direction.playable==1)
                {
                    playable = 1;
                    x=8;
                    y=8;
                }


            }
        }

        //überprüfen ob spieler spielen kann für die passen funktion
        int playabale_tiles = Count_Tiles (brett,Spielbar);

        //anzeigen des cursors
        Cursor_tile (cursor.x, cursor.y, lastplay);


        //anzeigen des win-screens
        if (playable == 0)
        {
            if (white_tiles < black_tiles)
            {
                win_screen(time_played,Schwarz,white_tiles,black_tiles);
                reset=1;
            }
            else if (white_tiles > black_tiles)
            {
                win_screen(time_played,Weiss,white_tiles,black_tiles);
                reset=1;
            }
            else if (white_tiles == black_tiles)
            {
                win_screen(time_played,Leer,white_tiles,black_tiles);
                reset=1;
            }
        }
        //reset des spiels nach spielende
        if (reset == 1)
        {
            for(int x = 0; x < 8; x++)
            {
                for(int y = 0; y < 8; y++)
                {
                    brett[x][y] = Leer;
                }
            }
            cursor.x=0;
            cursor.y=0;
            starttime=time(NULL);
            lastplay=Schwarz;
            brett [3] [4] = Weiss;
            brett [4] [3] = Weiss;
            brett [3] [3] = Schwarz;
            brett [4] [4] = Schwarz;
            reset = 0;
        }

        //warten auf tastatureingabe
        switch(getch())
        {
        case 72: //pfeiltaste runter
            if (cursor.y >0)
                cursor.y--;
            break;
        case 80: //pfeiltaste hoch
            if (cursor.y <8)
                cursor.y++;
            break;
        case 77: //pfeiltaste rechts
            if (cursor.x <7)
                cursor.x++;
            break;
        case 75: //pfeiltaste links
            if (cursor.x >0)
                cursor.x--;
            break;
        case 13: //entertaste
            if (cursor.y<8) //nur wenn curur auf dem feld ist
            {
                if (brett[cursor.x][cursor.y]==Spielbar) //überprüfen auf spielbarkeit
                {
                    if (lastplay == Schwarz)            //weiss am zug
                    {
                        brett [cursor.x] [cursor.y] = Weiss;    //feld auf weiss setzem
                        capture_pieces(cursor.x,cursor.y,brett,lastplay,playable_tiles_direction);
                        lastplay = Weiss; //wechseln der person am zug
                    }
                    else if (lastplay == Weiss)         //schwarz am zug
                    {
                        brett [cursor.x] [cursor.y] = Schwarz;
                        capture_pieces(cursor.x,cursor.y,brett,lastplay,playable_tiles_direction);
                        lastplay = Schwarz;
                    }
                }
            }
            if (cursor.y==8 && cursor.x==0) //wenn cursor Über der laden funktion
            {
                select_load(&savegame); //auswahl des savegames zum laden
                if (savegame == 11)     //savegame 11 = back
                {
                    break;
                }
                else
                {
                    load_game(brett,&starttime,&lastplay,&cursor.x,&cursor.y,savegame);//spiel laden aus datei
                }
                break;
            }
            if (cursor.y==8 && cursor.x==1) //wenn curosr über speichern
            {
                select_save(&savegame);     //asuwahl des savegames zum speichern
                if (savegame == 11)
                {
                    break;
                }
                else
                {
                    save_game(brett,starttime,lastplay,cursor.x,cursor.y,savegame); //spiel speichern in datei
                }
                break;
            }
            if (cursor.y==8 && cursor.x==2) //wenn cursor Über der pause funktion
            {
                starttime = pause (starttime); //pausieren des spiels
                break;
            }
            if (cursor.y==8 && cursor.x==3) //wenn cursur über passen funktion ist
            {
                if (lastplay == Schwarz)
                {
                    if(playabale_tiles==0) lastplay = Weiss; //wenn weiss am zug und nicht spielbar ist spieler wechseln
                    else        //fehler anzeigen wenn eine spielbare fläche verfügbar ist
                    {
                        set_cursor (5,33);
                        printf ("Passen ist nur moeglich wenn kein spielbarer zug verfuegbar ist");
                        getch();
                        set_cursor (5,33);
                        printf ("\33[2K");
                    }
                }
                else if (lastplay == Weiss)
                {
                    if(playabale_tiles==0) lastplay = Schwarz;
                    else
                    {
                        set_cursor (5,33);
                        printf ("Passen ist nur moeglich wenn kein spielbarer zug verfuegbar ist");
                        getch();
                        set_cursor (5,33);
                        printf ("\33[2K");
                    }
                }
                break;
            }
            if (cursor.y==8 && cursor.x==4) //wenn cursor über der beenden funktion
            {
                exit_game( brett, starttime, lastplay, cursor.x, cursor.y); //aufrufen der spiel beenden funktion
                break;
            }

        }
        if (cursor.y >= 8 && cursor.x >= 4) //cursor überlauf nach rechts verhindern
        {
            cursor.x = 4;
        }


    }
    return 0;
}


