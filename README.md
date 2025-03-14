# Code for TB2024 paper

## Quick Start (under centOS)
### First setup
```bash
bash # -- in KNU; change from csh to bash
git clone git@github.com:KyeongPil-Lee/TB2024.git -b TB2024Paper
cd TB2024
source buildNinstall.sh
source envset.sh
```

### After the first setup
```bash
source envset.sh
```

### Examples
1. Produce average time structure (ATS) histograms
```bash
# -- compile a code
./compile.sh produceHist_ATS.cc
# -- run 10482: calibration run (10000 events), 60 GeV e+ beam @M5T1
./produceHist_ATS 10482 100
```
-> results: `./Avg/Avg_Run_10482.root` (`./Avg` is automatically created)

2. Draw DWC position plots (the output will be used in the event loop to obtain DWC offset)
```bash
./compile.sh draw_DWC.cc
./draw_DWC 10482
```
-> results: `./DWC/DWC_Run_10482.root` (`./DWC` is automatically created)

3. Event loop: produce histograms for intADC and (calibrated) energy distributions
```bash
# -- use the input values defined in header/preset.h and header/customizer.h: need to check before running!
# ---- e.g. integration range, AUX detector cut values, calibration constants, scale factors, etc
# -- it needs the output file at step 2 (./DWC/DWC_Run_10482.root)
./compile.sh eventLoop.cc
./eventLoop 10482 -1
```
-> results: `./Hist/Hist_Run_10482.root` (`./Hist` is automatically created)

### condor submission (for parallel processing)
NOTE: sometimes, the output file is not made for a few jobs depending on the server status -> need to check carefully!

```bash
cd condor
# -- create a condor submission file (not submitting yet)
# -- open condorSubmit.py and adjust parameters under if __name__ == '__main__' (mode and macro)
python condorSubmit.py

# -- submit the jobs
condor_submit condorSub.txt
```
-> results: made under `./condor/condor_vXYZ` (XYZ is the version number; automatically increased to avoid duplication)

## Analysis code structure (under `./analysis`)

### Event loop codes (main codes to run)
* `produceHist_ATS.cc`: produce average time structure (ATS) histograms
* `draw_DWC.cc`: draw DWC position plots (no change from KY & SW's repository)
* `eventLoop.cc`: event loop code for producing intADC and (calibrated) energy histograms

### Header files (under `./header`)
* `./detector/*`: collection of classes representing detectors
   * `DRCFiber.h`: the smallest unit of DRC
   * `DRCTower.h`: a tower of DRC containing S- and C-fibers
   * `DRCModule.h`: a module of DRC containing 4 towers
   * `DRC.h`: DRC class containing 9 modules (or smaller units), representing the whole DRC
   * `AuxDetector.h`: auxiliary detector class (preshower, muon chamber)
   * `DWC.h`: DWC class
   * `DWCPair.h`: a pair of DWCs

* `./preset/*`: preset and customizer files
  * Define common values widely used in the analysis codes (e.g. integration range, AUX detector cut values, calibration constants, scale factors, etc)
  * Several different preset or customizer files exist for each purpose: the setting that you want to use should be selected by symbolic links with the name of `./header/preset.h` and `./header/customizer.h`
  * Dedicated explanation: `./preset/README.md`

* `ATS.h`: class for easily calculating average time structure (ATS)
* `commonTool.h`: collection of common tools
* `HistContainer.h`: class for easily managing histograms (declaration, filling, saving, etc)
  * `HistSet.h`: class for managing a set of arbitrary histograms (used in `HistContainer.h`)

### PostProcessing codes (under `./postProcess`)
Codes to post-process the results of the event loop
(explanation will be updated soon)


## Reference

### Base code

```bash
git clone git@github.com:swkim95/TB2024.git -b TB2024_centos
```

### ntuples

```
/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2024_DRC_TB_ntuple
```

### physics runs

* [google sheet](https://docs.google.com/spreadsheets/d/1H2w0b0rfcMFYRcDRZUMS6uL91V1MmawK/edit?usp=sharing&ouid=117548372861877042914&rtpof=true&sd=true)





