/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Radoslav Dimitrov
* @idnumber 4MI0600351
* @compiler VC
*
* code
*
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int ROWS = 10;
const int COLS = 8;

int score = 0;


bool userIdentification()
{
    fstream db;
    ofstream dbInput;
    string username, password, score;
    char choice;
    bool userExists = false;
    bool isReadyForGame = 0;

    cout << "Welcome! \n";
    while (true) 
    {															//loop to re-open the menu after every try
        cout << "===========================================\nTo REGISTER press 1\nTo LOG IN press 2\nTo EXIT press e\nYour choice: ";
        cin >> choice;

        if (choice == '1')
        {													//registration
            cout << "===========================================\nRegistration\nUsername: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            db.open("Database.txt");										//opening a read-only connection to file
            dbInput.open("Database.txt", ios::app);							//opening a write connection to file
            if (db.is_open()) 
            {												//if the connection works execute the code below
                string line;
                while (getline(db, line)) 
                {									//check every line of the file for the registered user
                    string usernameInFile;
                    for (int i = 0; i < line.length(); i++)					//get only the username from line in the file
                    {
                        if (line[i] == ' ') break;
                        usernameInFile += line[i];
                    }
                    if (username == usernameInFile) {						//check if a username in in the file is equal to entered username. This way a username cannot be used more than once					userExists = true;
                        userExists = true;
                        break;
                    }
                }
                if (userExists) 
                {											//if the user exists go back
                    cout << "User with that name already exists! Try to log in!\n";
                    continue;
                }
                else if (!userExists) 
                {										// if user doen's exist create one and close connections
                    string newUser = username + " - " + password + " - " + "0";
                    dbInput << newUser << endl;
                    cout << "Successful registration!\n";
                    dbInput.close();
                    db.close();
                    continue;
                }
            }
            else 
            {
                cout << "Database did not open! Exit the program!\n";
                break;
            }
        }
        else if (choice == '2') 
        {												//login
            cout << "===========================================\nPlease, enter username and password\nUsername: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            db.open("Database.txt");
            dbInput.open("Database.txt", ios::app);
            if (db.is_open()) 
            {
                string line;
                string usernameInFile;
                while (getline(db, line)) 
                {									//check if there is an existing user with entered name and password
                    int count = 0;

                    for (int i = 0; i < line.length(); i++)					//get only the username from line in the file
                    {
                        if (line[i] == ' ')
                        {
                            count++;
                        }


                        if (count >= 3 && line[i] != ' ' && line[i] != '-')
                        {
                            score += line[i];
                        }

                        usernameInFile += line[i];
                    }

                    if (usernameInFile == (username + " - " + password + " - " + score)) {
                        userExists = true;
                        break;
                    }

                    score = "";
                    usernameInFile = "";
                }
                if (userExists) 
                {											//if there is an existing user break the loop and output success
                    system("CLS");
                    cout << "You have loged in successfully!\n";  
                    cout << endl;
                    isReadyForGame = 1;
                    //return isReadyForGame;
                    break;
                }
                else if (!userExists) 
                {										//if there isn't return to menu
                    cout << "Wrong username or password! Try registering!\n";
                    score = "";
                    usernameInFile = "";
                    dbInput.close();
                    db.close();
                    continue;
                }
            }
        }

        else if (choice == 'e')
        {
            isReadyForGame = 0;
            //return isReadyForGame;
            break;
        }

        else 
        {																//if user's input is wrong
            cout << "Please enter 1 or 2!\n";
            cin >> choice;
            continue;
        }
    }
    if (isReadyForGame)
    {
        return 1;
    }
    return 0;
}

void initMatrix(char matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            matrix[i][j] = '*';
        }
    }
}

int random(int lowest, int highest) 
{
    return(lowest + rand() % (highest + 1));
}

int randomChar()
{
    return('a' + rand() % 26);
}

void swap(char& a, char& b)
{
    char temp = a;
    a = b;
    b = temp;
}

void printMatrix(char matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

bool inputValidation(int startOfBrick, int newDestination , int row)
{
    bool result = 1;

    if (startOfBrick < 0 || startOfBrick > 7 || newDestination < 0 || newDestination >7 || row < 0 || row > 9) return !result;

    return result;
}

bool isEmpty(char matrix[][COLS], int row)
{
    for (int i = 0; i < COLS; i++)
    {
        if (matrix[row][i] != '*')
        {
            return 0;
        }
    }
    return 1;
}

bool isFull(char matrix[][COLS], int row)
{
    for (int i = 0; i < COLS; i++)
    {
        if (matrix[row][i] == '*')
        {
            return 0;
        }
    }
    return 1;
}

void pushAllRows(char matrix[ROWS][COLS])
{
    for (int i = 1; i < ROWS; i++)
    {
        if (isEmpty(matrix, i))
        {
            continue;
        }

        for (int j = 0; j < COLS; j++)
        {
            matrix[i - 1][j] = matrix[i][j];
        }
    }
}

void nullRow(char matrix[ROWS][COLS], int row)
{
    for (int i = 0; i < COLS; i++)
    {
        matrix[row][i] = '*';
    }
}

void dropAllRows(char matrix[ROWS][COLS])
{
    int emptyRow = 0;

    bool isChangeMade = 0;

    for (int i = ROWS - 1; i > 0; i--)
    {
        if (isEmpty(matrix, i) && !(isEmpty(matrix, i - 1)))
        {
            emptyRow = i;
            isChangeMade = 1;
            break;
        }      
    }

    for (int i = emptyRow - 1; i > 0; i--)
    {
        for (int j = 0; j < COLS; j++)
        {
            matrix[i + 1][j] = matrix[i][j];
        }
        nullRow(matrix, i);
    }         

    if (isChangeMade)
    {       
        dropAllRows(matrix);
    }
}

bool checkForDefeat(char matrix[ROWS][COLS])
{
    if (!isEmpty(matrix, 0))
    {
        cout << endl;
        printMatrix(matrix);
        cout << "Defeat" << endl;            
        return 0;
    }
    return 1;
}

int lenghtBrick(char matrix[ROWS][COLS], int startOfBrick, int row)
{
    int count = 1;

    for (int i = startOfBrick + 1; i < COLS; i++)
    {
        if (matrix[row][i] == matrix[row][startOfBrick] + ('a' - 'A'))
        {
            count++;
        }
        else break;
    }

    return count;
}

bool checkIfStartOfBrick(char matrix[ROWS][COLS], int row, int startOfBrick)
{
    if (matrix[row][startOfBrick] >= 'A' && matrix[row][startOfBrick] <= 'Z')
    {
        return 1;
    }
    return 0;
}

bool checkIfLegalNewDestination(char matrix[ROWS][COLS], int row, int startOfBrick, int lenghtOfBrick, int newDestination)
{
    bool result = 1;

    if (startOfBrick == newDestination) return !result;

    if (startOfBrick < newDestination)
    {
        if ((COLS - lenghtOfBrick) < newDestination) return !result;

        return result;
    }

    else
    {
        if (newDestination < (COLS - COLS)) return !result;

        return result;
    }
}

bool chechIfPossibleMove(char matrix[ROWS][COLS], int row, int lenghtOfBrick, int startOfBrick, int newDestination)
{
    bool result = 1;

    if (startOfBrick < newDestination)
    {
        for (int i = startOfBrick + lenghtOfBrick; i < newDestination + lenghtOfBrick; i++)
        {
            if (matrix[row][i] == '*')
            {
                continue;
            }
            result = 0;
        }
    }

    else
    {
        for (int i = startOfBrick - 1; i >= newDestination ; i--)
        {
            if (matrix[row][i] == '*')
            {
                continue;
            }
            result = 0;
        }
    }

    return result;
}

void moveBrick(char matrix[ROWS][COLS], int row, int startOfBrick, int newDestination, int lenghtOfBrick)
{
    int endOfBrick = startOfBrick + lenghtOfBrick - 1;

    if (startOfBrick < newDestination)
    {       
        int destinationOfEndBrick = newDestination + lenghtOfBrick - 1;

        for (int i = endOfBrick; i >= startOfBrick; i--)
        {
            for (int j = i; j < destinationOfEndBrick; j++)
            {
                swap(matrix[row][j], matrix[row][j + 1]);
            }
            destinationOfEndBrick--;
        }
    }

    else if (startOfBrick > newDestination)
    {
        int destinationOfStartBrick = newDestination;

        for (int i = startOfBrick; i <= endOfBrick; i++)
        {
            for (int j = i; j > destinationOfStartBrick; j--)
            {
                swap(matrix[row][j], matrix[row][j - 1]);
            }
            destinationOfStartBrick++;
        }
    }
}

void playerMove(char matrix[ROWS][COLS])
{
    cout << "Enter row (9 - 0 starting from the bottom)\nEnter start of a brick (0 - 7 left to right)\nEnter desired new position" << endl;
    int row = 0;
    int startOfBrick = 0;
    int newDestination = 0;
    

    int lenghtOfBrick = 0;
    bool correctInput = 0;

    do
    {      
        cin >> row >> startOfBrick >> newDestination;
        cout << endl;

        if (!inputValidation(startOfBrick, newDestination, row))
        {
            cout << "Incorrect input. Try again." << endl;            
            continue;
        }

        if (!checkIfStartOfBrick(matrix, row, startOfBrick))
        {
            cout << "Not a brick. Try again." << endl;
            continue;
        }   

        lenghtOfBrick = lenghtBrick(matrix, startOfBrick, row);

        if (!checkIfLegalNewDestination(matrix, row, startOfBrick, lenghtOfBrick, newDestination))
        {
            cout << "Not a valid move. Try again." << endl;
            continue;
        }

        if (!chechIfPossibleMove(matrix, row, lenghtOfBrick, startOfBrick, newDestination))
        {
            cout << "Impossible move. Try again." << endl;
            continue;
        }

        correctInput = 1;
    } while (!correctInput);

    moveBrick(matrix, row, startOfBrick, newDestination, lenghtOfBrick);
}

void addRandomRowLast(char matrix[ROWS][COLS])
{
    int countOfElems = 0; //Elements to be added to the row

    while (countOfElems < COLS)
    {
        int elementSize = random(1,3);

        while (elementSize + countOfElems > COLS)
        {
            elementSize = random(1, 3);
        }

        bool isElementBrick = random(0, 3);

        if (isElementBrick == 0) //elementsize
        {
            int element = elementSize;
            countOfElems += element;
        }

        else
        {
            char color = randomChar();

            for (int i = 0; i < elementSize; i++)
            {
                matrix[ROWS - 1][countOfElems + i] = color ;
            }
            matrix[ROWS-1][countOfElems] -= ('a' - 'A');

            countOfElems += elementSize;                      
        }
    }
    if (isEmpty(matrix,9)) addRandomRowLast(matrix);  

    if (isFull(matrix, 9))
    {
        nullRow(matrix, 9);
        addRandomRowLast(matrix);
    }
}

void rowDestruction(char matrix[ROWS][COLS], int row)
{
    for (int i = 0; i < COLS; i++)
    {
        matrix[row][i] = '*';
    }
}

void fullRowDestruction(char matrix[ROWS][COLS])
{
    for (int i = ROWS - 1; i > 0; i--)
    {
        if (isFull(matrix, i))
        {
            ::score += 10;
            rowDestruction(matrix, i);
        }
    }
}

void bricksFall(char matrix[ROWS][COLS])
{
    bool returnData = 0;
    bool isChangeMade = 0;
    for (int i = 0; i < ROWS-1; i++)
    {
        if (isEmpty(matrix, i)) continue;
        
        for (int j = 0; j < COLS; j++)
        {
            if (checkIfStartOfBrick(matrix, i, j))
            {
                int lenghtOfBrick = lenghtBrick(matrix, j, i);
                bool result = 1;
                for (int k = 0; k < lenghtOfBrick; k++)
                {
                    if (matrix[i + 1][(j+k)] != '*')
                    {
                        result = 0;
                    }
                }

                if (result)
                {
                    for (int m = 0; m < lenghtOfBrick; m++)
                    {
                        swap(matrix[i + 1][j+m], matrix[i][(j+m)]);
                    }
                    j += lenghtOfBrick - 1;
                    isChangeMade = 1;

                }
            }
        }
    }
    if (isChangeMade) bricksFall(matrix);
}

void standartGameLoop(char matrix[ROWS][COLS])
{
    fullRowDestruction(matrix);

   // dropAllRows(matrix);

    bricksFall(matrix);
}

void BricksDrop(char matrix[ROWS][COLS])
{
    initMatrix(matrix);

    while (checkForDefeat(matrix))
    {
        system("CLS");
        addRandomRowLast(matrix);
        printMatrix(matrix);

        system("CLS");
        bricksFall(matrix);
        printMatrix(matrix);

        system("CLS");
        standartGameLoop(matrix);

        printMatrix(matrix);
        cout << endl;
        cout << ::score << endl;
        cout << endl;

        playerMove(matrix);        
        system("CLS");
        printMatrix(matrix);


        bricksFall(matrix);    
        system("CLS");
        printMatrix(matrix);

        standartGameLoop(matrix);
        system("CLS");
        printMatrix(matrix);

        pushAllRows(matrix);

        nullRow(matrix, 9);
        system("CLS");
        printMatrix(matrix);
    }
}

int main()
{
    char matrix[10][8] = {};
    srand(time(0));
    if (userIdentification())BricksDrop(matrix);
    
   
    return 0;
}

