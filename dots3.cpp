#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Square {
 public:
    int top;
    int bottom;
    int left;
    int right;
    bool topFill;
    bool bottomFill;
    bool leftFill;
    bool rightFill;
};

Square blocks[3][3];
char scores[3][3];
int vert[3][4];
int vertFill[3][4];
int horiz[3][4];
int horizFill[4][3];

void initBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scores[i][j] = ' ';
	}
    }
    // initialize vert numbers
    int vertNum = 4;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            vert[i][j] = vertNum;
	    vertNum++;
	    vertFill[i][j] = 0;
	}
	vertNum += 3;
    }

    // initialize horiz numbers
    int horizNum = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            horiz[i][j] = horizNum;
	    horizNum++;
	    horizFill[i][j] = 0;
	}
	horizNum += 4;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            blocks[i][j].top = horiz[i][j];
            blocks[i][j].bottom = horiz[i + 1][j];
	    blocks[i][j].left = vert[i][j];
	    blocks[i][j].right = vert[i][j + 1];
            blocks[i][j].topFill = false;
            blocks[i][j].bottomFill = false;
	    blocks[i][j].leftFill = false;
	    blocks[i][j].rightFill = false;
	}
    }
}

void displayBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (horizFill[i][j] == 0) {
  	        std::cout << " o " << "---" << std::setw(2) << horiz[i][j] << "----"; 
	    } else {
                std::cout << " o " << "---------";
	    }
	}
        std::cout << " o" << std::endl;
	std::cout << std::setw(2) << "|";
        for (int j = 0; j < 3; j++) {
            std::cout << std::setw(12) << "|";
	}
	std::cout << std::endl;
	if (vertFill[i][0] == 0) {
	    std::cout << std::setw(2) << vert[i][0]; 
	} else {
            std::cout << std::setw(2) << "|";
	}
	for (int j = 0; j < 3; j++) {
	    if (vertFill[i][j+1] == 0) {
                std::cout << std::setw(5) << scores[i][j] << std::setw(7) << vert[i][j+1]; 
    	    } else {
                std::cout << std::setw(5) << scores[i][j] << std::setw(7) << "|";
	    }
	}
	std::cout << std::endl;
	std::cout << std::setw(2) << "|";
	for (int j = 0; j < 3; j++) {
            std::cout << std::setw(12) << "|";
	}
	std::cout << std::endl;
    }

    for (int j = 0; j < 3; j++) {
	if (horizFill[3][j] == 0) {
	    std::cout << " o " << "---" << horiz[3][j] << "----"; 
	} else {
            std::cout << " o " << "---------";
	}
    }
    std::cout << " o" << std::endl;
}
 
void checkWin(char player, int blockI, int blockJ) {
    if (blocks[blockI][blockJ].topFill == true) {
        if (blocks[blockI][blockJ].bottomFill == true) {
            if (blocks[blockI][blockJ].leftFill == true) {
                if (blocks[blockI][blockJ].rightFill == true) {
                    scores[blockI][blockJ] = player;
		}
	    }
	}
    }
}

int checkValid(int move) {
    int iInd, jInd;
    if (move < 1 || move > 24) {
        return 0;
    }
    if (move % 7 == 1 || move % 7 == 2 || move % 7 == 3) {
        iInd = move / 7;
	jInd = move - iInd * 7 - 1;
	if (horizFill[iInd][jInd] == 1) {
            return 0;
	}
    } else {
        if (move % 7 == 0) {
            iInd = move / 7 - 1;
	    jInd = 3;
	} else {
  	    iInd = move / 7;
	    jInd = move - iInd * 7 - 4;
	}
        if (vertFill[iInd][jInd] == 1) {
	    return 0;
	}
    }
    return 1;
}

void updateGame(char player, int move) {
    int iInd, jInd;
    if (move % 7 == 1 || move % 7 == 2 || move % 7 == 3) {
        iInd = move / 7;
	jInd = move - iInd * 7 - 1;
	horizFill[iInd][jInd] = 1;
	// update Fills in block
	for (int i = 0; i < 3; i++) {
        // check top of top row
	    if (blocks[0][i].top == move) {
                blocks[0][i].topFill = true;
		checkWin(player, 0, i);
		return;
	    }
	// check bottom of bottom row
	    if (blocks[2][i].bottom == move) {
                blocks[2][i].bottomFill = true;
		checkWin(player, 2, i);
		return;
	    }
	}
	// check bottom of first two rows, matches top of last two rows
	for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                if (blocks[i][j].bottom == move) {
                    blocks[i][j].bottomFill = true;
		    blocks[i + 1][j].topFill = true;
		    checkWin(player, i, j);
		    checkWin(player, i + 1, j);
		    return;
		}
	    }
	}
    } else {
	if (move % 7 == 0) {
            iInd = move / 7 - 1;
	    jInd = 3;
	} else {
  	    iInd = move / 7;
	    jInd = move - iInd * 7 - 4;
	}
        vertFill[iInd][jInd] = 1;
 	// update Fills in block
	for (int i = 0; i < 3; i++) {
            // check left of left column
	    if (blocks[i][0].left == move) {
                blocks[i][0].leftFill = true;
		checkWin(player, i, 0);
		return;
	    }
	    // check right of right column
            if (blocks[i][2].right == move) {
                blocks[i][2].rightFill = true;
		checkWin(player, i, 2);
		return;
	    }
	}
	// check left of first two columns, matches right of last two columns
	for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
		if (blocks[i][j].right == move) {
                    blocks[i][j].rightFill = true;
		    blocks[i][j + 1].leftFill = true;
		    checkWin(player, i, j);
		    checkWin(player, i, j + 1);
		    return;
		}
	    }
	}
    }
}

void printResults(char player1, char player2) {
    int player1Count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (scores[i][j] == player1) {
	        player1Count++;
	    }
	}
    }
    if (player1Count >= 5) {
        std::cout << player1 << " wins!" << std::endl;
    } else {
        std::cout << player2 << " wins!" << std::endl;
    }
}

int main() {
    initBoard();
    displayBoard();
    char player1, player2;
    std::cout << "What is player 1's letter?" << std::endl;
    std::cin >> player1;
    std::cout << "What is player 2's letter?" << std::endl;
    std::cin >> player2;
    std::cout << "Begin Game: " << player1 << " vs. " << player2 << std::endl;
    displayBoard();
    char thisPlayer = player1;
    int thisMove;
    int isValid;
    for (int i = 0; i < 24; i++) {
        std::cout << "Enter player " << thisPlayer << " move: ";
	std::cin >> thisMove;
        isValid = checkValid(thisMove);
	while (!isValid) {
	    std::cout << "Not valid input, try again." << std::endl; 
	    std::cout << "Enter player " << thisPlayer << " move: ";
	    std::cin >> thisMove;
	    isValid = checkValid(thisMove);
	}
        updateGame(thisPlayer, thisMove);
	displayBoard();
	if (thisPlayer == player1) {
            thisPlayer = player2;
	} else {
            thisPlayer = player1;
	}
    }
    printResults(player1, player2);
}
