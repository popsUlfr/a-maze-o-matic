#include "mazegame.hpp"

#include "mazedrawer.hpp"
#include "mazeplayground.hpp"
#include "maze.hpp"

const int MazeGame::MazeMargin=4;
const int MazeGame::MinimalScreenSize=8;

MazeGame::~MazeGame(){
    delete(_mp);
    delete(_maze);
}

void MazeGame::drawScreen(){
    _tb.clear(); // We clear the whole screen
    int width=_tb.width();
    int height=_tb.height();
    if((width-((MazeMargin<<1)+MinimalScreenSize))>0 &&
        (height-((MazeMargin<<1)+MinimalScreenSize))>0
    ){
        delete(_mp);
        delete(_maze);
        _maze=new Maze(MazeDrawer::targetMazeWidth(width-(MazeMargin<<1)),MazeDrawer::targetMazeHeight(height-(MazeMargin<<1)));
        _mp=new MazePlayground(*_maze);
        MazeDrawer::drawMaze(_tb,*_maze,MazeMargin,MazeMargin);
        MazeDrawer::drawEntryPoints(_tb,*_mp,MazeMargin,MazeMargin);
    }
    _tb.present();
}

void MazeGame::updatePlayer(){
    MazeDrawer::clearCell(_tb,MazeMargin,MazeMargin,
                          _maze->posToCoordX(_mp->getPrevPos()),
                          _maze->posToCoordY(_mp->getPrevPos()));
    MazeDrawer::drawPlayer(_tb,MazeMargin,MazeMargin,
                           _maze->posToCoordX(_mp->getCurrPos()),
                           _maze->posToCoordY(_mp->getCurrPos())
                          );
    _tb.present();
}

void MazeGame::keyHandler(uint16_t key){
    switch(key){
        case TB_KEY_SPACE:
            drawScreen();
            updatePlayer();
            break;
        case TB_KEY_ARROW_UP:
            if(_mp->movePlayerN())
                updatePlayer();
            break;
        case TB_KEY_ARROW_DOWN:
            if(_mp->movePlayerS())
                updatePlayer();
            break;
        case TB_KEY_ARROW_LEFT:
            if(_mp->movePlayerW())
                updatePlayer();
            break;
        case TB_KEY_ARROW_RIGHT:
            if(_mp->movePlayerE())
                updatePlayer();
            break;
        default: ;
    }
}


void MazeGame::run(){
    drawScreen();
    updatePlayer();
    struct tb_event ev;
    bool cont=true;
    for(;cont;){
        int type=_tb.poll_event(&ev);
        switch(type){
            case TB_EVENT_KEY:
                if(ev.key==TB_KEY_ESC)
                    cont=false;
                else
                    keyHandler(ev.key);
                break;
            case TB_EVENT_RESIZE:
                drawScreen();
                updatePlayer();
                break;
            default: ;
        }
    }
}

