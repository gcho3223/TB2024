#!/bin/bash

#!/bin/bash
cd $INSTALL_DIR_PATH/../analysis
echo "working directory: "$(pwd)

echo "Will run:"
echo "ROOT macro:   $1"
echo "run number:   $2"

cmd="./$1 $2 -1" # -- always run over the full stat.

echo "will run: $cmd"
eval $cmd

echo "done"