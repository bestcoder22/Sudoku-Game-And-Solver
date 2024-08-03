#include <stdio.h>
#include <stdlib.h>

int column_check1(int row, int col, char temporary[9][9], int number_to_be_tested)
{ /*
This function keeps record of all the filled char in the present column in the form of count_array.
For example, if 4 is present in whatever row but the same concerned column then,
the array value corresponding to index equal to that character face value stored is [1] and otherwise [0].
*/
    int count_array[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        count_array[i] = 0;
    }
    for (int i = 0; i < 9; i++)
    {
        if (temporary[i][col] != '.')
        {
            count_array[temporary[i][col] - '0'] = 1;
        }
    }

    /*
    It further tests a input number on the basis of the data of already present elements.
    If the input number turns out to be unique and never used before in the concerned column then,
    the function returns [1] for such input values otherwise it returns [0].
    */

    if (count_array[number_to_be_tested] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int row_check1(int row, int col, char temporary[9][9], int number_to_be_tested)
{
    /*
    This function keeps record of all the filled char in the present row in the form of count_array.
    For example, if 4 is present in whatever column but the same concerned row then,
    the array value corresponding to index equal to that character face value stored is [1] and otherwise [0].
    */
    int count_array[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        count_array[i] = 0;
    }
    for (int i = 0; i < 9; i++)
    {
        if (temporary[row][i] != '.')
        {
            count_array[temporary[row][i] - '0'] = 1;
        }
    }
    /*
    It further tests a input number on the basis of the data of already present elements.
    If the input number turns out to be unique and never used before in the concerned row then,
    the function returns [1] for such input values otherwise it returns [0].
    */
    if (count_array[number_to_be_tested] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int box_check1(int row, int col, char temporary[9][9], int number_to_be_tested)
{
    /*
    This function keeps record of all the filled char in the present square in the form of count_array.
    For example, if 4 is present in whatever row or column but the same concerned box/square then,
    the array value corresponding to index equal to that character face value stored is [1] and otherwise [0].
    */
    int count_array[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        count_array[i] = 0;
    }
    /*
    how  we identify in which square/box our decider function is resting on.
    if we have our current position such that, row=row and column=col then,
    the given (row,col) coordinate lies  in square/box defined by boundary points:-
    upper left=(a,b);
    lower right=(a+2,b+2);
    where a and b are defined as follows:-
    a = (row / 3) * 3;
    b = (col / 3) * 3;
    */
    int a = (row / 3) * 3;
    int b = (col / 3) * 3;
    for (int i = a; i < a + 3; i++)
    {
        for (int j = b; j < b + 3; j++)
        {
            if (temporary[i][j] != '.')
            {
                count_array[temporary[i][j] - '0'] = 1;
            }
        }
    }
    /*
    It further tests a input number on the basis of the data of already present elements.
    If the input number turns out to be unique and never used before in the concerned column then,
    the function returns [1] for such input values otherwise it returns [0].
    */
    if (count_array[number_to_be_tested] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void decider1(int row, int col, char temporary[9][9], char board[9][9], int *solved)
{
    // This is our main controlling unit of our code
    if (*solved == 1)
    {
        return;
    }
    if (row > 8) // It means we haqve filled all our enteries.
    {
        // Copy to Board
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = temporary[i][j];
            }
        }
        *solved = 1; // Update solved value to 1, because we have obtained the answer atleast 1 time.
        return;
    }

    if (temporary[row][col] != '.')
    {
        decider1(row, col + 1, temporary, board, solved); // No work to be done...move the index to next position.
        return;
    }

    if (col > 8) // Exeeding the boundary conditions, needs repositioning.
    {
        decider1(row + 1, 0, temporary, board, solved); // Repositioning
        return;
    }

    if (temporary[row][col] == '.') // Now the real part starts.
    {

        for (int z = 1; z <= 9; z++) // Heat and Trial...start by 1 till the value(z) reaches 9.Try all possibility.
        {

            if (column_check1(row, col, temporary, z) == 1 && row_check1(row, col, temporary, z) == 1 && box_check1(row, col, temporary, z) == 1)
            // after going through the conditions not all qualify...only few possibilites remaining.
            {
                // we start by least possible value...
                temporary[row][col] = (char)(z + (int)('0'));    // Allocation
                decider1(row, col + 1, temporary, board, solved); // Move on to next position
                temporary[row][col] = '.';                       // Reassigning the index with unnfilled mark
            }                                                    // trying other possibilities.
        }
        if (temporary[row][col] == '.')
        {
            return;
            // if no possibilitie remains then, we would be going to previous indices to make changes so that atleast one possibility remains for this index.
        }
    }
}

void solveSudoku1(char board[9][9])
{
    /*
    we are initialising one more 2D char array named temporary
    this will keep track of our progress and at last copy its all filled positions to Board.
    */
    char temporary[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            temporary[i][j] = board[i][j];
        }
    }
    int solved = 0;                           // This is our boolean sort of int which indicates wheather we have reacher atleast 1 answer or not.
    decider1(0, 0, temporary, board, &solved); // solved is passed by reference, we need it not change its value during backtracking.
}

void display1(char user_board[9][9])
{

    printf("\n");
    for (int i = 0; i < 9; i++)
    {

        for (int j = 0; j < 9; j++)
        {

            printf("%c ", user_board[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    /*
    Board is the final answer ttoo unfilled sudoku.
    it is a 2D array storing the input characters
    numerical char for filled positions and '.' for unfilled positions
    */
    printf("\nWelcome to unique-solution-sudoku solver\n\n\n");
    char board[9][9];
    // This is the input which we give and which gets updated to solution board.
    char user_board[9][9];
    // This is a board identitical to board's initial condition.
    // This board gets updated in real time according to user's response.
    printf("Please input the VALID incomplete SUDOKU: \n\n");
    printf("NOTE : Use '.' in place of empty space.\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char x;
            scanf(" %c", &x);
            board[i][j] = x;
            user_board[i][j] = x;
        }
    }
    // input  of board complete
    solveSudoku1(board);
    // board  get solved and  board  is now the solution to initial problem
    printf("\n\n\n\n\n");
    int win = 1;
    // This is for checking if the  player wins or not.
    int errors = 0;
    // This  keep track of errors encountered
    int hints = 0;
    // This  keeps record of hints taken
    int quits = 0;
    // This is for checking if the  palyer has quit or not.
    int counter = 0;
    // This keep track of  the blank spases filled till time.
    int morehints = 0;
    // This  keep track of unnecessary attepts for hints despite having none left.
    int total = 81;
    // Total blocks.
    int temp_counter = 0;
    // This keep track of errors and hints updation.

    // counting  of blank spaces.
    for (int m = 0; m < 9; m++)
    {

        for (int n = 0; n < 9; n++)
        {

            if (user_board[m][n] != '.')
            {

                total--;
            }
        }
    }

    while (total)
    {
        counter++;

        display1(user_board);
        // Display the  user_board so as to keep track of all thing done  till now.
        printf("\n\nEnter the cordinates :\n\n");
        int m, n;
        // providing the  user with the freedom of  choosing the  cordinates to work on.
        printf("Enter the row-cordinates :\n\n");
        scanf("%d", &m);
        printf("Enter the coluumn-cordinates :\n\n");
        scanf("%d", &n);
        // checking for valid cordinates
        if (user_board[m - 1][n - 1] != '.')
        {
            printf("** Please input valid cordinates ( The space is already occupied! ) ***** \n");
            counter--;
            continue;
        }
        // input of  answer  to choosen block
        printf("\n [ %d. ] Enter the entry at %dth row and %dth column :  \n\n*[ *ERRORS: %d(max. 3)*   *HINTS LEFT:%d(max.3)*   * QUIT(Q) *   * HINT(H) *]*\n", counter, m, n, errors, 3 - hints);

        char v;
        scanf(" %c", &v);
        // This v stores  the  user's response
        // which will be then categorised into below given possibilities.

        // This one is for invalid response
        if (((int)v < (int)'1' || (int)v > (int)'9') && v != 'Q' && v != 'H')
        {
            printf("\n* INVALID INPUT **\n** TRY AGAIN ****\n");

            counter--;
            continue;
        }
        // This one is for  QUIT
        if (v == 'Q')
        {

            win = 0;
            break;
        }
        // This one is for HINT.
        if (v == 'H')
        {

            hints++;
            // Checking the limits of hints
            if (hints > 3)
            {
                printf("\n** NO MORE HINTS ****\n");
                morehints++;
                // Checking the limits  of morehints i.e unecessary attempts.
                if (morehints > 3)
                {

                    win = 0;
                    break;
                }

                counter--;
                continue;
            }
            // Extracting the right answer from the board.
            printf("\nThe required element is : ['%c']", board[m - 1][n - 1]);

            counter--;
            continue;
        }
        // Checking for the right  or wrong response.
        if (v != board[m - 1][n - 1])
        {
            // if not  correct, increase the error by one.
            errors++;
            // Checking the limits of Errors
            if (errors == 4)
            {

                win = 0;
                break;
            }

            printf("\n** ERROR **\n* TRY AGAIN! ***\n");

            counter--;
            continue;
        }
        // If all correct then finally the user's board get updated.
        user_board[m - 1][n - 1] = v;
        total--;
        temp_counter++; // increase the temp_counter only after final updation,
        // Reupdation of Errors and Hints(also morehints) after successfully answering 9 voids. [BONUS].
        if (temp_counter == 9)
        {
            errors = 0;
            hints = 0;
            morehints = 0;
            temp_counter = 0;
        }
    }
    // checcking if the player has  won or not
    if (win == 0)
    {
        printf("\n**** GAME OVER! ******\n");
        printf("\n SOLUTION to the above given SUDOKU is given below: \n");
        // Printing the Board
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                printf("%c ", board[i][j]); // Solution
            }
            printf("\n");
        }
        printf("\n**** HOPE TO SEE YOU AGAIN *******\n");
    }
    else
    {

        printf("\n** CONGRATULATIONS! YOU HAVE SUCCESSFULLY COMPLETED THE  GAME *******\n"); // Complete.
    }
}
//***************END*****************//
// various inputs;


// 7 . 8 6 . 4 . 2 1
// . . . . 8 7 6 . .
// 4 6 . . 2 . . 8 .
// 9 2 1 8 . . 5 . 3
// . . 4 . 1 . . 7 .
// 6 8 . 5 4 3 2 . .
// . 4 . . 9 . . 6 5
// . 1 . . 6 . . . 2
// 5 . 6 4 3 . 1 9 8



// 8 . 2 . . 1 . 6 3
// . 6 . 8 . 2 . 7 .
// . 4 1 6 . . 8 . 2
// . . . 1 7 . . . .
// . 7 . 9 6 . 2 8 5
// . 9 . 2 . . . . .
// . . 9 . . 8 . 4 .
// 4 1 . 3 9 . . . 8
// . . . . . . . 3 .



// . . 3 . . 4 . . .
// . . . . . 3 . . 7
// 4 . . . . 2 . 9 6
// . . . . . . 7 . .
// . . 6 . . . 8 5 .
// 7 . 4 . . . . 3 .
// 1 . . . . 8 . 6 .
// 2 5 . 6 . . . . .
// . . . . 4 . . . 5

// . . . . 9 . . 7 8
// . . . . 5 2 3 4 .
// . . . 3 . . 5 9 .
// 6 . . . . . . 8 9
// . . . 5 . 6 . . .
// 1 8 . . . . . . 7
// . 6 9 . . 5 . . .
// . 2 8 7 6 . . . . 
// 7 5 . . 2 . . . . 