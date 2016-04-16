#include <iostream>

using namespace std;


class VillageInfo
{
    unsigned int V; // number of villages
    unsigned int P; // number of police stations
    unsigned int* villagePositions;

public:
    VillageInfo();
    virtual ~VillageInfo();
    virtual void readInput();
    virtual void computeSolution();

private:
    /*
     * D[n][k] stores the optimal solution for placing
     * k stations among the first n stations
     * for k >= n, D[n][k] == 0
     */
    unsigned int** D;
};


int main()
{
    return 0;
}


VillageInfo::VillageInfo()
{
    this->villagePositions = reinterpret_cast<unsigned int*>(0);
}
VillageInfo::~VillageInfo()
{
    if (this->villagePositions != reinterpret_cast<unsigned int*>(0))
        delete this->villagePositions;
}

void VillageInfo::readInput()
{
    cin >> this->V >> this->P;
    this->villagePositions = new unsigned int[this->V];
    for (unsigned int i = 0; i < this->V; i++)
        cin >> this->villagePositions[i];
}
void VillageInfo::computeSolution()
{
}
