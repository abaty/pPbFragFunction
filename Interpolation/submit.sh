if [ $# -ne 0 ]
then
  echo "Usage: ./psort.sh <trackqual> <file-list> <tag> <nmin> <nmax> <pttrigmin> <pttrigmax> <ptassmin> <ptassmax>"
  exit 1
fi

now="spectra_$(date +"%Y_%m_%d__%H_%M_%S")"
njobs=25

mkdir $now
cp fake*.root $now
cp eff*.root $now
cp secondary*.root $now

cp run.sh $now
cat run.condor | sed "s@log_flag@$now@g" | sed "s@dir_flag@$PWD/$now@g" | sed "s@user_flag@$USER@g" |  sed "s@arglist@$njobs@g" | sed "s@transfer_filelist@run.exe@g" | sed "s@njobs@$njobs@g" > $now/run.condor

NAME="Spectra.C"
g++ $NAME $(root-config --cflags --libs) -Werror -Wall -O2 -o "run.exe"
cp run.exe $now
rm run.exe
echo
cat $now/run.condor
echo 
echo condor_submit $now/run.condor
echo
# condor_submit $now/run.condor

