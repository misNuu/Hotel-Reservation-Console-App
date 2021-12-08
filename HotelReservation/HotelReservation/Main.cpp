#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

const int MAX_ROOMS = 300;
const int MAX_GUESTS = MAX_ROOMS; // Max number of guests is the same as max rooms since double sized rooms are reserved for one name/person only

struct Guest {
	string fullName;
	int reservationId = 0;
	int roomNumber = 0;
	string roomType;
	int howManyNights = 0;
	int totalBill = 0;
};

struct Room {
	vector<bool> roomsAvailability;
	int roomsCount = 0;
	int singleRoomPrice = 100;
	int doubleRoomPrice = 150;
};

// Function prototypes
Room initializeRooms();
void mainMenu(Room&);
void printMenuChoices();
void reservationMenu(Room&, Guest[MAX_GUESTS]);
void searchReservations(Room&, Guest[MAX_GUESTS]);
bool isAvailable(Room&); // Checks if room is available for reservation
int countHowManyAvailable(Room&);
int intInput(); // Used for all integer inputs, handles errors
double discount(int bill); // Generates discount based on random number

int main()
{
	cout << R"(                _[]_  
 __[]___[]___[]/____\_[]_    )
/______________|[][]|____\  (
|[][]|[][]|[][]|[][]|[][]|__[]_
|  /\|/\  |  /\|  /\|/\  |_____\
|[]|||||[]|[]|||[]|||||[]|[_]|||
================================)" << endl;

	cout << "Welcome to the hotel room reservation program!" << endl << endl;
	Room room = initializeRooms();

	mainMenu(room);

	return 0;
}

int intInput()
{
	int choice = 0;

	cin >> choice;
	while (cin.fail()) {
		cout << endl << "Incorrect input! Try a number: ";

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cin >> choice;
	}

	return choice;
}

Room initializeRooms()
{
	Room room;

	srand(time(0));

	//room.roomsCount = 2 * (rand() % MAX_ROOMS + 1) ; // Generate an even room count between 40 - 300
	room.roomsCount = MAX_ROOMS;

	for (int i = 0; i <= room.roomsCount; i++) { // Initialize all rooms as available
		room.roomsAvailability.push_back(1);
	}

	//cout << "Generated a total of " << room.roomsCount << " rooms!" << endl << endl;

	return room;
}

void mainMenu(Room &room)
{
	Guest guests[MAX_GUESTS];
	int userChoice;
	do {
		printMenuChoices();
		cout << endl << "Your choice: ";
		userChoice = intInput();

		switch (userChoice)
		{
		case 1:
			cout << "------------------------------------------------" << endl;
			reservationMenu(room, guests);
			break;
		case 2:
			cout << "------------------------------------------------" << endl;
			cout << "Type\t\tPrice ($/night)" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Single\t\t100" << endl;
			cout << "Double\t\t150" << endl;
			cout << "------------------------------------------------" << endl;
			break;
		case 3:
			cout << "------------------------------------------------" << endl;
			searchReservations(room, guests);
			break;
		case 4:
			cout << "Exiting program..." << endl;
			break; // Exit
		default:
			cout << endl;
			cout << "Incorrect input! Enter a number between 1 - 4" << endl << endl;
		}

	} while (userChoice != 4);
}

void printMenuChoices()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Reserve a room" << endl;
	cout << "2. Check pricing" << endl;
	cout << "3. Search room reservations" << endl;
	cout << "4. Exit program" << endl;
}

bool isAvailable(Room &room, int roomNumber)
{
	if (room.roomsAvailability[roomNumber] == 1) {
		return true;
	}
	else {
		return false;
	}
}

int countHowManyAvailable(Room& room)
{
	int count = 0;
	for (int i = 1; i <= room.roomsCount; i++) {
		if (room.roomsAvailability[i] == 1) {
			count += 1;
		}
	}
	return count;
}

void reservationMenu(Room& room, Guest guests[])
{
	static int i = 0;
	bool roomIsAvailable;
	int bill = 0;
	int choice;
	int roomNumber = 0;
	int rnd;

	cout << "We have a total of " << countHowManyAvailable(room) << " room(s) free." << endl;
	cout << "Rooms 1 - " << room.roomsCount / 2 << " are for a single person (single rooms)" << endl << "Rooms " << room.roomsCount / 2 + 1 << " - " << room.roomsCount << " are for two people (double rooms)" << endl << endl;
	cout << "You can choose a room yourself or we can choose for you. What would you like to do?" << endl << "1. Let us choose for you" << endl << "2. I'll pick myself" << endl;

	cout << endl << "Your choice: ";
	choice = intInput();

	switch (choice) {
	case 1:
		// If generated room number is not available, generate a new one
		do {
			rnd = rand() % room.roomsCount + 1;
			roomIsAvailable = isAvailable(room, rnd);
			if (countHowManyAvailable(room) == 0) { // If no rooms are available, stop trying to generate a room number and break out of loop
				break;
			}
		} while (!roomIsAvailable);

		roomNumber = rnd;
		cout << "We picked room number " << roomNumber << " for you." << endl;
		break;
	case 2:
		do {
			cout << "Enter a room number that you would like to reserve: ";
			choice = intInput();
		} while (choice > room.roomsCount || choice <= 0);

		roomNumber = choice;
		break;
	default:
		cout << "Incorrect input! Enter a number between 1 - 2" << endl;
	}

	roomIsAvailable = isAvailable(room, roomNumber);

	if (roomIsAvailable)
	{
		cout << endl << "How many nights would you like to stay?: ";
		choice = intInput();
		guests[i].howManyNights = choice;

		cout << endl << "Enter your full name: ";
		//cin >> guests[i].fullName;
		cin.ignore();
		getline(cin, guests[i].fullName);

		guests[i].roomNumber = roomNumber;

		guests[i].reservationId = rand() % 99999 + 10000; // Generate a reservation id for guests

		if (guests[i].roomNumber <= room.roomsCount / 2)
		{
			bill = guests[i].howManyNights * room.singleRoomPrice;
		}
		else if (guests[i].roomNumber > room.roomsCount / 2) {
			bill = guests[i].howManyNights * room.doubleRoomPrice;
		}

		room.roomsAvailability[guests[i].roomNumber] = 0; // Mark room as reserved by inserting a value of 0 (false)

		cout << endl << "Room number " << guests[i].roomNumber << " reserved succesfully for: " << guests[i].fullName << endl;
		cout << "Reservation ID: " << guests[i].reservationId << endl;
		guests[i].totalBill = discount(bill); // Checks if a discount will be applied to total price
		cout << "Total bill: " << guests[i].totalBill << "$" << endl;
		cout << "------------------------------------------------" << endl;
	}
	else {
		cout << endl << "THAT ROOM IS ALREADY RESERVED! Try another one." << endl << endl;
		cout << "------------------------------------------------" << endl;
	}
	
	i+=1; // Iterate index by 1 everytime this function is called, so next guest will be stored in next index in the array
}

void searchReservations(Room& room, Guest guests[])
{
	int choice;
	bool found;
	int count = 0;

	cout << "You can search reservations either by name or by reservation ID." << endl;
	cout << "What would you like to to?" << endl << "1. Search by reservation ID" << endl << "2. Search by name" << endl << endl;
	cout << "Your choice: ";
	choice = intInput();

	switch (choice)
	{
		case 1:
			int idToSearch;
			cout << "Enter reservation ID to search: ";
			idToSearch = intInput();

			for (int i = 0; i <= MAX_GUESTS; i++) { //Linear search for searching reservation names by reservation ID
				if (idToSearch == guests[i].reservationId) {
					cout << endl << "Name\t\t\t" << "Room\t\t" << "Bill\t\t" << "ID\t\t" << endl;
					count += 1;
					cout << guests[i].fullName << "\t\t" << guests[i].roomNumber << "\t\t" << guests[i].totalBill << "$" << "\t\t" << guests[i].reservationId << endl;
					found = true;
				}
				else if (count == 0) {
					found = false;
				}
			}
			if (!found) {
				cout << "Found no reservations for that ID!" << endl;
			}
			break;
		case 2:
			string nameToSearch;
			cout << "Enter a full name to search: ";
			cin.ignore();
			getline(cin, nameToSearch);

			for (int i = 0; i <= MAX_GUESTS; i++) { //Linear search for searching reservation names by reservation name
				if (nameToSearch == guests[i].fullName) {
					cout << endl << "Name\t\t\t" << "Room\t\t" << "Bill\t\t" << "ID\t\t" << endl;
					count += 1;
					cout << guests[i].fullName << "\t\t" << guests[i].roomNumber << "\t\t" << guests[i].totalBill << "$" << "\t\t" << guests[i].reservationId << endl;
					found = true;
				}
				else if (count == 0) {
					found = false;
				}
			}
			if (!found) {
				cout << "Found no reservations for that name!" << endl;
			}
			break;
	}
	
	cout << "------------------------------------------------" << endl;

}

double discount(int bill)
{
	int rnd = rand() % 3 + 1;
	if (rnd == 1) {
		cout << "You got a 10% discount!" << endl;
		return bill - (bill * 0.10); // 10 % discount
	}
	else if (rnd == 2) {
		cout << "You got a 20% discount!" << endl;
		return bill - (bill * 0.20); // 20 % discount
	}
	else {
		return bill;
	}
}