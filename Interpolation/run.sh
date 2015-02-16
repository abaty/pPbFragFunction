if [ $# -ne 1 ]
then
  echo "Usage: ./run.sh <condor_iteration> <njobs>"
  exit 1
fi

echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "0}' 
echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "0}' | bash

echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "1}'
echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "1}' | bash

echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "2}'
echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "2}' | bash

sleep $((10 * $1))

echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}'
echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}' | bash
rm *.root
echo "job done successfully"
