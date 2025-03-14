# Preset and customizer

## Preset (preset_*.h)
* define basic values used over the analysis
* e.g. integration range, AUX detector cut values, calibration constants, scale factors, etc
* to use a specific preset file: **make a symbolic link** under `./header` with the name `preset.h`
   * e.g. under `./header`, `ln -s ./preset/preset_default.h preset.h`

### List of preset files
* `preset_default.h`: default preset values (scale factors are calculated with resepct to M8T2)



## Customizer (customizer_*.h)
* customize the preset values used in the analysis
  * Change only a few values from the preset values: easier to understand what was changed (instead of copying and changing the whole preset file)
* to use a specific customizer file: **make a symbolic link** under `./header` with the name `customizer.h`
   * e.g. under `./header`, `ln -s ./preset/customizer_nearM8T2.h customizer.h`

### List of customizer files
* `customizer.h`: default one, nothing is changed from the preset values -> keep it as `./header/customizer.h` if you don't want to change anything
* `customizer_M5T1.h`: customize scale factors with respect to M5T1
* `customizer_M5T3.h`: customize scale factors with respect to M5T3
* `customizer_M9T1.h`: customize scale factors with respect to M9T1
* `customizer_nearM8T2.h`: customize scale factors with respect to the towers near M8T2 only
* `customizer_singleTower.h`: customize scale factors with respect to the single tower only
