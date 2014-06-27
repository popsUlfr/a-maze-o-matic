#ifndef _MAZEGAME_HPP
#define _MAZEGAME_HPP

#include "termbox.hpp"
#include "player.hpp"
#include "opponent.hpp"

#include "observer.hpp"
#include "observable.hpp"

#include <thread>

class Maze;
class MazePlayground;

class MazeGame:public Observer<Actor>,public Observable<struct tb_event&>{
public:
    static const int MazeMargin;
    static const int MinimalScreenSize;
    MazeGame(Termbox &tb);
    virtual ~MazeGame();
    virtual void run();
    
    virtual void update(Actor& actor);
    
protected:
    virtual void createMaze();
    virtual void deleteMaze();
    virtual void eventListener();
    virtual void stopGame();
    virtual void launchGame();
    
    Termbox &_tb;
    Maze* _maze;
    MazePlayground* _mp;
    Player _player;
    Opponent _opponent;
    std::thread _playerThread;
    std::thread _opponentThread;
};
#endif