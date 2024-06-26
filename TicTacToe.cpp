#include <bits/stdc++.h>
using namespace std;

char AI_X = 'X';
char HUMAN_O = 'O';
char EMPTY = ' ';

vector<vector<char>> board(3, vector<char>(3, EMPTY));

void printBoard()
{
    cout << "Playing board :" << endl;
    cout << "  0   1   2" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }

        cout << endl;
        if (i < 2)
            cout << " ---+---+---" << endl;
    }
}



 // check if there are any moves left
bool movesLeft(vector<vector<char>> &b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b[i][j] == EMPTY)
                return true;
        }
    }
    return false;
}



// evaluate the board and return a score
int evaluate(vector<vector<char>> &b) 
{
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2])
        {
            if (b[row][0] == AI_X) return +10;
               
            else if (b[row][0] == HUMAN_O) return -10;
               
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col])
        {
            if (b[0][col] == AI_X) return +10;
               
            else if (b[0][col] == HUMAN_O)  return -10;
              
        }
    }


    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == AI_X)  return +10;
          
        else if (b[0][0] == HUMAN_O) return -10;
           
    }


    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == AI_X)  return +10;
          
        else if (b[0][2] == HUMAN_O) return -10;
           
    }
    return 0;

}



bool isDraw()
{
    return !movesLeft(board) && evaluate(board) == 0;
}



// Minimax function with Alpha-Beta pruning
int minimax(vector<vector<char>> &b, int depth, bool isMax, int alpha, int beta) 
{
    int score = evaluate(b);

    if (score == 10) return score - depth;
       
    if (score == -10) return score + depth;
       
    if (!movesLeft(b))  return 0;
      

    if (isMax)
    {
        int best = INT_MIN;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == EMPTY)
                {
                    b[i][j] = AI_X;
                    best = max(best, minimax(b, depth + 1, !isMax, alpha, beta));
                    b[i][j] = EMPTY;

                    alpha = max(alpha, best);

                    if (beta <= alpha)break;
                        
                }
            }
        }
        return best;
    }
    else
    {
        int best =INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == EMPTY)
                {
                    b[i][j] = HUMAN_O;
                    best = min(best, minimax(b, depth + 1, !isMax, alpha, beta));
                    b[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) break;
                       
                }
            }
        }
        return best;
    }
}


// findind best move for AI
pair<int, int> findBestMove()
{
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = AI_X;
                int moveVal = minimax(board, 0, false, INT_MIN,INT_MAX);
                board[i][j] = EMPTY;
                
                if (moveVal > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}



void playGame()
{
    int row, col;
    char currentPlayer = HUMAN_O; // Human player starts first

    while (true)
    {
        printBoard();
        if (currentPlayer == AI_X)
        {
            pair<int, int> bestMove = findBestMove();
            board[bestMove.first][bestMove.second] = AI_X;
            currentPlayer = HUMAN_O;
        }
        else
        {
            cout << "Enter your move (row and column) : ";
            while (!(cin >> row >> col) || row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != EMPTY)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid move. Enter your move (row and column): ";
            }
            board[row][col] = HUMAN_O;
            currentPlayer = AI_X;
        }

        int score = evaluate(board);
        if (score == 10)
        {
            printBoard();
            cout << "AI win " << endl;
            break;
        }
        else if (score == -10)
        {
            printBoard();
            cout << "You win " << endl;
            break;
        }
        else if (isDraw())
        {
            printBoard();
            cout << "Draw" << endl;
            break;
        }
    }
}



int main()
{
    cout << "Welcome to Tic-Tac-Toe game With AI : " << endl;
    playGame();
    return 0;
}
