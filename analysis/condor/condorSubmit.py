import os
import sys

# -- run list: https://docs.google.com/spreadsheets/d/1H2w0b0rfcMFYRcDRZUMS6uL91V1MmawK/edit?gid=390899459#gid=390899459
list_run_calib = [
10458, 10459, 10457, 10456, # -- M1, T1-4
10460, 10463, 10461, 10462,
10464, 10465, 10467, 10466,
10450, 10451, 10449, 10448,
10482, 10483, 10481, 10480,
10468, 10469, 10479, 10470, 
10444, 10447, 10445, 10446,
10476, 10477, 10475, 10474,
10478, 10471, 10473, 10472, # -- M9, T1-4
]

list_run_emScan = [
10547, 10555, 10554, 10557, 10533, 10556, 10553, # -- M5T1
10548, 10552, 10551, 10550, 10535, 10545, 10549, # -- M5T3
10560, 10562, 10561, 10559, 10538, 10544, 10558, # -- M8T2
10571, 10570, 10569, 10568, 10540, 10543, 10567, # -- M9T1
]

# -- runs for LC calibration: can be used MC ADC range check?
list_run_muBeam = [10509, 10503, 10505, 10507]

def Get_RunList(mode):
  if mode == "calib":
    return list_run_calib
  elif mode == "emScan":
    return list_run_emScan
  elif mode == "muBeam":
    return list_run_muBeam
  else:
    print("no run list for " + mode)
    sys.exit()

def CreateCondorDir():
    i = 1
    while "condor_v%03d" % (i) in os.listdir("."):
        i = i+1

    dirName = "condor_v%03d" % (i)
    os.mkdir(dirName)

    return os.path.abspath(dirName)

if __name__ == '__main__':
  # -- input values -- #
  mode = "calib"
  # mode = "muBeam"
  # mode = "emScan"
  
  # macro = "draw_DWC"
  # macro = "produceHist_ATS"
  macro = "eventLoop"
  # ------------------ #

  condorDir = CreateCondorDir()
  
  subFileName = "condorSub.txt"
  f = open(subFileName, "w")
  f.write(
"""
universe    = vanilla
executable  = run_macro.sh
getenv      = True
output      = {condorDir_}/job.$(ClusterId).$(ProcId).out
error       = {condorDir_}/job.$(ClusterId).$(ProcId).err
log         = {condorDir_}/job.$(ClusterId).$(ProcId).log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

+JobFlavour = "longlunch"
requirements = (Machine != "cluster341.knu.ac.kr" && Machine != "cluster275.knu.ac.kr" && Memory >= 2048 && Cpus >= 1)

""".format(condorDir_=condorDir)
  )

  f.write("Queue Arguments From (\n")
  for run in Get_RunList(mode):
    f.write("  %s %d\n" % (macro, run))
  f.write(")\n")
  f.close();
  os.system( "cp %s %s" % (subFileName, condorDir) )

  print("*** condor submission file is made ***")
  print("- macro    = %s" % macro)
  print("- run list = %s\n" % mode)
  print("to submit the jobs:")
  print("condor_submit %s\n" % subFileName )
