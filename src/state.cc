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

Pawn* State::bk = new King('K', 1, KING);
Pawn* State::bq = new Queen('Q', 1, QUEEN);
Pawn* State::bt = new Rook('R', 1, ROOK);
Pawn* State::bb = new Bishop('B', 1, BISHOP);
Pawn* State::bh = new Knight('N', 1, KNIGHT);
Pawn* State::bs = new Soldier('P', 1, PAWN);


State::State()
{
    // Initialize board with NULL values
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = NULL;

    // Soldiers
    for (int i = 0; i < 8; i++) {
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

    //Black pawns
    board[0][7] = bt;
    board[1][7] = bh;
    board[2][7] = bb;
    board[3][7] = bq;
    board[4][7] = bk;
    board[5][7] = bb;
    board[6][7] = bh;
    board[7][7] = bt;
}


void State::UpdateState(Move* move)
{
    std::wcout << L"START\n";
    std::wcout << move->GetStartTile().GetColumn() << "\n";
    std::wcout << move->GetStartTile().GetRow() << "\n";;

    std::wcout << L"END\n";
    std::wcout << move->GetEndTile().GetColumn() << "\n";
    std::wcout << move->GetEndTile().GetRow() << "\n";;

    // Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
    // Asetetaan my�hemmin, jos tarvii.


    //Tarkastetaan on siirto lyhyt linna
    if (move->GetStartTile().GetColumn() == move->GetEndTile().GetColumn() &&
        move->GetStartTile().GetRow() == move->GetEndTile().GetRow()) {
        std::wcout << L"Ei lyhyt linna\n";
    }

    // onko pitkä linna
    if (move->GetStartTile().GetColumn() != move->GetEndTile().GetColumn() &&
        move->GetStartTile().GetRow() != move->GetEndTile().GetRow()) {
        std::wcout << L"Ei pitkä linna\n";
    }



    // Kaikki muut siirrot

    //Ottaa siirron alkuruudussa olleen nappulan talteen 
    Pawn* startPawn = board[move->GetStartTile().GetRow()][move->GetStartTile().GetColumn()];

    //Laittaa talteen otetun nappulan uuteen ruutuun
    board[move->GetEndTile().GetRow()][move->GetEndTile().GetColumn()] = startPawn;


    // Tarkistetaan oliko sotilaan kaksoisaskel
    // (asetetaan kaksoisaskel-lippu)
    if (move->GetStartTile().GetColumn() == move->GetEndTile().GetColumn() &&
        move->GetStartTile().GetRow() == move->GetEndTile().GetRow()) {
        std::wcout << L"Kaksoisaskel\n";
    }

    // Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.
    if (move->GetStartTile().GetColumn() != move->GetEndTile().GetColumn() &&
        move->GetStartTile().GetRow() != move->GetEndTile().GetRow()) {
        std::wcout << L"Ohestalyönti\n";
    }

    // Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa 
    //eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?



    //
    ////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula

    // katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)

    // katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)

//p�ivitet��n _siirtovuoro

}



int State::GetTurn()
{
    return 0;
}


void State::GetTurn(int vuoro)
{

}


bool State::GetWKingState()
{
    return false;
}


bool State::GetBKingState()
{
    return false;
}




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
double State::Evaluate()
{
    return 0;

    //kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta

    //1. Nappuloiden arvo

    //2. Kuningas turvassa

    //3. Arvosta keskustaa

    // 4. Arvosta linjoja

}


double State::CalculatePawnValues(int vari)
{
    return 0;

}


bool State::IsOpeningOrMiddle(int vari)
{
    return 0;
    // Jos upseereita 3 tai v�hemm�n on loppupeli
    // mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�

    //Jos vari on 0 eli valkoiset
    //niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double State::PawnsMiddle(int vari)
{
    return 0;

    //sotilaat ydinkeskustassa + 0.25/napa
    //ratsut ydinkeskustassa + 0.25/napa
    //sotilaat laitakeskustassa + 0.11/napa
    //ratsut laitakeskustassa + 0.11/napa

    //valkeille ydinkeskusta



    //valkeille laitakeskusta



    //mustille ydinkeskusta

    //mustille laitakeskusta

}


double State::Lines(int vari)
{
    return 0;

    //valkoiset

    //mustat

}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMax State::GetMinMax(int syvyys)
{
    MinMax value;

    // Generoidaan aseman lailliset siirrot.

    // Rekursion kantatapaus 1: peli on loppu

    // Rekursion kantatapaus 2: katkaisusyvyydess�

    // Rekursioaskel: kokeillaan jokaista laillista siirtoa s
    // (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

    return value;
}


MinMax State::Max(int syvyys)
{
    MinMax value;
    return value;
}


MinMax State::Min(int syvyys)
{
    MinMax value;
    return value;
}


bool State::TileAtRisk(Tile* tile, int opponentColor)
{

    return false;
}


void State::WatchKingCheck(std::list<Move>& moveList, int color)
{

}


void State::GetLegalMoves(std::list<Move>& moveList) {

}
