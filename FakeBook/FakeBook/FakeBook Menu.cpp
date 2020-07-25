#include<iostream>
#include<string>
#include"FakeBook.h"
using namespace std;
void ADD_USER(FakeBook *F)
{
	string Name, LOC;
	char G;
	int age;
	cout << "\tEnter Name: ";
	cin >> Name;
	cout << "\tEnter Location: ";
	cin >> LOC;
	cout << "\tEnter Gender: ";
	cin >> G;
	cout << "\tEnter Age: ";
	cin >> age;
	FakeBookUser FU(Name, LOC, G, age);
	F->addUser(FU);
}

void REMOVE_USER(FakeBook *F)
{
	int id = { 0 };
	cout << "Enter ID: ";
	cin >> id;
	F->deleteUser(id);
}

void ADD_FRIEND(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tWho is sending friend request?" << endl;
	cout << "\tEnter ID of sender:";
	cin >> id1;
	cout << "\tTo whom you are sending friend request" << endl;
	cout << "\tEnter ID of Reciver: ";
	cin >> id2;
	if (!F->addFriend(id1, id2))
		cout << "\tID did Not Find" << endl;
	else
		cout << "\tSuccessfully Make Friend" << endl;
}

void REMOVE_FRIEND(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tEnter ID of User 1:";
	cin >> id1;
	cout << "\tEnter ID of User 2: ";
	cin >> id2;
	if (!F->removeFriend(id1, id2))
		cout << "\tID did Not Find" << endl;
	else
		cout << "\tSuccessfully Make Friend" << endl;
}

void MUTUAL_FRIENDS(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tEnter ID of First User: ";
	cin >> id1;
	cout << "\tEnter ID of Second User: ";
	cin >> id2;
	F->PrintAllMutualFriends(id1, id2);
}

void PrintAllUsersBetweenAges(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tEnter Lower Age:";
	cin >> id1;
	cout << "\tEnter Higher Age: ";
	cin >> id2;
	F->printAllUsersBetweenAges(id1, id2);
}

void PrintAllMalesBetweenAges(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tEnter Lower Age:";
	cin >> id1;
	cout << "\tEnter Higher Age: ";
	cin >> id2;
	F->printAllMalesBetweenAges(id1, id2);
}

void PrintAllFemalesBetweenAges(FakeBook *F)
{
	int id1 = { 0 }, id2 = { 0 };
	cout << "\tEnter Lower Age:";
	cin >> id1;
	cout << "\tEnter Higher Age: ";
	cin >> id2;
	F->printAllFemalesBetweenAges(id1, id2);
}

int main()
{
	string FileName;
	int NOF = { 0 }, x = { 0 }, id = { 0 };
	FakeBook *Fb = FakeBook::CreateFakeBookObject();
	char G;
	cout << "\t   WEL COME TO ABDULRAFAY's FACEBOOK " << endl;
	do
	{
		cout << "_______________________________________________________" << endl;
		cout << "\t\t   Enter 0 to Read File" << endl;
		cout << "\t      Enter 1 to Create New Account" << endl;
		cout << "\t\t  Enter 2 to ADD Friend" << endl;
		cout << "\t       Enter 3 to Display All Users " << endl;
		cout << "\t\tEnter 4 to Display Friends" << endl;
		cout << "\t     Enter 5 to Print Mutual Friends" << endl;
		cout << "\tEnter 6 to Print Profile of Suggested Friend" << endl;
		cout << "\t\t Enter 7 to REMOVE Friend" << endl;
		cout << "\t   Enter 8 to Print All Users Between Ages" << endl;
		cout << "\tEnter 9 to Print All Male Users Between Ages" << endl;
		cout << "      Enter 10 to Print All Female Users Between Ages" << endl;
		cout << "\t\tEnter 11 Delete Your Account" << endl;
		cout << "\t\t      Enter 12 to exit" << endl;
		cout << "_______________________________________________________" << endl;
		cout << "\t\t    Your Choice: ";
		cin >> x;
		switch (x)
		{
		case 0:
			cout << "\tEnter File Name: ";
			cin >> FileName;
			Fb->ReadFromFile(FileName);
			break;
		case 1:
			ADD_USER(Fb);
			break;
		case 2:
			ADD_FRIEND(Fb);
			break;
		case 3:
			Fb->printFakeBook();
			break;
		case 4:
			id = { 0 };
			cout << "\t  Enter ID: ";
			cin >> id;
			if (!Fb->PrintAllfriends(id))
				cout << "\t  ID NOT FOUND" << endl;
			break;
		case 5:
			MUTUAL_FRIENDS(Fb);
			break;
		case 6:
			id = { 0 };
			cout << "\t  Enter ID: ";
			cin >> id;
			Fb->PrintThreeMostLikelyPeopleIknow(id);
			break;
		case 7:
			REMOVE_FRIEND(Fb);
			break;
		case 8:
			PrintAllUsersBetweenAges(Fb);
			break;
		case 9:
			PrintAllMalesBetweenAges(Fb);
			break;
		case 10:
			PrintAllFemalesBetweenAges(Fb);
			break;
		case 11:
			REMOVE_USER(Fb);
			break;
		case 12:
			Fb->saveFakeBook(FileName);
		default:
			break;
		}

	} while (x != 12);
	Fb->DeleteFakeBook();
	return 0;
}