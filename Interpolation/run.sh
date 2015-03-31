if [ $# -ne 1 ]
then
  echo "Usage: ./run.sh <condor_iteration>"
  exit 1
fi

sleep $((1 * $1))

echo | awk -v i=$(($1%2)) -v j=$((($1%2)*3)) '{print "./run.exe masterList.txt masterMBList.txt "i" "j}' 
echo | awk -v i=$(($1%2)) -v j=$((($1%2)*3)) '{print "./run.exe masterList.txt masterMBList.txt "i" "j}' | bash

echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}'
echo | awk -v tag=$4 -v user=$USER '{print "mv spectra*.root /net/hisrv0001/home/"user"/pPb_Fragfunc/CMSSW_6_2_11/src/Interpolation/tempRootFiles/"}' | bash
rm *.root
echo "job done successfully"
