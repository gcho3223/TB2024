# PostProcess
Code for post-processing the outputs from event loops
* Draw validation plots
  * Draw average time structure distributions
  * Draw cut-flow plots (intADC distribution after applying cuts one by one)
  * Draw energy distribution
  * ...
* Calculate calibration constants and scale factor
* Calculate energy resolution or scale per energy and fit (final results)

## Codes
### header
* `SimplePlotTools.h`: Collection of classes and functions to easily draw plots
* `RunInfo.h`: pre-define the runs for its purpose (calibration, muon beam, energy scan per each center tower)
* `GausFitter.h`: fitter to fit a given distribution with gaussian function

### ATS
ATS = average time structure
* `comp_ATS.cc`
  * Input: output `.root` files from `produceHist_ATS.cc` for all calibration runs and muon beam runs
    * The path to the input directory should be given when `PlotProducer` is declared, e.g. `PlotProducer producer("./Avg");`
  * Output: various ATS distributions for each run

### Calib
Directory for the codes used in the calibration steps
* `producePlot.cc`: one-step code to produce cut-flow plots, calculate calibration constant, and the scale factor
  * Input: output `.root` files from `eventLoop.cc` for all calibration runs
    * The path to the input directory shoudl be given in the code
* `CutEffectChecker.h`
  * Used in `producePlot.cc`
  * Produce various plots useful to check the cut effects
* `Calibrator.h`
  * Used in `producePlot.cc`
  * Calculate calibration constants and relevant plots
* `ScaleFactor.h`
  * Used in `producePlot.cc`
  * Calculate the scale factor: the output is meaningful only when the input `.root` file is made with the proper calibration constants

### EMResol
Codes for EM resolution results (resolution vs. energy and uniformity)
* `produce_emResol.cc`: calculate resolution vs. energy, scale vs. energy and draw corresponding plots
  * Input
    * Center tower to be used (e.g. `M8-T2`)
    * output `.root` files from `eventLoop.cc` for all EM scan runs with respect to the center tower specified above
      * Calibration constants & scale factor should be applied to obtain the correct results
* `EMResolution.h`
  * Used in `produce_emResol.cc`
  * Contains all details for the EM resolution calculation


