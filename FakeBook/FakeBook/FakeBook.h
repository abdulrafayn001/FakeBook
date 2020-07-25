#pragma once
#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class FakeBookUser
{
	class FakeBookUserInformation
	{
		static int GlobalUserIDCount;
		string name;
		int id; //this is the id shown in the picture above 
		string location;
		char gender;
		int age;
	public:

		FakeBookUserInformation(string N, string LOC, char G, int A)
		{

			name = N;
			id = GlobalUserIDCount++;
			location = LOC;
			gender = G;
			age = A;
		}
		bool operator==(const FakeBookUserInformation& FUI)
		{
			return this->id == FUI.id && this->name == FUI.name && this->location == FUI.location && this->gender == FUI.gender && this->age == FUI.age;
		}
		int GetGlobalUserIDCount()
		{
			return GlobalUserIDCount;
		}
		string GetName()
		{
			return name;
		}
		int Getid()
		{
			return id;
		}
		string GetLocation()
		{
			return location;
		}
		char GetGender()
		{
			return gender;
		}
		int GetAge()
		{
			return age;
		}
		void SetName(string N)
		{
			name = N;
		}
		void SetLocation(string LOC)
		{
			location = LOC;
		}
		void SetGender(char G)
		{
			gender = G;
		}
		void SetAge(int A)
		{
			age = A;
		}
		~FakeBookUserInformation()
		{

		}
		void PrintInformation()
		{
			cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "+                 PROFILE                 +" << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "\tName : " << name << endl;
			cout << "\tUser ID : " << id << endl;
			cout << "\tLocation : " << location << endl;
			cout << "\tGender : " << gender << endl;
			cout << "\tAge : " << age << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
		}
		friend ostream& operator<<(ostream&, FakeBookUserInformation &obj)
		{
			obj.PrintInformation();
			return cout << endl;
		}
	};
	FakeBookUserInformation  * UserData;
	list <FakeBookUser*> Friends;

public:
	FakeBookUser(string N, string LOC, char G, int A)
	{
		UserData = new FakeBookUserInformation(N, LOC, G, A);
	}
	void UpdateName(string NewName)
	{
		UserData->SetName(NewName);
	}
	void UpdateLocation(string NewLocation)
	{
		UserData->SetLocation(NewLocation);
	}
	void UpdateGender(char NewGender)
	{
		UserData->SetGender(NewGender);
	}
	void UpdateAge(int age)
	{
		UserData->SetAge(age);
	}
	int GetCurrentID()
	{
		return UserData->Getid();
	}
	bool isFriend(FakeBookUser& friendObj)
	{
		list<FakeBookUser*> Tmp;
		Tmp.push_back(&friendObj);
		auto x = Tmp.begin();
		for (auto i = this->Friends.begin(); i != this->Friends.end(); i++)
		{
			if ((*i)->GetCurrentID() == (*x)->GetCurrentID())
				return true;
		}
		return false;
	}
	list <FakeBookUser*>& GetFriends()
	{
		return Friends;
	}
	FakeBookUserInformation* GetFakeBookUserInformation()
	{
		return UserData;
	}
	bool AddFriend(FakeBookUser& friendObj)
	{
		if (!isFriend(friendObj))
		{
			Friends.push_back(&friendObj);
			return true;
		}
		return false;
	}
	friend bool operator==(FakeBookUser &FBU1, const FakeBookUser &FBU2)
	{
		bool flag = false;
		auto pi = FBU2.Friends.begin();
		auto li = FBU1.Friends.begin();
		for (; li != FBU1.Friends.end(); li++)
		{
			if (li == pi)
			{
				flag = true;
			}
			else
			{
				flag = false;
				break;
			}
			pi++;
			if (pi == FBU2.Friends.end())
			{
				break;
			}
		}

		if (pi == FBU2.Friends.end() && li == FBU1.Friends.end() && flag == true)
			flag = true;
		else
			flag = false;
		return FBU1.UserData == FBU2.UserData;
	}
	bool RemoveFriend(FakeBookUser& friendObj)
	{
		if (isFriend(friendObj))
		{
			Friends.remove(&friendObj);
			return true;
		}
		return false;

	}
	~FakeBookUser()
	{
	}
};
int FakeBookUser::FakeBookUserInformation::GlobalUserIDCount = 1;


class FakeBook
{

	static FakeBook* Instance;
	list<FakeBookUser> AllUsers;
	int n; //number of users
	FakeBook()
	{
		n = 0;
	}

	void PrintID(int ID)
	{
		auto li = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() == ID)
				break;
			li++;
		}
		li->GetFakeBookUserInformation()->PrintInformation();
	}

	int CountAllMutualFriends(int id1, int id2)
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() != id1 && i == false)
			{
				li++;
			}
			else
			{
				i = true;
			}

			if (ki->GetCurrentID() != id2 && k == false)
			{
				ki++;
			}
			else
			{
				k = true;
			}
			if (i == k && k == true)
				break;
		}
		int count = { 0 };
		if (i == k == true)
		{

			for (auto k = li->GetFriends().begin(); k != li->GetFriends().end(); k++)
			{
				for (auto l = ki->GetFriends().begin(); l != ki->GetFriends().end(); l++)
				{
					if ((*k)->GetCurrentID() == (*l)->GetCurrentID())
					{
						count++;
					}
				}
			}
		}
		return count;
	}

	void RemoveDublicates(vector<int> &V)
	{
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()), V.end());
	}

	vector<int> FriendsofFriend(int ID)
	{
		auto i = AllUsers.begin();
		while (i != AllUsers.end())
		{
			if (i->GetCurrentID() == ID)
				break;
			i++;
		}

		vector<int> FOF;
		for (auto li = i->GetFriends().begin(); li != i->GetFriends().end(); li++)
		{
			for (auto xi = (*li)->GetFriends().begin(); xi != (*li)->GetFriends().end(); xi++)
			{
				if ((*xi)->GetCurrentID() != ID)
				{
					if (!i->isFriend(*(*xi)))
					{
						FOF.push_back((*xi)->GetCurrentID());
					}
				}
			}
		}
		return FOF;
	}

public:


	static FakeBook* CreateFakeBookObject()
	{
		if (Instance == nullptr)
			Instance = new FakeBook();
		return Instance;
	}

	void addUser(const FakeBookUser &obj)
	{
		AllUsers.push_back(obj);
		n++;
	}

	void deleteUser(const FakeBookUser &obj) //it will take a reference to a user and remove the user from the allusers list
	{
		auto li = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (*li == obj)
			{
				deleteUser(li->GetCurrentID());
				n--;
				break;
			}
			li++;
		}
	}

	void deleteUser(int id) // it will take a id to a user and remove the user from the allusers list
	{
		int NOF = { 0 };
		for (auto li = AllUsers.begin(); li != AllUsers.end(); li++)
		{
			if (li->GetCurrentID() == id)
			{
				NOF = (int)li->GetFriends().size();
				auto pi = li->GetFriends().begin();
				while (NOF > 0)
				{
					removeFriend(id, (*pi)->GetCurrentID());
					NOF--;
					pi = li->GetFriends().begin();
				}
				AllUsers.erase(li);
				n--;
				break;
			}
		}
	}

	bool addFriend(int id1, int id2) //it will take ids to two users and make them friends of each other.
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() != id1 && i == false)
			{
				li++;
			}
			else
			{
				i = true;
			}

			if (ki->GetCurrentID() != id2 && k == false)
			{
				ki++;
			}
			else
			{
				k = true;
			}
			if (i == k && k == true)
				break;
		}

		if (i == k && k == true)
		{
			return li->AddFriend(*ki) && ki->AddFriend(*li);
		}
		return false;
	}

	void ReadFromFile(string FileName)// Read all the users information from the file and also read all the friends information and establish the links
	{
		ifstream fin;
		fin.open(FileName);
		fin >> this->n;

		string name, loc;
		char x;
		int age;
		for (int i = 0; i < n; i++)
		{
			fin.ignore();
			getline(fin, name, '#');
			getline(fin, loc, '#');
			fin.get(x);
			fin.ignore();
			fin >> age;
			FakeBookUser FU(name, loc, x, age);
			name.clear();
			loc.clear();
			AllUsers.push_back(FU);
		}
		int id1, id2;
		for (int i = 0; i < n; i++)
		{
			fin >> id1;
			fin.get(x);
			while (x != '\n')
			{
				fin >> id2;
				addFriend(id1, id2);
				fin.get(x);
			}
		}
		fin.close();
	}

	bool addFriend(const FakeBookUser & obj1, const FakeBookUser & obj2)//it will take reference to two users and make them friends of each other.
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (*li == obj1)
			{
				i = true;
			}
			else
			{
				if (i == false)
				{
					li++;
				}
			}

			if (*ki == obj2)
			{
				k = true;
			}
			else
			{
				if (k == false)
				{
					ki++;
				}
			}
			if (i == k && k == true)
			{
				break;
			}
		}
		if (li->GetCurrentID() == ki->GetCurrentID())
		if (i == k && k == true)
		{
			return li->AddFriend(*ki) && ki->AddFriend(*li);
		}
		return false;
	}

	bool removeFriend(int id1, int id2)//it will take ids to two users and make them un-friends of each other.
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() != id1 && i == false)
			{
				li++;
			}
			else
			{
				i = true;
			}

			if (ki->GetCurrentID() != id2 && k == false)
			{
				ki++;
			}
			else
			{
				k = true;
			}
			if (i == k && k == true)
				break;
		}

		if (i == k && k == true)
		{
			return li->RemoveFriend(*ki) && ki->RemoveFriend(*li);
		}
		return false;
	}

	bool removeFriend(const FakeBookUser & obj1, const FakeBookUser & obj2)//it will take reference to two users and make them un-friends of each other.
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (*li == obj1)
			{
				i = true;
			}
			else
			{
				if (i == false)
				{
					li++;
				}
			}

			if (*ki == obj2)
			{
				k = true;
			}
			else
			{
				if (k == false)
				{
					ki++;
				}
			}
		}

		if (i == k && k == true)
		{
			return li->RemoveFriend(*ki) && ki->RemoveFriend(*li);
		}
		return false;
	}

	bool PrintAllfriends(const FakeBookUser &obj)  // it will take a reference to a user and print all the friends of the user
	{
		bool flag = false;
		auto li = AllUsers.begin();
		list<FakeBookUser> tmp;
		tmp.push_back(obj);
		auto ki = tmp.begin();
		while (li != AllUsers.end())
		{
			if (*li == *ki)
			{
				flag = true;
				break;
			}
			li++;
		}

		if (flag == true)
		{
			auto ki = li->GetFriends().begin();
			while (ki != li->GetFriends().end())
			{
				(*ki)->GetFakeBookUserInformation()->PrintInformation();
				ki++;
			}
			return true;
		}
		return false;
	}

	bool PrintAllfriends(int id)// it will take a id of a user and prints all the friends of the user
	{
		bool flag = false;
		auto li = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() == id)
			{
				flag = true;
				break;
			}
			li++;
		}

		if (flag == true)
		{
			cout << "\t############################" << endl;
			cout << "\t#     FRIENDS OF ID: " << id << "     #" << endl;
			cout << "\t############################" << endl;

			auto ki = li->GetFriends().begin();
			while (ki != li->GetFriends().end())
			{
				(*ki)->GetFakeBookUserInformation()->PrintInformation();
				ki++;
			}
			return true;
		}
		return false;
	}

	void printFakeBook()  // it will print all the users in the FakeBook
	{
		cout << "\t############################" << endl;
		cout << "\t#    ALL FakeBook USERS    #" << endl;
		cout << "\t############################" << endl;
		for (auto li = AllUsers.begin(); li != AllUsers.end(); li++)
		{
			cout << *(li->GetFakeBookUserInformation());
		}
	}

	void saveFakeBook(string FileName) // Save the current state of FakeBook to a file that can be used to load the FakeBook again
	{
		ofstream fout(FileName);
		fout << this->n;
		fout << '\n';
		for (auto i = AllUsers.begin(); i != AllUsers.end(); i++)
		{
			fout << i->GetFakeBookUserInformation()->GetName();
			fout << "#";
			fout << i->GetFakeBookUserInformation()->GetLocation();
			fout << "#";
			fout << i->GetFakeBookUserInformation()->GetGender();
			fout << "#";
			fout << i->GetFakeBookUserInformation()->GetAge();
			fout << '\n';
		}
		fout << '\n';
		for (auto i = AllUsers.begin(); i != AllUsers.end(); i++)
		{
			fout << i->GetCurrentID();
			for (auto j = i->GetFriends().begin(); j != i->GetFriends().end(); j++)
			{
				fout << ' ' << (*j)->GetCurrentID();
			}
			fout << endl;
		}
		fout.close();
	}

	void PrintAllMutualFriends(int id1, int id2)// it will print all the mutual friend between users with IDs id1 and id2
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() != id1 && i == false)
			{
				li++;
			}
			else
			{
				i = true;
			}

			if (ki->GetCurrentID() != id2 && k == false)
			{
				ki++;
			}
			else
			{
				k = true;
			}
			if (i == k && k == true)
				break;
		}
		int count = { 0 };
		if (i == k == true)
		{
			cout << "       ###############################" << endl;
			cout << "       # MUTUAL FRIENDS B/W ID " << id1 << " & " << id2 << " #" << endl;
			cout << "       ###############################" << endl;

			for (auto k = li->GetFriends().begin(); k != li->GetFriends().end(); k++)
			{
				for (auto l = ki->GetFriends().begin(); l != ki->GetFriends().end(); l++)
				{
					if ((*k)->GetCurrentID() == (*l)->GetCurrentID())
					{
						(*k)->GetFakeBookUserInformation()->PrintInformation();
					}
				}
			}
		}
	}

	void PrintAllMutualFriends(const FakeBookUser & obj1, const FakeBookUser & obj2)// it will print all the mutual friend between users obj1 and obj2
	{
		bool i = false, k = false;
		auto li = AllUsers.begin();
		auto ki = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (*li == obj1)
			{
				i = true;
			}
			else
			{
				if (i == false)
				{
					li++;
				}
			}

			if (*ki == obj2)
			{
				k = true;
			}
			else
			{
				if (k == false)
				{
					ki++;
				}
			}
			if (i == k && k == true)
			{
				break;
			}
		}
		if (i == k == true)
		{
			cout << "       ###############################" << endl;
			cout << "       # MUTUAL FRIENDS B/W ID " << li->GetCurrentID() << " & " << ki->GetCurrentID() << " #" << endl;
			cout << "       ###############################" << endl;
			for (auto k = li->GetFriends().begin(); k != li->GetFriends().end(); k++)
			{
				for (auto l = ki->GetFriends().begin(); l != ki->GetFriends().end(); l++)
				{
					if (k == l)
						(*k)->GetFakeBookUserInformation()->PrintInformation();
				}
			}
		}
	}

	void printAllUsersBetweenAges(int agelow, int agehigh)//prints the users between ages given in parameters.
	{
		if (agelow > agehigh)
		{
			swap(agelow, agehigh);
		}
		int age = { 0 };
		cout << "      ##############################" << endl;
		cout << "      #    USERS B/W AGE " << agelow << " & " << agehigh << "   #" << endl;
		cout << "      ##############################" << endl;
		for (auto li = AllUsers.begin(); li != AllUsers.end(); li++)
		{
			age = li->GetFakeBookUserInformation()->GetAge();
			if (age > agelow && age < agehigh)
				cout << *(li->GetFakeBookUserInformation());
		}
	}

	void printAllMalesBetweenAges(int agelow, int agehigh)//prints the male users between ages given in parameters.
	{
		if (agelow > agehigh)
		{
			swap(agelow, agehigh);
		}
		int age = { 0 };
		char g = '\0';
		cout << "      ##############################" << endl;
		cout << "      # MALE USERS B/W AGE " << agelow << " & " << agehigh << " #" << endl;
		cout << "      ##############################" << endl;
		for (auto li = AllUsers.begin(); li != AllUsers.end(); li++)
		{
			age = li->GetFakeBookUserInformation()->GetAge();
			g = li->GetFakeBookUserInformation()->GetGender();
			if ((g == 'M' || g == 'm') && (age > agelow && age < agehigh))
				cout << *(li->GetFakeBookUserInformation());
		}
	}

	void printAllFemalesBetweenAges(int agelow, int agehigh)//prints the female users between ages given in parameters.
	{
		if (agelow > agehigh)
		{
			swap(agelow, agehigh);
		}
		int age = { 0 };
		char g = '\0';
		cout << "      ###############################" << endl;
		cout << "      # FEMALE USERS B/W AGE " << agelow << " & " << agehigh << "#" << endl;
		cout << "      ###############################" << endl;
		for (auto li = AllUsers.begin(); li != AllUsers.end(); li++)
		{
			age = li->GetFakeBookUserInformation()->GetAge();
			g = li->GetFakeBookUserInformation()->GetGender();
			if ((g == 'F' || g == 'f') && (age > agelow && age < agehigh))
				cout << *(li->GetFakeBookUserInformation());
		}
	}

	void PrintThreeMostLikelyPeopleIknow(int id)// it will print the information of three people who have the greatest number of mutual friends with the user with given ID, but who are not themselves friends of User (this is one way in which the actual Facebook suggests you new friends).
	{
		bool found = false;
		auto li = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (li->GetCurrentID() == id)
			{
				found = true;
				break;
			}
			li++;
		}

		if (found)
		{
			cout << "       ###############################" << endl;
			cout << "       #     SUGGESTIONS FOR ID " << id << "    #" << endl;
			cout << "       ###############################" << endl;
			vector<int> X = FriendsofFriend(li->GetCurrentID());
			RemoveDublicates(X);

			int count = { 0 }, first, second, third, firstID = { 0 }, secondID = { 0 }, thirdID = { 0 };
			third = first = second = INT_MIN;
			if (X.size() == 1)
			{
				firstID = *max_element(X.begin(), X.end());
				PrintID(firstID);
				return;
			}
			else
			if (X.size() == 2)
			{
				firstID = *max_element(X.begin(), X.end());
				secondID = *min_element(X.begin(), X.end());
				PrintID(firstID);
				PrintID(secondID);
				return;
			}
			else
			{
				for (int i = 0; i<X.size(); i++)
				{
					count = CountAllMutualFriends(id, X[i]);
					if (count > first)
					{
						third = second;
						thirdID = secondID;
						second = first;
						secondID = firstID;
						first = count;
						firstID = X[i];
					}
					else if (count > second)
					{
						third = second;
						thirdID = secondID;
						second = count;
						secondID = X[i];
					}
					else if (count > third)
					{
						third = count;
						thirdID = X[i];
					}
				}
			}
			PrintID(firstID);
			PrintID(secondID);
			PrintID(thirdID);
		}
	}

	void PrintThreeMostLikelyPeopleIknow(const FakeBookUser &obj)// it will print the names of three people who have the greatest number of mutual friends with the user given as a reference, but who are not themselves friends of User (this is one way in which the actual Facebook suggests you new friends).
	{
		bool found = false;
		auto li = AllUsers.begin();
		while (li != AllUsers.end())
		{
			if (*li == obj)
			{
				found = true;
				break;
			}
			li++;
		}

		if (found)
		{
			vector<int> X = FriendsofFriend(li->GetCurrentID());
			RemoveDublicates(X);

			int count = { 0 }, first, second, third, firstID = { 0 }, secondID = { 0 }, thirdID = { 0 };
			third = first = second = INT_MIN;
			if (X.size() == 1)
			{
				firstID = *max_element(X.begin(), X.end());
				PrintID(firstID);
				return;
			}
			else
			if (X.size() == 2)
			{
				firstID = *max_element(X.begin(), X.end());
				secondID = *min_element(X.begin(), X.end());
				PrintID(firstID);
				PrintID(secondID);
				return;
			}
			else
			{
				for (int i = 0; i<X.size(); i++)
				{
					count = CountAllMutualFriends(li->GetCurrentID(), X[i]);
					if (count > first)
					{
						third = second;
						thirdID = secondID;
						second = first;
						secondID = firstID;
						first = count;
						first = X[i];
					}
					else if (count > second)
					{
						third = second;
						thirdID = secondID;
						second = count;
						secondID = X[i];
					}
					else if (count > third)
					{
						third = count;
						thirdID = X[i];
					}
				}
			}
			PrintID(firstID);
			PrintID(secondID);
			PrintID(thirdID);
		}
	}

	void DeleteFakeBook()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

	~FakeBook()
	{

	}
};
FakeBook* FakeBook::Instance = nullptr;