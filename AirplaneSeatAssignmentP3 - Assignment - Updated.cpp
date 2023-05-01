// Mark Bulmer - CSC 134 - 12-9-2021
// Airplane Assignment 3

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cctype>

using namespace std;

///
/// Global constants
///
const string EMPTY_SEAT = "<EMPTY>";
const int SEAT_STR_ROW_NUM_DIGITS = 2;
const int SEAT_STR_LETTER_NUM_CHARS = 1;
const int SEAT_STR_ROW_START_POS = 0;
const int SEAT_STR_LETTER_START_POS = 2;
const int SEAT_ROWS_START = 1;
const int SEAT_ROWS_END = 4;
const int NUM_SEAT_ROWS = SEAT_ROWS_END - SEAT_ROWS_START + 1;
const int NUM_SEAT_LETTERS = 4;
const char SEAT_TYPE_INDEX[NUM_SEAT_LETTERS]{ 'A', 'B', 'C', 'D' };
const int LETTER_OFFSET = (int)'A';

///
/// Used in displayFullMenu, displayShortMenu
///
const string CLEAR_SCREEN_MESSAGE = ". Clear Screen and Refresh Full Menu";
const string EXIT_PROGRAM_MESSAGE = ". Exit Program";
const string ENTER_CHOICE_MESSAGE = "Enter your choice: ";

///
/// Used in displayHeader, and as part of constant DASH_LENGTH
///
const string HEADER_TEXT = "Airline Seating Assignment Program";


///
/// Used in displayHeader, displayFullMenu
///
const size_t DASH_LENGTH = HEADER_TEXT.length();


///
/// Used in displayFullMenu
///
const string CREATE_MANIFEST_MESSAGE = ". Create Manifest";
const string CREATE_SEATING_CHART_MESSAGE = ". Create Seating Chart";
const string FIND_PASSENGER_MESSAGE = ". Find Passenger (by name)";
const string SHOW_OCCUPANT_MESSAGE = ". Show Seat Occupant (by seat)";
const string ASSIGN_SEAT_MESSAGE = ". Assign Seat (by name)";
const string REMOVE_PASSENGER_MESSAGE = ". Remove Passenger (by name)";
const string MOVE_PASSENGER_MESSAGE = ". Move Passenger (by name)";
const string REQUEST_WINDOW_MESSAGE = ". Request Window (by name)";
const string REQUEST_AISLE_MESSAGE = ". Request Aisle (by name)";


///
/// Used in main, displayFullMenu
///
const char MENU_CREATE_MANIFEST = '1';
const char MENU_CREATE_SEATING_CHART = '2';
const char MENU_FIND_PASSENGER = '3';
const char MENU_SHOW_OCCUPANT = '4';
const char MENU_ASSIGN_SEAT = '5';
const char MENU_REMOVE_PASSENGER = '6';
const char MENU_MOVE_PASSENGER = '7';

///
/// Used in main, displayFullMenu, requestWindowAisle
///
const char MENU_REQUEST_WINDOW = '8';
const char MENU_REQUEST_AISLE = '9';


///
/// Used in main, displayFullMenu, displayShortMenu, getMenuChoice
///
const char MENU_EXIT_PROGRAM = 'E';
const char MENU_CLEAR_SCREEN = 'C';


///
/// Used in createManifest
///
const int DISPLAY_WIDTH_CM = 15;
const int NUM_DISPLAY_COLS_CM = 2;
const string PASSENGER_HEADING = "Passenger";
const string SEAT_HEADING = "Seat";
const char PAD_CHAR = '0';


///
/// Used in createSeatingChart
///
const int DISPLAY_WIDTH_CSC = 10;
const int NUM_DISPLAY_COLS_CSC = 5;
const string ROW_HEADING = "row ";
const string ROW_HEADING_SUFFIX = ":";


///
/// Used in requestWindowAisle
///
const int NUM_WINDOW_SEAT_LETTERS = 2;
const int NUM_AISLE_SEAT_LETTERS = 2;
const int WINDOW_SEAT_INDEX[NUM_WINDOW_SEAT_LETTERS]{ 0, 3 };
const int AISLE_SEAT_INDEX[NUM_AISLE_SEAT_LETTERS]{ 1, 2 };


///
/// Used in dashLine 
///
const char REPEAT_CHAR = '-';


///
/// Used in isSeatValid
/// 
const string ERROR_MESSAGE_PREFIX = "***";
const string INVALID_SEAT_LENGTH_MESSAGE = "Invalid seat length";
const string INVALID_SEAT_ROW_NON_NUMERIC_MESSAGE = "Invalid seat row -- non-numeric";
const string INVALID_SEAT_ROW_OUT_OF_RANGE_LOWER_MESSAGE = "Invalid seat row -- out of range - less than ";
const string INVALID_SEAT_ROW_OUT_OF_RANGE_UPPER_MESSAGE = "Invalid seat row -- out of range - greater than ";
const string INVALID_SEAT_LETTER_NON_ALPHABETIC = "Invalid seat letter -- non-alphabetic";
const string INVALID_SEAT_LETTER_OUT_OF_RANGE = "Invalid seat letter - must be ";


///
/// Used in isPassengerNameValid
///
const string INVALID_PASSENGER_NAME_MESSAGE = "Invalid passenger name";


///
/// Function Prototypes
///
void displayHeader();
void displayShortMenu();
void displayFullMenu();
char getMenuChoice();

void createManifest(string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
void createSeatingChart(string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
string findPassenger(string passengerName, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
string showOccupant(string seat, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
bool assignSeat(string seat, string passengerName, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
bool releaseSeat(string seat, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);
string requestWindowAisle(int seatType, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[]);

void dashLine(size_t lineLength);
string upperCase(string string2upper);
bool isSeatValid(string seat);
bool isPassengerNameValid(string passengerName);

int main()
{
    ///
    /// Constants used in main 
    ///
    const string CREATE_MANIFEST_LOG_TEXT = "Create Manifest";
    const string CREATE_SEATING_LOG_TEXT = "Create Seating Chart";
    const string FIND_PASSENGER_LOG_TEXT = "Find Passenger";
    const string SHOW_OCCUPANT_LOG_TEXT = "Show Seat Occupant";
    const string ASSIGN_SEAT_LOG_TEXT = "Assign Seat";
    const string REMOVE_PASSENGER_LOG_TEXT = "Remove Passenger";

    const string MANIFEST_MESSAGE = "Manifest was created. File name: ";
    const string SEATING_CHART_MESSAGE = "Seating chart was created. File name: ";
    const string FOUND_PASSENGER_MESSAGE = " is assigned seat ";
    const string NOT_FOUND_PASSENGER_MESSAGE = " does not have an assigned seat";
    const string FOUND_OCCUPANT_MESSAGE = " is occupied by ";
    const string NOT_FOUND_OCCUPANT_MESSAGE = " is empty";
    const string ASSIGNED_SEAT_TO_PASSENGER_MESSAGE = FOUND_PASSENGER_MESSAGE;
    const string NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE = " cannot be assigned seat ";
    const string REMOVED_PASSENGER_MESSAGE = " was removed from seat ";
    const string NOT_REMOVED_PASSENGER_MESSAGE = " was not removed from seat ";
    const string INVALID_CHOICE_ERROR_MESSAGE = "Please enter a valid choice: ";
    const string NO_AISLE_SEATS_AVAILABLE_MESSAGE = "There are no aisle seats available";
    const string NO_WINDOW_SEATS_AVAILABLE_MESSAGE = "There are no window seats available";
    const string AISLE_SEATS_AVAILABLE_MESSAGE = " is an available aisle seat";
    const string WINDOW_SEATS_AVAILABLE_MESSAGE = " is an available window seat";

    const char* WINDOWS_CLEAR_SCREEN = "cls";

    const string SEAT_PROMPT = "Please enter the seat number (format = NNA e.g. 02C): ";
    const string FIND_PASSENGER_PROMPT = "Please enter the passenger's name: ";

    ///
    /// Variables used in main 
    ///
    bool exitProgram = false;
    char choice;
    string seat;
    string oldSeat, newSeat;
    string passengerNameToMove;
    string passengerName;
    bool found = false;
    int letter = 0;

    string seatRow1[NUM_SEAT_LETTERS];
    string seatRow2[NUM_SEAT_LETTERS];
    string seatRow3[NUM_SEAT_LETTERS];
    string seatRow4[NUM_SEAT_LETTERS];

    seatRow1[0] = EMPTY_SEAT;
    seatRow1[1] = "Avery";
    seatRow1[2] = "Daniel";
    seatRow1[3] = "Luke";

    seatRow2[0] = "Leo";
    seatRow2[1] = "Abigail";
    seatRow2[2] = EMPTY_SEAT;
    seatRow2[3] = "Isabella";

    seatRow3[0] = "Lillian";
    seatRow3[1] = EMPTY_SEAT;
    seatRow3[2] = "Isaac";
    seatRow3[3] = "Ella";

    seatRow4[0] = "Evelyn";
    seatRow4[1] = "Aurora";
    seatRow4[2] = "Noah";
    seatRow4[3] = EMPTY_SEAT;


    displayFullMenu();


    do {
        choice = toupper(getMenuChoice());

        switch (choice) {

        case MENU_CREATE_MANIFEST:
            createManifest(seatRow1, seatRow2, seatRow3, seatRow4);

            displayShortMenu();

            break;

        case MENU_CREATE_SEATING_CHART:
            createSeatingChart(seatRow1, seatRow2, seatRow3, seatRow4);

            displayShortMenu();

            break;

        case MENU_FIND_PASSENGER:
            cout << FIND_PASSENGER_PROMPT;
            getline(cin, passengerName);

            seat = findPassenger(passengerName, seatRow1, seatRow2, seatRow3, seatRow4);

            cout << endl;

            if (seat != EMPTY_SEAT) {
                dashLine((passengerName + FOUND_PASSENGER_MESSAGE + seat).length());
                cout << passengerName << FOUND_PASSENGER_MESSAGE << seat << endl;
                dashLine((passengerName + FOUND_PASSENGER_MESSAGE + seat).length());
            }
            else {
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
                cout << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
            }

            cout << endl;

            displayShortMenu();

            break;

        case MENU_SHOW_OCCUPANT:
            do {
                cout << SEAT_PROMPT;
                getline(cin, seat);
            } while (!isSeatValid(seat));

            passengerName = showOccupant(seat, seatRow1, seatRow2, seatRow3, seatRow4);

            cout << endl;

            if (passengerName != EMPTY_SEAT) {
                dashLine((upperCase(seat) + FOUND_OCCUPANT_MESSAGE + passengerName).length());
                cout << upperCase(seat) << FOUND_OCCUPANT_MESSAGE << passengerName << endl;
                dashLine((upperCase(seat) + FOUND_OCCUPANT_MESSAGE + passengerName).length());
            }
            else {
                dashLine((upperCase(seat) + NOT_FOUND_OCCUPANT_MESSAGE).length());
                cout << upperCase(seat) << NOT_FOUND_OCCUPANT_MESSAGE << endl;
                dashLine((upperCase(seat) + NOT_FOUND_OCCUPANT_MESSAGE).length());
            }

            cout << endl;

            displayShortMenu();

            break;

        case MENU_ASSIGN_SEAT:
            do {
                cout << SEAT_PROMPT;
                getline(cin, seat);
            } while (!isSeatValid(seat));

            do {
                cout << FIND_PASSENGER_PROMPT;
                getline(cin, passengerName);
            } while (!isPassengerNameValid(passengerName));

            cout << endl;

            if (assignSeat(seat, passengerName, seatRow1, seatRow2, seatRow3, seatRow4)) {
                dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                cout << passengerName << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
            }
            else {
                dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                cout << passengerName << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
            }

            cout << endl;

            displayShortMenu();

            break;

        case MENU_REMOVE_PASSENGER:
            cout << FIND_PASSENGER_PROMPT;
            getline(cin, passengerName);

            seat = findPassenger(passengerName, seatRow1, seatRow2, seatRow3, seatRow4);

            if (seat != EMPTY_SEAT) {
                if (releaseSeat(seat, seatRow1, seatRow2, seatRow3, seatRow4)) {
                    dashLine((passengerName + REMOVED_PASSENGER_MESSAGE + seat).length());
                    cout << passengerName << REMOVED_PASSENGER_MESSAGE << seat << endl;
                    dashLine((passengerName + REMOVED_PASSENGER_MESSAGE + seat).length());
                }
                else {
                    dashLine((passengerName + NOT_REMOVED_PASSENGER_MESSAGE + seat).length());
                    cout << passengerName << NOT_REMOVED_PASSENGER_MESSAGE << seat << endl;
                    dashLine((passengerName + NOT_REMOVED_PASSENGER_MESSAGE + seat).length());
                }
            }
            else {
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
                cout << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
            }

            cout << endl;

            displayShortMenu();

            break;


        
        case MENU_MOVE_PASSENGER: // Creating menu to move a passenger.
            cout << FIND_PASSENGER_PROMPT; // Display prompt for user input about passenger information.
            getline(cin, passengerNameToMove); // Allow for input into passenger name string. 

            oldSeat = findPassenger(passengerNameToMove, seatRow1, seatRow2, seatRow3, seatRow4); // Determines what seat the passenger to be moved is sitting in.

             

            if (oldSeat != EMPTY_SEAT) { // If the passenger has not been succesfully removed from a seat.
                do {
                    cout << SEAT_PROMPT; // Output a message asking for the user to input a new seat.
                    getline(cin, newSeat); // Allow for input of a new seat.

                } while (!isSeatValid(newSeat)); // Run when the selection is not valid for new seat is not valid.

                cout << endl;

                passengerName = showOccupant(newSeat, seatRow1, seatRow2, seatRow3, seatRow4); // Displays passenger name with new seat information. 

            

                if (passengerName == EMPTY_SEAT) { // Runs when the passenger has succesfully been removed from a seat.
                    if (releaseSeat(oldSeat, seatRow1, seatRow2, seatRow3, seatRow4)) { // If the seat has been released.
                        dashLine((passengerNameToMove + REMOVED_PASSENGER_MESSAGE + oldSeat).length()); // Display that the passenger has been removed from the seat.
                        cout << passengerNameToMove << REMOVED_PASSENGER_MESSAGE << oldSeat << endl; 
                        dashLine((passengerNameToMove + REMOVED_PASSENGER_MESSAGE + oldSeat).length());
                    }
                    else { // If unsuccesful
                        dashLine((passengerNameToMove + NOT_REMOVED_PASSENGER_MESSAGE + oldSeat).length()); // Display message that passenger is not removed from seat.
                        cout << passengerNameToMove << NOT_REMOVED_PASSENGER_MESSAGE << oldSeat << endl;
                        dashLine((passengerNameToMove + NOT_REMOVED_PASSENGER_MESSAGE + oldSeat).length());
                    }
                    cout << endl;

                    if (assignSeat(newSeat, passengerNameToMove, seatRow1, seatRow2, seatRow3, seatRow4)) { // Runs when passenger has succesfully been assigned new seat.
                        dashLine((passengerNameToMove + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length()); // Displays message stating success and new seat number.
                        cout << passengerNameToMove << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(newSeat) << endl;
                        dashLine((passengerNameToMove + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length());
                    }
                    else {
                        dashLine((passengerNameToMove + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length()); // Runs when passenger assignment is unsuccesful.
                        cout << passengerNameToMove << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(newSeat) << endl; // Displays message stating lack of success.
                        dashLine((passengerNameToMove + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length());
                    }
                }
                else {
                    dashLine((passengerNameToMove + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length()); // Runs when assignment is unsuccesful.
                    cout << passengerNameToMove << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(newSeat) << endl; // Displays lack of success.
                    dashLine((passengerNameToMove + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(newSeat)).length());
                }
            }
            else {
                dashLine((passengerNameToMove + NOT_FOUND_PASSENGER_MESSAGE).length()); // Displays when passenger name is not found.
                cout << passengerNameToMove << NOT_FOUND_PASSENGER_MESSAGE << endl;
                dashLine((passengerNameToMove + NOT_FOUND_PASSENGER_MESSAGE).length());
            }
                

            cout << endl;

            displayShortMenu;

            break;


        
        
        case MENU_REQUEST_WINDOW: // Menu to request a window seat.
            
            seat = requestWindowAisle(MENU_REQUEST_WINDOW, seatRow1, seatRow2, seatRow3, seatRow4); // Assign seat to window or aisle
         

            if (seat != EMPTY_SEAT) { // If the seat is not empty
                dashLine((seat + WINDOW_SEATS_AVAILABLE_MESSAGE).length()); // Display which seats are available by the window.
                cout << seat << WINDOW_SEATS_AVAILABLE_MESSAGE << endl;
                dashLine((seat + WINDOW_SEATS_AVAILABLE_MESSAGE).length());

                cout << endl;

                do {
                    cout << FIND_PASSENGER_PROMPT; // Request user input for passenger name
                    getline(cin, passengerName);
                } while (!isPassengerNameValid(passengerName)); // if the passenger name is not valid, do above.

                cout << endl;

                if (assignSeat(seat, passengerName, seatRow1, seatRow2, seatRow3, seatRow4)) { // If the seat has been assigned
                    dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length()); // Display message stating seat assigned succesfully.
                    cout << passengerName << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                    dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                }
                else {
                    dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length()); // Otherwise state message stating lack of success.
                    cout << passengerName << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                    dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                }
            }
            else {
                dashLine(NO_WINDOW_SEATS_AVAILABLE_MESSAGE.length()); // If no seats are available by window, state this.
                cout << NO_WINDOW_SEATS_AVAILABLE_MESSAGE << endl;
                dashLine(NO_WINDOW_SEATS_AVAILABLE_MESSAGE.length());
            }

            cout << endl;

            displayShortMenu();

            break;
            

        case MENU_REQUEST_AISLE: // Menu to request an aisle seat.

            seat = requestWindowAisle(MENU_REQUEST_AISLE, seatRow1, seatRow2, seatRow3, seatRow4); // Assign seat to window or aisle

             

            if (seat != EMPTY_SEAT) {
                dashLine((seat + AISLE_SEATS_AVAILABLE_MESSAGE).length());
                cout << seat << AISLE_SEATS_AVAILABLE_MESSAGE << endl;
                dashLine((seat + AISLE_SEATS_AVAILABLE_MESSAGE).length());

                cout << endl;

                do {
                    cout << FIND_PASSENGER_PROMPT; // Request user input for passenger name
                    getline(cin, passengerName);
                } while (!isPassengerNameValid(passengerName)); // if the passenger name is not valid, do above.

                cout << endl;

                if (assignSeat(seat, passengerName, seatRow1, seatRow2, seatRow3, seatRow4)) { // If the seat has been assigned
                    dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length()); // Display message stating seat assigned succesfully.
                    cout << passengerName << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                    dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                }
                else {
                    dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length()); // Otherwise state message stating lack of success.
                    cout << passengerName << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << upperCase(seat) << endl;
                    dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + upperCase(seat)).length());
                }
            }
            else {
                dashLine(NO_AISLE_SEATS_AVAILABLE_MESSAGE.length()); // If no seats are available by window, state this.
                cout << NO_AISLE_SEATS_AVAILABLE_MESSAGE << endl;
                dashLine(NO_AISLE_SEATS_AVAILABLE_MESSAGE.length());
            }

            cout << endl;

            displayShortMenu();

            break;






        case MENU_EXIT_PROGRAM:
            exitProgram = true;
            break;

        case MENU_CLEAR_SCREEN:
            system(WINDOWS_CLEAR_SCREEN);
            displayFullMenu();
            break;

        default:
            cout << INVALID_CHOICE_ERROR_MESSAGE;

        }
    } while (!exitProgram);
}


void displayHeader()
{
    cout << endl;

    dashLine(DASH_LENGTH);

    cout << HEADER_TEXT << endl;

    dashLine(DASH_LENGTH);
}


void displayShortMenu()
{
    displayHeader();

    cout << MENU_CLEAR_SCREEN << CLEAR_SCREEN_MESSAGE << endl;
    cout << MENU_EXIT_PROGRAM << EXIT_PROGRAM_MESSAGE << endl;
    cout << endl;
    cout << ENTER_CHOICE_MESSAGE;
}


void displayFullMenu()
{
    displayHeader();

    cout << MENU_CREATE_MANIFEST << CREATE_MANIFEST_MESSAGE << endl;
    cout << MENU_CREATE_SEATING_CHART << CREATE_SEATING_CHART_MESSAGE << endl;
    cout << MENU_FIND_PASSENGER << FIND_PASSENGER_MESSAGE << endl;
    cout << MENU_SHOW_OCCUPANT << SHOW_OCCUPANT_MESSAGE << endl;
    cout << MENU_ASSIGN_SEAT << ASSIGN_SEAT_MESSAGE << endl;
    cout << MENU_REMOVE_PASSENGER << REMOVE_PASSENGER_MESSAGE << endl;
    cout << MENU_MOVE_PASSENGER << MOVE_PASSENGER_MESSAGE << endl;
    cout << MENU_REQUEST_WINDOW << REQUEST_WINDOW_MESSAGE << endl;
    cout << MENU_REQUEST_AISLE << REQUEST_AISLE_MESSAGE << endl;
    dashLine(DASH_LENGTH);
    cout << MENU_EXIT_PROGRAM << EXIT_PROGRAM_MESSAGE << endl;
    dashLine(DASH_LENGTH);
    cout << endl;
    cout << MENU_CLEAR_SCREEN << CLEAR_SCREEN_MESSAGE << endl;
    cout << endl;
    cout << ENTER_CHOICE_MESSAGE;
}


char getMenuChoice()
{
    char choice;

    cin >> choice;
    cin.ignore();

    cout << endl << endl;

    return choice;
}


void createManifest(string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    cout << left;
    cout << setw(DISPLAY_WIDTH_CM) << PASSENGER_HEADING << setw(DISPLAY_WIDTH_CM) << SEAT_HEADING << endl;

    dashLine(DISPLAY_WIDTH_CM * NUM_DISPLAY_COLS_CM);

    cout << endl;

    string seat = "";

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
        if (seatRow1[letter] != EMPTY_SEAT) {
            seat = "01" + string(1, SEAT_TYPE_INDEX[letter]);
            cout << setw(DISPLAY_WIDTH_CM) << seatRow1[letter] << setw(DISPLAY_WIDTH_CM) << seat << endl;
        }

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
        if (seatRow2[letter] != EMPTY_SEAT) {
            seat = "02" + string(1, SEAT_TYPE_INDEX[letter]);
            cout << setw(DISPLAY_WIDTH_CM) << seatRow2[letter] << setw(DISPLAY_WIDTH_CM) << seat << endl;
        }

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
        if (seatRow3[letter] != EMPTY_SEAT) {
            seat = "03" + string(1, SEAT_TYPE_INDEX[letter]);
            cout << setw(DISPLAY_WIDTH_CM) << seatRow3[letter] << setw(DISPLAY_WIDTH_CM) << seat << endl;
        }

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
        if (seatRow4[letter] != EMPTY_SEAT) {
            seat = "04" + string(1, SEAT_TYPE_INDEX[letter]);
            cout << setw(DISPLAY_WIDTH_CM) << seatRow4[letter] << setw(DISPLAY_WIDTH_CM) << seat << endl;
        }

    dashLine(DISPLAY_WIDTH_CM * NUM_DISPLAY_COLS_CM);
    cout << endl;
}


void createSeatingChart(string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    cout << left;
    cout << setw(DISPLAY_WIDTH_CSC) << " ";

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
        cout << setw(DISPLAY_WIDTH_CSC) << SEAT_TYPE_INDEX[letter];

    cout << endl;

    dashLine(DISPLAY_WIDTH_CSC * NUM_DISPLAY_COLS_CSC);

    cout << endl;

    cout << setw(DISPLAY_WIDTH_CSC) << ROW_HEADING + "1" + ROW_HEADING_SUFFIX;

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++) {
        cout << setw(DISPLAY_WIDTH_CSC) << seatRow1[letter];
    }

    cout << endl;

    cout << setw(DISPLAY_WIDTH_CSC) << ROW_HEADING + "2" + ROW_HEADING_SUFFIX;

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++) {
        cout << setw(DISPLAY_WIDTH_CSC) << seatRow2[letter];
    }

    cout << endl;

    cout << setw(DISPLAY_WIDTH_CSC) << ROW_HEADING + "3" + ROW_HEADING_SUFFIX;

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++) {
        cout << setw(DISPLAY_WIDTH_CSC) << seatRow3[letter];
    }

    cout << endl;

    cout << setw(DISPLAY_WIDTH_CSC) << ROW_HEADING + "4" + ROW_HEADING_SUFFIX;

    for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++) {
        cout << setw(DISPLAY_WIDTH_CSC) << seatRow4[letter];
    }

    cout << endl;

    dashLine(DISPLAY_WIDTH_CSC * NUM_DISPLAY_COLS_CSC);

    cout << endl;
}

string findPassenger(string passengerName, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    string seat = EMPTY_SEAT;
    bool found = false;
    int letter;

    passengerName = upperCase(passengerName);

    letter = 0;
    while (!found && letter < NUM_SEAT_LETTERS) {
        if (upperCase(seatRow1[letter]) == passengerName) {
            seat = "01" + string(1, SEAT_TYPE_INDEX[letter]);
            found = true;
        }
        letter++;
    }

    letter = 0;
    while (!found && letter < NUM_SEAT_LETTERS) {
        if (upperCase(seatRow2[letter]) == passengerName) {
            seat = "02" + string(1, SEAT_TYPE_INDEX[letter]);
            found = true;
        }
        letter++;
    }

    letter = 0;
    while (!found && letter < NUM_SEAT_LETTERS) {
        if (upperCase(seatRow3[letter]) == passengerName) {
            seat = "03" + string(1, SEAT_TYPE_INDEX[letter]);
            found = true;
        }
        letter++;
    }

    letter = 0;
    while (!found && letter < NUM_SEAT_LETTERS) {
        if (upperCase(seatRow4[letter]) == passengerName) {
            seat = "04" + string(1, SEAT_TYPE_INDEX[letter]);
            found = true;
        }
        letter++;
    }

    return seat;
}


string showOccupant(string seat, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    string passengerName = EMPTY_SEAT;

    seat = upperCase(seat);

    string rowNum = seat.substr(0, 2);
    int letterIndex = seat.at(2) - LETTER_OFFSET;

    if (rowNum == "01") {
        passengerName = seatRow1[letterIndex];
    }

    else if (rowNum == "02") {
        passengerName = seatRow2[letterIndex];
    }

    else if (rowNum == "03") {
        passengerName = seatRow3[letterIndex];
    }

    else if (rowNum == "04") {
        passengerName = seatRow4[letterIndex];
    }

    return passengerName;
}


bool assignSeat(string seat, string passengerName, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    bool assignSeatOK = false;

    seat = upperCase(seat);

    string rowNum = seat.substr(0, 2);
    int letterIndex = seat.at(2) - LETTER_OFFSET;

    if (rowNum == "01") {
        if (seatRow1[letterIndex] == EMPTY_SEAT) {
            seatRow1[letterIndex] = passengerName;
            assignSeatOK = true;
        }
    }

    else if (rowNum == "02") {
        if (seatRow2[letterIndex] == EMPTY_SEAT) {
            seatRow2[letterIndex] = passengerName;
            assignSeatOK = true;
        }
    }

    else if (rowNum == "03") {
        if (seatRow3[letterIndex] == EMPTY_SEAT) {
            seatRow3[letterIndex] = passengerName;
            assignSeatOK = true;
        }
    }

    else if (rowNum == "04") {
        if (seatRow4[letterIndex] == EMPTY_SEAT) {
            seatRow4[letterIndex] = passengerName;
            assignSeatOK = true;
        }
    }

    return assignSeatOK;
}


bool releaseSeat(string seat, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{
    bool releaseSeatOK = true;

    seat = upperCase(seat);

    string rowNum = seat.substr(0, 2);
    int letterIndex = seat.at(2) - LETTER_OFFSET;

    if (rowNum == "01") {
        seatRow1[letterIndex] = EMPTY_SEAT;
    }

    else if (rowNum == "02") {
        seatRow2[letterIndex] = EMPTY_SEAT;
    }

    else if (rowNum == "03") {
        seatRow3[letterIndex] = EMPTY_SEAT;
    }

    else if (rowNum == "04") {
        seatRow4[letterIndex] = EMPTY_SEAT;
    }

    return releaseSeatOK;
}

string requestWindowAisle(int seatType, string seatRow1[], string seatRow2[], string seatRow3[], string seatRow4[])
{



    bool requestOK = false; // Set requestOK variable, defaults to "false".

    int letter = 0; // Sets variable letter with a value of "0"

    string seat = EMPTY_SEAT; // Creates string "seat" which defaults to "empty".

    switch (seatType) { // Function to switch seat types

    case MENU_REQUEST_WINDOW: // Create menu for requesting window seat.
        while (!requestOK && letter < NUM_WINDOW_SEAT_LETTERS) { // Runs when the request is not OK, and there are available window seats.
            if (upperCase(seatRow1[WINDOW_SEAT_INDEX[letter]]) == EMPTY_SEAT) { // Checks for seat in 1st row.
                seat = "01" + string(1, SEAT_TYPE_INDEX[WINDOW_SEAT_INDEX[letter]]); // Assigns seat if one is available.
                requestOK = true; // Request is changed to OK.
            }
            else if (upperCase(seatRow2[WINDOW_SEAT_INDEX[letter]]) == EMPTY_SEAT) { // Checks for seat in 2nd row.
                seat = "02" + string(1, SEAT_TYPE_INDEX[WINDOW_SEAT_INDEX[letter]]); // Assigns seat if one is available.
                requestOK = true; // Request is changed to OK.
            }
            else if (upperCase(seatRow3[WINDOW_SEAT_INDEX[letter]]) == EMPTY_SEAT) { // Checks for seat in 3rd row.
                seat = "03" + string(1, SEAT_TYPE_INDEX[WINDOW_SEAT_INDEX[letter]]); // Assigns seat if one is available.
                requestOK = true; // Request is changed to OK.
            }
            else if (upperCase(seatRow4[WINDOW_SEAT_INDEX[letter]]) == EMPTY_SEAT) { // Checks for seat in 4th row.
                seat = "04" + string(1, SEAT_TYPE_INDEX[WINDOW_SEAT_INDEX[letter]]); // Assigns seat if one is available.
                requestOK = true; // Request is changed to OK.
            }
            letter++; // The value of the seat is assigned.
        }
        break; // Terminate the loop.

    case MENU_REQUEST_AISLE:
        while (!requestOK && letter < NUM_AISLE_SEAT_LETTERS) {
            if (upperCase(seatRow1[AISLE_SEAT_INDEX[letter]]) == EMPTY_SEAT) {
                seat = "01" + string(1, SEAT_TYPE_INDEX[AISLE_SEAT_INDEX[letter]]);
                requestOK = true; // Request is changed to OK.
            } 
            else if (upperCase(seatRow2[AISLE_SEAT_INDEX[letter]]) == EMPTY_SEAT) {
                seat = "02" + string(1, SEAT_TYPE_INDEX[AISLE_SEAT_INDEX[letter]]);
                requestOK = true; // Request is changed to OK.
            }
            else if (upperCase(seatRow3[AISLE_SEAT_INDEX[letter]]) == EMPTY_SEAT) {
                seat = "03" + string(1, SEAT_TYPE_INDEX[AISLE_SEAT_INDEX[letter]]);
                requestOK = true; // Request is changed to OK.
            }
            else if (upperCase(seatRow4[AISLE_SEAT_INDEX[letter]]) == EMPTY_SEAT) {
                seat = "04" + string(1, SEAT_TYPE_INDEX[AISLE_SEAT_INDEX[letter]]);
                requestOK = true; // Request is changed to OK.
            }
            letter++; // The value of the seat is assigned.
        }
        break; // Terminate the loop.

    }

    return seat; // Display the assigned seat to user.
}
void dashLine(size_t lineLength)
{
    for (size_t x = 0; x < lineLength; x++)
        cout << REPEAT_CHAR;

    cout << endl;
}


string upperCase(string string2Upper)
{
    string stringUpperCased;

    for (size_t x = 0; x < string2Upper.length(); x++) {
        stringUpperCased += toupper(string2Upper[x]);
    }

    return stringUpperCased;
}


bool isSeatValid(string seat)
{
    bool validSeat = true;

    if (seat.length() != (SEAT_STR_ROW_NUM_DIGITS + SEAT_STR_LETTER_NUM_CHARS)) {
        cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LENGTH_MESSAGE << ERROR_MESSAGE_PREFIX << endl << endl;
        validSeat = false;
    }
    else {
        for (int x = 0; x < SEAT_STR_ROW_NUM_DIGITS; x++) {
            if (!isdigit(seat[x]))
                validSeat = false;
        }
        if (!validSeat) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_NON_NUMERIC_MESSAGE << ERROR_MESSAGE_PREFIX << endl << endl;
        }
    }

    string seatTypeIndexStr = string(SEAT_TYPE_INDEX);

    if (validSeat) {

        if (stoi(seat.substr(SEAT_STR_ROW_START_POS, SEAT_STR_ROW_NUM_DIGITS - SEAT_STR_ROW_START_POS)) < SEAT_ROWS_START) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_OUT_OF_RANGE_LOWER_MESSAGE << SEAT_ROWS_START << ERROR_MESSAGE_PREFIX << endl << endl;
            validSeat = false;
        }
        else if (stoi(seat.substr(SEAT_STR_ROW_START_POS, SEAT_STR_ROW_NUM_DIGITS - SEAT_STR_ROW_START_POS)) > NUM_SEAT_ROWS) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_OUT_OF_RANGE_UPPER_MESSAGE << NUM_SEAT_ROWS << ERROR_MESSAGE_PREFIX << endl << endl;
            validSeat = false;
        }
        else if (!isalpha(seat[SEAT_STR_LETTER_START_POS])) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LETTER_NON_ALPHABETIC << ERROR_MESSAGE_PREFIX << endl << endl;
            validSeat = false;
        }
        else if (seatTypeIndexStr.find(toupper(seat[SEAT_STR_LETTER_START_POS])) == string::npos) {

            // Zero and one based indexing.
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LETTER_OUT_OF_RANGE << SEAT_TYPE_INDEX[0] << "-" << SEAT_TYPE_INDEX[NUM_SEAT_LETTERS - 1] \
                << ERROR_MESSAGE_PREFIX << endl << endl;
            validSeat = false;
        }
        else
            seat[SEAT_STR_LETTER_START_POS] = toupper(seat[SEAT_STR_LETTER_START_POS]);
    }

    return validSeat;
}

bool isPassengerNameValid(string passengerName) {

    bool validPassengerName = true;

    if (passengerName.find_first_not_of(" ") == passengerName.npos) {
        cout << endl << INVALID_PASSENGER_NAME_MESSAGE << endl << endl;
        validPassengerName = false;
    }

    return validPassengerName;
}