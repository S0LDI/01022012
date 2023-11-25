#include <iostream>
#include <vector>
#include <string>

class Property {
public:
    Property(const std::string& address, const std::string& name, double price)
        : address(address), name(name), price(price) {}

    const std::string& getAddress() const {
        return address;
    }

    double getPrice() const {
        return price;
    }

private:
    std::string address;
    std::string name;
    double price;
};

class Owner {
public:
    Owner(int id, const std::string& firstName, const std::string& lastName, double accountBalance)
        : id(id), firstName(firstName), lastName(lastName), accountBalance(accountBalance) {}

    int getId() const {
        return id;
    }

    void addProperty(Property* property) {
        ownedProperties.push_back(property);
    }

    void transferProperty(Owner& newOwner, Property* property) {
        auto it = std::find(ownedProperties.begin(), ownedProperties.end(), property);
        if (it != ownedProperties.end()) {
            // Передача власності
            ownedProperties.erase(it);
            newOwner.addProperty(property);

            // Передача коштів
            double transferPrice = property->getPrice();
            accountBalance -= transferPrice;
            newOwner.accountBalance += transferPrice;

            std::cout << "Власність " << property->getAddress() << " була передана від власника " << lastName
                << " до власника " << newOwner.getLastName() << ". Сума: " << transferPrice << std::endl;
        }
        else {
            std::cout << "Власник " << lastName << " не володіє вказаною власністю." << std::endl;
        }
    }

    void printBalance() const {
        std::cout << "Власник " << lastName << ": " << "ID: " << id << ", баланс: " << accountBalance << std::endl;
    }

    const std::string& getLastName() const {
        return lastName;
    }

private:
    int id;
    std::string firstName;
    std::string lastName;
    double accountBalance;
    std::vector<Property*> ownedProperties;
};

int main() {
    setlocale(LC_ALL, "ukr");
    // Створення об'єктів власності
    Property property1("Вулиця 1", "Будинок", 100000.0);
    Property property2("Вулиця 2", "Квартира", 75000.0);

    // Створення власників
    Owner owner1(1, "Іван", "Іванов", 50000.0);
    Owner owner2(2, "Петро", "Петров", 80000.0);

    // Надання власностей власникам
    owner1.addProperty(&property1);
    owner2.addProperty(&property2);

    // Перегляд початкового стану
    std::cout << "Початковий стан:" << std::endl;
    owner1.printBalance();
    owner2.printBalance();

    // Передача власності від одного власника до іншого
    owner1.transferProperty(owner2, &property1);

    // Перегляд оновленого стану
    std::cout << "Оновлений стан:" << std::endl;
    owner1.printBalance();
    owner2.printBalance();

    return 0;
}
