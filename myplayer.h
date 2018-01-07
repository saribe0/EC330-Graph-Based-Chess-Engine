#ifndef MYPLAYER_H
#define	MYPLAYER_H

#include 
#include "chessBoard.h"
#include "chessPlayer.h"
#include 
#include 

class myPlayer : public chessPlayer {
public:
    //Creates a player
    myPlayer(chessBoard::colorType col);

    //gets the enemy move so the internal board can be updated
    void enemyMove(chessBoard::move theMove);

    //Returns a move of type move to the main
    chessBoard::move getMove();

    //Defines a class called node which keeps information about
    //	a board including the node that contains the board that 
    //	came before it, a list of children nodes which contain
    //	boards that it can go to, and a rating for the board
    class node {
    public:
        node(chessBoard chess){ board = chess; parent = NULL; rating = 0; }

        void addChild(node child){ children.push_back(child); }

        void setParent(node* par){ parent = par; }

        void setRating(int rat){ rating = rat; }

        void setID(int id){ ID = id; }

        node getChild(int ii){ return children[ii]; }

        int numChild(){ return children.size(); }

        node* getParent(){ return parent; }

        int getRating(){ return rating; }

        chessBoard getBoard(){ return board; }

        int getID(){ return ID; }

    private:
        chessBoard board;
        vector children;
        node* parent;
        int rating;
        int ID;
    };

    //Rates a node
    void rate(node &child, bool myTurn, bool playerTaken);

private:
    chessBoard myBoard; // internal version of the current board

};
#endif	/* MYPLAYER_H */