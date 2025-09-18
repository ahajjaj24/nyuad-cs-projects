#include <iostream>
#include <cmath>
using namespace std;
int main() {
     // Set the beam parameters to their initial default values.
    double x = 2.5, L = 5, P = 20000, a = 3, E = 30e6, I = 0.0256;
    int option;
    // Main menu loop
    while (true) {
     // main option menu
        cout << "Main Menu:\n";
        cout << "1) Calculate the beam deflection\n";
        cout << "2) Help\n";
        cout << "3) Exit\n";
        cout << "Enter option: ";
        cin >> option;
        // Confirm the main menu selection
        while (option < 1 || option > 3) {
            cout << "This option is invalid! Select 1, 2, or 3 please: ";
            cin >> option;
        }
        if (option == 1) { // menu for input beam parameters
            int sub_option;
            while (true) {
                cout << "Beam Parameters Menu:\n";
                cout << "1) Calculation Point (x) [Current: " << x << " ]\n";
                cout << "2) Length of the Beam  (L) [Current: " << L << " ]\n";
                cout << "3) Load (P) [Current: " << P << " ]\n";
                cout << "4) Location where the load is applied (a) [Current: " << a << " ]\n";
                cout << "5) Young’s Modulus of the beam material (E) [Current: " << E << " ]\n";
                cout << "6) Second Moment of Area (I) [Current: " << I << " ]\n";
                cout << "7) Calculate beam deflection\n";
                cout << "Enter option: ";
                cin >> sub_option;
                // Invalid values for secondary menu
                while (sub_option < 1 || sub_option > 7) {
                    cout << "This option is invalid! Please enter a valid option between 1 and 7: ";
                    cin >> sub_option;
                }
                // updating input beam parameters
                if (sub_option >= 1 && sub_option <= 6) {
                    double updated_value;  // input for the new parameter
                    
                      // Show the current value in the prompt message based on the chosen parameter
                      if (sub_option == 1)
                          cout << "Please enter the Deflection Calculation Point (current: " << x <<"): ";
                      else if (sub_option == 2)
                          cout << "Please enter the Length of the Beam (current: " << L << "): ";
                      else if (sub_option == 3)
                          cout << "Please enter the Load (current: " << P << "): ";
                      else if (sub_option == 4)
                          cout << "Please enter the Location where the load is applied (current: " << a << "): ";
                      else if (sub_option == 5)
                          cout << "Please enter Young’s Modulus of the beam material (current: " << E << "): ";
else if (sub_option == 6)
                          cout << "Please enter the Second Moment of Area (current: " << I << "): ";
                    cin >> updated_value;
                    // Invalid input for new parameters
                    while (updated_value < 0 ||
                                 (sub_option == 1 && (updated_value <= 0 || updated_value > L)) ||  // x can´t be negative and larger than L
                                 (sub_option == 2 && updated_value <= 0) ||  // L can´t be negative
                                 (sub_option == 3 && updated_value <= 0) ||  // P can´t be negative
                                 (sub_option == 4 && (updated_value <= 0 || updated_value > L)) ||  // a can´t be negative and larger than L
                                 (sub_option == 6 && updated_value <= 0)) // I can´t be negative
                    {
                        cout << "Invalid input. Ensure values are positive and valid: ";
                        cin >> updated_value;
                    }
                    // Assign the new parameters
                    if (sub_option == 1) x = updated_value;
                    else if (sub_option == 2) L = updated_value;
                    else if (sub_option == 3) P = updated_value;
                    else if (sub_option == 4) a = updated_value;
                    else if (sub_option == 5) E = updated_value;
                    else if (sub_option == 6) I = updated_value;
                }
                // Compute beam deflection
                if (sub_option == 7) {
                    double V;
                    if (x < a) {
                        V = (-P * x * (L * L - a * a - x * x)) / (6 * E * I);
                    } else {
                        V = (-P * (L - a) * (L * L - x * x - (L - a) * (L - a))) / (6 * E * I);
                                        }
                    cout << "The Beam deflection at x = " << x << " is " << V << " \n";
                    break; // back to main menu
                }
            }
        }
        else if (option == 2) { // displaying help menu
            cout << "Help Menu:\n";
            cout << "This program computes a simply supported beam's deflection.\n";
            cout << "Beam parameters can be updated before any computations.\n";
            cout << "Select Option 1 to input the parameters before computing deflection.\n";
            cout << "To see the results, select 'Compute beam deflection' from the secondary menu.\n";
            cout << "Select Option 3 from the main menu to exit the program.\n";
            cout << " Back to the Main Menu.\n";
        }
        else if (option == 3) { // option to exit program
            cout << "You have chosen to quit. Exiting the program. \n";
            return(0);
        }
    }
}

