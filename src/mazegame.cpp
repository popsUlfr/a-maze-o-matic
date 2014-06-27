/*
 * Copyright (c) 2014 Philipp Richter
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "mazegame.hpp"

#include "mazedrawer.hpp"
#include "mazeplayground.hpp"
#include "maze.hpp"
#include "aihuman.hpp"
#include "actor.hpp"

#include <chrono>

const int MazeGame::MazeMargin=4;
const int MazeGame::MinimalScreenSize=8;

MazeGame::MazeGame(Termbox &tb):
_tb(tb),
_maze(MinimalScreenSize,MinimalScreenSize),
_mp(_maze),
_opponent(0x2689,TB_MAGENTA|TB_BOLD)

{
    _player.attachObserver(this);
    attachObserver(&_player);
    _opponent.attachObserver(this);
}

void MazeGame::createMaze(){
    _tb.clear();
    drawTitle();
    drawKeys();
    int width=_tb.width();
    int height=_tb.height();
    if((width-((MazeMargin<<1)+MinimalScreenSize))>0 &&
        (height-((MazeMargin<<1)+MinimalScreenSize))>0
    ){
        _maze=Maze(MazeDrawer::targetMazeWidth(width-(MazeMargin<<1)),
                       MazeDrawer::targetMazeHeight(height-(MazeMargin<<1)));
        _mp=MazePlayground(_maze);
        _mp.addActorStart(_player);
        _mp.addActorEnd(_opponent);
        MazeDrawer::drawMaze(_tb,_maze,MazeMargin,MazeMargin);
        MazeDrawer::drawEntryPoints(_tb,_mp,MazeMargin,MazeMargin);
        printScore();
    }
    _tb.present();
}

void MazeGame::drawTitle(){
    std::string title(MAZEGAME_TITLE);
    std::string::size_type size=title.size();
    int width=_tb.width();
    if((std::string::size_type)width>size){
        _tb.printString((width-size)/2,MazeMargin/2,title,TB_WHITE|TB_BOLD);
    }
}

void MazeGame::drawKeys(){
    _tb.printString(MazeMargin,MazeMargin/2+1,"ESC to quit, SPACE to retry",TB_WHITE);
}

void MazeGame::printTimer(std::chrono::seconds s){
    std::chrono::minutes mins=std::chrono::duration_cast<std::chrono::minutes>(s);
    std::string minsString=std::to_string(mins.count());
    std::string secsString=std::to_string((s%60).count());
    std::string string=std::string("Timer: ")+std::string((minsString.size()==1)?"0":"")+minsString+":"+
    std::string((secsString.size()==1)?"0":"")+secsString;
    _tb.printString(_tb.width()-MazeMargin-string.size(),_tb.height()-(MazeMargin>>1)-1,string);
}

void MazeGame::gameTimer(){
    std::chrono::seconds _ellapsed=std::chrono::seconds::zero();
    for(;_timerState.load();){
        printTimer(_ellapsed);
        ++_ellapsed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MazeGame::startTimer(){
    _timerState.store(true);
    _timer=std::thread(&MazeGame::gameTimer,this);
}

void MazeGame::stopTimer(){
    _timerState.store(false);
}

void MazeGame::printScore(){
    std::string pS=std::to_string(_player.getScore());
    std::string oS=std::to_string(_opponent.getScore());
    std::string string=std::string((pS.size()==1)?"0":"")+pS+":"+
    std::string((oS.size()==1)?"0":"")+oS;
    int x=(_tb.width()-string.size())>>1;
    _tb.printString(x,_tb.height()-(MazeMargin>>1)-1,string.substr(0,2),TB_RED|TB_BOLD);
    _tb.printString(x+2,_tb.height()-(MazeMargin>>1)-1,string.substr(2,1),TB_WHITE|TB_BOLD);
    _tb.printString(x+3,_tb.height()-(MazeMargin>>1)-1,string.substr(3),TB_MAGENTA|TB_BOLD);
}

void MazeGame::winner(Actor& actor){
    stopGame();
    Player* p=dynamic_cast<Player*>(&actor);
    if(p!=nullptr)
        _tb.printString(MazeMargin,_tb.height()-(MazeMargin>>1)-1,"YOU WIN!",TB_WHITE|TB_BOLD);
    else
        _tb.printString(MazeMargin,_tb.height()-(MazeMargin>>1)-1,"OPPONENT WINS!!",TB_WHITE|TB_BOLD);
    
    actor.setScore(actor.getScore()+1);
    printScore();
}

void MazeGame::update(Actor& actor){
    MazeDrawer::clearCell(_tb,MazeMargin,MazeMargin,
                          _maze.posToCoordX(actor.getPrevPosition()),
                          _maze.posToCoordY(actor.getPrevPosition()));
    MazeDrawer::drawPlayer(_tb,MazeMargin,MazeMargin,
                           _maze.posToCoordX(actor.getPosition()),
                           _maze.posToCoordY(actor.getPosition()),
                           actor.getPlayerSymbol(),
                           actor.getPlayerColor()
                          );
    if(actor.getPosition()==actor.getGoalPosition()){ //WINNER!
        winner(actor);
    }
    _tb.present();
}

void MazeGame::launchGame(){
    createMaze();
    update(_player);
    update(_opponent);
    startTimer();
    _playerThread=std::thread(&Player::run,&_player,&_mp);
    _opponentThread=std::thread(&Opponent::run,&_opponent,&_mp);
}

void MazeGame::stopGame(){
    stopTimer();
    _player.stop();
    _opponent.stop();
}

void MazeGame::joinThreads(){
    _timer.join();
    _playerThread.join();
    _opponentThread.join();
}

void MazeGame::run(){
    eventListener();
}

void MazeGame::eventListener(){
    launchGame();
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
                    joinThreads();
                    launchGame();
                }
                else
                    notifyObserver(ev);
                break;
            /*case TB_EVENT_RESIZE:
                stopGame();
                launchGame();
                break;*/
            default: ;
        }
    }
    stopGame();
    joinThreads();
}
