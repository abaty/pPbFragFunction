#!/bin/bash

now="processed_$(date +"%Y_%m_%d__%H_%M_%S")"
UE=$(ls spectrapp2jet40_100_0_*|sed s/spectrapp2jet40_100_0_UE//|sed s/_0_15.root//)
echo $UE

mkdir $now
hadd $now/pp2_UE${UE}_0_15.root spectrapp2*_0_UE*_0_15.root
hadd $now/pPb5_UE${UE}_0_15.root spectrapPb5*_0_UE*_0_15.root
hadd $now/Pbp5_UE${UE}_0_15.root spectraPbp5*_0_UE*_0_15.root
hadd $now/pp7_UE${UE}_0_15.root spectrapp7*_0_UE*_0_15.root
hadd $now/pp2MC_UE${UE}_0_15.root spectrapp2*_1_UE*_0_15.root
hadd $now/pPb5MC_UE${UE}_0_15.root spectrapPb5*_1_UE*_0_15.root
hadd $now/pp7MC_UE${UE}_0_15.root spectrapp7*_1_UE*_0_15.root
hadd $now/pp5MC_UE${UE}_0_15.root spectrapp5*_1_UE*_0_15.root
