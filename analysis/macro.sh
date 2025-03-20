#!/bin/bash

# macro for all good runs

calibRun=(
    10458 10459 10457 10456
    10460 10463 10461 10462 
    10464 10465 10467 10466
    10450 10451 10449 10448
    10482 10483 10481 10480
    10468 10469 10479 10470 
    10444 10447 10445 10446
    10476 10477 10475 10474
    10478 10471 10473 10472
)

evt=-1

if [ "$1" == "ats" ]; then
    opt="produceHist_ATS"
elif [ "$1" == "dwc" ]; then
    opt="draw_DWC"
elif [ "$1" == "evt" ]; then
    opt="eventLoop"
else
    echo "Usage: $0 [ats|dwc|evt]"
    exit 1
fi

RunCompile="./compile.sh ${opt}"
eval $RunCompile

for ((run=0; run<${#calibRun[@]}; run++)); do
    echo "Processing run ${calibRun[run]}"
    RunCmd="./${opt} ${calibRun[run]} ${evt}"
    eval $RunCmd
done
