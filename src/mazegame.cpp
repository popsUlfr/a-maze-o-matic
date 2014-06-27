#include "mazegame.hpp"

#include "mazedrawer.hpp"
#include "mazeplayground.hpp"
#include "maze.hpp"
#include "aihuman.hpp"
#include "actor.hpp"

const int MazeGame::MazeMargin=4;
const int MazeGame::MinimalScreenSize=8;

MazeGame::MazeGame(Termbox &tb):
_tb(tb),
_maze(nullptr),
_mp(nullptr){
    _player.attachObserver(this);
    attachObserver(&_player);
    _opponent.attachObserver(this);
}

void MazeGame::deleteMaze(){
    if(_mp!=nullptr) delete(_mp);
    if(_maze!=nullptr) delete(_maze);
}

MazeGame::~MazeGame(){
    deleteMaze();
}

void MazeGame::createMaze(){
    _tb.clear();
    int width=_tb.width();
    int height=_tb.height();
    if((width-((MazeMargin<<1)+MinimalScreenSize))>0 &&
        (height-((MazeMargin<<1)+MinimalScreenSize))>0
    ){
        deleteMaze();
        _maze=new Maze(MazeDrawer::targetMazeWidth(width-(MazeMargin<<1)),
                       MazeDrawer::targetMazeHeight(height-(MazeMargin<<1)));
        _mp=new MazePlayground(*_maze);
        _mp->addActorStart(_player);
        _mp->addActorEnd(_opponent);
        MazeDrawer::drawMaze(_tb,*_maze,MazeMargin,MazeMargin);
        MazeDrawer::drawEntryPoints(_tb,*_mp,MazeMargin,MazeMargin);
    }
    _tb.present();
}

void MazeGame::update(Actor& actor){
    MazeDrawer::clearCell(_tb,MazeMargin,MazeMargin,
                          _maze->posToCoordX(actor.getPrevPosition()),
                          _maze->posToCoordY(actor.getPrevPosition()));
    MazeDrawer::drawPlayer(_tb,MazeMargin,MazeMargin,
                           _maze->posToCoordX(actor.getPosition()),
                           _maze->posToCoordY(actor.getPosition())
    );
    _tb.present();
}

void MazeGame::launchGame(){
    createMaze();
    update(_player);
    update(_opponent);
    _playerThread=std::thread(&Player::run,&_player,_mp);
    _opponentThread=std::thread(&Opponent::run,&_opponent,_mp);
}

void MazeGame::stopGame(){
    _player.stop();
    _opponent.stop();
    _playerThread.join();
    _opponentThread.join();
}

void MazeGame::run(){
    launchGame();
    eventListener();
}

void MazeGame::eventListener(){
    struct tb_event ev;
    bool cont=true;
    for(;cont;){
        int type=_tb.poll_event(&ev);
        switch(type){
            case TB_EVENT_KEY:
                if(ev.key==TB_KEY_ESC)
                    cont=false;
                else if(ev.key==TB_KEY_SPACE){
                    stopGame();
                    launchGame();
                }
                else
                    notifyObserver(ev);
                break;
            case TB_EVENT_RESIZE:
                stopGame();
                launchGame();
                break;
            default: ;
        }
    }
    stopGame();
}
