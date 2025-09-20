#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


#define MAXCARDS 40
#define SUIT 4


// functions helping
void printLine() {
    cout << "---------------------------------------------" << endl;
}


void skipLines(int n = 3) {
    for (int i = 0; i < n; ++i) cout << endl;
}


bool isValidMove(int prevCard, int newCard) {
    return (prevCard % 10 == newCard % 10) || ((prevCard - 1) / 10 == (newCard - 1) / 10);
}


bool isValidMovePow(int newCard, int suit) {
    return (newCard % 10 == 7) || (suit == (newCard - 1) / 10);
}


bool isExceptionCard(int card) {
    int val = card % 10;
    return (val == 1 || val == 2 || val == 7);
}


void printCardName(int k) {
    const char* suits[] = {"Clubs", "Cups", "Swords", "Coins"};
    int suit = (k - 1) / 10;
    int val = k % 10;
    if (val == 0) val = 10;
    if (val == 8) cout << "The Jack of " << suits[suit] << endl;
    else if (val == 9) cout << "The Horse of " << suits[suit] << endl;
    else if (val == 10) cout << "The King of " << suits[suit] << endl;
    else cout << "The " << val << " of " << suits[suit] << endl;
}


void announceSuit(int suit) {
    const char* suits[] = {"Clubs", "Cups", "Swords", "Coins"};
    cout << "The chosen suit is now: " << suits[suit] << endl;
}


//  cards class
class Cards {
private:
    int** deck;
public:
    Cards() {
        deck = new int*[SUIT];
        for (int i = 0; i < SUIT; ++i) {
            deck[i] = new int[MAXCARDS / SUIT];
            for (int j = 0; j < MAXCARDS / SUIT; ++j) deck[i][j] = i * 10 + j + 1;
        }
    }
    void shuffleDeck() {
        int flat[MAXCARDS], idx = 0;
        for (int i = 0; i < SUIT; ++i)
            for (int j = 0; j < MAXCARDS / SUIT; ++j)
                flat[idx++] = deck[i][j];
        for (int i = MAXCARDS - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(flat[i], flat[j]);
        }
        idx = 0;
        for (int i = 0; i < SUIT; ++i)
            for (int j = 0; j < MAXCARDS / SUIT; ++j)
                deck[i][j] = flat[idx++];
    }
    int drawCard() {
        for (int i = 0; i < SUIT; ++i)
            for (int j = 0; j < MAXCARDS / SUIT; ++j)
                if (deck[i][j] != 0) {
                    int card = deck[i][j];
                    deck[i][j] = 0;
                    return card;
                }
        return -1;
    }
    ~Cards() {
        for (int i = 0; i < SUIT; ++i) delete[] deck[i];
        delete[] deck;
    }
};


// player class
class Player {
public:
    string name;
    int* hand;
    int handSize;
    Player() { hand = new int[MAXCARDS]; handSize = 0; }
    void draw(Cards* deck) {
        int card = deck->drawCard(); if (card != -1) hand[handSize++] = card;
    }
    void showHand() {
        for (int i = 0; i < handSize; ++i) {
            cout << (i + 1) << ") ";
            printCardName(hand[i]);
        }
    }
    bool hasPlayableCard(int prev, int suit) {
        for (int i = 0; i < handSize; ++i)
            if ((suit == -1 && isValidMove(prev, hand[i])) || (suit != -1 && isValidMovePow(hand[i], suit)))
                return true;
        return false;
    }
    int playCard(int prev, int suit) {
        int choice;
        while (true) {
            cout << "Choose card to play: "; cin >> choice;
            if (choice >= 1 && choice <= handSize) {
                int c = hand[choice - 1];
                if ((suit == -1 && isValidMove(prev, c)) || (suit != -1 && isValidMovePow(c, suit))) {
                    for (int i = choice - 1; i < handSize - 1; ++i)
                        hand[i] = hand[i + 1];
                    handSize--;
                    return c;
                }
            }
            cout << "Invalid move! Try again." << endl;
        }
    }
    ~Player() { delete[] hand; }
};


// game class
class Game {
private:
    Player* players;
    int numPlayers;
    Cards* deck;
    int topCard;
    int suitChange;
    int skipCount;
    int drawTwoCount;
public:
    Game(int n) {
        numPlayers = n;
        players = new Player[n];
        deck = new Cards();
        suitChange = -1;
        skipCount = 0;
        drawTwoCount = 0;
    }
    void start() {
        deck->shuffleDeck();
        for (int i = 0; i < numPlayers; ++i) {
            cout << "Player " << i+1 << " name: "; cin >> players[i].name;
            for (int j = 0; j < 5; ++j) players[i].draw(deck);
        }
        do { topCard = deck->drawCard(); } while (isExceptionCard(topCard));
        cout << "Start card: "; printCardName(topCard);
        int turn = 0;
        while (true) {
            Player& p = players[turn];
            skipLines(); printLine();
            if (skipCount > 0) {
                cout << p.name << " is skipped!" << endl;
                skipCount--;
                suitChange = -1;
            } else {
                cout << p.name << "'s turn. Top: "; printCardName(topCard);
                p.showHand();
                if (drawTwoCount > 0) {
                    cout << "Draw " << drawTwoCount << " cards" << endl;
                    for (int i = 0; i < drawTwoCount; ++i) p.draw(deck);
                    drawTwoCount = 0;
                } else if (!p.hasPlayableCard(topCard, suitChange)) {
                    cout << "No playable cards. Drawing..." << endl;
                    p.draw(deck);
                } else {
                    int played = p.playCard(topCard, suitChange);
                    topCard = played;
                    int val = played % 10;
                    if (val == 1) { skipCount++; suitChange = -1; }
                    else if (val == 2) { drawTwoCount += 2; suitChange = -1; }
                    else if (val == 7) {
                        cout << "You played a 7! Choose a suit:" << endl;
                        cout << "0) Clubs" << endl;
                        cout << "1) Cups" << endl;
                        cout << "2) Swords" << endl;
                        cout << "3) Coins" << endl;
                        cin >> suitChange;
                        announceSuit(suitChange);
                    } else {
                        suitChange = -1;
                    }
                    if (p.handSize == 0) { cout << p.name << " wins!" << endl; break; }
                }
            }
            turn = (turn + 1) % numPlayers;
        }
    }
    ~Game() { delete[] players; delete deck; }
};


// main menu help option
void showHelp() {
    cout << "\nHELP:\n";
    cout << "Match number or suit.\n";
    cout << "7: Wildcard (choose suit)\n";
    cout << "1: Skip next\n";
    cout << "2: Draw two (stackable)\n";
    cout << "Empty hand wins.\n\n";
}


int main() {
    srand(time(0));
    while (true) {
        cout << "MENU\n1) Play\n2) Help\n3) Exit\n";
        int ch; cin >> ch;
        if (ch == 1) {
            int pc; cout << "Players(2-4): "; cin >> pc;
            Game g(pc); g.start();
        } else if (ch == 2) showHelp();
        else if (ch == 3) break;
        else cout << "Invalid" << endl;
    }
    return 0;
}






