#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

void endGame(int &w/*Win condition*/, int &m/*Player's money*/, int &b/*Bet*/)   // Some money should be involved
{
    switch (w)
    {
    case 1:
        cout << "You win!\n";
        m+=b*2;
        break;
    case 2:
        cout << "You lose.\n";
        break;
    case 3:
        cout << "Draw.\n";
        m+=b;
        break;
    default:
        cout << "ERROR!!!\n";
        m+=b;
    }
    _sleep(2000);
    system ("cls");
}

void pullingCard(int &x/*Score*/, int (&y)[52]/*Deck*/)
{
    int a;
    while (true) {
        a=rand()%51;    // "Pulling" card from the deck and adding a score afterwards
        if (y[a]!=0)
        {
            if (y[a]==11)   // In case this is Ace
            {
                if (x<=10){x += y[a];}
                else {x+=1;}
            }
            else {x += y[a];}
            y[a]=0;     // Card is "pulled"
            break;
        }
    }
}

void startGame(int &x/*Score*/, int &x1/*Opponent score*/, int (&y)[52]/*Deck*/, int &w/*Win condition*/)
{
    cout << "Starting a game...\n";

    for (int a=1; a<=2; a++)
    {
        pullingCard(x,y);   // Player's starting hand
    }
    for (int a=1; a<=2; a++)
    {
        pullingCard(x1,y);  // Opponent's starting hand
    }
    if (x==21 && x1==21)
    {
        _sleep(1500);
        system ("cls");
        cout << "Both players got blackjack. ";
        _sleep(1200);
        w = 3;
        _sleep(2000);       // There must be logic to start next round. Same with other if cases.
    }
    else if (x==21)
    {
        _sleep(1500);
        system ("cls");
        cout << "Player got blackjack. ";
        _sleep(1200);
        w = 1;
        _sleep(2000);
    }
    else if (x1==21)
    {
        _sleep(1500);
        system ("cls");
        cout << "Opponent got blackjack. ";
        _sleep(1200);
        w = 2;
        _sleep(2000);
    }
    _sleep(1500);
}

void midGame(int &x/*Score*/, int (&y)[52]/*Deck*/, int a/*Choice*/, int &w/*Win condition*/)
{
    switch (a)
        {
    case 1:
        cout << "Pulling card...\n";
        _sleep(1500);
        pullingCard(x,y);
        a = 0;
        break;
    case 2:
        cout << "Passing...\n";
        _sleep(1500);
        a = 0;
        break;
    default:
        cout << "Wrong input. Try again.\n";
        _sleep(1500);
        a = 0;
        break;
        }
    system ("cls");
}

void CPU(int &x/*Score*/, int &x1/*Opponent score*/ , int (&y)[52]/*Deck*/, int &w/*Win condition*/)
{
    int a;
    while (true) {
    if (x1<=x && x1!=21) {
        a = 1;
        midGame(x1, y, a, w);
        if (x1>21) {
                cout << "Opponent got more than 21. ";
                w=1;
                break;}
        }
    else {
            a = 2;
            midGame(x1, y, a, w);
            break;
        }
    }
}

void shuffle(int x[52], int (&y)[52], int &a, int &b)
{
    for (int a=0; a<52; a++)
    {
        y[a]=x[a];
    }
    a = 0;
    b = 0;
}

int main()
{
    srand(time(0));

    int cardsMain[52]={2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11};    //yes
    int cards[52]={2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11};    // Use this deck for play, cardsMain is for shuffling
    int scorePlayer=0;
    int scoreOppnt=0;
    int money = 100;
    int bet = 0;
    int choice=0;
    int winCond=0;  // 0 - nothing happened, 1 - player won, 2 - opponent won, 3 - draw.

    cout << "Welcome to Blackjack\n\n" << "Press any key to continue...";
    _getch();
    system ("cls");

    while (money>0) {      // Main process
        while (winCond==0) {        // Game in process. Player's turn.
            while (true) {
            cout << "Place your bet             Your money: " << money << endl;
            cout << ">> ";
            cin>>bet;       // Need insufficient money logic
            if (bet>money) {cout << "Insufficient money"; _sleep(1200); bet = 0; system("cls");}
            else if (bet<1) {bet=1; money-=bet; break;}
            else {money-=bet; break;}
            }
            system ("cls");
            startGame(scorePlayer, scoreOppnt, cards, winCond);
            if (winCond!=0) {break;}
            while (choice!=2) {
                cout << "Your turn\n";
                cout << "Score: " << scorePlayer << "       Money: " << money << "  Bet: " << bet << endl;
                cout << "1. Hit         2. Pass\n";
                cout << ">> ";
                cin>>choice;
                midGame(scorePlayer, cards, choice, winCond);
                if (scorePlayer>21) {
                        cout << "More than 21. ";
                        winCond=2;
                        break;
                }
                if (choice==2) {break;}
            }
            if (winCond==2) {break;}    // Now this is AI's turn
            cout << "Opponent's turn.\n";
            CPU(scorePlayer, scoreOppnt, cards, winCond);
            break;
        }
        if (scorePlayer==scoreOppnt) {winCond=3;}
        else if (scoreOppnt>scorePlayer && scoreOppnt<=21) {winCond=2;}
        endGame(winCond, money, bet);
        shuffle(cardsMain, cards, scorePlayer, scoreOppnt);
        winCond = 0;
        choice = 0;
    }

    cout << "You have ran out of money.\n";
    _sleep(2000);
    cout << "Game over.\n";
    _sleep(2000);

    return 0;
}
