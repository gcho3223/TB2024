#include "TBread.h"
#include "TBdetector.h"
#include "TButility.h"
#include "TBconfig.h"

#include <chrono>
#include <vector>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char *argv[])
{
  int fRunNum = 6034;
  int fMaxEvent = -1;
  int fMaxFile = -1;

  ANSI_CODE ANSI = ANSI_CODE();

  TButility util = TButility();
  util.LoadMapping("../mapping/mapping_TB2024_v1.root");

  // 1 17 M11-T1-S 1 0 0 0
  // 1 26 M11-T2-C 1 1 0 0
  // 3 4 M1-T4-C 1 1 0 0

  std::vector<TBcid> aCID = {TBcid(1, 17), TBcid(3,4), TBcid(1, 26)};

  // or below is possible
  // std::vector<std::string> aName = {"M11-T1-S", "M1-T4-C", "M11-T2-C"};
  // std::vector<TBcid> aCID;
  // for (int i = 0; i < aName.size(); i++)
  //   aCID.push_back(util.GetCID(aName.at(i)));

  TBread<TBwaveform> readerWave = TBread<TBwaveform>(fRunNum, fMaxEvent, fMaxFile, false, "../sample_data", util.GetUniqueMID(aCID));

  if (fMaxEvent == -1)
    fMaxEvent = readerWave.GetMaxEvent();

  if (fMaxEvent > readerWave.GetMaxEvent())
    fMaxEvent = readerWave.GetMaxEvent();

  std::chrono::time_point time_begin = std::chrono::system_clock::now();

  for (int i = 0; i < fMaxEvent; i++) {
    if (i > 0 && i % 10 == 0) {

      std::chrono::duration time_taken = std::chrono::system_clock::now() - time_begin; // delete
      float percent_done = 1. * (float)i / (float)fMaxEvent;
      std::chrono::duration time_left = time_taken * (1 / percent_done - 1);
      std::chrono::minutes minutes_left = std::chrono::duration_cast<std::chrono::minutes>(time_left);
      std::chrono::seconds seconds_left = std::chrono::duration_cast<std::chrono::seconds>(time_left - minutes_left);
      std::cout << "\r\033[F" + ANSI.BOLD
                << " " << i << " / " << fMaxEvent << " events  " << minutes_left.count() << ":";
      printf("%02d left (%.1f %%) | ", int(seconds_left.count()), percent_done * 100);

      std::cout << ANSI.END << std::endl;
    }


    TBevt<TBwaveform> aEvent = readerWave.GetAnEvent();



  }


  return 0;
}
