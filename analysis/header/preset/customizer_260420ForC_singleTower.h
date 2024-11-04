#include "printHelper.h"
// -- customize the condition defined in preset.h

namespace TB2024 {

  void Customize_Preset() {

    TB2024::map_sf.clear(); // -- remove existing values
    TB2024::map_sf.insert(
      { 
        // -- single tower only
        {"c", 0.8631438573},
        {"s", 0.8638638639},
      }
    );

    Print_SF(TB2024::map_sf);
  }

};