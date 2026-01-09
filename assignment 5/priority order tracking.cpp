#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/* Step 1: Define structure */
struct Order {
    int orderID;
    string customerName;
    int itemCount;
    float itemPrice;
};

/* Function to calculate total bill */
float calculateTotal(const Order& o) {
    return o.itemCount * o.itemPrice;
}

int main() {

    /* Step 2: Use vector */
    vector<Order> orders;
    int n;

    /* Step 3: Input orders */
    cout << "Enter number of orders: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Order o;
        cout << "\nEnter details for order " << i + 1 << endl;

        cout << "Order ID: ";
        cin >> o.orderID;

        cout << "Customer Name: ";
        cin >> o.customerName;

        cout << "Number of Items: ";
        cin >> o.itemCount;

        cout << "Price per Item: ";
        cin >> o.itemPrice;

        /* Step 7: Validation */
        if (o.itemCount <= 0 || o.itemPrice <= 0) {
            cout << "Invalid input! Items and price must be positive.\n";
            i--;   // repeat this order input
            continue;
        }

        orders.push_back(o);
    }

    /* Step 5: Write high-value orders to file */
    ofstream fout("priority_orders.txt");

    if (!fout) {
        cout << "Error: Could not open file for writing!" << endl;
        return 1;
    }

    for (int i = 0; i < orders.size(); i++) {
        float totalBill = calculateTotal(orders[i]);

        if (totalBill > 5000) {
            fout << orders[i].orderID << " "
                 << orders[i].customerName << " "
                 << orders[i].itemCount << " "
                 << orders[i].itemPrice << " "
                 << totalBill << endl;
        }
    }

    fout.close();

    /* Step 6: Read and display priority orders */
    ifstream fin("priority_orders.txt");

    if (!fin) {
        cout << "Error: Could not open file for reading!" << endl;
        return 1;
    }

    cout << "\nPriority Orders (Total > 5000)\n";
    cout << "ID\tName\tItems\tPrice\tTotal\n";

    int id, items;
    string name;
    float price, total;

    while (fin >> id >> name >> items >> price >> total) {
        cout << id << "\t"
             << name << "\t"
             << items << "\t"
             << price << "\t"
             << total << endl;
    }

    fin.close();

    return 0;
}

   