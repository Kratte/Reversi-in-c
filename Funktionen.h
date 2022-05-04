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

extern struct directions is_playable(int x, int y, int brett[8][8], int lastplay);

extern void capture_pieces( int x, int y, int brett[8][8],int lastplay, int playable_tiles_direction[8][8][8] );

extern int distance( int X1, int y1, int x1, int y2 );

extern int is_valid_position( int x, int y );

extern void white_tile (int x, int y);

extern void Black_tile (int x, int y);

extern void Playable_tile (int x, int y,int lastplay);

extern void Cursor_tile (int x, int y,int lastplay);

extern void empty_tile (int x, int y);

extern int save_game ( int brett[8][8], long long starttime, int lastplay, int x, int y, int savegame);

extern int load_game (int brett[8][8], long long *starttime, int *lastplay, int *x, int *y, int savegame);

extern int select_save (int *savegame);

extern int select_load (int *savegame);

extern void win_screen (struct time_played time_played, int winner, int white_tiles, int black_tiles);

extern void exit_game ( int brett[8][8], long long starttime, int lastplay, int x, int y);

extern int Count_Tiles (int brett[8][8],int tile);

extern struct time_played caculate_time_played(long long starttime);

extern long long pause (long long starttime);

extern int set_console_width(const int width);

extern int set_console_size(const int width, const int height);

extern int set_code_page(const int code_page);

extern int set_cursor(const int x, const int y);




#endif // FUNKTIONEN_H_INCLUDED
