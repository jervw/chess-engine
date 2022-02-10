#include <iostream>
#include "state.hh"


#include "minmax.hh"
#include "pawn.hh"
#include "tile.hh"

Pawn* State::wk = new King('K', WHITE, KING);
Pawn* State::wq = new Queen('Q', WHITE, QUEEN);
Pawn* State::wt = new Rook('R', WHITE, ROOK);
Pawn* State::wb = new Bishop('B', WHITE, BISHOP);
Pawn* State::wh = new Knight('N', WHITE, KNIGHT);
Pawn* State::ws = new Soldier('P', WHITE, PAWN);

Pawn* State::bk = new King('k', BLACK, KING);
Pawn* State::bq = new Queen('q', BLACK, QUEEN);
Pawn* State::bt = new Rook('r', BLACK, ROOK);
Pawn* State::bb = new Bishop('b', BLACK, BISHOP);
Pawn* State::bh = new Knight('n', BLACK, KNIGHT);
Pawn* State::bs = new Soldier('p', BLACK, PAWN);

State::State() {
    // Initialize board with NULL values
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = NULL;

    // Soldiers
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i][1] = ws;
        board[i][6] = bs;
    }

    // White pawns
    board[0][0] = wt;
    board[1][0] = wh;
    board[2][0] = wb;
    board[3][0] = wq;
    board[4][0] = wk;
    board[5][0] = wb;
    board[6][0] = wh;
    board[7][0] = wt;

    // Black pawns
    board[0][7] = bt;
    board[1][7] = bh;
    board[2][7] = bb;
    board[3][7] = bq;
    board[4][7] = bk;
    board[5][7] = bb;
    board[6][7] = bh;
    board[7][7] = bt;
}
// Update board
void State::UpdateState(Move* move) {

    // Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
    // Asetetaan my�hemmin, jos tarvii.
    this->doublestepOnCol = -1;

    // Tarkastetaan on move lyhyt linna

    if (move->IsShortCastle()) {
        if (_turn == 0) {
            board[4][0] = NULL;
            board[6][0] = wk;
            board[7][0] = NULL;
            board[5][0] = wt;
        }

        if (_turn == 1) {
            board[4][7] = NULL;
            board[6][7] = bk;
            board[7][7] = NULL;
            board[5][7] = bt;
        }
    }


    // onko pitkä linna
    else if (move->IsLongCastle()) {
        if (_turn == 0) {
            board[4][0] = NULL; // kuninkaan paikalle tyhjä
            board[2][0] = wk; // kuningas uudelle paikalle
            board[0][0] = NULL; // tornin paikalle tyhjä
            board[3][0] = wt; // torni uudella paikalle
        }
        if (_turn == 1) {
            board[4][7] = NULL; // kuninkaan paikalle tyhjä
            board[2][7] = bk; // kuningas uudelle paikalle
            board[0][7] = NULL; // tornin paikalle tyhjä
            board[3][7] = bt; // torni uudella paikalle
        }

    }

    // Kaikki muut siirrot
    else {
        int startRow = move->Start().row;
        int startCol = move->Start().column;

        // Ottaa siirron alkuruudussa olleen nappulan talteen
        Pawn* movingPawn = board[startCol][startRow];


        int endRow = move->End().row;
        int endCol = move->End().column;

        // Tarkistetaan oliko sotilaan kaksoisaskel
        if (board[startCol][startRow]->GetCode() == PAWN && (startRow - endRow) == 2 || startRow - endRow == -2)
            doublestepOnCol = startCol;

        // Ohestalynti on tyhjään tileun. Vieressä oleva (sotilas) poistetaan.
        if (board[startCol][startRow]->GetCode() == PAWN && startRow != endRow && board[endCol][endRow] == NULL)
            board[endCol][startRow] = NULL;


        // Laittaa talteen otetun nappulan uuteen tileun
        board[startCol][startRow] = NULL;
        board[endCol][endRow] = movingPawn;

        // katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
        if (movingPawn->GetCode() == KING) {

            if (movingPawn->GetColor() == WHITE)
                wKingMoved = true;
            else
                bKingMoved = true;
        }

        //Katsotaan onko liikkunut nappula torni ja muutetaan sen xRookMoved arvo
        if (movingPawn->GetCode() == ROOK) {
            if (movingPawn->GetColor() == WHITE) {
                if (startCol == 7 && startRow == 0)
                    wKRookMoved = true;
                else
                    wQRookMoved = true;
            }
            else {
                if (startCol == 7 && startRow == 7)
                    bKRookMoved = true;
                else
                    bQRookMoved = true;
            }
        }

    }

    if (_turn == WHITE)
        _turn = BLACK;
    else
        _turn = WHITE;
}

int State::GetTurn() { return _turn; }

void State::GetTurn(int vuoro) {}

/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L�hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv� ett� kunigas g1 tai b1/c1
Loppupeliss� vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est�m�ss� vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki� linjoja daami, torni ja l�hetti
*/
double State::Evaluate() {
    return 0;

    // kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa
    // voidaan s��t�� helposti yhdest� paikasta

    // 1. Nappuloiden arvo

    // 2. Kuningas turvassa

    // 3. Arvosta keskustaa

    // 4. Arvosta linjoja
}

double State::CalculatePawnValues(int color) { return 0; }

bool State::IsOpeningOrMiddle(int color) {
    return 0;
    // Jos upseereita 3 tai v�hemm�n on loppupeli
    // mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�

    // Jos color on 0 eli valkoiset
    // niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
}

double State::PawnsMiddle(int color) {
    return 0;

    // sotilaat ydinkeskustassa + 0.25/napa
    // ratsut ydinkeskustassa + 0.25/napa
    // sotilaat laitakeskustassa + 0.11/napa
    // ratsut laitakeskustassa + 0.11/napa

    // valkeille ydinkeskusta

    // valkeille laitakeskusta

    // mustille ydinkeskusta

    // mustille laitakeskusta
}

double State::Lines(int color) {
    return 0;

    // valkoiset

    // mustat
}

// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi
// (lis�sin parametrina staten)
// int maxi(int depth, state a)
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

// int mini(int depth, state a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMax State::GetMinMax(int syvyys) {
    MinMax value;

    // Generoidaan staten lailliset siirrot.

    // Rekursion kantatapaus 1: peli on loppu

    // Rekursion kantatapaus 2: katkaisusyvyydess�

    // Rekursioaskel: kokeillaan jokaista lailmoveList movea s
    // (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

    return value;
}

MinMax State::Max(int syvyys) {
    MinMax value;
    return value;
}

MinMax State::Min(int syvyys) {
    MinMax value;
    return value;
}

bool State::TileAtRisk(Tile* tile, int opponentColor) { return false; }

void State::WatchTileKingCheck(std::list<Move>& moveList, int color) {}

void State::GetLegalMoves(std::list<Move>& moveList) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            //Ei kysele tyhjiltä ruuduilta nappulan nimeä
            if (board[i][j] == NULL || board[i][j]->GetColor() != _turn) continue;
            board[i][j]->GetMoves(moveList, &Tile(i, j), this, _turn); // myähäinen sidonta!
        }
}