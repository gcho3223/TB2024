#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    // -- w.r.t. M9T1
    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        {"c", 0.784739},
        {"s", 0.766002},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};