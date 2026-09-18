#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//test string you can use :xx8x5xxx65x3xxx94221x9xx758x3xx826x1xx46x95xx6x913xx7x391xx8x25452xxx8x78xxx2x3xx

    char lengh[82];
    int sudoku[10][9][9], AmmountOfCharacters = 0, SudokuLayer = 0, SudokuRow = 0, SudokuColum = 0;
    int TempSudokuRow = 0, TempSudokuColum = 0, HoldingValue = 0;
    bool HasClearedCell = false;

void FindWhatEmptyCanBe () {

    int HoldingValueY = 0, HoldingValueX = 0;

    SudokuLayer = 0, SudokuRow = 0, SudokuColum = 0, HoldingValue = 0;

    for (int ClearedCells = 0; ClearedCells <= 80;ClearedCells++) {
        //creates the potentials list were we store what values a clear cell can be
        bool potentials[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

        TempSudokuRow = 0, TempSudokuColum = 0;

        //starts the loop to check the full sudoku
        if (sudoku[0][SudokuRow][SudokuColum] == 0) {
            while (TempSudokuColum <= 8) {
                //checks the colum for variables potentials cannot be
                if (sudoku[0][SudokuRow][TempSudokuColum] != 0) {
                    potentials[sudoku[0][SudokuRow][TempSudokuColum] - 1] = 0;
                }
                TempSudokuColum++;
            }

            while (TempSudokuRow <= 8) {
                //checks the row for variables potentials cannot be
                if (sudoku[0][TempSudokuRow][SudokuColum] != 0) {
                    potentials[sudoku[0][TempSudokuRow][SudokuColum] - 1] = 0;
                }
                TempSudokuRow++;
            }
            //centers the temp coordinates at the top left of the box its inside
            TempSudokuColum = SudokuColum / 3;
            TempSudokuRow = SudokuRow / 3;
            TempSudokuColum *= 3;
            TempSudokuRow *= 3;
            HoldingValueX = TempSudokuColum;
            HoldingValueY = TempSudokuRow;

            //iterates through the small square to find what variables potentials cannot be
            for (;;) {
                if ((TempSudokuColum - HoldingValueX) <= 2) {
                    if (sudoku[0][TempSudokuRow][TempSudokuColum] != 0) {
                        potentials[sudoku[0][TempSudokuRow][TempSudokuColum] - 1] = 0;
                    }
                    TempSudokuColum++;
                    if (TempSudokuColum - HoldingValueX >= 2) {
                        TempSudokuColum = HoldingValueX;
                        TempSudokuRow++;
                    }
                }
                if (TempSudokuRow - HoldingValueY >= 3) {
                    break;
                }
            }
            /*takes the potentials list and inputs it to the higher levels of the array with a -1 at
            the end unless it hits the last cell*/
            SudokuLayer = 1;
            for (int i = 0; i <= 8; i++) {
                if (potentials [i] == 1) {
                    sudoku[SudokuLayer][SudokuRow][SudokuColum] = i + 1;
                    SudokuLayer++;
                }
            }
            if (SudokuLayer <= 8) {
                sudoku[SudokuLayer][SudokuRow][SudokuColum] = -1;
            }
        }
        SudokuLayer = 0;
        SudokuColum++;
        if (SudokuColum >= 9) {
            SudokuColum = 0;
            SudokuRow++;
        }
    }

}

int FillingWhatEmptyCanBe () {

    SudokuRow = 0, SudokuColum = 0, HoldingValue = 0;

    //goes through the whole array and writes in the values clear cells can be
    for (int ClearedCells = 0; ClearedCells <= 80;ClearedCells++) {
        if (sudoku[0][SudokuRow][SudokuColum] == 0) {
            if (sudoku[2][SudokuRow][SudokuColum] == -1) {
                sudoku[0][SudokuRow][SudokuColum] = sudoku[1][SudokuRow][SudokuColum];
                HasClearedCell = 1;
            }
        }
        SudokuColum++;
        if (SudokuColum >= 9) {
            SudokuColum = 0;
            SudokuRow++;
        }
    }
}

int main(void) {

    //takes a input from the user, translates 'x' to 0 and puts it into the 3d array on the first level
    printf("input the sudoku from left to right, top to bottom.");
    printf("example: 2x6x87194x... \n:");
    fgets (lengh, 82, stdin);

    while (AmmountOfCharacters <= 80) {
        HoldingValue = lengh[AmmountOfCharacters] - 48;
        if (HoldingValue == 72) {
            HoldingValue = 0;
        }
        sudoku[0][SudokuRow][SudokuColum] = HoldingValue;
        SudokuColum++;
            if (SudokuColum >= 9) {
                SudokuColum = 0;
                SudokuRow++;
        }
        AmmountOfCharacters++;
    }

    //loops over the two functions until HasClearedCell is false
    do {
        HasClearedCell = 0;
        FindWhatEmptyCanBe ();
        FillingWhatEmptyCanBe ();
    } while (HasClearedCell);

    SudokuRow = 0;
    SudokuColum = 0;

    //Checks if the sudoku was too hard to solve
    while (SudokuRow <= 8) {
        if (sudoku [0][SudokuRow][SudokuColum] == 0) {
            printf("Sudoku is too hard. Cannot solve.\n");
            system("pause");
            return 0;
        }
        SudokuColum++;
        if (SudokuColum >= 9) {
            SudokuColum = 0;
            SudokuRow++;
        }
    }

    SudokuRow = 0;
    SudokuColum = 0;

    //prints the output in the form of a sudoku
    for (int i = 0; i <= 80; i++) {
        printf(" %d ", sudoku[0][SudokuRow][SudokuColum]);
        SudokuColum++;
        if (SudokuColum == 3 || SudokuColum == 6) {
            printf (" %c ", 186);
        }
        if (SudokuColum >= 9) {
            SudokuColum = 0;
            SudokuRow++;
            printf("\n");

            if (SudokuRow == 3 || SudokuRow == 6) {
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 205, 205, 205,
                    205, 205, 205, 205, 205, 205, 205, 206, 205, 205,
                    205, 205, 205, 205, 205, 205, 205, 205, 205, 206,
                    205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
                printf("\n");
            }
        }
    }

    printf("\n");
    system("pause");

    return 0;
}