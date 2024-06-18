#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Define a struct to store sales data
struct SalesData {
    std::string productName;
    double value;
};

class SalesSystem {
private:
    std::vector<SalesData> sales;
    std::vector<SalesData> expenses;
    double netProfit;
    double netSales = -1;

    // Additional data
    std::string time;
    std::string date;
    std::string day;

public:
    // Constructor
    SalesSystem() : netProfit(0.0) {}

    // Function prototypes
    void displayLoginScreen();
    bool authenticateUser();
    void enterDateTime();
    void displayMainScreen();
    void enterSalesData();
    void enterExpenseData();
    void displayNetSalesScreen();
    void displayNetProfitScreen();
    void displayStatisticsScreen();
    void displayReviewsScreen();
    void exitProgram();
};

// Function definitions
void SalesSystem::displayLoginScreen() {
    std::cout << "Welcome to the Sales System\n";
}

bool SalesSystem::authenticateUser() {
    std::string username, password;
    int attempts = 0;

    do {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (username == "admin" && password == "admin") {
            return true; // Authentication successful
        }
        else {
            attempts++;
            std::cout << "Authentication failed. Attempts left: " << 3 - attempts << std::endl;
        }
    } while (attempts < 3);

    std::cout << "You've reached the maximum number of attempts. Exiting program.\n";
    exit(1); // Exit the program if authentication fails
}

void SalesSystem::enterDateTime() {
    std::cout << "Enter time: ";
    std::cin.ignore(); // Clear newline from previous input
    std::getline(std::cin, time);

    std::cout << "Enter date: ";
    std::getline(std::cin, date);

    std::cout << "Enter day: ";
    std::getline(std::cin, day);
}

void SalesSystem::displayMainScreen() {
    std::cout << "\nMain Menu\n";
    std::cout << "1. Enter Sales\n";
    std::cout << "2. Statistics\n";
    std::cout << "3. Reviews\n";
    if (sales.size() > 0) {
        std::cout << "4. Enter Expenses\n";
        if (expenses.size() > 0) {
            std::cout << "5. Net Sales\n";
            std::cout << "6. Net Profit\n";
        }
    }
    std::cout << "*. Exit\n";
    std::cout << "Choose an option: ";
}

void SalesSystem::enterSalesData() {
    int numSales;
    std::cout << "Enter the number of sales transactions: ";
    std::cin >> numSales;

    if (numSales < 1) {
        std::cout << "Number of sales transactions must be at least 1.\n";
        return;
    }

    for (int i = 0; i < numSales; ++i) {
        SalesData sale;
        std::cout << "Enter sales value for product " << i + 1 << ": ";
        std::cin >> sale.value;
        std::cout << "Enter product name for product " << i + 1 << ": ";
        std::cin.ignore(); // Clear newline from previous input
        std::getline(std::cin, sale.productName);
        sales.push_back(sale);
    }

    std::cout << "Sales data entered successfully.\n";
}

void SalesSystem::enterExpenseData() {
    int numExpenses;
    std::cout << "Enter the number of expense transactions: ";
    std::cin >> numExpenses;

    if (numExpenses < 1) {
        std::cout << "Number of expense transactions must be at least 1.\n";
        return;
    }

    for (int i = 0; i < numExpenses; ++i) {
        SalesData expense;
        std::cout << "Enter expense value for product " << i + 1 << ": ";
        std::cin >> expense.value;
        std::cout << "Enter product name for product " << i + 1 << ": ";
        std::cin.ignore(); // Clear newline from previous input
        std::getline(std::cin, expense.productName);
        expenses.push_back(expense);
    }

    std::cout << "Expense data entered successfully.\n";
}

void SalesSystem::displayNetSalesScreen() {
    // Calculate and display net sales
    double totalSales = 0.0, totalExpenses = 0.0;

    for (const auto& sale : sales) {
        totalSales += sale.value;
    }

    for (const auto& expense : expenses) {
        totalExpenses += expense.value;
    }

    netSales = totalSales - totalExpenses;

    std::cout << "\nNet Sales for " << date << " - " << time << " (" << day << "): " << netSales << " dinars\n";
}

void SalesSystem::displayNetProfitScreen() {
    // Calculate and display net profit
    if (sales.empty() || expenses.empty()) {
        std::cout << "Please enter sales and expenses first.\n";
        return;
    }

    if (netSales == -1) {
        std::cout << "Please calculate net sales first.\n";
        return;
    }

    double totalSales = 0.0, totalExpenses = 0.0;

    for (const auto& sale : sales) {
        totalSales += sale.value;
    }

    for (const auto& expense : expenses) {
        totalExpenses += expense.value;
    }

    double netSales = totalSales - totalExpenses;
    double netProfit = netSales - (0.16 * netSales); // Deduct 16% tax

    std::cout << "\nNet Profit for " << date << " - " << time << " (" << day << "): " << netProfit << " dinars\n";
}

void SalesSystem::displayStatisticsScreen() {
    if (sales.empty() || expenses.empty()) {
        std::cout << "Please enter sales and expenses first.\n";
        return;
    }

    // Display statistics options
    std::cout << "\nStatistics Menu\n";
    std::cout << "1. Highest Sales Value\n";
    std::cout << "2. Highest Expense Value\n";
    std::cout << "3. Lowest Sales Value\n";
    std::cout << "4. Lowest Expense Value\n";
    std::cout << "5. Values where Sales match Expenses\n";
    std::cout << "6. Return to Main Menu\n";
    std::cout << "Choose an option: ";

    char choice;
    std::cin >> choice;

    switch (choice) {
    case '1': {
        // Highest Sales Value
        auto maxSale = std::max_element(sales.begin(), sales.end(), [](const SalesData& a, const SalesData& b) {
            return a.value < b.value;
            });
        std::cout << "\nHighest Sales Value: " << maxSale->productName << " - " << maxSale->value << " dinars\n";
        break;
    }
    case '2': {
        // Highest Expense Value
        auto maxExpense = std::max_element(expenses.begin(), expenses.end(), [](const SalesData& a, const SalesData& b) {
            return a.value < b.value;
            });
        std::cout << "\nHighest Expense Value: " << maxExpense->productName << " - " << maxExpense->value << " dinars\n";
        break;
    }
    case '3': {
        // Lowest Sales Value
        auto minSale = std::min_element(sales.begin(), sales.end(), [](const SalesData& a, const SalesData& b) {
            return a.value < b.value;
            });
        std::cout << "\nLowest Sales Value: " << minSale->productName << " - " << minSale->value << " dinars\n";
        break;
    }
    case '4': {
        // Lowest Expense Value
        auto minExpense = std::min_element(expenses.begin(), expenses.end(), [](const SalesData& a, const SalesData& b) {
            return a.value < b.value;
            });
        std::cout << "\nLowest Expense Value: " << minExpense->productName << " - " << minExpense->value << " dinars\n";
        break;
    }
    case '5': {
        // Values where Sales match Expenses
        std::cout << "\nMatching Sales and Expenses Values:\n";
        for (const auto& sale : sales) {
            for (const auto& expense : expenses) {
                if (sale.value == expense.value) {
                    std::cout << sale.productName << " - " << sale.value << " dinars\n";
                }
            }
        }
        break;
    }
    case '6':
        return; // Return to Main Menu
    default:
        std::cout << "Invalid choice. Please try again.\n";
    }
    std::cout << "1. Return to Statistics\n";
    bool loops = true;
    while (loops) {
        char choice1;
        std::cin >> choice1;
        if (choice1 == '1')
        {
            loops = false;
            displayStatisticsScreen();
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void SalesSystem::displayReviewsScreen() {
    if (sales.empty() || expenses.empty()) {
        std::cout << "Please enter sales and expenses first.\n";
        return;
    }

    double totalSales = 0.0, totalExpenses = 0.0;

    for (const auto& sale : sales) {
        totalSales += sale.value;
    }

    for (const auto& expense : expenses) {
        totalExpenses += expense.value;
    }

    double netSales = totalSales - totalExpenses;

    std::cout << "\nReviews Menu\n";

    if (netSales < 0) {
        std::cout << "Warning: There is a problem with income. Management should be informed.\n";
    }
    else if (netSales > 1000) {
        std::cout << "Thank you! Financial status is excellent.\n";
    }
    else if (netSales > 0 && netSales < 1000) {
        std::cout << "The situation is within the critical range.\n";
    }

    std::cout << "Return to Main Menu\n";
}

void SalesSystem::exitProgram() {
    char choice;
    std::cout << "Do you really want to exit the program? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        std::cout << "Exiting program. Thank you for using the system.\n";
        exit(0); // Exit the program
    }
}

int main() {
    SalesSystem system;

    // User authentication
    system.displayLoginScreen();
    if (!system.authenticateUser()) {
        std::cout << "Authentication failed. Exiting program.\n";
        return 1;
    }

    // Enter date, time, and day
    system.enterDateTime();

    // Main program loop
    char choice;

    do {
        system.displayMainScreen();
        std::cin >> choice;

        switch (choice) {
        case '1':
            system.enterSalesData();
            break;
        case '2':
            system.displayStatisticsScreen();
            break;
        case '3':
            system.displayReviewsScreen();
            break;
        case '4':
            system.enterExpenseData();
            break;
        case '5':
            system.displayNetSalesScreen();
            break;
        case '6':
            system.displayNetProfitScreen();
            break;
        case '*':
            system.exitProgram();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}
