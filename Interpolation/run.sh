if [ $# -ne 2 ]
then
  echo "Usage: ./run.sh <condor_iteration> <njobs>"
  exit 1
fi

sleep $((2 * $1))

nModes=3

echo | awk -v i=$1 -v j=$2 -v k=$(($1 % $nModes)) '{print "./run.exe "i" "j" "k}' 
echo | awk -v i=$1 -v j=$2 -v k=$(($1 % $nModes)) '{print "./run.exe "i" "j" "k}' | bash

echo | awk -v i=$1 -v j=$2 -v k=$((($1 + 1) % $nModes)) '{print "./run.exe "i" "j" "k}'
echo | awk -v i=$1 -v j=$2 -v k=$((($1 + 1) % $nModes)) '{print "./run.exe "i" "j" "k}' | bash

echo | awk -v i=$1 -v j=$2 -v k=$((($1 + 2) % $nModes)) '{print "./run.exe "i" "j" "k}'
echo | awk -v i=$1 -v j=$2 -v k=$((($1 + 2) % $nModes)) '{print "./run.exe "i" "j" "k}' | bash

echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}'
echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}' | bash
rm *.root
echo "job done successfully"
