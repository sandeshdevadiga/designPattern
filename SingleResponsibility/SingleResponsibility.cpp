/*

Each class should have single responsibily, what is is not the concern of the object should
not be part of the class
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Journal class: Responsible for managing journal entries
class Journal {
public:
    Journal(const std::string&& title) : title(title) {}

    void addEntry(const std::string& entry) {
        entries.push_back(entry);
    }
    
    
    

    const std::vector<std::string>& getEntries() const {
        return entries;
    }

    const std::string& getTitle() const {
        return title;
    }

private:
    std::string title;
    std::vector<std::string> entries;
};

// PersistenceManager class: Responsible for saving the journal to a file
class PersistenceManager {
public:
    static void save(const Journal& journal, const std::string& filename) {
        std::ofstream ofs(filename);
        if (ofs.is_open()) {
            ofs << "Journal: " << journal.getTitle() << std::endl;
            for (const auto& entry : journal.getEntries()) {
                ofs << entry << std::endl;
            }
            ofs.close();
        } else {
            std::cerr << "Could not open file for writing: " << filename << std::endl;
        }
    }
};

int main() {
    std::cout<< &main<< " address of main\n";
    Journal myJournal("My Personal Journal");
    myJournal.addEntry("Today I learned about the Single Responsibility Principle.");
    myJournal.addEntry("I wrote some C++ code to demonstrate it.");

    PersistenceManager::save(myJournal, "journal.txt");

    return 0;
}