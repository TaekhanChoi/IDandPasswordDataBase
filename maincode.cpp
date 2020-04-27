#include<iostream>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>
using namespace std;

class Caps{
	private:
		string name;
	public:
		Caps(string entry){
			StoreStrings(entry);
		}
		void StoreStrings(string entry)
		{
			name = entry;
		}
		string GetName()
		{
			return name;
		}
};

class BookKeeping{
	private:
		char first;
		char second;
		char third;
		char fourth;
		int entry;
		string site;
	public:
		BookKeeping(string entry){
			site = entry;
		}
		int alphabet_to_number1()
		{
			first = site[0] - 32;
			return first;
		}
		int alphabet_to_number2()
		{
			second = site[1] - 32;
			return second;
		}
		int alphabet_to_number3()
		{
			third = site[2] - 32;
			return third;
		}
		int alphabet_to_number4()
		{
			fourth = site[3] - 32;
			return fourth;
		}
		int entry_calc()
		{
			entry = alphabet_to_number1() + alphabet_to_number2() +
					alphabet_to_number3() + alphabet_to_number4();
			return entry;
		}
};

void outputREADME(ifstream & fin)
{
	string line;
	if(!fin)
	{
		cout << "File is not Found :(" << endl;
	}
	else 
	{		
		while(getline(fin, line))
		{
			cout << line << '\n';
		}
		fin.close();
	}
}

void IDandPasswordRecord(ofstream &fout, string site, int index)
{		
	string ID;
	cout << "Enter ID: ";
	cin >> ID;
		
	string password;
	cout << "Enter Password: ";
	cin >> password;
	fout << index << " " << site << " " << ID << " " << password << endl;
}

void Filling_Notepad(int array[380][10], int &index, int entry)
{
	int identifier = 0;
	bool filled = false;
	
	while(filled == false)
	{
		if(array[entry][identifier] != 0)
		{
			int prev_id = 0;
			prev_id = identifier;
			identifier++;
			cout << "Filled, Shifting Identifier from " << prev_id << " to " << identifier << endl;
		}
		else
		{
			array[entry][identifier] = index;
			filled = true;
			break;
		}
		if(identifier >= 10)
		{
			cout << "All spots filled, cannot record anymore" << endl;
			filled = true;
			break;
		}
	}
	
	index++;
}

void populate_array(ifstream &fin, int array[380][10])
{
	int value = 0;
	for(int count = 0; count < 380; count++)
	{
		for(int counter = 0; counter < 10; counter++)
		{
			fin >> value;
			array[count][counter] = value;						
		}
	}
}

void store_array(ofstream &fout, int array[380][10])
{
	for(int count = 0; count < 380; count++)
	{
		for(int counter = 0; counter < 10; counter++)
		{
			fout << array[count][counter] << " ";						
		}
		cout << endl;
	}
}

void SearchEngine(ifstream &fin, int index)
{
	string siteName;
	string id;
	string password;
	int bookmark = 0;
		
	while(fin >> bookmark >> siteName >> id >> password)
	{
		if(bookmark == index)
		{
			cout << "Site: " << siteName << "ID: " << id << "Password: " << password;
			break;
		}
	}
}

int main()
{
	string Answer1 = "";
	string Answer2 = "y";
	int first_value = 0;
	int second_value = 0;
	int array[380][10] = {0};
	int index = 1;
	
	ifstream finindex("index.txt");
	ofstream foutindex("index.txt", ofstream::trunc);
	
	ifstream finIDandPassword("ID_Password.txt");
	ofstream foutIDandPassword("ID_Password.txt", ios::app);
	
	ifstream finREADME("readmeID.txt");
	
	ifstream finARRAY("array.txt");
	ofstream foutARRAY("array.txt", ofstream::trunc);
	
	populate_array(finARRAY, array);
	finindex >> index;
	cout << index;
	do{
		cout << "Add (A) or Search (S)? ";
		cin >> Answer1;
		
		if(Answer1 == "A" && "a")
		{
			int entry = 0;
			string site = "";
			string line = "";
	
			outputREADME(finREADME);
			
			cout << "Enter the Site to add: "; 
			cin >> site;
			
			BookKeeping entryNUM(site);
			
			IDandPasswordRecord(foutIDandPassword, site, index);
			
			Filling_Notepad(array, index, entryNUM.entry_calc());
		}
		else if(Answer1 == "S" && "s")
		{
			string site = "";
			
			cout << "Enter Site to Search: ";
			cin >> site;
			
			BookKeeping entryNUM(site);
			int bookmark_index = 0;
			bookmark_index = entryNUM.entry_calc();
			
			for(int identifier = 1; identifier < 10 || array[entryNUM.entry_calc()][identifier] > 0; identifier++)
			{
				SearchEngine(finIDandPassword, entryNUM.entry_calc());
			}
		}
		else
		{
			cout << "Invalid Entry, Please try again";
		}
		cout << endl << "Would you like to continue? (y/n) ";
		cin >> Answer2;
	}while(Answer2 == "y");
	
	store_array(foutARRAY, array);
	foutindex << index;
}
