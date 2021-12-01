#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

const int MAX_ROOMS = 2;
const int MAX_GUESTS = MAX_ROOMS; // Max number of guests is the same as max rooms since double sized rooms are reserved for one name/person only

struct Guest {
	string fullName;
	int phoneNum = 0;
	int reservationId = 0;
	int roomNumber = 0;
	int howManyNights = 0;
	float totalBill = 0.0;
};

struct Room {
	vector<bool> roomsAvailability;
	int roomsCount = 0;
	int singleRoomPrice = 100;
	int doubleRoomPrice = 150;
	int howManyNights = 0;
};

// Function prototypes
Room GenerateRooms();
void MainMenu(Room&);
void PrintMenuChoices();
void ReservationMenu(Room&, Guest[MAX_GUESTS]); 
bool isAvailable(Room&);
int CountHowManyAvailable(Room&);
// Used for all integer inputs, handles errors
int IntInput();

// Generates discount based on random number
float Discount(float bill);

int main()
{
	cout << "Welcome to the hotel room reservation program!" << endl << endl;
	Room room = GenerateRooms();

	MainMenu(room);

	return 0;
}

int IntInput()
{
	int choice = 0;

	cin >> choice;
	while (!cin.good()) {
		cout << "Incorrect input. Try again: ";

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cin >> choice;
	}

	return choice;
}

Room GenerateRooms()
{
	Room room;

	srand(time(0));

	room.roomsCount = 2 * (rand() % MAX_ROOMS + 1) ; // Generate an even room count between 40 - 300

	for (int i = 0; i <= room.roomsCount; i++) { // Initialize all rooms as available
		room.roomsAvailability.push_back(1);
	}


	cout << "Generated a total of " << room.roomsCount << " rooms!" << endl << endl;

	return room;
}

void MainMenu(Room &room)
{
	Guest guests[MAX_GUESTS];
	int userChoice;
	do {
		PrintMenuChoices();
		cout << endl << "Your choice: ";
		userChoice = IntInput();

		switch (userChoice)
		{
		case 1:
			cout << "------------------------------------------------" << endl;
			ReservationMenu(room, guests);
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
			cout << "Room number\tName\t\t\tPhone\t\t\tID" << endl;
			for (int i = 0; i < MAX_GUESTS; i++) {
				cout << guests[i].roomNumber << "\t\t" << guests[i].fullName << "\t\t" << guests[i].phoneNum << "\t\t" << guests[i].reservationId << endl;
			}
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

void PrintMenuChoices()
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

int CountHowManyAvailable(Room &room)
{
	int totalCount = 0;

	for (int i = 0; i < room.roomsCount; i++) {
		if (room.roomsAvailability[i] == 1) {
			totalCount += 1;
		}
	}

	return totalCount;
}

void ReservationMenu(Room& room, Guest guests[])
{
	static int i = 0;
	bool roomIsAvailable;
	float bill = 0;
	int choice;
	int roomNumber = 0;
	room.roomsAvailability[1] = 0;

	cout << "We have a total of " << room.roomsCount << " rooms. Of which " << CountHowManyAvailable(room) << " are available right now!" << endl;
	cout << "Rooms 1 - " << room.roomsCount / 2 << " are for a single person (single rooms)" << endl << "Rooms " << room.roomsCount / 2 + 1 << " - " << room.roomsCount << " are for two people (double rooms)" << endl << endl;
	cout << "You can choose a room yourself or we can choose for you. What would you like to do?" << endl << "1. Let us choose for you" << endl << "2. I'll pick myself" << endl;
	
	cout << endl << "Your choice: ";
	choice = IntInput();

	switch (choice) {
		case 1:
			roomNumber = rand() % room.roomsCount + 1; // Generates a room number
			cout << "We picked room number " << roomNumber << " for you." << endl;
			break;
		case 2:
			do {
				cout << "Enter a room number that you would like to reserve: ";
				choice = IntInput();
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
			choice = IntInput();
			guests[i].howManyNights = choice;
		
			cout << endl << "Enter your full name: ";
			cin.ignore(); 
			getline(cin, guests[i].fullName);

			cout << endl << "Enter your phone number: ";
			choice = IntInput();
			guests[i].phoneNum = choice;

			guests[i].roomNumber = roomNumber;

			guests[i].reservationId = rand() % 99999 + 10000; // Generate a reservation id for the guest
	
			if (guests[i].roomNumber <= room.roomsCount / 2)
			{
				bill = guests[i].howManyNights * room.singleRoomPrice;
			}
			else if (guests[i].roomNumber > room.roomsCount / 2) {
				bill = guests[i].howManyNights * room.doubleRoomPrice;
			}
			guests[i].totalBill = Discount(bill); // Checks if discount will be applied to total price

			room.roomsAvailability[guests[i].roomNumber] = 0; // Mark room as reserved by inserting a value of 0 (false)

			cout << endl << "Room number " << guests[i].roomNumber << " reserved succesfully for: " << guests[i].fullName << endl;
			cout << "Total bill: " << guests[i].totalBill << " $" << endl;
			cout << "------------------------------------------------" << endl;
	}
	else {
		cout << endl << "That room is already reserved! Try again." << endl << endl;
	}
	
	

	i+=1; // Iterate index by 1 everytime this function is called, so next guest will be stored in next index in the array
}

float Discount(float bill)
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