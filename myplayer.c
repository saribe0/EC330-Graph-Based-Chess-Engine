#include "myPlayer.h"

//Initialize a new player
myPlayer::myPlayer(chessBoard::colorType col) : chessPlayer(col)
{
    srand(time(NULL));
}

//Gets the enemy move to update the local board
void myPlayer::enemyMove(chessBoard::move theMove)
{
    myBoard.makeMove(theMove);
}

//Makes a move
chessBoard::move myPlayer::getMove()
{
    //Create graph of chess boards
    node root(myBoard);
    for (int ii = 0; ii < myBoard.numMoves(); ii++)
    {
        chessBoard chess = chessBoard(myBoard);
        chessBoard::move testMove = chess.nthMove(ii);
        bool playerTaken = !chess.emptySquareQ(testMove.from);
        chess.makeMove(testMove);

        //Create new node
        node child(chess);
        //Add parent as root
        child.setParent(&root);
        //Add ID
        child.setID(ii);

        rate(child, false, playerTaken);

        //Add children
        if (!chess.gameOverQ() && child.getRating() >= 0)
        {
            for (int jj = 0; jj < chess.numMoves(); jj++)
            {
                chessBoard chess2 = chessBoard(chess);
                chessBoard::move testMove2 = chess2.nthMove(jj);
                bool playerTaken2 = !chess.emptySquareQ(testMove2.from);
                chess2.makeMove(testMove2);

                //Create new node
                node child2(chess2);
                //Add parent as the child
                child2.setParent(&child);

                rate(child2, true, playerTaken2);

                //Add children
                if (!chess2.gameOverQ() && child2.getRating() >= 0)
                {
                    for (int kk = 0; kk < chess2.numMoves(); kk++)
                    {
                        chessBoard chess3 = chessBoard(chess2);
                        chessBoard::move testMove3 = chess3.nthMove(kk);
                        bool playerTaken3 = !chess.emptySquareQ(testMove3.from);
                        chess3.makeMove(testMove3);

                        //Create new node
                        node child3(chess3);
                        //Add parent as the child
                        child3.setParent(&child2);
                        //Rate Board, 
                        rate(child3, false, playerTaken3);

                        if (!chess3.gameOverQ() && child3.getRating() >= 0)
                        {
                            for (int kk = 0; kk < chess2.numMoves(); kk++)
                            {
                                chessBoard chess4 = chessBoard(chess3);
                                chessBoard::move testMove4 = chess4.nthMove(kk);
                                bool playerTaken4 = !chess.emptySquareQ(testMove4.from);
                                chess4.makeMove(testMove4);

                                //Create new node
                                node child4(chess4);
                                //Add parent as the child
                                child4.setParent(&child3);
                                //Rate Board, 
                                rate(child4, true, playerTaken4);

                                if (!chess4.gameOverQ() && child4.getRating() >= 0)
                                {
                                    for (int kk = 0; kk < chess4.numMoves(); kk++)
                                    {
                                        chessBoard chess5 = chessBoard(chess4);
                                        chessBoard::move testMove5 = chess5.nthMove(kk);
                                        bool playerTaken5 = !chess.emptySquareQ(testMove5.from);
                                        chess5.makeMove(testMove5);

                                        //Create new node
                                        node child5(chess5);
                                        //Add parent as the child
                                        child5.setParent(&child5);
                                        //Rate Board, 
                                        rate(child5, false, playerTaken5);
                                        //Add child to parent's children
                                        child4.addChild(child5);
                                    }
                                }
                                rate(child4, true, playerTaken4);
                                //Add child to parent's children
                                child3.addChild(child4);
                            }
                        }
                        rate(child3, false, playerTaken3);
                        //Add child to parent's children
                        child2.addChild(child3);
                    }
                }
                //Rate and add child to parent's children
                rate(child2, true, playerTaken2);
                child.addChild(child2);
            }
        }
        //Rate and add child to parent's children
        rate(child, false, playerTaken);
        root.addChild(child);
    }

    //Find the move that gives board with the best rating 
    int maxRating = -2000;
    int moveID[3];
    for (int ii = 0; ii < myBoard.numMoves(); ii++)
    {
        if ((root.getChild(ii)).getRating() >= maxRating)
        {
            maxRating = (root.getChild(ii)).getRating();
            moveID[0] = (root.getChild(ii)).getID();
            moveID[1] = moveID[0];
        }
    }

    //Make the move that has the best rating
    chessBoard::move theMove = myBoard.nthMove(moveID[rand()%2]);
    myBoard.makeMove(theMove); 
    return theMove; 
}

//Rate boards based on whether someone wins, loses, or has a piece taken
void myPlayer::rate(node &child, bool myTurn, bool playerTaken)
{
    int val = 0;
    
    if (child.numChild() != 0)
    {
        for (int ii = 0; ii < child.numChild(); ii++)
            val += (child.getChild(ii)).getRating();
    }
    else
    {
        if ((child.getBoard()).gameOverQ())
            if (myTurn)
                val -= 100;
            else
                val += 250;
        if (playerTaken)
            if (myTurn)
                val -= 1;
            else
                val += 10;
    }

    //Applies the rating to the child 
    child.setRating(val);
}