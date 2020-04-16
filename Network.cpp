#include <iostream>
#include <string>			// For string functions for number extraction after file reading
#include <fstream>			// For file reading
#include <vector>			// For vector functions
#include <algorithm>			// For advance functions like sort and unique

using namespace std;

class Network
{
private:
	struct Computer
	{
		int id;
		Computer* next;

		// For checking connections through [][]
		bool operator [] (int j)
		{
			Computer* temp = next;

			while (temp != NULL)
			{
				if (temp->id == j)
					return 1;
				temp = temp->next;
			}
			return 0;
		}
	};

	vector<Computer*>net;
	void addConnection(Computer*& head, int id)
	{
		if (head == NULL)
		{
			head = new Computer;
			head->id = id;
			head->next = NULL;
		}
		else
		{
			Computer* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = new Computer;
			temp->next->id = id;
			temp->next->next = NULL;
		}
	}


public:
	Network()
	// Default Constructor
	{
		// Setting the vector (net) to NULL
		net.clear();
	}

	~Network()
	// Destructor
	{
		// Setting the vector (net) to NULL
		net.clear();
	}

	// Parametrized Constructor
	Network(string file)
	{
		string s;
		ifstream hfile;
		hfile.open(file);
		int x = 0;
		hfile.ignore(256, '\n');
		vector<int>h;
		while (getline(hfile, s))
		{
			int x = s[0] - 48;
			Computer* temp = new Computer;
			temp->id = x;
			temp->next = NULL;

			net.push_back(temp);
			for (int i = 4; i < s.length(); i = i + 2)
			{
				{
					int y = s[i] - 48;
					temp->next = new Computer;
					temp = temp->next;
					temp->id = y;
					temp->next = NULL;
				}
			}
			temp->next = NULL;
		}
		hfile.close();
	}

	// Parametrized Consructor
	Network(int size)
	{
		net.resize(size, NULL);
		for (int i = 0; i < net.size(); i++)
		{
			net[i] = new Computer;
			net[i]->id = i;
			net[i]->next = NULL;
		}
	}

	// SIZE DETERMINATION
	int siz(int i)
	{
		int x = 0;
		Computer* temp = net[i];
		while (temp->next != NULL)
		{
			temp = temp->next;
			x++;
		}
		return x;
	}

	// Overloading the << operator (for printing)
	friend ostream& operator << (ostream& output, Network& obj)
	{
		for (int i = 0; i < obj.net.size(); i++)
		{
			Computer* temp = obj.net[i];
			while (temp != NULL)
			{
				output << temp->id << " ";
				temp = temp->next;
			}
			output << endl;
		}
		return output;
	}

	// Copy constructor
	Network(const Network& obj)
	{
		for (int i = 0; i < obj.net.size(); i++)
		{
			Computer* head = NULL;
			Computer* temp = obj.net[i];
			while (temp != NULL)
			{
				addConnection(head, temp->id);
				temp = temp->next;
			}
			net.push_back(head);
		}
	}

	// Overloading = operator
	const Network& operator =(const Network& obj)
	{
		Network E;
		E.net = obj.net;
		for (int i = 0; i < obj.net.size(); i++)
		{
			Computer* head = NULL;
			Computer* temp = E.net[i];
			while (temp != NULL)
			{
				addConnection(head, temp->id);
				temp = temp->next;
			}
			net.push_back(head);
		}
		return E;
	}

	// Adding y to x and x to y 
	void addConnection(int x, int y)
	{
		int count = 0;
		int a;
		for (int i = 0; i < net.size(); i++)
		{
			if (net[i]->id == x)
			{
				count++;
				a = i;
			}
		}
		if (count != 0)
		{
			Computer* temp = net[a]->next;
			int count1 = 0;
			while (temp != NULL)
			{
				if ((temp->id) == y)
				{
					count1++;
				}
				temp = temp->next;
			}
			if (count1 == 0)
			{
				addConnection(net[a], y);
			}
		}

		int counter = 0;
		int b;
		for (int i = 0; i < net.size(); i++)
		{
			if (net[i]->id == y)
			{
				counter++;
				b = i;
			}
		}
		if (counter != 0)
		{
			Computer* temp = net[b]->next;
			int counter1 = 0;
			while (temp != NULL)
			{
				if ((temp->id) == x)
				{
					counter1++;
				}
				temp = temp->next;
			}
			if (counter1 == 0)
			{
				addConnection(net[b], x);
			}
		}
	}

	// Getting all neighbours of a particular nid
	vector<int> getNeighbors(int nid)
	{
		int count = 0;
		int a;
		for (int i = 0; i < net.size(); i++)
		{
			if (net[i]->id == nid)
			{
				count++;
				a = i;
			}
		}
		vector<int>gn;
		if (count != 0)
		{
			Computer* temp = net[nid]->next;
			while (temp != NULL)
			{
				gn.push_back(temp->id);
				temp = temp->next;
			}
		}
		else
		{
			gn.clear();
		}
		return gn;
	}

	//get all unique neighbors-of-neighbors of computer nid
	vector<int> getNeighborsOfNeighbors(int nid)
	{
		int count = 0;
		int a;
		for (int i = 0; i < net.size(); i++)
		{
			if (net[i]->id == nid)
			{
				count++;
				a = i;
			}
		}
		vector<int>gn;
		if (count != 0)
		{
			Computer* temp = net[nid]->next;
			while (temp != NULL)
			{
				vector<int>tempo;
				tempo = getNeighbors(temp->id);

				for (int i = 0; i < tempo.size(); i++)
				{
					gn.push_back(tempo[i]);
				}
				sort(gn.begin(), gn.end());
				gn.erase(unique(gn.begin(), gn.end()), gn.end());
				//gn.insert(gn.begin(), tempo.size()-1);
				temp = temp->next;
			}
		}
		else
		{
			gn.clear();
		}
		return gn;
	}
	
	// Overloading + operator (union)
	Network operator + (Network obj)
	{
		Network N;
		int x;
		int y;
		if (net.size() >= obj.net.size())
		{
			x = net.size();
			y = obj.net.size();
			N.net = net;
		}
		else
		{
			x = obj.net.size();
			y = net.size();
			N.net = obj.net;
		}

		for (int i = 0; i < x; i++)
		{
			vector<int>u;
			if (i >= y)
			{
				u.clear();
			}
			else
			{
				Computer* temp = net[i]->next;
				while (temp != NULL)
				{
					u.push_back(temp->id);
					temp = temp->next;
				}

				temp = obj.net[i]->next;
				while (temp != NULL)
				{
					u.push_back(temp->id);
					temp = temp->next;
				}

				sort(u.begin(), u.end());
				u.erase(unique(u.begin(), u.end()), u.end());
				u.insert(u.begin(), i);

				N.net[i] = NULL;
			}


			for (int j = 0; j < u.size(); j++)
			{
				addConnection(N.net[i], u[j]);
			}
			N.net[i]->id = i;

		}
		return N;
	}

	// Overloading * operator (intersection)
	Network operator * (const Network& obj)
	{
		Network N;
		int x;
		if (net.size() >= obj.net.size())
		{
			x = obj.net.size();
			N.net = obj.net;
		}
		else
		{
			x = net.size();
			N.net = net;
		}
		//N.net = obj.net;
		for (int i = 0; i < x; i++)
		{
			vector<int>intersects;
			Computer* temp = net[i];
			while (temp != NULL)
			{
				Computer* temp1 = obj.net[i];
				while (temp1 != NULL)
				{
					if (temp->id == temp1->id)
					{
						intersects.push_back(temp->id);
					}
					temp1 = temp1->next;
				}

				N.net[i] = NULL;
				for (int j = 0; j < intersects.size(); j++)
				{
					addConnection(N.net[i], intersects[j]);
				}
				N.net[i]->id = i;
				temp = temp->next;
			}
		}
		return N;
	}

	// Checking connections by [][] overloading
	Computer& operator [](int i)
	{
		Computer* temp = net[i];
		return (*temp);
	}

	// Overloading ++ operator
	void operator ++ (int)
	{
		Computer* temp = new Computer;
		net.push_back(temp);
		temp->id = net.size() - 1;
		temp->next = NULL;
	}

	// Overloading - operator for difference (e.g N-C) 
	Network operator - (const Network& obj)
	{
		Network N;
		for (int i = 0; i < net.size(); i++)
		{
			Computer* temp = new Computer;
			N.net.push_back(temp);
			N.net[i]->id = i;
			N.net[i]->next = NULL;
		}

		for (int i = 0; i < net.size(); i++)
		{
			int count = 0;
			Computer* temp1 = net[i]->next;
			if (i >= obj.net.size())
			{	
				while (temp1 != NULL)
				{	
					addConnection(N.net[i], temp1->id);
					temp1 = temp1->next;
				}
			}
			else if (i < obj.net.size())
			{	
				Computer* temp1 = net[i]->next;
				
				while (temp1 != NULL)
				{	
					count = 0;
					Computer* temp2 = obj.net[i]->next;
					while (temp2 != NULL)
					{
						if (temp1->id == temp2->id)
						{
							count++;
						}
						temp2 = temp2->next;
					}
					if (count == 0)
					{
						addConnection(N.net[i], temp1->id);
					}
					temp1 = temp1->next;
				}
			}
		}
		return N;
	}

	// Checking for subnetworks
	bool subNetwork(const Network& obj)
	{
		if (obj.net.size() > net.size())
		{
			return false;
		}
		for (int i = 0; i < obj.net.size(); i++)
		{
			Computer* temp = obj.net[i]->next;
			Computer* temp1 = net[i]->next;
			while (temp != NULL)
			{
				if (temp->id != temp1->id)
				{
					return 0;
				}
				temp = temp->next;
				temp1 = temp1->next;
			}
		}
		return true;
	}

	// Overloading - operator (Complement) 
	Network operator - ()
	{
		Network N;
		for (int i = 0; i < net.size(); i++)
		{
			Computer* temp = new Computer;
			N.net.push_back(temp);
			N.net[i]->id = i;
			N.net[i]-> next = NULL;
		}
		for (int i = 0; i < net.size(); i++)
		{	
			for (int j = 0; j < net.size(); j++)
			{
				int count = 0;
				Computer* temp = net[i]->next;
				if (i != j)
				{
					while (temp != NULL)
					{
						if ((temp->id) == net[j]->id)
						{
							count++;
						}
						temp = temp->next;
					}
					if (count == 0)
					{
						addConnection(N.net[i], net[j]->id);
					}
				}
			}
		}
		return N;
	}
};

int main()
{
	
	cout << "---ASSIGNMENT 3 MAKING COMPUTER  NETOWRKS THROUGH NODES---" << endl << endl;
	cout << "TEST FOR PARAMETRIZED CONSTRUCTOR (FILE HANDLING)" << endl;
	Network N("test1 (1).txt"); 
	cout << "---N---(file1)" << endl;
	cout << N;

	Network C("test2.txt");
	cout << "---C---(file2)" << endl;
	cout << C;

	cout << endl << "TEST FOR COPY CONSTRUCTOR" << endl;
	Network N1 = N;
	cout << "---Network Copy (N1)---" << endl;
	cout << N1;

	cout << endl << "TEST FOR ASSIGNMENT OPERATOR OVERLOADING" << endl;
	Network N2;
	N2 = N; 
	cout << "---N2 = N---" << endl;
	cout << N2;

	cout << endl;
	cout << "TESTING UNION FUNCTION (+ OPERATOR)" << endl;
	cout << "---N + C---" << endl;
	Network U1;
	U1 = N+C;
	cout << U1;
	cout << "---N + N---" << endl;
	Network U2;
	U2 = N + N;
	cout << U2;
	
	cout << endl << endl << "TEST FOR INTERSECTION (* OPERATOR)" << endl;
	cout << "C * C" << endl;
	Network inte = C*C;
	cout << inte;
	cout << endl << "C * N" << endl;
	Network inte2 = C * N;
	cout << inte2;

	cout << endl;
	cout << "TESTING FOR COMPLEMENT FUNCTION" << endl;
	cout << "---(-N)---" << endl;
	Network Comp = -N;
	cout << Comp;

	cout << "---(-C)---" << endl;
	Network Comp2 = -C;
	cout << Comp2;

	cout << endl;
	cout << "TESTING DIFFERENCE FUNCTION (-)" << endl;
	cout << "--- C-N ---" << endl;
	Network diff;
	diff = C - N;
	cout << diff;
	cout << "--- C-C ---" << endl;
	Network diff2;
	diff2 = N - N;
	cout << diff2;

	cout << endl;
	cout << "TEST FOR [][] (CONNECTION)" << endl;
	int x = 1;
	int y = 2;
	cout << "Are " << x << " and " << y << " connected?" << endl;
	if (C[x][y])
	{
		cout << "Connected " << endl;
	}
	else
	{
		cout << "Not connected" << endl;
	}

	cout <<  endl << "TEST FOR SUBNETWORK FUNCTION" << endl;
	cout << "Is C a subnetwork of N?" << endl;
	cout << N.subNetwork(C);
	cout << endl << "Is N a subnetwork of C?" << endl;
	cout << C.subNetwork(N);

	cout << endl;
	cout << endl << "TEST FOR ++ OPERATOR OVERLOADING (N++)" << endl;
	N++;
	cout << N;

	cout << endl << "TEST FOR ADD CONNECTION FUNCTION" << endl;
	N.addConnection(1, 2); 
	N.addConnection(8, 9);
	cout << "---N---" << endl;
	cout << N;

	cout << endl << "NEIGHBOUR FUNCTION TEST" << endl;
	int p = 98;
	cout << "Num =" << p << endl;
	vector<int>n = N.getNeighbors(p);
	if (!n.empty())
	{
		cout << "Neighbours of " << p << " are ";
		for (int i = 0; i < n.size(); i++)
		{
			cout << n[i] << " ";
		}
	}
	else
	{
		cout << "Such net doesnt exist. Cannot print neighbours of " << p;
	}

	cout << endl;
	cout <<  endl << "NEIGHBOUR OF NEIGHBOUR FUNCTION TEST" << endl;
	int q = 0;
	cout << "Num =" << q << endl;
	vector<int>n1 = C.getNeighborsOfNeighbors(q);
	if (n1.empty())
	{
		cout << "DO NOT EXIST" << endl;
	}
	else
	{
		cout << "Neighbours of Neighbors of " << q << " are ";
		for (int i = 0; i < n1.size(); i++)
		{
			cout << n1[i] << " ";
		}
	}
	cout << endl << endl;

	cout << "TEST FOR DESTRUCTOR (CREATING A LOCAL INSTANCE)" << endl;
	{
		Network D("test2.txt");
		cout << "Destructor checked (No error)" << endl;
	}
	return 0;
}
