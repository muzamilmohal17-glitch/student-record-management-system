// tests/test_store.cpp
// Tests the file-handling part (no GUI needed). Useful as evidence in your report.
// Build:  g++ -std=c++17 -I. tests/test_store.cpp studentstore.cpp -o test_store
#include <cstdio>
#include <fstream>
#include <iostream>
#include "studentstore.h"

static int failures = 0;

static void check(bool condition, const std::string& testName) {
    std::cout << (condition ? "PASS  " : "FAIL  ") << testName << '\n';
    if (!condition) ++failures;
}

static Student makeStudent(const std::string& roll, const std::string& name, double gpa) {
    return Student{name, roll, "Father " + name, "Caste", "Khairpur", gpa};
}

int main() {
    const std::string path = "test_students.txt";
    std::remove(path.c_str());

    StudentStore store(path);
    store.load();
    check(store.count() == 0, "Missing file starts with 0 records");

    check(store.add(makeStudent("26SW001", "Ali", 3.5)), "Add first student");
    check(store.add(makeStudent("26SW002", "Sara", 3.9)), "Add second student");
    check(!store.add(makeStudent("26SW001", "Other", 2.0)), "Duplicate roll number is rejected");
    check(store.count() == 2, "Count is 2 after duplicate rejected");

    check(store.update(makeStudent("26SW002", "Sara Khan", 4.0)), "Update existing student");
    check(!store.update(makeStudent("99XX999", "Nobody", 1.0)), "Update of unknown roll number fails");

    // Reload from the file to prove it was really saved.
    StudentStore reloaded(path);
    reloaded.load();
    check(reloaded.count() == 2, "Reload finds 2 records");
    check(reloaded.at(1).name == "Sara Khan" && reloaded.at(1).gpa == 4.0, "Updated data was saved");

    check(reloaded.remove("26SW001"), "Delete existing student");
    check(!reloaded.remove("26SW001"), "Delete of missing student fails");

    // A damaged line and a blank line must be skipped, not crash the program.
    {
        std::ofstream bad(path, std::ios::app);
        bad << "this,line,is,broken\n\nAli,26SW010,Ahmed,Caste,Sukkur,notanumber\n";
    }
    StudentStore withBadLines(path);
    withBadLines.load();
    check(withBadLines.count() == 1, "Damaged and blank lines are skipped");

    std::remove(path.c_str());
    std::cout << (failures == 0 ? "\nAll tests passed.\n" : "\nSome tests FAILED.\n");
    return failures;
}
