#!/bin/bash

now="processed_$(date +"%Y_%m_%d__%H_%M_%S")"

mkdir $now
hadd $now/pp2_3_0_15.root spectrapp2*_0_3_0_15.root
hadd $now/pPb5_3_0_15.root spectrapPb5*_0_3_0_15.root
hadd $now/Pbp5_3_0_15.root spectraPbp5*_0_3_0_15.root
hadd $now/pPb5Pbp5_3_0_15.root spectra*5jet*_0_3_0_15.root
hadd $now/pp7_3_0_15.root spectrapp7*_0_3_0_15.root
hadd $now/pp2MC_3_0_15.root spectrapp2*_1_3_0_15.root
hadd $now/pPb5MC_3_0_15.root spectrapPb5*_1_3_0_15.root
hadd $now/pp7MC_3_0_15.root spectrapp7*_1_3_0_15.root

