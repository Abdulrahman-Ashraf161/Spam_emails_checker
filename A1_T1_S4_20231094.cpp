// File: A1_T1_S4_20231094.cpp
// Purpose: This program contains 5 sections:
//          1) Split: Extracts words between delimiters.
//          2) Binary Print: Converts a decimal number to binary.
//          3) Numbers: Adds a prefix to binary index numbers.
//          4) Teddy Bears: Determines if a number can be reduced to 42 under certain rules.
//          5) Spam Email Checker: Scans an email file for spam-related words.
// Author: Abdulrahman Ashraf Mohamed Ahmed
// Section: S4
// ID: 20231094
// Date: 10 Oct 2024

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

// Function to split a string based on a delimiter.
vector<string> split1(string& target, string& delimiter) {
    vector<string> list;
    size_t end; // Position of the next delimiter
    size_t start = 0; // Starting position of the substring

    // Loop to find and split the string by the delimiter
    while ((end = target.find(delimiter, start)) != string::npos) {
        list.push_back(target.substr(start, end - start)); // Add substring to list
        start = end + delimiter.length(); // Update the starting point for the next search
    }

    // Add the last part of the string after the final delimiter
    list.push_back(target.substr(start));
    return list;
}

static string binary_N;  // Global variable to hold the binary representation

// Recursive function to convert a decimal number to binary
static void binaryPrint2(int n) {
    if (n == 0) return; // Base case: when the number is reduced to 0
    binaryPrint2(n / 2); // Recursive call with n divided by 2
    binary_N.append(to_string(n % 2)); // Append the remainder (0 or 1) to binary representation
}

// Function to generate binary numbers with a given prefix
void numbers3(const string& prefix, int k) {
    binary_N = ""; // Clear the previous binary string
    static int n = pow(2, k) - 1; // Calculate maximum binary number for given bit length
    binaryPrint2(n);
    n--; // Decrease the number for next iteration
    cout << prefix << right << setfill('0') << setw(k) << binary_N << endl; // Print formatted binary number

    // Recursively call the function to print remaining numbers
    if (n >= 0)
        numbers3(prefix, k);
}

// Recursive function to play the Teddy Bear game and determine if the number can reach 42
static bool Teddy_bears4(int n) {
    if (n == 42) return true; // Success: the number is reduced to 42
    if (n < 42) return false; // Failure: the number is less than 42 and cannot reach it

    // Check if number is even, then recursively subtract half
    if (n % 2 == 0) {
        if (Teddy_bears4(n - n / 2)) return true;
    }

    // Check if number is divisible by 3 or 4, then subtract the product of its last two digits
    if (n % 3 == 0 || n % 4 == 0) {
        int l_Digit = n % 10; // Last digit
        int Sl_Digit = (n % 100) / 10; // Second last digit
        int product = l_Digit * Sl_Digit; // Product of the two digits
        if (product > 0 && Teddy_bears4(n - product)) return true;
    }

    // Check if number is divisible by 5, then subtract 42
    if (n % 5 == 0) {
        if (Teddy_bears4(n - 42)) return true;
    }

    return false; // Default: if none of the rules apply, return false
}

// Spam words list with associated points for spam detection
unordered_map<string, int> spamWords = {
        {"urgent", 3}, {"verify", 3}, {"detected", 3}, {"limited-time", 2},
        {"win", 3}, {"password", 3}, {"offer", 1}, {"suspicious", 3},
        {"immediately", 2}, {"alert", 3}, {"important", 2}, {"update", 2},
        {"required", 2}, {"unusual", 3}, {"problem", 3}, {"identity", 3},
        {"free", 2}, {"instant", 3}, {"download", 3}, {"bank", 3},
        {"exclusive", 2}, {"check", 2}, {"opportunity", 2}, {"open", 3},
        {"emergency", 3}, {"apple", 2}, {"confirm", 3}, {"secure", 3},
        {"verification", 3}, {"paypal", 3}, {"invoice", 2}, {"congratulations!", 2},
        {"click", 3}, {"payment", 3}
};

// Function to count occurrences of spam-related words in a file
unordered_map<string, int> count_Spam_Words(const string &filename) {
    unordered_map<string, int> wordCount;
    fstream file(filename, ios::in);

    if (file.is_open()) {
        string line;
        // Read file line by line
        while (getline(file, line)) {
            string word;
            stringstream ss(line);
            // Extract and process each word in the line
            while (ss >> word) {
                transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert word to lowercase
                // If the word is in the spam list, increase its count
                if (spamWords.find(word) != spamWords.end()) {
                    wordCount[word]++;
                }
            }
        }
        file.close();
    }
    return wordCount;
}

// Function to calculate total points based on word frequency
int calc_Total_Points(const unordered_map<string, int> &wordCount) {
    int totalPoints = 0;
    // Loop through the counted words and calculate their total points
    for (const auto &entry : wordCount) {
        const string &word = entry.first;
        int count = entry.second;
        totalPoints += count * spamWords[word]; // Add points based on word frequency and value
    }
    return totalPoints;
}

// Function to print the results of the spam detection
void printResults(const unordered_map<string, int> &wordCount, int totalPoints) {
    cout << "================================================================" << endl;
    cout << left << setw(25) << "Words" << "Occurrences  " << "Points  " << "Total_Points\n";
    cout << "=================================================================" << endl;

    // Display each word, its occurrences, points per occurrence, and total points
    for (const auto &entry : wordCount) {
        const string &word = entry.first;
        int count = entry.second;
        int points = spamWords[word];
        cout << left << setw(29) << word << "\t" << count << "\t" << points << "\t" << (count * points) << "\n";
    }

    cout << "=================================================================\n";
    cout << "==> Total Points: " << totalPoints << endl; // Display the total points
}

// Main function for phishing email detection program
void run_phishing_scanner() {
    string filename;
    while (true) {
        cout << "==> Enter your file name:";
        getline(cin, filename); // Get the file name from the user
        ifstream file(filename);
        if (!file.is_open()) { // Check if the file exists
            cout << "Error: File does not exist !!!\n";
            cout << "Options:\n";
            cout << "1) Reassign the file name\n";
            cout << "2) Exit the program\n";
            char choice;
            cout << "Please enter your choice (1 or 2) :";
            cin >> choice;

            // Handle user's choice to retry or exit
            if (choice == '2') {
                cout << "==> Exiting the program. Goodbye!!\n";
                return;
            } else if (choice != '1') {
                cout << "=> Error: Invalid input!!" << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            unordered_map<string, int> wordCount = count_Spam_Words(filename); // Count spam words in file
            int totalPoints = calc_Total_Points(wordCount); // Calculate total points
            printResults(wordCount, totalPoints); // Print the results
            break;
        }
    }
}


//*************>> MENU <<****************
int main() {
    string choice1; // Variable to store the user's main menu choice
    while (true) { // Infinite loop for the menu
        cout << "************>> Welcome to the program menu <<************" << "\n\n";
        cout << "Choose the number of problem you want \n(1) Split\n(2) BinaryPrint/Numbers\n(3) BooleanBear\n(4) PhishingScanner\n(5) Exit" << endl;
        cout << "=> Enter your choice :";
        cin >> choice1; // Get user's choice from the menu

        // Handling the choice for the Split program
        if (choice1 == "1") {
            cout << "----->> Welcome to split program  <<-----" << "\n\n";
            cout << "=> Enter the target string:";
            string targ, deli; // Variables to hold the target string and delimiter
            cin >> targ; // Get the target string from user
            cout << "\n=> Enter the delimiter string:";
            cin >> deli; // Get the delimiter from user
            vector<string> result = split1(targ, deli); // Call the split function
            // Output the result of the split
            for (auto& token : result) {
                if (token == result.back()) cout << token << '.' << endl; // End the last token with a period
                else cout << token << ' '; // Print other tokens separated by space
            }
        }
            // Handling the choice for BinaryPrint/Numbers program
        else if (choice1 == "2") {
            cout << "----->> Welcome to BinaryPrint/Numbers program  <<-----" << "\n\n";
            string choice2; // Variable to store the user's choice between BinaryPrint and Numbers
            while (true) { // Infinite loop for BinaryPrint/Numbers menu
                cout << "(1)BinaryPrint program\n(2)Numbers program\n";
                cout << "Please enter your choice (1 or 2): ";
                cin >> choice2; // Get user's choice

                // Handling the choice for BinaryPrint program
                if (choice2 == "1") {
                    cout << "----->> Welcome to BinaryPrint program  <<-----" << "\n\n";
                    int n; // Variable to hold the decimal number input
                    cout << "=> Enter your decimal number:";
                    cin >> n; // Get the decimal number from user
                    // Validate input for decimal number
                    if (cin.fail()) {
                        cout << "==> Error: Invalid input!!" << endl;
                        cin.clear(); // Clear the error flag on cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                        continue; // Retry input
                    }
                    binaryPrint2(n); // Call the binary print function
                    // Output the result
                    if (n == 0) cout << "n = 0        Output: 0" << endl; // Handle case for 0
                    else cout << "n = " << n << "       Output: " << binary_N << endl; // Output for non-zero
                    break; // Exit the loop for BinaryPrint
                }
                    // Handling the choice for Numbers program
                else if (choice2 == "2") {
                    cout << "----->> Welcome to Numbers program  <<-----" << "\n\n";
                    int k; // Variable to hold the number of indexes
                    string prefix; // Variable to hold the prefix
                    cout << "=> Enter the number of indexes:";
                    cin >> k; // Get the number of indexes from user
                    // Validate input for the number of indexes
                    if (cin.fail()) {
                        cout << "==> Error: Invalid input!!" << endl;
                        cin.clear(); // Clear the error flag on cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                        continue; // Retry input
                    }
                    cout << "=> Enter the prefix: ";
                    cin >> prefix; // Get the prefix from user
                    numbers3(prefix, k); // Call the Numbers function
                    break; // Exit the loop for Numbers
                } else {
                    cout << "==> Error: Invalid input!!" << endl; // Handle invalid choice
                }
            }
        }
            // Handling the choice for Teddy_bears program
        else if (choice1 == "3") {
            cout << "----->> Welcome to Teddy_bears program  <<-----" << "\n\n";
            int n_bear; // Variable to hold the number of bears
            cout << "=> Enter the number of bears:";
            cin >> n_bear; // Get the number of bears from user
            // Validate input for the number of bears
            if (cin.fail()) {
                cout << "==> Error: Invalid input!!" << endl;
                cin.clear(); // Clear the error flag on cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                continue; // Retry input
            }
            // Check if the bears can reach 42 using game rules
            if (Teddy_bears4(n_bear)) {
                cout << "==> The bear count " << n_bear << " can reach 42 using the game rules.\n";
            } else {
                cout << "==> The bear count " << n_bear << " cannot reach 42 using the game rules.\n";
            }
        }
            // Handling the choice for Phishing Scanner program
        else if (choice1 == "4") {
            cout << "----->> Welcome to Phishing Scanner program  <<-----" << "\n\n";
            run_phishing_scanner(); // Call the phishing scanner function
        }
            // Handling the choice for exiting the program
        else if (choice1 == "5") {
            cout << "**********>> Exiting the program. Goodbye!! <<**********\n"; // Exit message
            break; // Exit the loop and end the program
        } else {
            cout << "==> Error: Invalid input!!" << endl; // Handle invalid input for main menu
        }
    }
    return 0;
}


