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



/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Kontrolliert welche Richtung spielbar ist
 *
 * \param x x-Position des Steines
 * \param y y-Position des Steines
 * \param brett [8][8] array mit den Steinen
 * \param lastplay Spieler der vorher gespielt hat
 * \return Struct directions, alle Richtungen in die spielbar ist
 *  modified from: rodolfoams (rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br)
 */

struct directions is_playable(int x, int y, int brett[8][8], int lastplay)
{
    struct directions directions= {0,0,0,0,0,0,0,0};
    directions.playable = FALSE;        //Standartm��ig wird die Spielbar-Variable auf False gesetzt
    if ( !is_valid_position( x, y ) ) return directions;         //wenn die gew�hlte Position valide ist werden die m�glichen Spielbahnen zur�ck gegeben
    if ( brett[x][y] != Leer && brett[x][y] != Spielbar) return directions;
    int current_player=0;

    if (lastplay == 1)      //Wenn Spieler 1 als letztes gesetzt hat:
    {
        current_player = 2; //Spieler 2 ist der aktuelle Spieler
    }
    else
    {
        current_player = 1; //Spieler 1 ist der aktuelle Spieler
    }
    // Test Oben Links diagonal
    int y_pos = y-1, x_pos = x-1;   //Diagonal die Postion verschieben
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )  // �berpr�fung ob Position i.O ist und ob an der stelle bereits ein gegnerischer Stein liegt
    {
        y_pos --;   // wenn ja, wird weiter Diagonal geschaut
        x_pos --;
    }
    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )     //�berpr�fung ob Position i.O ist und ob an der stelle bereits ein eigener Stein liegt
    {
       directions.UL = 1;              //Richtung unten Links wird auf 1 gesetzt
        directions.playable = TRUE;     // Spielbar wird auf True gesetzt
    }

    // Test Oben Grade
    y_pos = y-1, x_pos = x;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        y_pos --;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.U = 1;
        directions.playable = TRUE;
    }

    // Test oben Rechts Diagonal
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

    // Test Links path
    y_pos = y, x_pos = x-1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        x_pos --;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.L = 1;
        directions.playable = TRUE;
    }

    // Test Rechts path
    y_pos = y, x_pos = x+1;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        x_pos ++;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player )
    {
        directions.R = 1;
        directions.playable = TRUE;
    }

    // Test unten Links Diagonal
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

    // Test unten path
    y_pos = y+1, x_pos = x;
    while ( is_valid_position( y_pos, x_pos ) && brett[x_pos][y_pos] == lastplay )
        y_pos ++;

    if ( is_valid_position( y_pos, x_pos ) && distance( y, x, y_pos, x_pos ) > 1 && brett[x_pos][y_pos] == current_player  )
    {
        directions.D = 1;
        directions.playable = TRUE;
    }

    // Test unten Rechts Diagonal
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
    return directions;  //R�ckgabe des Struct directions
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Die zwischen zwei eigenen Steinen liegenden gegnerischen Steine werden umgedreht
 *
 * \param x x-Position des Steines
 * \param y y-Position des Steines
 * \param brett [8][8] array mit den Steinen
 * \param lastplay Spieler der vorher gespielt hat
 * \param playable_tiles_direction[8][8][8] Array mit den m�glichen Spielrichtungen
 * \return void
 *  modified from: rodolfoams (rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br)
 */

void capture_pieces( int x, int y, int brett[8][8],int lastplay, int playable_tiles_direction[8][8][8] )
{
    int current_player;
    int opponent_player;
    if (lastplay == 1)          //Definition des letzten Spielers, wenn als letztes Spieler 1 gesprielt hat
    {
        current_player = 2;     //aktueller Spieler 2
        opponent_player = 1;    //gegner Spieler 1
    }
    else
    {
        current_player = 1;     //aktueller spieler 1
        opponent_player = 2;    //gegner Spieler 2
    }
    int x_pos, y_pos;           // Deklaration der x und y Positionsvariable

    // wenden oben links diagonal
    if ( playable_tiles_direction[x][y][0] )    //Wenn position 0 (oben Links) wahr
    {
        y_pos = y-1, x_pos = x-1;
        while ( brett[x_pos][y_pos] == opponent_player )    //umdrehen solange die aktuelle Position gegnerisch ist
        {
            brett[x_pos][y_pos] = current_player;   // Position mit dem aktuellen Spieler �berschreiben
            y_pos --;                               //weiter in der Reihe
            x_pos --;
        }
    }

    // Wenden Oben grade
    if ( playable_tiles_direction[x][y][1] )
    {
        y_pos = y-1, x_pos = x;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos --;
        }
    }

    // Wenden oben Rechts Diagonal
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

    // Wenden links grade
    if ( playable_tiles_direction[x][y][3] )
    {
        y_pos = y, x_pos = x-1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            x_pos --;
        }
    }

    // Wenden rechts grade
    if ( playable_tiles_direction[x][y][4] )
    {
        y_pos = y, x_pos = x+1;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            x_pos ++;
        }
    }

    // Wenden unten Links diagonal
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

    // Wenden unten grade
    if ( playable_tiles_direction[x][y][6] )
    {
        y_pos = y+1, x_pos = x;
        while ( brett[x_pos][y_pos] == opponent_player )
        {
            brett[x_pos][y_pos] = current_player;
            y_pos ++;
        }
    }

    // Wenden unten Rechts diagonal
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

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief bestimmt die Entfernung zwischen zwei Feldern
 *
 * \param x1 1.x Koordinate
 * \param y1 1.y Koordinate
 * \param x2 2.x Koordinate
 * \param y2 2.y Koordinate
 * \return Abstand als Integer
 *  modified from: rodolfoams (rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br)
 */
int distance( int X1, int y1, int x1, int y2 )
{
    int dx = abs( X1 - x1 ), dy = abs( y1 - y2 );   //Berechnung der Abst�nde durch Subtraktion, berechnet nur mit vorzeichenlosen Zahlen
    if ( dx > 0 ) return dx;                        //Wenn dx gr��er als 0 ist, dx zur�ck geben, ansonsten dy	
    return dy;
}
/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup is_valid_position
 * \brief bestimmt ob ddie aktuell gew�hlte Koordinate im 8x8 Raster liegt
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return true oder false
 *  modified from: rodolfoams (rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br)
 */
int is_valid_position( int x, int y )
{
    if ( x < 0 || x >= 8 || y < 0 || y >= 8 ) return FALSE; //wenn x oder y kleiner 0 oder gr��er 8 sind wird ein False zur�ck gegeben, liegt es im Spielfeld wurd ein true zur�ck gegeben
    return TRUE;
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief druckt die gew�hlte position in wei�
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
void white_tile (int x, int y)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);     //Handle für die farbfunktion
    int x_cursor[8] = {2,11,20,29,38,47,56,65};     //X Positionen f�r den Cursor
    int y_cursor[8] = {1,5,9,13,17,21,25,29};       //Y Positionen f�r den Cursor


    set_cursor (x_cursor[x],y_cursor[y]);           //Position des Cursors setzten
    SetConsoleTextAttribute(hConsole, 7);           //Farbe des gedruckten textes
    printf (smallrow);                              //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+1);         //Position des Cursors in der nächsten reihe setzten
    printf (smallrow);                              //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+2);         //Position des Cursors in der nächsten reihe setzten
    printf (smallrow);                              //Ausgabe der Zeichen f�r ein Spielfeld

}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief druckt die gew�hlte position in Schwarz
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
void Black_tile (int x, int y)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Handle für die farbfunktion
    int x_cursor[8] = {2,11,20,29,38,47,56,65}; //X Positionen f�r den Cursor
    int y_cursor[8] = {1,5,9,13,17,21,25,29};   //Y Positionen f�r den Cursor

    set_cursor (x_cursor[x],y_cursor[y]);       //Position des Cursors setzten
    SetConsoleTextAttribute(hConsole, 8);       //Farbe des gedruckten textes
    printf (smallrow);                          //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+1);     //Position des Cursors in der nächsten reihe setzten
    printf (smallrow);                          //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+2);     //Position des Cursors in der nächsten reihe setzten
    printf (smallrow);                          //Ausgabe der Zeichen f�r ein Spielfeld
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief markiert die Spielbaren Felder bei einem Zug
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
void Playable_tile (int x, int y,int lastplay)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                 //Handle für die farbfunktion
    if (lastplay == 1) SetConsoleTextAttribute(hConsole, 7);    //Wenn Schwarz als letztes am Zug war wird die textfarbe auf Wei� gesetzt
    else   SetConsoleTextAttribute(hConsole, 8);                //Wenn Wei� als letztes am Zug war wird die textfarbe auf SChwarz gesetzt
    int x_cursor[8] = {2,11,20,29,38,47,56,65};             //X Positionen f�r den Cursor
    int y_cursor[8] = {1,5,9,13,17,21,25,29};               //Y Positionen f�r den Cursor

    set_cursor (x_cursor[x]+3,y_cursor[y]+1);               //Position des Cursors in die mitte des leeren feldes setzten

    printf ("\xDB");                                   //Ausgabe der Zeichen f�r einen einzelnen punkt
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief markiert die aktuelle ausgew�hlte Spielfl�che
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
void Cursor_tile (int x, int y,int lastplay)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (lastplay == 1) SetConsoleTextAttribute(hConsole, 7);    //Wenn Schwarz als letztes am Zug war wird die Konsolenfarbe auf Wei� gesetzt
    else   SetConsoleTextAttribute(hConsole, 8);                //Wenn Wei� als letztes am Zug war wird die Konsolenfarbe auf Schwarz gesetzt
    int x_cursor[8] = {2,11,20,29,38,47,56,65};                 //X Positionen f�r den Cursor
    int y_cursor[8] = {1,5,9,13,17,21,25,29};                   //Y Positionen f�r den Cursor

    //entfernen des vorherigen Cursors
    for (size_t i = 0; i < 8; i++)
    {
        set_cursor  (0,y_cursor[i]-1);  //positionierung des Cursors
        printf ("\33[2K");              //leerung der zeile
    }
    set_cursor  (0,32);                 //positionierung des Cursors
    printf ("\33[2K");                  //leerung der zeile
    if (y<8)                            //ist der cursor auf dem spielfeld
    {
        set_cursor (x_cursor[x]-1,y_cursor[y]-1);           //positionierung des Cursors über der Spielfl�che
        printf ("\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");    //oberer teil vom cursor    
        set_cursor (x_cursor[x]-1,y_cursor[y]+3);           //positionierung des Cursors unter der Spielfl�che
        printf ("\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");    //unterer teil vom cursor
        set_cursor (x_cursor[x]+3,y_cursor[y]+2);           //positionierung des Cursors in der mitte von der spielfl�che
    }
    else        //ist der cursor nicht auf dem spielfeld
    {
        int x_cursor2[5] = {2,10,22,30,39}; //cursor positionen für die spieloptionen
        set_cursor (x_cursor2[x],34);
    }
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Einf�rben der nicht bespielten Felder
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
void empty_tile (int x, int y)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x_cursor[8] = {2,11,20,29,38,47,56,65};             //X Positionen f�r den Cursor
    int y_cursor[8] = {1,5,9,13,17,21,25,29};               //Y Positionen f�r den Cursor

    set_cursor (x_cursor[x],y_cursor[y]);                   //Position des Cursors setzten
    SetConsoleTextAttribute(hConsole, 2);                   //Farbe des gedruckten textes
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");                //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+1);                 //Position des Cursors in der nächsten reihe setzten
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");                //Ausgabe der Zeichen f�r ein Spielfeld
    set_cursor (x_cursor[x],y_cursor[y]+2);                 //Position des Cursors in der nächsten reihe setzten
    printf ("\xDB\xDB\xDB\xDB\xDB\xDB\xDB");                //Ausgabe der Zeichen f�r ein Spielfeld
}
/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Speichert den aktuellen Spielstand in einer TXT Datei, im Spieleordner
 *
 * \param brett[8][8] array des spielfeldes
 * \param starttime die startzeit
 * \param lastplay letzte spieler
 * \param x  die x koordinate des cursors
 * \param y  die y koordinate des cursors
 * \param savegame ausgewähltes savegame
 * \return Int
 */
int save_game ( int brett[8][8], long long starttime, int lastplay, int x, int y, int savegame)
{
    int timeplayed = time(NULL) - starttime;    //Berechnung der aktuellen Spielzeit
    FILE *fp;
    if (savegame == 1) fp = fopen ("savegame1.txt","w");    //�ffnen der einzelnen Spielst�nde im schreiben modus
    else if(savegame == 2 ) fp = fopen ("savegame2.txt","w");
    else if(savegame == 3 ) fp = fopen ("savegame3.txt","w");
    else if(savegame == 4 ) fp = fopen ("savegame4.txt","w");
    else if(savegame == 5 ) fp = fopen ("savegame5.txt","w");
    else if(savegame == 6 ) fp = fopen ("savegame6.txt","w");
    else if(savegame == 7 ) fp = fopen ("savegame7.txt","w");
    else if(savegame == 8 ) fp = fopen ("savegame8.txt","w");
    else if(savegame == 9 ) fp = fopen ("savegame9.txt","w");
    else if(savegame == 10 ) fp = fopen ("savegame10.txt","w");
    if (fp == NULL)     //Fehler beim �ffnen der Datei gibt eine NULL zur�ck
    {
        printf("Error opening file!\n");                    //Ausgabe einer Fehlermeldung
        exit(1);
    }
    for (size_t i = 0; i < 8; i++)                          //Zeilen
    {
        for (size_t j = 0; j < 8; j++)                      //Spalten
        {
            fprintf(fp, "%d ", brett[i][j]);                //Schreiben der Spalten in die Datei
        }
        fprintf(fp, "\n");                                  //sprung zur nächsten Zeile
    }
    fprintf(fp, "%d %d %d %d %d\n", timeplayed,lastplay, x, y, 0);  //Schreiben der aktuellen Speilzeit, letzten Spieler, x und Y Koordinate des Cursors in die datei
    fclose(fp); //schlie�en der TXT Datei
    return 0;
}
/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Laden eines bereits gespeicherten Spielstandes
 *
 * \param brett[8][8] array des spielfeldes
 * \param *starttime pointer auf die startzeit
 * \param *lastplay pointer auf den letzten spieler
 * \param *x  pointer auf die x koordinate des cursors
 * \param *y  pointer auf die y koordinate des cursors
 * \param savegame ausgewähltes savegame
 * \return Int
 */
int load_game (int brett[8][8], long long *starttime, int *lastplay, int *x, int *y, int savegame)
{
    int timeplayed; //deklaration der Spielzeit
    FILE *fp;
    if (savegame == 1) fp = fopen ("savegame1.txt","r");        //�ffen der TXT Spielstand Datei im lesen modus
    else if(savegame == 2 ) fp = fopen ("savegame2.txt","r");
    else if(savegame == 3 ) fp = fopen ("savegame3.txt","r");
    else if(savegame == 4 ) fp = fopen ("savegame4.txt","r");
    else if(savegame == 5 ) fp = fopen ("savegame5.txt","r");
    else if(savegame == 6 ) fp = fopen ("savegame6.txt","r");
    else if(savegame == 7 ) fp = fopen ("savegame7.txt","r");
    else if(savegame == 8 ) fp = fopen ("savegame8.txt","r");
    else if(savegame == 9 ) fp = fopen ("savegame9.txt","r");
    else if(savegame == 10 ) fp = fopen ("savegame10.txt","r");
    if (fp == NULL)     //Fehler beim �ffnen der Datei gibt eine NULL zur�ck
    {
        printf("Error opening file!\n");    //Ausgabe einer Fehlermeldung
        exit(1);
    }

    for (size_t i = 0; i < 8; i++)              //Zeilen
    {
        for (size_t j = 0; j < 8; j++)          //Spalten
        {
            fscanf(fp, "%d ", &brett[i][j]);    //Lesen der Spalten
        }
    }

    fscanf(fp, "%d %d %d %d\n", &timeplayed, lastplay, x, y);   //Einlesen Spielzeit, letzter Spieler, X und Y Position des Cursors

    *starttime = time(NULL) - timeplayed;                       //spielzeit in die unix startzeit umsetzen
    fclose(fp);                                                 //schlie�en der TXT Datei
    return 0;
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Auswahl des Spielstandes im Speichern Men�
 *
 * \param *savegame pointer auf Savegame
 * \return Int
 */
int select_save (int *savegame)
{
    struct cursor cursorsave = {0,0};
    int cursory[11] = {6,8,10,12,14,16,18,20,22,24,26};
    for (size_t i = 0; i < 32; i++)         //Löschen des bildschirms
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,3);                      //Positionierung des Cursors
    printf("Select savegame to Save:");     //Ausgabe des Anzeige Textes
    set_cursor (20,6);
    printf ("savegame 1");
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
    while (1)                       //Dauerschleife
    {
        set_cursor (20,cursory[cursorsave.y]);      //Positionierung der Cursors
        switch(getch())                             //Einlesen der Tastatureingaben
        {
        case 72:                                    //Pfeiltaste runter
            if (cursorsave.y >0)                    //Wenn der Cursor nicht an der oberen Grenze
                cursorsave.y--;
            break;
        case 80:                                    //Pfeiltaste Hoch
            if (cursorsave.y <10)
                cursorsave.y++;
            break;
        case 13:                                    //Entertaste
            *savegame = cursorsave.y+1;             //rückgabe des ausgewählten Spielstandes
            for (size_t i = 0; i < 32; i++)         //Löschen des bildschirms
            {
                set_cursor (1,i+1);
                printf ("\33[2K");
            }
            return 0;
        }
    }
}
/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Auswahl des zu ladenden Spielstandes und Aufbau des Men�s
 *
 * \param *savegame Pointer auf Savegame
 * \return int
 */
int select_load (int *savegame)
{
    struct cursor cursorsave = {0,0};
    int cursory[11] = {6,8,10,12,14,16,18,20,22,24,26};     //Cursor Postitionen im Men�
    for (size_t i = 0; i < 32; i++)                         //Löschen des bildschirms
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,3);                                      //Positoniert den Cursors an der entsprechenden Position
    printf("Select savegame to Load:");                     //Ausgabe des Textes f�r das Laden Men�s
    set_cursor (20,6);
    printf ("savegame 1");
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
        set_cursor (20,cursory[cursorsave.y]);          //Positioniert des Cursors
        switch(getch())                                 
        {               
        case 72:                                        //Pfeiltaste Hoch
            if (cursorsave.y >0)                        //Oberste Position im Men� erreicht
                cursorsave.y--;                         //Reduzierung der Cursorposition
            break;
        case 80:                                        //Pfeiltaste runter
            if (cursorsave.y <10)                       //Unterste Position im Men� erreicht
                cursorsave.y++;                         //Erh�hung der Cursorposition
            break;
        case 13:                                        //Entertaste
            *savegame = cursorsave.y+1;                 //rückgabe des ausgewählten Spielstandes
            for (size_t i = 0; i < 32; i++)             //Löschen des bildschirms
            {
                set_cursor (1,i+1);
                printf ("\33[2K");
            }
            return 0;
        }
    }
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Anzeige des Gewinner-Bildschirms
 *
 * \param time_played dauer des spiels
 * \param winner gewinner
 * \param white_tiles anzahl der wei�en Steine
 * \param black_tiles anzahl der schwarzen Steine
 * \return void
 */
void win_screen (struct time_played time_played, int winner, int white_tiles, int black_tiles)
{
    for (size_t i = 0; i < 35; i++) //Löschen des bildschirms
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    set_cursor (20,5);
    if (winner == Schwarz) printf ("Schwarz hat gewonnen!");        //Abfrage welcher Spieler gewonnen hat: Schwarz
    else if (winner == Weiss) printf ("Weiss hat gewonnen!");       //Abfrage welcher Spieler gewonnen hat: Wei�
    else printf ("Unentschieden!");                                 //Unentschieden
    set_cursor (20,7);
    printf ("Spieldauer");
    set_cursor (20,8);
    printf ("%ih : %im : %is",time_played.h,time_played.m,time_played.s);  //Ausgabe der Spielzeit im Format Stunden : Minuten : Sekunden

    set_cursor (20,10);
    printf ("Endspielstand");
    set_cursor (20,11);
    printf ("Weiss: %2i", white_tiles);                         //Ausgabe der Wei�en Spielsteine
    set_cursor (20,12);
    printf ("Schwarz: %2i", black_tiles);                       //Ausgabe der SChwarzen Spelsteine
    set_cursor (20,14);
    printf ("Taste druecken um ein neues Spiel zu starten");
    getch();
    getch();                                    //doppeltes getch da die pfeiltasten den buffer doppelt füllt
    for (size_t i = 0; i < 35; i++)             //Löschen des bildschirms
    {
        set_cursor (1,i+1);
        printf ("\33[2K");

    }


}


/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Anzeige des Verlassen-Bildschirms
 *
 * \param brett[8][8] aktuelles Spielbrett
 * \param starttime Zeitpunkt des Spielbeginns
 * \param lastplay spieler der den letzten zug ausgeführt hat
 * \param x x-Koordinate des curors
 * \param y y-Koordinate des curors
 * \return Void
 */
void exit_game ( int brett[8][8], long long starttime, int lastplay, int x, int y)
{
    int savegame, i=0,cursor=0;
    for (size_t i = 0; i < 35; i++) //Löschen des bildschirms
    {
        set_cursor (1,i+1);
        printf ("\33[2K");
    }
    while (i == 0 )         //schleife bis eine auswahl getroffen wurde
    {
        i=0;
        set_cursor (20,5);                                              //Positionierung des Cursors , f�r Abfrage Speichern Y/N
        printf ("Wollen Sie das Spiel vorher Speichern?");
        set_cursor (35,7);
        printf ("ja    /   nein");
        if(cursor==0) set_cursor (35,7);                                //Wenn Pfeiltaste rechts gedr�ckt ,wird der Cursor an der ensprechenden Stelle Positioniert
        else if(cursor==1) set_cursor (45,7);                            //Wenn Pfeiltaste Links gedr�ckt ,wird der Cursor an der ensprechenden Stelle Positioniert
        switch(getch())
        {
            break;
        case 77:                //pfeiltaste rechts
            cursor=1;
            break;
        case 75:                //pfeiltaste links
            cursor=0;
            break;
        case 13:                //enter
            if (cursor==0)      //wenn ja
            {
                select_save(&savegame);     //Aufruf der Funktion select_save
                if (savegame == 11)         //Wenn Men�punkt back im Speichern Men� gedr�ckt wird spirng man zur�ck in das Verlassen Mne�
                {
                    break;
                }
                else
                {
                    save_game(brett,starttime,lastplay,x,y,savegame);        //Aufruf der Funktion save_game zum Sichern des Spielstandes
                    i=1;                                                     //Ende der Schleife
                }
                break;
            }
            else if (cursor==1)
            {
                i=1;                                                         //Ende der Schleife
                break;
            }
        }
        for (size_t i = 0; i < 35; i++)         //leerung des billdschirms
        {
            set_cursor (1,i+1);
            printf ("\33[2K");
        }
    }
    i=0;
    while (i == 0 )                 //schleife bis eine auswahl getroffen wurde
    {
        i=0;
        set_cursor (20,5);
        printf ("Wollen Sie das Spiel Wirklich beenden?");
        set_cursor (35,7);
        printf ("ja    /   nein");
        if(cursor==0)
            set_cursor (35,7);
        else
            set_cursor (45,7);
        switch(getch())
        {
            break;
        case 77:        //pfeiltaste rechts
            cursor=1;
            break;
        case 75:        //pfeiltaste links
            cursor=0;
            break;
        case 13:        //enter
            if (cursor==0)
            {
                exit(0);    //beenden des Programms mit r�ckgabe Successfull termination
                break;
            }
            else if (cursor==1)
            {
                //bildschirm leeren bevor die funktion verlassen wird
                for (size_t i = 0; i < 35; i++)
                {
                    set_cursor (1,i+1);
                    printf ("\33[2K");
                }
                return;
            }

        }
        break;

    }
}



/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief z�hlt die aktuelle Anzahl der Spielsteine auf dem Spielfeld
 *
 * \param brett[8][8] spiuelfeld
 * \param tile farbe des Spielsteins
 * \return int
 */
int Count_Tiles (int brett[8][8],int tile)
{
    int k=0;
    for (int i=0; i<8; i++)     //Zeilen
    {
        for (int j=0; j<8; j++) //Spalten
        {
            if (brett[i][j]==tile)  //Wenn ein Spielstein auf der Position liegt
            {
                k++;                //Variable k+1
            }
        }
    }
    return k;                       //r�ckgabe der Anzahl der liegenden Spielsteine
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup time_played calculate_time_played
 * \brief berechnet die Spielzeit und Pausemen�
 *
 * \param starttime Startzeit des Spiels
 * \return struct time_played mit hh:mm:ss der Spielzeit
 */
struct time_played caculate_time_played(long long starttime)
{
    struct time_played time_played_since;
    long long time_played_in_seconds = time(NULL)-starttime;   //Berechnung der Spielzeit in Sekunden anhand der startzeit und der aktuellen unix zeit
    time_played_since.s = time_played_in_seconds % 60;          //Berechnung der Sekunden
    time_played_since.m = (time_played_in_seconds / 60) % 60;   //Berechnung der Minuten
    time_played_since.h = (time_played_in_seconds / 3600);      //Berechnung der Stunden
    return time_played_since;                                   //R�ckgabe der Spielzeit
}

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup pause
 * \brief pausiert die Spielzeit
 *
 * \param Startzeit
 * \return startzeit
 */
long long pause (long long starttime)
{
    long long pausestart = time(NULL);          //anfangszeit der pause

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);       //farbe rot
    set_cursor (78,1);
    printf ("||");                              //pausenzeichen vor der zeit
    set_cursor (25,10);
    printf ("Das Spiel ist Pausiert!");
    set_cursor (10,11);
    printf ("Druecken sie eine Beliebige Taste zum Fortfahren");
    getch();                                    //wartet auf eine beliebige Taste
    set_cursor (78,1);
    printf ("  ");                              //entfernen des pausenzeichen
    set_cursor (70,10);
    printf ("\33[2K");
    set_cursor (70,11);
    printf ("\33[2K");

    return starttime+time(NULL)-pausestart;     //r�ckgabe der neuen startzeit(startzeit + der aktuelle unix zeit - der anfangszeit der pause)
}





//funktionen aus einer demo von herrn wichmann

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


