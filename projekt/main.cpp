#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<string, int> rarityMap = {
    {"Common", 1},
    {"Rare", 2},
    {"Epic", 3},
    {"Legendary", 4}
};

class Item {
public:
    string name;
    int price;
    int amount;
    string rarity;
    int level;
    Item(string name, string rarity) : name{name}, rarity{rarity}, level{1} {}
    Item(string name) : name{name} {}
    Item(string name, int price) : name{name}, price{price} {}
    Item(string name, int price, int amount) : name{name}, price{price}, amount{amount} {}
    Item(string name, int price, string rarity, int level) : name{name}, price{price}, rarity{rarity}, level{level} {}
    virtual ~Item() {} //Wirtualny destruktor pozwala na właściwe usuwanie obiektów dziedziczących.

    void showDetails() const {
        cout << "Name: " << name << ", Price: " << price << ", Amount: " << amount << endl;
    }
};

class Weapon : public Item {
public:
    int damage;
    Weapon(string name, int price, int damage, string rarity, int level) : Item(name, price, rarity, level), damage{damage} {}

    void showDetails() const {
        cout << "Name: " << name << ", Price: " << price << ", Damage: " << damage << ", Rarity: " << rarity << ", Level: " << level << endl;
    }
};

class Armor : public Item {
public:
    int protection;
    Armor(string name, int price, int protection, string rarity, int level) : Item(name, price, rarity, level), protection{protection} {}

    void showDetails() const {
        cout << "Name: " << name << ", Price: " << price << ", Protection: " << protection << ", Rarity: " << rarity << ", Level: " << level << endl;
    }
};

class Food : public Item {
public:
    int healing;
    Food(string name, int price, int healing, int amount) : Item(name, price, amount), healing{healing} {}

    void showDetails() const {
        cout << "Name: " << name << ", Price: " << price << ", Healing: " << healing << ", Amount: " << amount << endl;
    }
};

class Sword : public Weapon {
public:
    Sword(string name, int price, int damage, string rarity, int level) : Weapon(name, price, damage, rarity, level) {}
};
class Axe : public Weapon {
public:
    Axe(string name, int price, int damage, string rarity, int level) : Weapon(name, price, damage, rarity, level) {}
};
class Kilof : public Weapon {
public:
    Kilof(string name, int price, int damage, string rarity, int level) : Weapon(name, price, damage, rarity, level) {}
};
class Pan : public Weapon {
public:
    Pan(string name, int price, int damage, string rarity, int level) : Weapon(name, price, damage, rarity, level) {}
};

class Helmet : public Armor {
public:
    Helmet(string name, int price, int protection, string rarity, int level) : Armor(name, price, protection, rarity, level) {}
};
class Chest : public Armor {
public:
    Chest(string name, int price, int protection, string rarity, int level) : Armor(name, price, protection, rarity, level) {}
};
class Pants : public Armor {
public:
    Pants(string name, int price, int protection, string rarity, int level) : Armor(name, price, protection, rarity, level) {}
};
class Boots : public Armor {
public:
    Boots(string name, int price, int protection, string rarity, int level) : Armor(name, price, protection, rarity, level) {}
};

class Bread : public Food {
public:
    Bread(string name, int price, int healing, int amount) : Food(name, price, healing, amount) {}
};
class Steak : public Food {
public:
    Steak(string name, int price, int healing, int amount) : Food(name, price, healing, amount) {}
};
class Apples : public Food {
public:
    Apples(string name, int price, int healing, int amount): Food(name, price, healing, amount) {}
};
class Carrots : public Food {
public:
    Carrots(string name, int price, int healing, int amount) : Food(name, price, healing, amount) {}
};



class Equipment {
    Item*** grid;
    int rows;
    int cols;
    void clear() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] != nullptr) {
                    delete grid[i][j];
                    grid[i][j] = nullptr;
                }
            }
        }
    }
public:
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
                cout << "[" << (grid[i][j] != nullptr ? grid[i][j]->name : " ") << "]\t";
            }
            cout << endl;
        }
    }
    int getRows() const {
        return rows;
    }
    int getCols() const {
        return rows;
    }
    Item*** getGrid() const {
        return grid;
    }

    bool levelUp(int r, int c) {
        if(grid[r][c] == nullptr) {
            return false;
        }

        grid[r][c]->level++;
        return true;
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
        stock.push_back(new Sword("Sword", 15, 13, "Common", 1));
        stock.push_back(new Sword("Sword", 20, 13, "Rare", 1));
        stock.push_back(new Sword("Sword", 25, 13, "Epic", 1));
        stock.push_back(new Sword("Sword", 30, 13, "Legendary", 1));
        stock.push_back(new Axe("Axe", 11, 12, "Common", 1));
        stock.push_back(new Axe("Axe", 16, 12, "Rare", 1));
        stock.push_back(new Axe("Axe", 21, 12, "Epic", 1));
        stock.push_back(new Axe("Axe", 26, 12, "Legendary", 1));
        stock.push_back(new Kilof("Kilof", 13, 9, "Common", 1));
        stock.push_back(new Kilof("Kilof", 18, 9, "Rare", 1));
        stock.push_back(new Kilof("Kilof", 23, 9, "Epic", 1));
        stock.push_back(new Kilof("Kilof", 28, 9, "Legendary", 1));
        stock.push_back(new Pan("Pan", 12, 8, "Common", 1));
        stock.push_back(new Pan("Pan", 17, 8, "Rare", 1));
        stock.push_back(new Pan("Pan", 22, 8, "Epic", 1));
        stock.push_back(new Pan("Pan", 27, 8, "Legendary", 1));
        stock.push_back(new Helmet("Helmet", 8, 9, "Common", 1));
        stock.push_back(new Helmet("Helmet", 13, 9, "Rare", 1));
        stock.push_back(new Helmet("Helmet", 18, 9, "Epic", 1));
        stock.push_back(new Helmet("Helmet", 23, 9, "Legendary", 1));
        stock.push_back(new Chest("Chest", 13, 15, "Common", 1));
        stock.push_back(new Chest("Chest", 18, 15, "Rare", 1));
        stock.push_back(new Chest("Chest", 23, 15, "Epic", 1));
        stock.push_back(new Chest("Chest", 18, 15, "Legendary", 1));
        stock.push_back(new Pants("Pants", 11, 13, "Common", 1));
        stock.push_back(new Pants("Pants", 16, 13, "Rare", 1));
        stock.push_back(new Pants("Pants", 21, 13, "Epic", 1));
        stock.push_back(new Pants("Pants", 26, 13, "Legendary", 1));
        stock.push_back(new Boots("Boots", 8, 7, "Common", 1));
        stock.push_back(new Boots("Boots", 13, 7, "Rare", 1));
        stock.push_back(new Boots("Boots", 18, 7, "Epic", 1));
        stock.push_back(new Boots("Boots", 23, 7, "Legendary", 1));
        stock.push_back(new Bread("Bread", 4, 3, 40));
        stock.push_back(new Steak("Steak", 6, 5, 40));
        stock.push_back(new Apples("Apples", 4, 4, 40));
        stock.push_back(new Carrots("Carrots", 3, 3, 40));
    }

    ~Shop() {
        for (auto& item : stock) {
            delete item;
        }
    }

    void displayStock() {
        for (auto& item : stock) {
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            Armor* armor = dynamic_cast<Armor*>(item);
            Food* food = dynamic_cast<Food*>(item);
            if (weapon) {
                cout << weapon->name << " - Price: " << weapon->price << ", Damage: " << weapon->damage << ", Rarity: " << weapon->rarity << endl;
            }
            if (armor) {
                cout << armor->name << " - Price: " << armor->price << ", Protection: " << armor->protection << ", Rarity: " << armor->rarity << endl;
            }
            if (food) {
                cout << food->name << " - Price: " << food->price << ", Healing: " << food->healing << ", Amount: " << food->amount << endl;
            }
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

    vector<Armor*> armorPieces;
public:
    Player() {
        HP = 100;
        gold = 150;
        mainHand = nullptr;
        armor = nullptr;
        eq = new Equipment();

        eq->getGrid()[0][0] = new Sword("Sword", 15, 13, "Common", 1);
        eq->getGrid()[0][1] = new Kilof("Kilof", 13, 9, "Common", 1);
        eq->getGrid()[0][2] = new Carrots("Carrots", 3, 3, 40);
    }

    void setMainWeapon(int i, int j) {
        if (dynamic_cast<Weapon*>(eq->getGrid()[i][j])) { //dynamic_cast jest używany, aby sprawdzić, czy wskaźnik wskazuje na obiekt klasy pochodnej (np. Weapon lub Armor)
            Item* temp = mainHand;
            mainHand = eq->getGrid()[i][j];
            eq->getGrid()[i][j] = temp;
        } else {
            cout << "This is not a weapon!" << endl;
        }
    }
    void setMainArmor(int i, int j) {
        bool found = false;
        for (int row = 0; row < eq->getRows(); row++) {
            for (int col = 0; col < eq->getCols(); col++) {
                if (row == i && col == j && dynamic_cast<Armor*>(eq->getGrid()[row][col])) {
                    string armorName = eq->getGrid()[row][col]->name;
                    // Check if the armor is not already equipped
                    for (auto armor : armorPieces) {
                        if (armor->name == armorName) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        // Equip the armor
                        armorPieces.push_back(dynamic_cast<Armor*>(eq->getGrid()[row][col]));
                        cout << "Equipped: " << armorName << endl;
                    } else {
                        cout << "You already have equipped " << armorName << endl;
                    }

                    found = true; // Set found to true as the armor was found
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Armor not found at position (" << i << ", " << j << ") in the player's equipment." << endl;
        }
    }

    bool move(int r1, int c1, int r2, int c2) {
        if(eq->getGrid()[r1][c1] == nullptr) {
            return false;
        }

        Item* temp = eq->getGrid()[r1][c1];
        eq->getGrid()[r1][c1] = eq->getGrid()[r2][c2];
        eq->getGrid()[r2][c2] = temp;

        return true;
    }

    void displayEquippedArmor() {
        if (!armorPieces.empty()) {
            for (auto armor : armorPieces) {
                cout << armor->name << endl;
            }
        } else {
            cout << "No armor equipped." << endl;
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
                            if (eq->getGrid()[row][col]->name == " ") {
                                eq->getGrid()[row][col] = shop.stock[i];
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

    void deleteItem(int i, int j) {
        bool found = false;
        for(int row = 0; row < eq->getRows(); row++) {
            for(int col = 0; col < eq->getCols(); col++) {
                if (row == i && col == j && eq->getGrid()[row][col]->name != " ") {
                    string itemName = eq->getGrid()[row][col]->name;
                    cout << "You dropped " << itemName << " from your equipment." << endl;
                    delete eq->getGrid()[row][col];
                    eq->getGrid()[row][col] = new Item(" ");
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Item not found at position (" << i << ", " << j << ") in your equipment." << endl;
        }
    }

    void sellItem(int row, int col) {
        bool found = false;
        if (row >= 0 && row < eq->getRows() && col >= 0 && col < eq->getCols()) {
            string itemName = eq->getGrid()[row][col]->name;
            for (size_t i = 0; i < shop.stock.size(); ++i) {
                if (shop.stock[i]->name == itemName) {
                    int sellingPrice = 0.75 * shop.stock[i]->price;
                    cout << "You sold " << itemName << " for " << sellingPrice << " gold." << endl;
                    gold += sellingPrice;
                    delete eq->getGrid()[row][col];
                    eq->getGrid()[row][col] = new Item(" ");
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            cout << "Item not found in your equipment." << endl;
        }
    }

    void showDetails(int row, int col) {
        bool found = false;
        if (row >= 0 && row < eq->getRows() && col >= 0 && col < eq->getCols()) {
            Item* item = eq->getGrid()[row][col];
            string itemName = item->name;
            cout << "Details of item \"" << itemName << "\" at Row: " << row << ", Col: " << col << endl;

            if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                weapon->showDetails();
            } else if (Armor* armor = dynamic_cast<Armor*>(item)) {
                armor->showDetails();
            } else if (Food* food = dynamic_cast<Food*>(item)) {
                food->showDetails();
            }
            cout << endl;

            found = true;
        }
        if (!found) {
            cout << "Item not found at position (" << row << ", " << col << ") in the player's equipment." << endl;
        }
    }

    void showEq() {
        eq->display();
    }
    void displayShop() {
        cout << "Shop stock:" << endl;
        shop.displayStock();
    }
    void displayPlayerStats() {
        cout << "HP: " << HP << endl;
        cout << "Gold: " << gold << endl;
        cout << (mainHand != nullptr ? "Main weapon: " + mainHand->name : "Main weapon: none") << endl;
        cout << "Main armor: ";
        if (!armorPieces.empty()) {
            displayEquippedArmor();
        } else {
            cout << "none";
        }
        cout << endl;
        eq->display();
    }
    void sortEquipment() {
        eq->sort();
    }
    void extendEq() {
        eq->extendEquipment();
    }


    ~Player() {
        delete eq;
    }
};

int main()
{
    Player P;
    // P.showEq();
    // P.displayShop();
    // P.buy("Chest");
    // P.buy("Boots");
    // P.setMainWeapon(0, 0);
    // P.setMainArmor(0, 3);
    // P.setMainArmor(0, 4);
    // P.setMainWeapon(2, 0);
    // P.buy("Sword");
    // P.sellItem(0, 4);
    // P.displayPlayerStats();
    P.move(0, 0, 3, 2);
    P.move(0, 1, 2, 4);
    P.showEq();
    // P.showDetails(0, 2);
    // P.deleteItem(0, 1);
    P.sortEquipment();
    // P.extendEq();
    P.showEq();
    return 0;
}
