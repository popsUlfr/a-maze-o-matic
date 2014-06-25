#ifndef _MAZEDRAWER_HPP
#define _MAZEDRAWER_HPP

#include "mazeplayground.hpp"
#include "termbox.hpp"

#include <cstdint>

#define MAZE_DEFAULT_PLAYER_SYMBOL 0x263B

class MazeDrawer{
public:
    MazeDrawer(){}
    
    static unsigned int realWidth(const Maze& maze){return (maze.getWidth()<<2)+1;}
    static unsigned int realHeight(const Maze& maze){return (maze.getHeight()<<1)+1;}
    
    static unsigned int targetMazeWidth(unsigned int width){return width>>2;}
    static unsigned int targetMazeHeight(unsigned int height){return height>>1;}

    static void drawMaze(const Termbox& tb,
                  const Maze& maze,
                  int tlx,
                  int tly,
                  uint16_t fg=TB_CYAN,
                  uint16_t bg=TB_DEFAULT);

    static void drawEntryPoints(const Termbox& tb,
                         const MazePlayground& mp,
                         int tlx,
                         int tly);
    
    static void drawPlayer(const Termbox& tb,
                           int tlx,
                           int tly,
                           unsigned int x,
                           unsigned int y,
                           uint32_t playerSymbol=MAZE_DEFAULT_PLAYER_SYMBOL,
                           uint16_t color=TB_RED|TB_BOLD,
                           uint16_t bg=TB_DEFAULT);
    
    static void clearCell(const Termbox& tb,
                          int tlx,
                          int tly,
                          unsigned int x,
                          unsigned int y);
    
    typedef enum{
        WALL_NORTH=0,
        WALL_EAST,
        WALL_SOUTH,
        WALL_WEST
    }Wall;
    
    static const uint32_t WallSymbols[];
    
    typedef enum{
        BORDER_NORTH=0,
        BORDER_NORTH_EAST,
        BORDER_EAST,
        BORDER_SOUTH_EAST,
        BORDER_SOUTH,
        BORDER_SOUTH_WEST,
        BORDER_WEST,
        BORDER_NORTH_WEST,
        BORDER_JUNCTION_NORTH,
        BORDER_JUNCTION_WEST,
        BORDER_JUNCTION_EAST,
        BORDER_JUNCTION_SOUTH
    }Border;
    
    static const uint32_t BorderSymbols[];
    
    typedef enum{
        JUNC_NONE=0,
        JUNC_HORZ,
        JUNC_HORZ_RIGHT,
        JUNC_HORZ_LEFT,
        JUNC_VERT,
        JUNC_VERT_UP,
        JUNC_VERT_DOWN,
        JUNC_UP_LEFT,
        JUNC_UP_RIGHT,
        JUNC_UP_HORZ,
        JUNC_DOWN_LEFT,
        JUNC_DOWN_RIGHT,
        JUNC_DOWN_HORZ,
        JUNC_VERT_LEFT,
        JUNC_VERT_RIGHT,
        JUNC_VERT_HORZ
    }Junction;
    
    static const uint32_t JunctionSymbols[];
    
    typedef enum{
        DOOR_START=0,
        DOOR_END
    }Door;
    
    static const uint32_t DoorSymbols[];
    
protected:
    static void drawPrettyJunctions(const Termbox& tb,
                                    const Maze& maze,
                                    int tlx,
                                    int tly,
                                    unsigned int x,
                                    unsigned int y,
                                    uint16_t color=TB_CYAN,
                                    uint16_t bg=TB_DEFAULT);

    static void drawMazeFrame(const Termbox& tb,
                              const Maze& maze,
                              int tlx,
                              int tly,
                              unsigned int x,
                              unsigned int y,
                              uint16_t color=TB_CYAN,
                              uint16_t bg=TB_DEFAULT);

    static void drawMazeWalls(const Termbox& tb,
                              const Maze& maze,
                              int tlx,
                              int tly,
                              unsigned int x,
                              unsigned int y,
                              uint16_t color=TB_CYAN,
                              uint16_t bg=TB_DEFAULT);

    static void drawMazeDoor(const Termbox& tb,
                             const Maze& maze,
                             int tlx,
                             int tly,
                             unsigned int x,
                             unsigned int y,
                             uint32_t mazeDoorSymbol=DoorSymbols[DOOR_START],
                             uint16_t color=TB_BLACK,
                             uint16_t bg=TB_RED);
};
#endif