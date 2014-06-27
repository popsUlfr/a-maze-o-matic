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
#ifndef _MAZEGAME_HPP
#define _MAZEGAME_HPP

#include "termbox.hpp"
#include "player.hpp"
#include "opponent.hpp"

#include "observer.hpp"
#include "observable.hpp"

#include <chrono>
#include <thread>

#define MAZEGAME_TITLE "A-MAZE-O-MATIC"

class Maze;
class MazePlayground;

class MazeGame:public Observer<Actor>,public Observable<struct tb_event&>{
public:
    static const int MazeMargin;
    static const int MinimalScreenSize;
    MazeGame(Termbox &tb);
    virtual ~MazeGame(){}
    virtual void run();
    
    virtual void update(Actor& actor);
    
protected:
    virtual void createMaze();
    virtual void eventListener();
    virtual void stopGame();
    virtual void launchGame();
    virtual void drawTitle();
    virtual void drawKeys();
    virtual void joinThreads();
    virtual void gameTimer();
    virtual void printTimer(std::chrono::seconds s);
    virtual void startTimer();
    virtual void stopTimer();
    virtual void winner(Actor& actor);
    virtual void printScore();
    
    Termbox &_tb;
    Maze _maze;
    MazePlayground _mp;
    Player _player;
    Opponent _opponent;
    std::thread _playerThread;
    std::thread _opponentThread;
    
    std::atomic_bool _timerState;
    std::thread _timer;
};
#endif