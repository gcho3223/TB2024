#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        // -- SF without fit
        {"c", 0.764087},
        {"s", 0.768333},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};