#ifndef FUNKTIONEN_H_INCLUDED
#define FUNKTIONEN_H_INCLUDED

struct cursor
{
    int x;
    int y;
};
struct time_played
{
    int h;
    int m;
    int s;
};
struct directions
{
    int playable,UL,U,UR,L,R,DL,D,DR;
};

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
extern struct directions is_playable(int x, int y, int brett[8][8], int lastplay);

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
extern void capture_pieces( int x, int y, int brett[8][8],int lastplay, int playable_tiles_direction[8][8][8] );

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
extern int distance( int X1, int y1, int x1, int y2 );

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup is_valid_position
 * \brief bestimmt ob ddie aktuell gew�hlte Koordinate im 8x8 Raster liegt
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return true oder false
 *  modified from: rodolfoams (rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br)
 */
extern int is_valid_position( int x, int y );

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief druckt die gew�hlte position in wei�
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
extern void white_tile (int x, int y);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief druckt die gew�hlte position in Schwarz
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
extern void Black_tile (int x, int y);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief markiert die Spielbaren Felder bei einem Zug
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
extern void Playable_tile (int x, int y,int lastplay);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief markiert die aktuelle ausgew�hlte Spielfl�che
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
extern void Cursor_tile (int x, int y,int lastplay);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Einf�rben der nicht bespielten Felder
 *
 * \param x x Koordinate
 * \param y y Koordinate
 * \return void
 */
extern void empty_tile (int x, int y);

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
extern int save_game ( int brett[8][8], long long starttime, int lastplay, int x, int y, int savegame);

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
extern int load_game (int brett[8][8], long long *starttime, int *lastplay, int *x, int *y, int savegame);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Auswahl des Spielstandes im Speichern Men�
 *
 * \param *savegame pointer auf Savegame
 * \return Int
 */
extern int select_save (int *savegame);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief Auswahl des zu ladenden Spielstandes und Aufbau des Men�s
 *
 * \param *savegame Pointer auf Savegame
 * \return int
 */
extern int select_load (int *savegame);

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
extern void win_screen (struct time_played time_played, int winner, int white_tiles, int black_tiles);

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
extern void exit_game ( int brett[8][8], long long starttime, int lastplay, int x, int y);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup Reversi
 * \brief z�hlt die aktuelle Anzahl der Spielsteine auf dem Spielfeld
 *
 * \param brett[8][8] spiuelfeld
 * \param tile farbe des Spielsteins
 * \return int
 */
extern int Count_Tiles (int brett[8][8],int tile);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup time_played calculate_time_played
 * \brief berechnet die Spielzeit
 *
 * \param starttime Startzeit des Spiels
 * \return struct time_played mit hh:mm:ss der Spielzeit
 */
extern struct time_played caculate_time_played(long long starttime);

/**------------------------------------------------------------------------------------------------------------------------------------------------
 * \ingroup pause
 * \brief pausiert die Spielzeit
 *
 * \param Startzeit
 * \return startzeit
 */
extern long long pause (long long starttime);



//funktionen aus einer demo von herrn wichmann

/**
 * \ingroup KonsolenDemo
 * \brief Sets width of console window.
 *
 * \param width width of console window as number of characters
 * \return 0 if console width was set, else 1
 */
extern int set_console_width(const int width);

/**
 * \ingroup KonsolenDemo
 * \brief Sets size of console window.
 *
 * \param width width of console window as number of characters
 * \param height height of console window as number of characters
 * \return 0 if console size was set, else 1
 */
extern int set_console_size(const int width, const int height);

/**
 * \ingroup KonsolenDemo
 * \brief Sets code page for current console to allow printing of special
 * characters. See also "C-Programmieren von Anfang an", page 307ff.
 *
 * \param code_page number identifying code page to be set
 * \return 0 if code page was set, else 1
 */
extern int set_code_page(const int code_page);

/**
 * \ingroup KonsolenDemo
 * \brief Sets cursor to a given position on the current console.
 *
 * \param x x-coordinate to be set
 * \param y y-coordinate to be set
 * \return 0 if cursor was set, 1 if failed
 */
extern int set_cursor(const int x, const int y);




#endif // FUNKTIONEN_H_INCLUDED
