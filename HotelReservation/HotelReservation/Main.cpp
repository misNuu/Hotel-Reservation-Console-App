#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

struct Guest {
	string fullName;
	int reservationId = 0;
	int roomNumber = 0;
	int howManyNights = 0;
};

struct Room {

	vector<bool> roomsAvailability;
	int roomsCount = 0;
	int singleRoomPrice = 100;
	int doubleRoomPrice = 150;
	int howManyNights = 0;
	float discount = 0;
};

// Function prototypes
Room GenerateRooms();
void MainMenu(Room&);
void PrintMenuChoices();
void ReservationMenu(Room&, Guest[300]);
bool isAvailable(Room&);
int CountHowManyAvailable(Room&);

int main()
{
	cout << "Welcome to the hotel room reservation program!" << endl << endl;
	Room room = GenerateRooms();

	MainMenu(room);

	return 0;
}

Room GenerateRooms()
{
	Room room;

	srand(time(0));

	room.roomsCount = 2 * (rand() % 100 + 40) ; // Generate an even room count between 40 - 300

	for (int i = 0; i < room.roomsCount; i++) { // Initialize all rooms as available
		room.roomsAvailability.push_back(1);
	}

	cout << "Generated a total of " << room.roomsCount << " rooms!" << endl << endl;

	return room;
}

void MainMenu(Room &room)
{
	Guest guests[300];
	int userChoice;
	room.roomsAvailability[3] = 0;
	do {
		PrintMenuChoices();

		cin >> userChoice;

		switch (userChoice)
		{
		case 1:
			cout << "------------------------------------------------" << endl;
			ReservationMenu(room, guests);
			break;
		case 2:
			// Search reservations
		case 3:
			cout << guests[0].fullName;
			break;
		case 4:
			cout << "Exiting program..." << endl;
			break; // Exit
		}

	} while (userChoice != 4);
}

void PrintMenuChoices()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Reserve a room" << endl;
	cout << "2. Search room reservations" << endl;
	cout << "3. Testing" << endl;
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
	int singleCount = 0;
	int doubleCount = 0;

	for (int i = room.roomsCount / 2; i < room.roomsCount; i++) { // Count how many double rooms are available
		if (room.roomsAvailability[i] == 1) {
			doubleCount += 1;
		}
	}

	for (int i = room.roomsCount / 2; i > 0; i--) { // Count how many single rooms are available
		if (room.roomsAvailability[i] == 1) {
			singleCount += 1;
		}
	}

	totalCount = singleCount + doubleCount;

	return totalCount;
}

void ReservationMenu(Room &room, Guest guests[])
{
	int i = 0; i += 1; // For multiple guests
	string name;
	int userChoice;
	bool roomIsAvailable;
	cout << "We currently have a total of " << CountHowManyAvailable(room) << " rooms available for you." << endl;
	
	cout << "Enter a room number that you would like to reserve or type draw to draw a random number" << endl << "Rooms 1 to " << room.roomsCount / 2 << " are for a single person";
	cout << " and rooms " << room.roomsCount / 2 + 1 << " to " << room.roomsCount << " are for two people" << endl;
	cin >> guests[i].roomNumber;
	roomIsAvailable = isAvailable(room, guests[i].roomNumber);

	do {
		if (roomIsAvailable)
		{
			cout << endl << "For how many nights would you like to stay?" << endl;
			cin >> guests[i].howManyNights;
		
			cout << endl << "Enter your full name (Name Surname)" << endl;
			cin.ignore(); 
			getline(cin, guests[i].fullName);



		}
		else {
			cout << endl << "Selected room is already reserved! Try another one." << endl;
			break;
		}
	} while (true);
}

void MakeReservation(Room& room, int userChoice)
{
	Guest guest;
	//guest.reservationId = 
	


	//cout << endl << userChoice;
}