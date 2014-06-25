#include "mazedrawer.hpp"

const uint32_t MazeDrawer::WallSymbols[]={
    0x2501, // WALL_NORTH
    0x2503, // WALL_EAST
    0x2501, // WALL_SOUTH
    0x2503  // WALL_WEST
};

const uint32_t MazeDrawer::BorderSymbols[]={
    0x2501, // BORDER_NORTH
    0x2513, // BORDER_NORTH_EAST
    0x2503, // BORDER_EAST
    0x251B, // BORDER_SOUTH_EAST
    0x2501, // BORDER_SOUTH
    0x2517, // BORDER_SOUTH_WEST
    0x2503, // BORDER_WEST
    0x250F, // BORDER_NORTH_WEST
    0x2533, // BORDER_JUNCTION_NORTH
    0x2523, // BORDER_JUNCTION_WEST
    0x252B, // BORDER_JUNCTION_EAST
    0x253B  // BORDER_JUNCTION_SOUTH
};

const uint32_t MazeDrawer::JunctionSymbols[]={
    0x0,    // JUNC_NONE
    0x2501, // JUNC_HORZ ━
    0x2501, // JUNC_HORZ_RIGHT ━
    0x2501, // JUNC_HORZ_LEFT ━
    0x2503, // JUNC_VERT ┃
    0x2503, // JUNC_VERT_UP ┃
    0x2503, // JUNC_VERT_DOWN ┃
    0x251B, // JUNC_UP_LEFT ┛
    0x2517, // JUNC_UP_RIGHT ┗
    0x253B, // JUNC_UP_HORZ ┻
    0x2513, // JUNC_DOWN_LEFT ┓
    0x250F, // JUNC_DOWN_RIGHT ┏
    0x2533, // JUNC_DOWN_HORZ ┳
    0x252B, // JUNC_VERT_LEFT ┫
    0x2523, // JUNC_VERT_RIGHT ┣
    0x254B, // JUNC_VERT_HORZ ╋
};

const uint32_t MazeDrawer::DoorSymbols[]={
    0x26A1, // DOOR_START
    0x2691  // DOOR_END
};

void MazeDrawer::drawPrettyJunctions(const Termbox& tb,
                                     const Maze& maze,
                                     int tlx,
                                     int tly,
                                     unsigned int x,
                                     unsigned int y,
                                     uint16_t color/*=TB_CYAN*/,
                                     uint16_t bg/*=TB_DEFAULT*/){
    Maze::Cell c=maze.getCellAt(x,y);
    Junction cd=JUNC_NONE;
    int pos;
    if(maze.hasWallS(c) || maze.hasBorderS(c))
        cd=JUNC_HORZ_LEFT;
    if(maze.hasWallE(c) || maze.hasBorderE(c)){
        if(cd==JUNC_HORZ_LEFT)
            cd=JUNC_UP_LEFT;
        else
            cd=JUNC_VERT_DOWN;
    }
    if((pos=maze.cellEPos(maze.coordToPos(x,y)))>0){
        if(maze.hasWallS(maze.getCellByPos(pos)) || maze.hasBorderS(maze.getCellByPos(pos))){
            if(cd==JUNC_UP_LEFT)
                cd=JUNC_UP_HORZ;
            else if(cd==JUNC_VERT_DOWN)
                cd=JUNC_UP_RIGHT;
            else if(cd==JUNC_HORZ_LEFT)
                cd=JUNC_HORZ;
            else
                cd=JUNC_HORZ_RIGHT;
        }
    }
    else
        cd=JUNC_NONE;
    if((pos=maze.cellSPos(maze.coordToPos(x,y)))>0){
        if(maze.hasWallE(maze.getCellByPos(pos)) || maze.hasBorderE(maze.getCellByPos(pos))){
            if(cd==JUNC_UP_HORZ)
                cd=JUNC_VERT_HORZ;
            else if(cd==JUNC_UP_LEFT)
                cd=JUNC_VERT_LEFT;
            else if(cd==JUNC_UP_RIGHT)
                cd=JUNC_VERT_RIGHT;
            else if(cd==JUNC_HORZ_LEFT)
                cd=JUNC_DOWN_LEFT;
            else if(cd==JUNC_HORZ_RIGHT)
                cd=JUNC_DOWN_RIGHT;
            else if(cd==JUNC_HORZ)
                cd=JUNC_DOWN_HORZ;
            else
                cd=JUNC_VERT_UP;
        }
    }
    else
        cd=JUNC_NONE;
    
    if(cd!=JUNC_NONE) tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
        JunctionSymbols[cd],color,bg);
}

void MazeDrawer::drawMazeFrame(const Termbox& tb,
                               const Maze& maze,
                               int tlx,
                               int tly,
                               unsigned int x,
                               unsigned int y,
                               uint16_t color/*=TB_CYAN*/,
                               uint16_t bg/*=TB_DEFAULT*/){
    // Now we place the beautiful junction points for the corner cases
    Maze::Cell c=maze.getCellAt(x,y);
    if(y==0){ // The upper row of wall elements
        if(x==0){
            tb.change_cell(tlx,tly,BorderSymbols[BORDER_NORTH_WEST],color,bg);
            if(maze.hasWallE(c) || maze.hasBorderE(c))
                tb.change_cell(tlx+4,tly,
                               BorderSymbols[BORDER_JUNCTION_NORTH],color,bg);
            else
                tb.change_cell(tlx+4,tly,
                               BorderSymbols[BORDER_NORTH],color,bg);
            if(maze.hasWallS(c) || maze.hasBorderS(c))
                tb.change_cell(tlx,tly+2,
                               BorderSymbols[BORDER_JUNCTION_WEST],color,bg);
            else
                tb.change_cell(tlx,tly+2,
                               BorderSymbols[BORDER_WEST],color,bg);
        }
        else if(x==maze.getWidth()-1){
            tb.change_cell(tlx+(x<<2)+4,tly,
                           BorderSymbols[BORDER_NORTH_EAST],color,bg);
            if(maze.hasWallS(c) || maze.hasBorderS(c))
                tb.change_cell(tlx+(x<<2)+4,tly+2,
                               BorderSymbols[BORDER_JUNCTION_EAST],color,bg);
            else
                tb.change_cell(tlx+(x<<2)+4,tly+2,
                               BorderSymbols[BORDER_EAST],color,bg);
        }
        else if(maze.hasWallE(c) || maze.hasBorderE(c))
            tb.change_cell(tlx+(x<<2)+4,tly,
                           BorderSymbols[BORDER_JUNCTION_NORTH],color,bg);
        else
            tb.change_cell(tlx+(x<<2)+4,tly,
                           BorderSymbols[BORDER_NORTH],color,bg);
    }
    else if(y==maze.getHeight()-1){
        if(x==0){
            tb.change_cell(tlx,tly+(y<<1)+2,
                           BorderSymbols[BORDER_SOUTH_WEST],color,bg);
            if(maze.hasWallE(c) || maze.hasBorderE(c))
                tb.change_cell(tlx+4,tly+(y<<1)+2,
                               BorderSymbols[BORDER_JUNCTION_SOUTH],color,bg);
            else
                tb.change_cell(tlx+4,tly+(y<<1)+2,
                               BorderSymbols[BORDER_SOUTH],color,bg);
        }
        else if(x==maze.getWidth()-1)
            tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
                           BorderSymbols[BORDER_SOUTH_EAST],color,bg);
        else if(maze.hasWallE(c) || maze.hasBorderE(c))
            tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
                           BorderSymbols[BORDER_JUNCTION_SOUTH],color,bg);
        else
            tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
                           BorderSymbols[BORDER_SOUTH],color,bg);
    }
    else if(x==0){
        if(maze.hasWallS(c) || maze.hasBorderS(c))
            tb.change_cell(tlx,tly+(y<<1)+2,
                           BorderSymbols[BORDER_JUNCTION_WEST],color,bg);
        else
            tb.change_cell(tlx,tly+(y<<1)+2,
                           BorderSymbols[BORDER_WEST],color,bg);
    }
    else if(x==maze.getWidth()-1){
        if(maze.hasWallS(c) || maze.hasBorderS(c))
            tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
                           BorderSymbols[BORDER_JUNCTION_EAST],color,bg);
        else
            tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,
                           BorderSymbols[BORDER_EAST],color,bg);
    }
}

void MazeDrawer::drawMazeWalls(const Termbox& tb,
                               const Maze& maze,
                               int tlx,
                               int tly,
                               unsigned int x,
                               unsigned int y,
                               uint16_t color/*=TB_CYAN*/,
                               uint16_t bg/*=TB_DEFAULT*/){
    // First we place the walls North, East, South, West
    Maze::Cell c=maze.getCellAt(x,y);
    if(y==0 && (maze.hasWallN(c) || maze.hasBorderN(c))){
        tb.change_cell(tlx+(x<<2)+1,tly+(y<<1),
                       WallSymbols[WALL_NORTH],color,bg);
        tb.change_cell(tlx+(x<<2)+2,tly+(y<<1),
                       WallSymbols[WALL_NORTH],color,bg);
        tb.change_cell(tlx+(x<<2)+3,tly+(y<<1),
                       WallSymbols[WALL_NORTH],color,bg);
    }
    if(maze.hasWallE(c) || maze.hasBorderE(c))
        tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+1,
                       WallSymbols[WALL_EAST],color,bg);
    if(maze.hasWallS(c) || maze.hasBorderS(c)){
        tb.change_cell(tlx+(x<<2)+1,tly+(y<<1)+2,
                       WallSymbols[WALL_SOUTH],color,bg);
        tb.change_cell(tlx+(x<<2)+2,tly+(y<<1)+2,
                       WallSymbols[WALL_SOUTH],color,bg);
        tb.change_cell(tlx+(x<<2)+3,tly+(y<<1)+2,
                       WallSymbols[WALL_SOUTH],color,bg);
    }
    if(x==0 && (maze.hasWallW(c) || maze.hasBorderW(c)))
        tb.change_cell(tlx+(x<<2),tly+(y<<1)+1,
                       WallSymbols[WALL_WEST],color,bg);
}

void MazeDrawer::drawMazeDoor(const Termbox& tb,
                              const Maze& maze,
                              int tlx,
                              int tly,
                              unsigned int x,
                              unsigned int y,
                              uint32_t mazeDoorSymbol/*=DoorSymbols[DOOR_START]*/,
                              uint16_t color/*=TB_BLACK*/,
                              uint16_t bg/*=TB_RED*/){
    if(x==0)
        tb.change_cell(tlx,tly+(y<<1)+1,mazeDoorSymbol,color,bg);
    else if(x==maze.getWidth()-1)
        tb.change_cell(tlx+(x<<2)+4,tly+(y<<1)+1,mazeDoorSymbol,color,bg);
    else if(y==0){
        tb.change_cell(tlx+(x<<2)+1,tly,0,TB_DEFAULT,bg);
        tb.change_cell(tlx+(x<<2)+2,tly,mazeDoorSymbol,color,bg);
        tb.change_cell(tlx+(x<<2)+3,tly,0,TB_DEFAULT,bg);
    }
    else if(y==maze.getHeight()-1){
        tb.change_cell(tlx+(x<<2)+1,tly+(y<<1)+2,0,TB_DEFAULT,bg);
        tb.change_cell(tlx+(x<<2)+2,tly+(y<<1)+2,mazeDoorSymbol,color,bg);
        tb.change_cell(tlx+(x<<2)+3,tly+(y<<1)+2,0,TB_DEFAULT,bg);
    }
}

void MazeDrawer::drawEntryPoints(const Termbox& tb, const MazePlayground& mp, int tlx, int tly){
    drawMazeDoor(tb,mp.getMaze(),tlx,tly,
                 mp.getMaze().posToCoordX(mp.getPosStart()),
                 mp.getMaze().posToCoordY(mp.getPosStart()),
                 DoorSymbols[DOOR_START],TB_BLACK,TB_RED);
    drawMazeDoor(tb,mp.getMaze(),tlx,tly,
                 mp.getMaze().posToCoordX(mp.getPosEnd()),
                 mp.getMaze().posToCoordY(mp.getPosEnd()),
                 DoorSymbols[DOOR_END],TB_BLACK,TB_GREEN);
}

void MazeDrawer::drawMaze(const Termbox& tb, const Maze& maze, int tlx, int tly, uint16_t fg, uint16_t bg/*=TB_DEFAULT*/){
    for(unsigned int y=0;y<maze.getHeight();++y){
        for(unsigned int x=0;x<maze.getWidth();++x){
            
            // First we place the walls North, East, South, West
            drawMazeWalls(tb,maze,tlx,tly,x,y,fg,bg);
            
            // We draw the fragments of the frame
            drawMazeFrame(tb,maze,tlx,tly,x,y,fg,bg);
            
            // We draw the junctions between walls
            drawPrettyJunctions(tb,maze,tlx,tly,x,y,fg,bg);
        }
    }
}

void MazeDrawer::drawPlayer(const Termbox& tb,
                       int tlx,
                       int tly,
                       unsigned int x,
                       unsigned int y,
                       uint32_t playerSymbol/*=0x263B*/,
                       uint16_t color/*=TB_RED*/,
                       uint16_t bg/*=TB_DEFAULT*/){
    tb.change_cell(tlx+(x<<2)+2,tly+(y<<1)+1,playerSymbol,color,bg);
}

void MazeDrawer::clearCell(const Termbox& tb,
                      int tlx,
                      int tly,
                      unsigned int x,
                      unsigned int y) {
    tb.change_cell(tlx+(x<<2)+1,tly+(y<<1)+1,0,TB_DEFAULT,TB_DEFAULT);
    tb.change_cell(tlx+(x<<2)+2,tly+(y<<1)+1,0,TB_DEFAULT,TB_DEFAULT);
    tb.change_cell(tlx+(x<<2)+3,tly+(y<<1)+1,0,TB_DEFAULT,TB_DEFAULT);
}