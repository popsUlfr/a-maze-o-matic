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
#ifndef _MAZESOLUTION_HPP
#define _MAZESOLUTION_HPP

#include "maze.hpp"

#include <vector>
#include <cstdint>

#define MAZE_BACKTRACK_NORTH 0x01
#define MAZE_BACKTRACK_EAST 0x02
#define MAZE_BACKTRACK_SOUTH 0x04
#define MAZE_BACKTRACK_WEST 0x08

#define MAZE_SOLUTION_NORTH 0x10
#define MAZE_SOLUTION_EAST 0x20
#define MAZE_SOLUTION_SOUTH 0x40
#define MAZE_SOLUTION_WEST 0x80

class MazeSolution{
public:
    typedef uint8_t CellSolution;
    
    MazeSolution(const Maze& maze)
    :_maze(maze),_cellSolutions(maze.getAmountOfCells(),0){}
    virtual ~MazeSolution(){}
    
    virtual const Maze& getMaze() const{return _maze;}
    
    virtual CellSolution& getCellSolutionAt(unsigned int x,unsigned int y){
        return _cellSolutions.at(_maze.coordToPos(x,y));
    }
    virtual CellSolution getCellSolutionAt(unsigned int x,unsigned int y) const{
        return _cellSolutions.at(_maze.coordToPos(x,y));
    }
    virtual CellSolution& getCellSolutionByPos(unsigned int i){
        return _cellSolutions.at(i);
    }
    virtual CellSolution getCellSolutionByPos(unsigned int i) const{
        return _cellSolutions.at(i);
    }
    
    static bool hasBacktrackN(CellSolution c) {
        return (c & MAZE_BACKTRACK_NORTH)==MAZE_BACKTRACK_NORTH;
    }
    static bool hasBacktrackE(CellSolution c) {
        return (c & MAZE_BACKTRACK_EAST)==MAZE_BACKTRACK_EAST;
    }
    static bool hasBacktrackS(CellSolution c) {
        return (c & MAZE_BACKTRACK_SOUTH)==MAZE_BACKTRACK_SOUTH;
    }
    static bool hasBacktrackW(CellSolution c) {
        return (c & MAZE_BACKTRACK_WEST)==MAZE_BACKTRACK_WEST;
    }
    
    static CellSolution& setBacktrackN(CellSolution& c){
        return c|=MAZE_BACKTRACK_NORTH;
    }
    static CellSolution& setBacktrackE(CellSolution& c){
        return c|=MAZE_BACKTRACK_EAST;
    }
    static CellSolution& setBacktrackS(CellSolution& c){
        return c|=MAZE_BACKTRACK_SOUTH;
    }
    static CellSolution& setBacktrackW(CellSolution& c){
        return c|=MAZE_BACKTRACK_WEST;
    }
    
    static bool hasSolutionN(CellSolution c){
        return (c & MAZE_SOLUTION_NORTH)==MAZE_SOLUTION_NORTH;
    }
    static bool hasSolutionE(CellSolution c){
        return (c & MAZE_SOLUTION_EAST)==MAZE_SOLUTION_EAST;
    }
    static bool hasSolutionS(CellSolution c){
        return (c & MAZE_SOLUTION_SOUTH)==MAZE_SOLUTION_SOUTH;
    }
    static bool hasSolutionW(CellSolution c){
        return (c & MAZE_SOLUTION_WEST)==MAZE_SOLUTION_WEST;
    }
    
    static CellSolution& setSolutionN(CellSolution& c){
        return c|=MAZE_SOLUTION_NORTH;
    }
    static CellSolution& setSolutionE(CellSolution& c){
        return c|=MAZE_SOLUTION_EAST;
    }
    static CellSolution& setSolutionS(CellSolution& c){
        return c|=MAZE_SOLUTION_SOUTH;
    }
    static CellSolution& setSolutionW(CellSolution& c){
        return c|=MAZE_SOLUTION_WEST;
    }
    
    static CellSolution& clearSolutionN(CellSolution& c){
        return c^=MAZE_SOLUTION_NORTH;
    }
    static CellSolution& clearSolutionE(CellSolution& c){
        return c^=MAZE_SOLUTION_EAST;
    }
    static CellSolution& clearSolutionS(CellSolution& c){
        return c^=MAZE_SOLUTION_SOUTH;
    }
    static CellSolution& clearSolutionW(CellSolution& c){
        return c^=MAZE_SOLUTION_WEST;
    }
protected:
    const Maze& _maze;    
    std::vector<CellSolution> _cellSolutions;
};
#endif