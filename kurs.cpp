
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

static const int BOARD_SIZE = 8;
//int INT_MIN = -99;
//int INT_MAX = 99;

class Checkers {
private:
char board[BOARD_SIZE][BOARD_SIZE];

public:
    Checkers() {
        // Инициализация доски: B - черные шашки, W - белые шашки, E - пустая клетка
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((i + j) % 2 == 0) {
                    if (i < 3) {
                        board[i][j] = 'B';
                    } else if (i > 4) {
                        board[i][j] = 'W';
                    } else {
                        board[i][j] = 'E';
                    }
                } else {
                    board[i][j] = 'E';
                }
            }
        }
    }

    // Получение содержимого клетки
    char getPiece(int row, int col) {
        return board[row][col];
    }

    // Оценочная функция для текущего состояния доски
    int Evaluation() {
           int score = 0;
    int blackPieces = 0;
    int whitePieces = 0;
    int blackKings = 0;
    int whiteKings = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'B') {
                blackPieces++;
            } else if (board[i][j] == 'W') {
                whitePieces++;
            } else if (board[i][j] == 'Q') {
                blackPieces++;
                blackKings++;
            } else if (board[i][j] == 'K') {
                whitePieces++;
                whiteKings++;
            }
        }
    }

    int pieceValue = 5;
    int kingValue = 10;
    score += pieceValue * (blackPieces - whitePieces);
    score += kingValue * (blackKings - whiteKings);

    int mobilityValue = 2;
    score += mobilityValue * (CalculateMobility('B') - CalculateMobility('W'));

    // проверка возможности выигрыша и добавление бонуса в 20 очков
    if (blackPieces == 0) {
        score += 20; // Бонус за выигрыш черных
    } else if (whitePieces == 0) {
        score -= 20; // Штраф за выигрыш белых
    }

    return score;
}

    // Подсчет подвижности для заданного игрока
    int CalculateMobility(char piece) {
        int mobility = 0;

        // Перебор всех клеток на доске
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == piece) {
                    // Проверка возможности обычного хода
                    if (CanMove(i, j, i - 1, j - 1)) {
                        mobility++;
                    }
                    if (CanMove(i, j, i - 1, j + 1)) {
                        mobility++;
                    }
                    if (CanMove(i, j, i + 1, j - 1)) {
                        mobility++;
                    }
                    if (CanMove(i, j, i + 1, j + 1)) {
                        mobility++;
                    }

                    // Проверка возможности съесть
                    if (CanEat(i, j, i - 2, j - 2, i - 1, j - 1)) {
                        mobility++;
                    }
                    if (CanEat(i, j, i - 2, j + 2, i - 1, j + 1)) {
                        mobility++;
                    }
                    if (CanEat(i, j, i + 2, j - 2, i + 1, j - 1)) {
                        mobility++;
                    }
                    if (CanEat(i, j, i + 2, j + 2, i + 1, j + 1)) {
                        mobility++;
                    }
                }
            }
        }
        return mobility;
    }

    // Проверка возможности обычного хода
 // Проверка возможности хода для шашки или дамки
    bool CanMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (fromRow < 0 || fromRow >= BOARD_SIZE || fromCol < 0 || fromCol >= BOARD_SIZE ||
            toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) {
            return false;
        }

        if (board[fromRow][fromCol] == 'B' || board[fromRow][fromCol] == 'Q') {
            if (toRow - fromRow != 1) {
                return false;
            }
        } else if (board[fromRow][fromCol] == 'W' || board[fromRow][fromCol] == 'K') {
            if (toRow - fromRow != -1) {
                return false;
            }
        }

        if (board[toRow][toCol] != 'E') {
            return false;
        }

        return true;
    }

    // Проверка возможности съесть
    bool CanEat(int fromRow, int fromCol, int jumpRow, int jumpCol, int toRow, int toCol) {
        if (fromRow < 0 || fromRow >= BOARD_SIZE || fromCol < 0 || fromCol >= BOARD_SIZE ||
            toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE ||
            jumpRow < 0 || jumpRow >= BOARD_SIZE || jumpCol < 0 || jumpCol >= BOARD_SIZE) {
            return false;
        }

        if (board[toRow][toCol] != 'E') {
            return false;
        }

        if (board[jumpRow][jumpCol] != 'E' && board[jumpRow][jumpCol] != board[fromRow][fromCol]) {
            if ((toRow - fromRow == 2 || toRow - fromRow == -2) && (toCol - fromCol == 2 || toCol - fromCol == -2)) {
                return true; // Ход со съедением
            }
        }

        return false;
    }
    

void MakeKing(int row, int col) {
    // Проверяем, достигла ли шашка конечной линии
    if ((row == 0 && getPiece(row, col) == 'W') || (row == BOARD_SIZE - 1 && getPiece(row, col) == 'B')) {
        // Превращаем шашку в дамку
        board[row][col] = (getPiece(row, col) == 'W') ? 'K' : 'Q';
    }
}

    void MakeMove(int fromRow, int fromCol, int toRow, int toCol) {
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = 'E';
        // После каждого хода проверяем возможность превращения в дамку
        MakeKing(toRow, toCol);
    }


    void PrintBoard() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

      bool GameOver() {
        int blackPieces = 0;
        int whitePieces = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 'B' || board[i][j] == 'Q') {
                    blackPieces++;
                } else if (board[i][j] == 'W' || board[i][j] == 'K') {
                    whitePieces++;
                }
            }
        }
        return (blackPieces == 0 || whitePieces == 0);
    }

    // Получение всех возможных ходов для конкретной шашки
    vector<pair<pair<int, int>, pair<int, int>>> GetAllMoves(int row, int col) {
        vector<pair<pair<int, int>, pair<int, int>>> moves;

        if (board[row][col] == 'B' || board[row][col] == 'Q') {
            // Ходы для черных шашек
            if (CanEat(row, col, row - 2, col - 2, row - 1, col - 1)) {
                moves.push_back({{row, col}, {row - 2, col - 2}});
            }
            if (CanEat(row, col, row - 2, col + 2, row - 1, col + 1)) {
                moves.push_back({{row, col}, {row - 2, col + 2}});
            }
            if (CanMove(row, col, row - 1, col - 1)) {
                moves.push_back({{row, col}, {row - 1, col - 1}});
            }
            if (CanMove(row, col, row - 1, col + 1)) {
                moves.push_back({{row, col}, {row - 1, col + 1}});
            }
        } else if (board[row][col] == 'W' || board[row][col] == 'K') {
            // Ходы для белых шашек
            if (CanEat(row, col, row + 2, col - 2, row + 1, col - 1)) {
                moves.push_back({{row, col}, {row + 2, col - 2}});
            }
            if (CanEat(row, col, row + 2, col + 2, row + 1, col + 1)) {
                moves.push_back({{row, col}, {row + 2, col + 2}});
            }
            if (CanMove(row, col, row + 1, col - 1)) {
                moves.push_back({{row, col}, {row + 1, col - 1}});
            }
            if (CanMove(row, col, row + 1, col + 1)) {
                moves.push_back({{row, col}, {row + 1, col + 1}});
            }
        }

        return moves;
    }

    // Получение всех возможных ходов для текущего игрока
    vector<pair<pair<int, int>, pair<int, int>>> GetAllMovesForPlayer(char player) {
        vector<pair<pair<int, int>, pair<int, int>>> allMoves;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if ((player == 'B' && (board[i][j] == 'B' || board[i][j] == 'Q')) ||
                    (player == 'W' && (board[i][j] == 'W' || board[i][j] == 'K'))) {
                    vector<pair<pair<int, int>, pair<int, int>>> moves = GetAllMoves(i, j);
                    allMoves.insert(allMoves.end(), moves.begin(), moves.end());
                }
            }
        }

        return allMoves;
    }


    // Минимакс алгоритм с альфа-бета отсечением
    int Minimax(Checkers& field, int depth, bool maximizingPlayer, int alpha, int beta) {
        if (depth == 0 || field.GameOver()) {
            return field.Evaluation();
        }

        int bestScore;

        if (maximizingPlayer) {
            bestScore = INT_MIN;
            vector<pair<pair<int, int>, pair<int, int>>> moves = field.GetAllMovesForPlayer('B');
            for (auto move : moves) {
                Checkers newField = field;
                newField.MakeMove(move.first.first, move.first.second, move.second.first, move.second.second);
                int score = Minimax(newField, depth - 1, false, alpha, beta);
                bestScore = max(bestScore, score);
                alpha = max(alpha, bestScore);
                if (beta <= alpha) {
                    break; // Произошло отсечение
                }
            }
        } else {
            bestScore = INT_MAX;
            vector<pair<pair<int, int>, pair<int, int>>> moves = field.GetAllMovesForPlayer('W');
            for (auto move : moves) {
                Checkers newField = field;
                newField.MakeMove(move.first.first, move.first.second, move.second.first, move.second.second);
                int score = Minimax(newField, depth - 1, true, alpha, beta);
                bestScore = min(bestScore, score);
                beta = min(beta, bestScore);
                if (beta <= alpha) {
                    break; // Произошло отсечение
                }
            }
        }

        return bestScore;
    }

void ComputerMove(int depth) {
    int bestScore = INT_MIN;
    pair<pair<int, int>, pair<int, int>> bestMove;

    vector<pair<pair<int, int>, pair<int, int>>> moves = GetAllMovesForPlayer('B');
    for (auto move : moves) {
        Checkers newField = *this;
        newField.MakeMove(move.first.first, move.first.second, move.second.first, move.second.second);
        int score = Minimax(newField, depth, false, INT_MIN, INT_MAX);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    // Выполнение лучшего хода компьютера
    if (bestScore > INT_MIN) {
        MakeMove(bestMove.first.first, bestMove.first.second, bestMove.second.first, bestMove.second.second);
    }
}
};

int main() {
    Checkers game;
    game.PrintBoard();

    while (!game.GameOver()) {
        int fromRow, fromCol, toRow, toCol;

        // Ход игрока
        bool validMove = false;
        while (!validMove) {
            cout << "Your move (fromRow fromCol toRow toCol): ";
            if (cin >> fromRow >> fromCol >> toRow >> toCol && game.CanMove(fromRow, fromCol, toRow, toCol)) {
                validMove = true;
            } else {
                cout << "Invalid move. Try again!" << endl;
                cin.clear();
                while (cin.get() != '\n');  // Очищаем буфер ввода до символа новой строки
            }
        }
        game.MakeMove(fromRow, fromCol, toRow, toCol);

        // Вывод текущего состояния доски после хода игрока
        game.PrintBoard();

        // Проверка завершения игры после хода игрока
        if (game.GameOver()) {
            cout << "Game over. Player wins!" << endl;
            break;
        }

        // Ход компьютера
        cout << "Computer's move:" << endl;
        game.ComputerMove(3); // Вызываем ход компьютера с определенной глубиной поиска

        // Вывод текущего состояния доски после хода компьютера
        game.PrintBoard();

        // Проверка завершения игры после хода компьютера
        if (game.GameOver()) {
            cout << "Game over. Computer wins!" << endl;
            break;
        }
    }

    return 0;
}