#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

bool recordSample(int sample, int &latest, int &callCount);
int nextPacketSequence();




int main()
{
    int latest{}, callCount{};
    recordSample(0, latest, callCount);
    recordSample(4096, latest, callCount);
    recordSample(4095, latest, callCount);
    recordSample(-1, latest, callCount);

    return 0;
}

bool recordSample(int sample, int &latest, int &callCount)
{
    static int success{};
    
    if (sample > 4095 || sample < 0)
    {
        std::cout << "FAIL  " << "latest:  " << latest << "success:  " << success << "callCount:  " << callCount << "\n";
        return false;
    }
    success++;
    callCount = nextPacketSequence();
    latest = sample;
    std::cout << "PASS  " << "latest:  " << latest << "success:  " << success << "callCount:  " << callCount << "\n";
    return true;
}
int nextPacketSequence()
{
    static int  count{};
   return  ++count;
}
