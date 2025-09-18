#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int print_Menu() {
    int selection;
    cout << "1) Play" << endl;
    cout << "2) Help" << endl;
    cout << "3) Exit" << endl;
    cout << "Please make a selection (1-3): ";
    cin >> selection;
    return selection;
}
void play_RPS(int player[], int computer[], int size) {
    // Array to turn options (1, 2, 3) to "Rock", "Paper", "Scissors"
    string Plays[3] = {"Rock", "Paper", "Scissors"};
    for (int i = 0; i < size; i++) {
        while (true) {
            cout << "Round " << i + 1 << ". Please select among 1) Rock, 2) Paper, or 3) Scissors: ";
            cin >> player[i];
            // Input validation
            if (player[i] < 1 || player[i] > 3) {
                cout << "This is an Invalid input! Please enter one of the following: 1, 2, or 3." << endl;
                continue; // Start over after skipping the rest of the loop.
            }
            computer[i] = rand() % 3 + 1; //to generate the computer's choice (1, 2, or 3) in a random way
            // Use the Plays array to show the moves taken by the computer and the user.
            cout << "You: " << Plays[player[i] - 1] << " Computer: " << Plays[computer[i] - 1] << endl; // array indices start at 0, but the user's options start at 1. so we decrement
            if (player[i] == computer[i]) {
                cout << "Tie! Please select again." << endl;
            } else {
                break;
            }
        }
    }
}
void print_Summary(int player[], int computer[], int size) {
    // Array to turn options (1, 2, 3) to "Rock", "Paper", "Scissors"
    string Plays[3] = {"Rock", "Paper", "Scissors"};
    int victory_count = 0;
    int loss_count = 0;
    for (int i = 0; i < size; i++) {
        // Find out the round's result
        if (player[i] == computer[i]) {
            // Ties do not count as wins or losses.
        } else if ((player[i] == 1 && computer[i] == 3) ||  // Rock beats Scissors
                   (player[i] == 2 && computer[i] == 1) ||  // Paper beats Rock
                   (player[i] == 3 && computer[i] == 2)) {  // Scissors beats Paper
            victory_count++; // user wins
        } else {
            loss_count++; // user loses
        }
    }
    // Printing the summary tabular at the end
    cout << "| Round | You | Computer | Result |" << endl;
    for (int i = 0; i < size; i++) {
        string result;
        if (player[i] == computer[i]) {
            result = "Tie";
        } else if ((player[i] == 1 && computer[i] == 3) ||  // Rock beats Scissors
                   (player[i] == 2 && computer[i] == 1) ||  // Paper beats Rock
                   (player[i] == 3 && computer[i] == 2)) {  // Scissors beats Paper
            result = "Win";
        } else {
            result = "Lose";
        }
        cout << "| " << i + 1 << " | " << Plays[player[i] - 1] << " | " << Plays[computer[i] - 1] << " | " << result << " |" << endl;
    }
    // displaying the last result
    if (victory_count > loss_count) {
        cout << "You win! (win: " << victory_count << ", lose: " << loss_count << ")" << endl;
    } else if (victory_count < loss_count) {
        cout << "You lose! (win: " << victory_count << ", lose: " << loss_count << ")" << endl;
    } else {
        cout << "It's a tie! (win: " << victory_count << ", lose: " << loss_count << ")" << endl;
    }
}
int main() {
    srand(time(0)); // Initialise the random number generator.
    int player[5];
    int computer[5];
    while (true) {
        int selection = print_Menu();
        if (selection == 1) {
            play_RPS(player, computer, 5);
            print_Summary(player, computer, 5);
        } else if (selection == 2) {
            cout << " This is a Rock Paper Scissors game against a computer. You will play 5 rounds then see the results." << endl;
        } else if (selection == 3) {
            cout << "Exiting the game ..." << endl;
            break;
        } else {
            cout << "Invalid input. Please retry." << endl;
        }
    }
    return 0;
}



