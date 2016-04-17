#include <iostream>
#include <cmath>

using namespace std;

const int INF = 10001;



class VillageInfo
{
    int V; // number of villages
    int P; // number of police stations
    int* villagePositions;
	int solution;

public:
    VillageInfo();
    virtual ~VillageInfo();
    virtual void readInput();
    virtual void computeSolution();
	virtual int getSolution() const;

private:
    /*
     * D[n][k] stores the optimal solution for placing
     * stations 1..k among villages 1..n
     * for k >= n, D[n][k] == 0
     */
    int** D;
	/*
	 * Z[s][v] stores the minimum distance of 1..v 
	 * when placing a single station at s
	 */
	int** Z;

private:
	void initDPTable();
	void constructDPTable();
	void destroyDPTable();
	/*
	 * get the optimal solution for placing a single station
	 * among villages (n - m + 1)..n
	 * i.e. the last m of the first n villages
	 */
	virtual int getZ(int n, int m);

private:
	void dbgPrint0();
};



int main()
{
	VillageInfo v;
	v.readInput();
	v.computeSolution();
	cout << v.getSolution() << endl;
    return 0;
}



VillageInfo::VillageInfo()
{
    this->villagePositions = reinterpret_cast<int*>(0);
}

VillageInfo::~VillageInfo()
{
    if (this->villagePositions != reinterpret_cast<int*>(0))
        delete this->villagePositions;
}


void VillageInfo::readInput()
{
	// read in the number of villages and stations
    cin >> this->V >> this->P;
	// initialise the village positions array
    this->villagePositions = new int[this->V + 1];
	// read in all the village positions
    for (int i = 1; i <= this->V; i++)
        cin >> this->villagePositions[i];
}

void VillageInfo::computeSolution()
{
	this->initDPTable();

	this->constructDPTable();
	this->solution = this->D[this->V][this->P];

	this->destroyDPTable();
}

int VillageInfo::getSolution() const
{
	return this->solution;
}


void VillageInfo::initDPTable()
{
	// allocate memory
	this->D = new int*[this->V + 1];
	this->Z = new int*[this->V + 1];
	for (int n = 1; n <= this->V; n++)
	{
		this->D[n] = new int[this->P + 1];
		this->Z[n] = new int[this->V + 1];
	}
	
	// initialise values
	for (int n = 1; n <= this->V; n++)
		for (int k = 1; k <= this->P; k++)
			if (k >= n)	this->D[n][k] = 0;
			else		this->D[n][k] = INF;
}

void VillageInfo::constructDPTable()
{
	// construct Z
	for (int s = 1; s <= this->V; s++)
	{
		Z[s][1] = abs(villagePositions[1] - villagePositions[s]);
		for (int v = 2; v <= this->V; v++)
			Z[s][v] = Z[s][v-1] + abs(villagePositions[v] - villagePositions[s]);
	}

	// construct D
	for (int n = 1; n <= this->V; n++)
	{
		D[n][1] = getZ(n, n);
	}

	for (int k = 2; k <= this->P; k++)
	{
		for (int n = 1; n <= this->V; n++)
		{
			int dist = INF;
			for (int m = 0; m < n; m++)
			{
				int candidate = D[n-m][k-1] + getZ(n, m);
				dist = (candidate < dist) ? candidate : dist;
			}
			D[n][k] = dist;
		}
	}
	this->dbgPrint0();
}

void VillageInfo::destroyDPTable()
{
	for (int n = 1; n <= this->V; n++)
	{
		delete this->Z[n];
		delete this->D[n];
	}
	delete Z;
	delete D;
}

int VillageInfo::getZ(int n, int m)
{
	// include start and end points
	int startV = n - m + 1;
	int endV = n;
	if (startV > endV) return 0; // zero is the most sensible return value in this case

	int minDistance = INF;
	if (startV == 1)
	{
		for (int s = startV; s <= endV; s++)
		{
			int candidate = Z[s][endV];
			minDistance = (candidate < minDistance) ? candidate : minDistance;
		}
	}
	else
	{
		for (int s = startV; s <= endV; s++)
		{
			int candidate = Z[s][endV] - Z[s][startV - 1];
			minDistance = (candidate < minDistance) ? candidate : minDistance;
		}
	}

	return minDistance;
}


void VillageInfo::dbgPrint0()
{
#ifdef DBG
	for (int v=1; v<=V; v++) cout << villagePositions[v] << "\t";
	cout << endl << endl;
	for (int n=1; n<=V; n++)
	{
		for (int k=1; k<=P; k++)
		{
			cout << D[n][k] << "\t";
		}
		cout << endl;
	}
#endif
}
