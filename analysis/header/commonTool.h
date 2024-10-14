#include <TStopwatch.h>
#include <iostream>

namespace TB2024 {

class Timer {
public:
  void Start() { timer_.Start(); }

  void PrintRunTime()
  {
    Double_t cpuTime = timer_.CpuTime();
    Double_t realTime = timer_.RealTime();

    std::cout << std::endl;
    std::cout << "************************************************" << std::endl;
    std::cout << "Total real time: " << realTime << " seconds = " << realTime / 60.0 << " minutes = " << realTime / (60.0*60.0) << " hours" << std::endl;
    std::cout << "Total CPU time:  " << cpuTime  << " seconds = " << cpuTime / 60.0  << " minutes = " << cpuTime / (60.0*60.0)  << " hours" << std::endl;
    std::cout << "  CPU time / real time = " << cpuTime / realTime << std::endl;
    std::cout << "************************************************" << std::endl;
  }

private:
  TStopwatch timer_;
};

}; // -- namespace TB2024