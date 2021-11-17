#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

struct Guest {
	string fullName;
	int reservationId = 0;
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
void Menu(Room&);
void PrintChoices();
void MakeReservation(Room&);
bool isAvailable(Room&);
void CheckHowManyAvailable(Room&);

int main()
{
	cout << "Welcome to the hotel room reservation program!" << endl << endl;
	Room room = GenerateRooms();

	Menu(room);

	return 0;
}

Room GenerateRooms()
{
	Room room;

	srand(time(0));

	room.roomsCount = rand() % 100 + 40 ; // Generate an even room count between 40 - 300

	for (int i = 0; i < room.roomsCount; i++) { // Initialize all rooms as available
		room.roomsAvailability.push_back(1);
	}

	cout << "Generated a total of " << room.roomsCount << " rooms!" << endl << endl;

	return room;
}

void Menu(Room &room)
{
	int userChoice;

	do {
		PrintChoices();

		cin >> userChoice;

		switch (userChoice)
		{
		case 1: 
			MakeReservation(room);
			break;
		case 2:
			break; // TODO: Search reservations
		case 3:
			//CheckAvailability(room);
			break;
		case 4:
			cout << "Exiting program..." << endl;
			break; // Exit
		}

	} while (userChoice != 4);
}

void PrintChoices()
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

void CheckHowManyAvailable(Room &room)
{
	int totalCount = 0;
	int singleCount = 0;
	int doubleCount = 0;

	/*for (int i = 0; i < room.roomsCount; i++) { // Count how many rooms are available in total
		if (room.roomsAvailability[i] == 1) {
			totalCount += 1;
		}
	}*/

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

	cout << "We have a total of " << totalCount<< " rooms available for you." << endl;
	cout << "Single rooms available: " << singleCount << endl;
	cout << "Double rooms available: " << doubleCount << endl;
	//return count;
}

void MakeReservation(Room &room)
{

	CheckHowManyAvailable(room);

	static int i = 0;
	i++;
	cout << i;
	room.roomsAvailability[i] = 0;
	//cout << "We have a total of " << CheckHowManyAvailable(room) << " rooms available for you." << endl;
	
}