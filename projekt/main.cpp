#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
public:
    string name;
    int price;
    int amount;
    Item(string name) : name{name} {}
    Item(string name, int price) : name{name}, price{price} {}
    Item(string name, int price, int amount) : name{name}, price{price}, amount{amount} {}
    virtual ~Item() {} //Wirtualny destruktor pozwala na właściwe usuwanie obiektów dziedziczących.

    void showDetails() {
        cout << "Name: " << name << ", Price: " << price << ", Amount: " << amount << endl;
    }
};

class Weapon : public Item {
public:
    Weapon(string name, int price, int amount) : Item(name, price, amount) {}
};

class Armor : public Item {
public:
    Armor(string name, int price, int amount) : Item(name, price, amount) {}
};

class Food : public Item {
public:
    Food(string name, int price, int amount) : Item(name, price, amount) {}
};

class Sword : public Weapon {
public:
    Sword(string name, int price, int amount) : Weapon(name, price, amount) {}
};

class Axe : public Weapon {
public:
    Axe(string name, int price, int amount) : Weapon(name, price, amount) {}
};

class Kilof : public Weapon {
public:
    Kilof(string name, int price, int amount) : Weapon(name, price, amount) {}
};

class Bow : public Weapon {
public:
    Bow(string name, int price, int amount) : Weapon(name, price, amount) {}
};

class Arrows : public Weapon {
public:
    Arrows(string name, int price, int amount) : Weapon(name, price, amount) {}
};

class Bread : public Food {
public:
    Bread(string name, int price, int amount) : Food(name, price, amount) {}
};

class Steak : public Food {
public:
    Steak(string name, int price, int amount) : Food(name, price, amount) {}
};

class Apples : public Food {
public:
    Apples(string name, int price, int amount) : Food(name, price, amount) {}
};

class Carrots : public Food {
public:
    Carrots(string name, int price, int amount) : Food(name, price, amount) {}
};

class Helmet : public Armor {
public:
    Helmet(string name, int price, int amount) : Armor(name, price, amount) {}
};

class Chest : public Armor {
public:
    Chest(string name, int price, int amount) : Armor(name, price, amount) {}
};

class Pants : public Armor {
public:
    Pants(string name, int price, int amount) : Armor(name, price, amount) {}
};

class Boots : public Armor {
public:
    Boots(string name, int price, int amount) : Armor(name, price, amount) {}
};

class Equipment {
    int rows;
    int cols;
public:
    Item*** grid;
    Equipment(int rows = 5, int cols = 5) : rows{rows}, cols{cols} {
        grid = new Item**[rows];
        for(int i = 0; i < rows; i++) {
            grid[i] = new Item*[cols];
        }
        int count = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                grid[i][j] = new Item(" ");
                count++;
            }
        }
    }
    ~Equipment() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                delete grid[i][j];
            }
        }
        for(int j = 0; j < rows; j++) {
            delete[] grid[j];
        }
        delete[] grid;
    }
    void display() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cout << "[" << (grid[i][j] != nullptr ? grid[i][j]->name : "none") << "]\t";
            }
            cout << endl;
        }
    }
    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void sort() {
        int index = 0;
        for (int row = 0; row < getRows(); ++row) {
            for (int col = 0; col < getCols(); ++col) {
                if (grid[row][col]->name != " ") {
                    Item* temp = grid[row][col];
                    grid[row][col] = grid[index / getCols()][index % getCols()];
                    grid[index / getCols()][index % getCols()] = temp;
                    ++index;
                }
            }
        }
    }

    void extendEquipment() {
        // Create a new grid with one extra row and column
        Item*** newGrid = new Item**[rows + 1];
        for(int i = 0; i < rows + 1; i++) {
            newGrid[i] = new Item*[cols + 1];
        }
        // Copy existing items to the new grid
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                newGrid[i][j] = grid[i][j];
            }
        }
        // Initialize new row and column with empty items
        for(int i = 0; i < rows + 1; i++) {
            newGrid[i][cols] = new Item(" ");
        }
        for(int j = 0; j < cols + 1; j++) {
            newGrid[rows][j] = new Item(" ");
        }
        // Delete old grid and update grid pointer
        for(int i = 0; i < rows; i++) {
            delete[] grid[i];
        }
        delete[] grid;
        grid = newGrid;
        // Update rows and cols
        rows++;
        cols++;
    }
};

class Shop {
    string name;
    int price;
    int amount;
public:
    vector<Item*> stock;
    Shop() {
        stock.push_back(new Sword("Sword", 15, 1));
        stock.push_back(new Axe("Axe", 11, 1));
        stock.push_back(new Kilof("Kilof", 13, 1));
        stock.push_back(new Bow("Bow", 17, 1));
        stock.push_back(new Arrows("Arrows", 8, 40));
        stock.push_back(new Helmet("Helmet", 8, 1));
        stock.push_back(new Chest("Chest", 13, 1));
        stock.push_back(new Pants("Pants", 11, 1));
        stock.push_back(new Boots("Boots", 8, 1));
        stock.push_back(new Bread("Bread", 4, 40));
        stock.push_back(new Steak("Steak", 6, 40));
        stock.push_back(new Apples("Apples", 4, 40));
        stock.push_back(new Carrots("Carrots", 3, 40));
    }

    ~Shop() {
        for (auto& item : stock) {
            delete item;
        }
    }

    void displayStock() {
        for (auto& item : stock) {
            cout << item->name << " - Price: " << item->price << ", Amount: " << item->amount << endl;
        }
    }
};

class Player {
    int HP;
    int gold;
    Item* mainHand;
    Item* armor;
    Equipment* eq;
    Shop shop;
public:
    Player() {
        HP = 100;
        gold = 150;
        mainHand = nullptr;
        armor = nullptr;
        eq = new Equipment();

        eq->grid[0][0] = new Sword("Sword", 15, 1);
        eq->grid[0][1] = new Kilof("Kilof", 13, 1);
        eq->grid[0][2] = new Carrots("Carrots", 3, 40);
    }
    void move(int row1, int col1, int row2, int col2) {
        Item* temp = eq->grid[row1][col1];
        eq->grid[row1][col1] = eq->grid[row2][col2];
        eq->grid[row2][col2] = temp;
    }
    void setMainWeapon(int i, int j) {
        if (dynamic_cast<Weapon*>(eq->grid[i][j])) { //dynamic_cast jest używany, aby sprawdzić, czy wskaźnik wskazuje na obiekt klasy pochodnej (np. Weapon lub Armor)
            Item* temp = mainHand;
            mainHand = eq->grid[i][j];
            eq->grid[i][j] = temp;
        } else {
            cout << "This is not a weapon!" << endl;
        }
    }
    void setMainArmor(int i, int j) {
        if (dynamic_cast<Armor*>(eq->grid[i][j])) {
            Item* temp = armor;
            armor = eq->grid[i][j];
            eq->grid[i][j] = temp;
        } else {
            cout << "This is not an armor!" << endl;
        }
    }
    Item* buy(const string& itemName) {
        for (size_t i = 0; i < shop.stock.size(); ++i) {
            if (shop.stock[i]->name == itemName) {
                if (gold >= shop.stock[i]->price) {
                    cout << "You bought " << shop.stock[i]->name << " for " << shop.stock[i]->price << " gold." << endl;
                    gold -= shop.stock[i]->price;

                    // Dodaj zakupiony przedmiot do ekwipunku gracza
                    for(int row = 0; row < eq->getRows(); row++) {
                        for(int col = 0; col < eq->getCols(); col++) {
                            if (eq->grid[row][col]->name == " ") {
                                eq->grid[row][col] = shop.stock[i];
                                return shop.stock[i];
                            }
                        }
                    }

                    cout << "Your inventory is full. Cannot add the purchased item." << endl;
                    return nullptr;
                } else {
                    cout << "You don't have enough gold to buy " << shop.stock[i]->name << "." << endl;
                    return nullptr;
                }
            }
        }
        cout << "Item not found in the shop." << endl;
        return nullptr;
    }
    void deleteItem(const string& itemName) {
        bool found = false;
        for(int row = 0; row < eq->getRows(); row++) {
            for(int col = 0; col < eq->getCols(); col++) {
                if (eq->grid[row][col]->name == itemName) {
                    cout << "You dropped " << itemName << " from your equipment." << endl;
                    delete eq->grid[row][col];
                    eq->grid[row][col] = new Item(" ");
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Item not found in your equipment." << endl;
        }
    }
    void sellItem(const string& itemName) {
        bool found = false;
        for(int row = 0; row < eq->getRows(); row++) {
            for(int col = 0; col < eq->getCols(); col++) {
                if (eq->grid[row][col]->name == itemName) {
                    for (size_t i = 0; i < shop.stock.size(); ++i) {
                        if (shop.stock[i]->name == itemName) {
                            int sellingPrice = 0.75 * shop.stock[i]->price;
                            cout << "You sold " << itemName << " for " << sellingPrice << " gold." << endl;
                            gold += sellingPrice;
                            delete eq->grid[row][col];
                            eq->grid[row][col] = new Item(" ");
                            found = true;
                            break;
                        }
                    }
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Item not found in your equipment." << endl;
        }
    }

    void showDetails(string itemName) {
        cout << "Enter item name: ";
        cin >> itemName;

        bool found = false;
        for(int row = 0; row < eq->getRows(); row++) {
            for(int col = 0; col < eq->getCols(); col++) {
                if (eq->grid[row][col]->name == itemName) {
                    cout << "Details of item \"" << itemName << "\" at Row: " << row << ", Col: " << col << endl;
                    eq->grid[row][col]->showDetails();
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Item \"" << itemName << "\" not found in the player's equipment." << endl;
        }
    }

    void showEq() {
        eq->display();
    }
    void extendEq() {
        eq->extendEquipment();
    }
    void displayShop() {
        cout << "Shop stock:" << endl;
        shop.displayStock();
    }
    void displayPlayerStats() {
        cout << "HP: " << HP << endl;
        cout << "Gold: " << gold << endl;
        cout << (mainHand != nullptr ? "Main weapon: " + mainHand->name : "Main weapon: none") << endl;
        cout << (armor != nullptr ? "Main armor: " + armor->name : "Main armor: none") << endl;
        eq->display();
    }
    void sortEquipment() {
        eq->sort();
    }
    ~Player() {
        delete eq;
    }
};


int main()
{
    Player P;

    P.showEq();
    //P.displayShop();
    //P.buy("Sword");
    //P.buy("Bread");
    P.displayPlayerStats();
    //P.deleteItem("Sword");
    //P.displayPlayerStats();
    //P.sell("Kilof");
    P.move(0, 0, 3, 2);
    P.move(0, 1, 2, 4);
    P.displayPlayerStats();
    P.sortEquipment();
    // P.showDetails("Carrots");
    P.extendEq();
    P.displayPlayerStats();
    // P.setMainWeapon(3, 4);
    // P.setMainArmor(2, 1);
    // P.displayPlayerStats();
    // P.setMainWeapon(2, 0);
    // P.setMainArmor(2, 3);
    // P.displayPlayerStats();

    return 0;
}
