[README (1).md](https://github.com/user-attachments/files/34871222/README.1.md)
# student-record-management-system# Student Record Management System

A desktop application written in **C++** with a **Qt 6 Widgets** graphical interface. It lets a user **add, update, delete and browse** student records. All records are saved in a plain text file, so they are kept after the program is closed.

**Course:** SW112 Programming Fundamentals, Open Ended Lab (OEL)
**Student:** Muzamil Khan, K26SW-010
**Department:** Software Engineering, MUET Shaheed Zulfiqar Ali Bhutto Campus, Khairpur Mir's
**Instructor:** Engr. Asmatullah Zubair
<img width="419" height="400" alt="entry-mode" src="https://github.com/user-attachments/assets/f39dbd97-a35e-49ef-bf15-2af7ee13c4f4" />

---

## Features

- **Add** a new student, with a confirmation message after saving.
- **Update** a saved student (the roll number identifies the record).
- **Delete** a student, with a confirmation question first.
- **Next / Previous** to move through saved records (wraps around at the ends).
- **New** to clear the form and return to a blank entry screen.
- **Record counter** such as "Record 2 of 5".
- **Input validation** with clear error messages.
- **File storage** in a comma-separated text file (`students.txt`).

Each student has six details: **Name, Roll Number, Father's Name, Caste, District and GPA**.

## Screenshots

| Entry mode (blank form) | Browse mode (saved record) |
|---|---|
| ![Entry mode](<img width="419" height="400" alt="entry-mode" src="https://github.com/user-attachments/assets/5ae246b2-145b-43e3-a386-949d9fbe39da" />
) | ![Browse mode](<img width="421" height="401" alt="browse-mode" src="https://github.com/user-attachments/assets/c88c0515-92e6-4768-addb-f2c3d8b28df1" />
) |

| Validation error | Data file |
|---|---|
| ![Validation error](<img width="422" height="400" alt="validation-error" src="https://github.com/user-attachments/assets/056cf034-ef5f-47ed-9311-ab507379dcde" />
) | ![students.txt](<img width="478" height="178" alt="data-file" src="https://github.com/user-attachments/assets/46666825-cfca-44e5-80d5-ff73d545fb99" />
) |

## Two modes

The window works in two modes, and the buttons switch automatically.

| Mode | When | Add | Update | Delete | New | Next / Previous |
|------|------|-----|--------|--------|-----|-----------------|
| **Entry** | Program start, blank form | On | Off | Off | Off | On if records exist |
| **Browse** | A saved record is shown | Off | On | On | On | On |

In Browse mode the **roll number is locked**, because it is the unique identifier used to find the record in the file.

## Input rules

| Field | Rule |
|-------|------|
| All fields | Must not be empty |
| Name, Father's Name, Caste, District | Letters and spaces only |
| Roll Number | Letters, digits and `-` only, and must be unique |
| GPA | A number from 0.0 to 4.0 |

Commas are not allowed in any field, so the file format cannot be broken.

## Data file format

Records are stored in `students.txt`, one student per line, fields separated by commas:

```
name,rollNo,fatherName,caste,district,gpa
```

Example:

```
Ali Raza,26SW001,Ahmed Raza,Soomro,Khairpur,3.45
Sara Khan,26SW002,Imran Khan,Memon,Sukkur,3.90
```

- The file is created automatically on first run if it does not exist.
- Blank or damaged lines are skipped when loading, so the program does not crash.
- The file is saved **next to the program (.exe)**, in the build folder.
- A sample file is provided in `sample_data/students.txt`.

## Project structure

```
StudentRecordSystem/
├── CMakeLists.txt        Build file
├── main.cpp              Starts the program
├── mainwindow.h/.cpp     Window, buttons, validation and mode logic
├── studentstore.h/.cpp   Loads and saves the file; add, update, remove by roll number
├── student.h             Student data (six fields)
├── sample_data/
│   └── students.txt      Example records
└── tests/
    └── test_store.cpp    Tests for the file-handling code (no GUI needed)
```

### Design

The code is split into three parts so that each one does a single job:

| Part | Job |
|------|-----|
| `Student` | Holds the six fields. No GUI or file code. |
| `StudentStore` | Keeps records in memory and saves them to the file. |
| `MainWindow` | Shows the form and buttons, checks input and calls `StudentStore`. |

Keeping the screen code separate from the file code makes the program easier to read, change and test.

## Tools and technologies

- **Language:** C++17
- **GUI framework:** Qt 6 Widgets (Qt Creator, CMake)
- **File handling:** standard C++ (`fstream`, `vector`, `string`)

Qt Widgets was chosen because it provides ready-made form controls, an event system (signals and slots) for button clicks, and a more polished look than lighter toolkits.

## How to build and run

1. Install **Qt 6** (6.5 LTS or newer) with **Qt Creator** and a **MinGW 64-bit** or MSVC kit.
2. Open Qt Creator and choose **File > Open File or Project**, then select `CMakeLists.txt`.
3. Select a Qt 6 kit and click **Configure Project**.
4. Press **Ctrl+B** to build and **Ctrl+R** to run.

To start with example data, copy `sample_data/students.txt` into the build folder next to the executable.

## Running the file-handling tests (optional)

The tests check the file code without opening the GUI. They need only a C++ compiler:

```
g++ -std=c++17 -I. tests/test_store.cpp studentstore.cpp -o test_store
./test_store
```

The tests cover: starting with no file, adding records, rejecting a duplicate roll number, updating, deleting, reloading from the file, and skipping damaged lines.

## Limitations

- Data is stored in a text file, not a database.
- There is no search or sort feature.
- There is no user login.

## Future work

- Store records in an **SQLite** database.
- Add **search** by roll number or name, and **sorting** by GPA.
- Add a table view of all records.
- Add a login system.

## Author

**Muzamil Khan**, K26SW-010
Software Engineering, MUET Khairpur
