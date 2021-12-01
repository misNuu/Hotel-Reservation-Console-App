#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

const int MAX_ROOMS = 5;
const int MAX_GUESTS = MAX_ROOMS; // Max number of guests is the same as max rooms since double sized rooms are reserved for one name/person only

struct Guest {
	string fullName;
	string address;
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

	room.roomsCount = 2 * (rand() % MAX_ROOMS + 1) ; // Generate an even room count between 40 - 300

	for (int i = 0; i <= room.roomsCount; i++) { // Initialize all rooms as available
		room.roomsAvailability.push_back(1);
	}

	cout << "Generated a total of " << room.roomsCount << " rooms!" << endl << endl;

	return room;
}

void MainMenu(Room &room)
{
	Guest guests[300];
	int userChoice;
	//room.roomsAvailability[3] = 0;
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
			cout << "------------------------------------------------" << endl;
			cout << "Type\t\tPrice ($/night)" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Single\t\t100" << endl;
			cout << "Double\t\t150" << endl;
			cout << "------------------------------------------------" << endl;
			break;
		case 3:
			cout << "Room number\tName\t\t\tAddress\t\t\tID" << endl;
			for (int i = 0; i < MAX_GUESTS; i++) {
				cout << guests[i].roomNumber << "\t\t" << guests[i].fullName << "\t\t" << guests[i].address << "\t\t" << guests[i].reservationId << endl;
			}
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

void ReservationMenu(Room &room, Guest guests[])
{
	static int i = 0; 
	bool roomIsAvailable;
	cout << "We currently have a total of " << CountHowManyAvailable(room) << " rooms available for you." << endl;
	
	cout << "Enter a room number that you would like to reserve" << endl << "Rooms 1 to " << room.roomsCount / 2 << " are for a single person";
	cout << " and rooms " << room.roomsCount / 2 + 1 << " to " << room.roomsCount << " are for two people" << endl;
	cin >> guests[i].roomNumber;

	roomIsAvailable = isAvailable(room, guests[i].roomNumber);

	do {
		if (roomIsAvailable)
		{
			cout << endl << "How many nights would you like to stay?: " << endl;
			cin >> guests[i].howManyNights;
		
			cout << endl << "Enter your full name: " << endl;
			cin.ignore(); 
			getline(cin, guests[i].fullName);

			cout << endl << "Enter your address: " << endl;
			//cin.ignore();
			getline(cin, guests[i].address);

			guests[i].reservationId = rand() % 99999 + 1000; // Generate a reservation id for the guest between 10000 - 99999

			room.roomsAvailability[guests[i].roomNumber] = 0; // Mark room as reserved by inserting a value of 0 (false)
	
			if (guests[i].roomNumber <= room.roomsCount / 2)
			{
				guests[i].totalBill = guests[i].howManyNights * room.singleRoomPrice;
			}
			else if (guests[i].roomNumber > room.roomsCount / 2) {
				guests[i].totalBill = guests[i].howManyNights * room.doubleRoomPrice;
			}

			cout << endl << "Room reserved succesfully for: " << guests[i].fullName << endl;
			cout << "Total bill: " << guests[i].totalBill << endl;
			cout << "------------------------------------------------" << endl;
			break;
		}
		else {
			cout << endl << "Selected room is already reserved! Try another one." << endl;
		}
	} while (roomIsAvailable);

	i+=1; // Iterate index by 1 everytime this function is called, so next guest will be stored in next index in the array
}
