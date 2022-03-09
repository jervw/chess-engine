#pragma once

// game parameters

namespace Params {
	// Weights for evaluation
	const static int C1 = 12; // for material value
	const static int C2 = 1; // for mobility value
	const static int C3 = 3; // for pawn rank value

	const static unsigned BUFFER_SIZE = 3;

	// Piece values
	const static unsigned PAWN = 1; // for pawns
	const static unsigned KNIGHT = 3; // for knights
	const static unsigned BISHOP = 3; // for bishops
	const static unsigned ROOK = 5; // for rooks
	const static unsigned QUEEN = 9; // for queens
	const static unsigned KING = 100; // for kings

	// Game states
	const static int STALEMATE = 0;
	const static int DRAW = 0;
	const static int CHECK = 2;

	const static int CHECKMATE = (CHECK * ((C1 * 103) + (C2 * 215) + (C3 * 48))) + 1;
}
