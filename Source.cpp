

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Ippo
{
protected:
	/*vector < */class Observer */*>*/ views;
	string por;
	string name;
	int year;
	int win;
	int speed;
	bool winner;
public:
	Ippo() {};
	Ippo(string por, string name, int year) 
	{
		this->por = por;
		this->name = name;
		this->year = year;
		this->win = 0;
		views = NULL;
	}
	void setspeed(int a)
	{
		this->speed = a;
	}
	int getspeed()
	{
		return this->speed;
	}
	void setwin()
	{
		this->win++;
	}
	int getwin()
	{
		return this->win;
	}

	void setwinner(bool flag)
	{
		this->winner = flag;
		notify();
	}
	bool getwinner()
	{
		return this->winner;
	}

	void attach(Observer *obs) {
		views = /*.push_back*/(obs);
	}

	string myprint()
	{
		string res, res1;
		res = "name: " + this->name + " poroda: " + this->por;
		char* tmp = new char(10);
		_itoa_s(this->year, tmp, 4, 10);
		res1 = (string)tmp;
		res += " year: " + res1;
		_itoa_s(this->win, tmp, 4, 10);
		res1 = (string)tmp;
		res += " win: " + res1;
		_itoa_s(this->speed, tmp, 4, 10);
		res1 = (string)tmp;
		res += " speed: " + res1;
		return res;
	}
	void notify();
	~Ippo() {};
};

class Observer {
	Ippo *model;
	string o_name;
public:
	Observer(Ippo *mod, string n) {
		model = mod;
		o_name = n;
		model->attach(this);
	}

	Observer() {
		model = NULL;
	}

	void update()
	{
		bool win = getSubject()->getwinner();
		cout << o_name;
		if (win)
		{
			cout << " win "  << '\n';
		}
		else
			cout << " not win " << '\n';
	}
protected:
	Ippo *getSubject() {
		return model;
	}
};

void Ippo::notify() {
	

		views->update();
}
int main()
{
	vector<Ippo> myIppo;
	ifstream in;
	in.open("File.txt");
	int kol, god;
	string line, poroda, imya;
	getline(in, line);
	kol = atoi(line.c_str());
	int numst = 0;
	bool contin=true;

	for (int i = 0; i < kol; i++)
	{
		getline(in, poroda);
		getline(in, imya);
		getline(in, line);
		god = atoi(line.c_str());
		Ippo tmpHorse(poroda, imya, god);
		myIppo.push_back(tmpHorse);
	}
	in.close();


	while (contin)
	{

		cout << "Vvedite name" << endl;
		string tmp;
		cin >> tmp;
		cout << "Viberite loshad" << endl;
		int l;
		cin >> l;
		Observer obs1(&myIppo[l], tmp);
		for (int i = 0; i < 5; i++)
		{
			cout << i << endl;
			for (int j = 0; j < kol; j++)
			{
				myIppo[j].setspeed(rand() % 50);
				cout << j << " " << myIppo[j].getspeed() << endl;
			}
			int max = 0;
			for (int j = 1; j < kol; j++)
			{
				if (myIppo[j].getspeed() > myIppo[max].getspeed())
				{
					max = j;
				}
			}
			myIppo[max].setwin();
		}
		int max = 0;
		for (int i = 1; i < kol; i++)
		{
			if (myIppo[i].getwin() > myIppo[max].getwin())
			{
				max = i;
			}
		}
		
			if (l == max)
			{
				myIppo[l].setwinner(true);
			}
			else
				myIppo[l].setwinner(false);
		
		ofstream out;
		char *numstch = new char(2);
		char Y;
		_itoa_s(numst, numstch, 4, 10);
		string res1 = (string)numstch;
		string fname;
		fname += "out" + res1 + ".txt";
		out.open(fname);
		for (int i = 0; i < kol; i++)
		{
			out << myIppo[i].myprint() << endl;
		}
		out.close();

	//	delete(&obs1);
		cout << "press y for continue" << endl;
		cin >> Y;
		if (Y == 'y')
		{
			contin = true;
		}
		else
			contin = false;
		numst++;
	}
	return 0;
}
