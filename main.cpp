#include "polynomial.h"
#include "polynomial_chatgpt.cpp"
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// Function to get a valid double input from the user
double getValidDouble() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
        }
    }
}

// Function to get a valid integer input from the user
int getValidInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value < 0) {
            cout << "Invalid input. Please enter a valid positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
        }
    }
}

// Function to get polynomial coefficients from the user
Polynomial getPolynomialFromUser() {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    degree = getValidInt();

    vector<double> coefficients(degree + 1);
    cout << "Enter the coefficients (from constant term to highest degree):\n";
    for (int i = 0; i <= degree; ++i) {
        cout << "Coefficient of x^" << i << ": ";
        coefficients[i] = getValidDouble();
    }

    return Polynomial(coefficients);
}

int main() {
    cout << "Welcome to the Polynomial Calculator!\n";

    // Get the first polynomial from the user
    cout << "Enter the first polynomial:\n";
    Polynomial p1 = getPolynomialFromUser();

    // Get the second polynomial from the user
    cout << "Enter the second polynomial:\n";
    Polynomial p2 = getPolynomialFromUser();

    // Perform operations
    cout << "\nChoose an operation to perform:\n";
    cout << "1. Add polynomials\n";
    cout << "2. Subtract polynomials\n";
    cout << "3. Multiply polynomials\n";
    cout << "4. Evaluate a polynomial\n";
    cout << "5. Find the derivative of a polynomial\n";
    cout << "6. Find the integral of a polynomial\n";
    cout << "7. Find the root of a polynomial\n";
    cout << "Your choice: ";

    int choice = getValidInt();

    switch (choice) {
        case 1: {
            Polynomial sum = p1 + p2;
            cout << "Result of addition: " << sum << endl;
            break;
        }
        case 2: {
            Polynomial diff = p1 - p2;
            cout << "Result of subtraction: " << diff << endl;
            break;
        }
        case 3: {
            Polynomial prod = p1 * p2;
            cout << "Result of multiplication: " << prod << endl;
            break;
        }
        case 4: {
            cout << "Which polynomial do you want to evaluate? (1 or 2): ";
            int polyChoice = getValidInt();
            double x;
            cout << "Enter the value of x: ";
            x = getValidDouble();
            double result = (polyChoice == 1) ? p1.evaluate(x) : p2.evaluate(x);
            cout << "Polynomial evaluated at x = " << x << " is: " << result << endl;
            break;
        }
        case 5: {
            cout << "Which polynomial's derivative do you want? (1 or 2): ";
            int polyChoice = getValidInt();
            Polynomial deriv = (polyChoice == 1) ? p1.derivative() : p2.derivative();
            cout << "Derivative: " << deriv << endl;
            break;
        }
        case 6: {
            cout << "Which polynomial's integral do you want? (1 or 2):";
            int polyChoice = getValidInt();
            Polynomial integral = (polyChoice == 1) ? p1.integral() : p2.integral();
            cout << "Indefinite integral: " << integral << endl;
            break;
        }
        case 7: {
            cout << "Which polynomial's root do you want to find? (1 or 2):";
            int polyChoice = getValidInt();
            try {
                double root = (polyChoice == 1) ? p1.getRoot() : p2.getRoot();
                cout << "Root of the polynomial: " << root << endl;
            } catch (const runtime_error& e) {
                cout << "Error finding root: " << e.what() << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice. Please run the program again." << endl;
            break;
    }

    return 0;
}

