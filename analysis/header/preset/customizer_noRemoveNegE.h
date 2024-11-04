#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    // -- when negative energy is not removed
    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        {"c", 0.907452},
        {"s", 0.923928},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};