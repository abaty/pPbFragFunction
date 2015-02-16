if [ $# -ne 1 ]
then
  echo "Usage: ./run.sh <condor_iteration> <njobs>"
  exit 1
fi

echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "}' 
echo | awk -v i=$1 j=$2 '{print "./run.exe "i" "j" "}' | bash

echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}'
echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}' | bash
rm *.root
echo "job done successfully"
