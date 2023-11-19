#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct User
{
    std::string name;
    std::string contactInfo;
    std::string bloodType;

    User *next;

    User() : next(nullptr) {}
};

class UserList
{
private:
    User *head;

public:
    UserList() : head(nullptr) {}

    void addUser(const std::string &name, const std::string &contactInfo, const std::string &bloodType)
    {
        User *newUser = new User();
        newUser->name = name;
        newUser->contactInfo = contactInfo;
        newUser->bloodType = bloodType;
        newUser->next = nullptr;

        if (head == nullptr)
        {
            head = newUser;
        }
        else
        {
            User *lastUser = head;
            while (lastUser->next != nullptr)
            {
                lastUser = lastUser->next;
            }
            lastUser->next = newUser;
        }
    }

    User *searchUser(const std::string &targetName) const
    {
        User *current = head;
        while (current != nullptr)
        {
            if (current->name == targetName)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void searchAndDisplayUser(const std::string &targetName) const
    {
        User *foundUser = searchUser(targetName);
        if (foundUser != nullptr)
        {
            std::cout << "User found:\n";
            std::cout << "Name: " << foundUser->name << "\n";
            std::cout << "Contact: " << foundUser->contactInfo << "\n";
            std::cout << "Blood Type: " << foundUser->bloodType << "\n";
        }
        else
        {
            std::cerr << "User not found.\n";
        }
    }

    void displayAllUsers() const
    {
        User *current = head;
        while (current != nullptr)
        {
            std::cout << "Name: " << current->name << ", Contact: " << current->contactInfo
                      << ", Blood Type: " << current->bloodType << std::endl;
            current = current->next;
        }
    }

    void updateUser(const std::string &targetName, const std::string &newContactInfo, const std::string &newBloodType)
    {
        User *targetUser = searchUser(targetName);
        if (targetUser != nullptr)
        {
            targetUser->contactInfo = newContactInfo;
            targetUser->bloodType = newBloodType;
            std::cout << "User updated successfully.\n";
        }
        else
        {
            std::cerr << "User not found.\n";
        }
    }

    void deleteUser(const std::string &targetName)
    {
        User *current = head;
        User *prev = nullptr;

        while (current != nullptr)
        {
            if (current->name == targetName)
            {

                if (prev != nullptr)
                {
                    prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                delete current; // Free the memory
                std::cout << "User deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        std::cerr << "User not found.\n";
    }

    void saveToCSV(const std::string &filename) const
    {
        std::ofstream outputFile(filename, std::ios::trunc); // Use std::ios::trunc to overwrite the file
        if (outputFile.is_open())
        {
            User *current = head;
            while (current != nullptr)
            {
                outputFile << current->name << "," << current->contactInfo << "," << current->bloodType << "\n";
                current = current->next;
            }
            outputFile.close();
            std::cout << "Data saved to " << filename << " successfully.\n";
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    void loadFromCSV(const std::string &filename)
    {
        std::ifstream inputFile(filename);
        if (inputFile.is_open())
        {
            // Clear the existing list before loading data
            clearList();

            std::string line;
            while (std::getline(inputFile, line))
            {
                std::istringstream iss(line);
                std::string name, contactInfo, bloodType;

                if (std::getline(iss, name, ',') &&
                    std::getline(iss, contactInfo, ',') &&
                    std::getline(iss, bloodType, ','))
                {
                    addUser(name, contactInfo, bloodType);
                }
            }
            inputFile.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    void clearList()
    {
        User *current = head;
        while (current != nullptr)
        {
            User *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

int main()
{
    const std::string adminUsername = "a";
    const std::string adminPassword = "a";

    UserList userList;

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (username == adminUsername && password == adminPassword)
    {
        int choice;
        do
        {
            std::cout << "\nAdmin Menu:\n";
            std::cout << "1. Add User\n";
            std::cout << "2. Search User\n";
            std::cout << "3. Update User\n";
            std::cout << "4. Delete User\n";
            std::cout << "5. Display All Users\n";
            std::cout << "6. Save to CSV\n";
            std::cout << "7. Load from CSV\n";
            std::cout << "8. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
            {
                std::string name, contactInfo, bloodType;
                std::cout << "Enter name: ";
                std::getline(std::cin, name);

                std::cout << "Enter contact information: ";
                std::getline(std::cin, contactInfo);

                std::cout << "Enter blood type: ";
                std::getline(std::cin, bloodType);

                userList.addUser(name, contactInfo, bloodType);
                break;
            }
            case 2:
            {
                std::string searchName;
                std::cout << "Enter name to search: ";
                std::getline(std::cin, searchName);
                User *foundUser = userList.searchUser(searchName);
                if (foundUser != nullptr)
                {
                    userList.searchAndDisplayUser(searchName);
                }
                else
                {
                    std::cerr << "User not found.\n";
                }
                break;
            }
            case 3:
            {
                std::string searchName, newContact, newBloodType;
                std::cout << "Enter name to update: ";
                std::getline(std::cin, searchName);
                std::cout << "Enter new contact information: ";
                std::getline(std::cin, newContact);

                std::cout << "Enter new blood type: ";
                std::getline(std::cin, newBloodType);

                userList.updateUser(searchName, newContact, newBloodType);
                break;
            }
            case 4:
            {
                std::string deleteName;
                std::cout << "Enter name to delete: ";
                std::getline(std::cin, deleteName);
                userList.deleteUser(deleteName);
                break;
            }
            case 5:
                std::cout << "All Users:\n";
                userList.displayAllUsers();
                break;
            case 6:
                userList.saveToCSV("user_data.csv");
                break;
            case 7:
                userList.loadFromCSV("user_data.csv");
                std::cout << "Data loaded from CSV.\n";
                break;
            case 8:
                std::cout << "Exiting the admin menu.\n";
                break;
            default:
                std::cerr << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }
    else
    {
        std::cerr << "Login failed. Exiting the program.\n";
    }

    return 0;
}
