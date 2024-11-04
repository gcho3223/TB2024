#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        // -- near M8T2 only
        {"c", 0.863079},
        {"s", 0.831340},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};