#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        // -- w.r.t. M5T1
        {"c", 0.753847},
        {"s", 0.756585},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};