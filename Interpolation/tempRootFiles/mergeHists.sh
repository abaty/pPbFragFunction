#!/bin/bash

now="processed_$(date +"%Y_%m_%d__%H_%M_%S")"

mkdir $now
hadd $now/pp2_UE0_0_15.root spectrapp2*_0_UE0_0_15.root
hadd $now/pPb5_UE0_0_15.root spectrapPb5*_0_UE0_0_15.root
hadd $now/Pbp5_UE0_0_15.root spectraPbp5*_0_UE0_0_15.root
hadd $now/pp7_UE0_0_15.root spectrapp7*_0_UE0_0_15.root
hadd $now/pp2MC_UE0_0_15.root spectrapp2*_1_UE0_0_15.root
hadd $now/pPb5MC_UE0_0_15.root spectrapPb5*_1_UE0_0_15.root
hadd $now/Pbp5MC_UE0_0_15.root spectraPbp5*_1_UE0_0_15.root
hadd $now/pp7MC_UE0_0_15.root spectrapp7*_1_UE0_0_15.root
hadd $now/pp5MC_UE0_0_15.root spectrapp5*_1_UE0_0_15.root
hadd $now/pp2_UE3_0_15.root spectrapp2*_0_UE3_0_15.root
hadd $now/pPb5_UE3_0_15.root spectrapPb5*_0_UE3_0_15.root
hadd $now/Pbp5_UE3_0_15.root spectraPbp5*_0_UE3_0_15.root
hadd $now/pp7_UE3_0_15.root spectrapp7*_0_UE3_0_15.root
hadd $now/pp2MC_UE3_0_15.root spectrapp2*_1_UE3_0_15.root
hadd $now/pPb5MC_UE3_0_15.root spectrapPb5*_1_UE3_0_15.root
hadd $now/Pbp5MC_UE3_0_15.root spectraPbp5*_1_UE3_0_15.root
hadd $now/pp7MC_UE3_0_15.root spectrapp7*_1_UE3_0_15.root
hadd $now/pp5MC_UE3_0_15.root spectrapp5*_1_UE3_0_15.root
