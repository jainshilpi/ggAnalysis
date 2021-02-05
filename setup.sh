#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;
presentDir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )
cd $presentDir
eval 'scramv1 project CMSSW CMSSW_9_4_13'
source /cvmfs/cms.cern.ch/cmsset_default.sh;
cd ${presentDir}/CMSSW_10_6_18/src
eval `scramv1 runtime -sh`;
git cms-init
git cms-addpkg CondFormats/JetMETObjects
git cms-addpkg JetMETCorrections/Modules;
git cms-addpkg RecoBTag/Combined;   
git cms-addpkg JetMETCorrections/Type1MET;   
git cms-addpkg RecoMET/METFilters;   
git cms-addpkg RecoEgamma/PhotonIdentification/;   
git cms-addpkg RecoEgamma/ElectronIdentification/;   
git cms-addpkg CommonTools/PileupAlgos;  
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_102X_v3;  
git cms-merge-topic -u cms-tau-pog:CMSSW_10_6_X_tau-pog_MVAdm; 
scram b -j 16;  
git clone git@github.com:cms-egamma/EgammaPostRecoTools.git  EgammaUser/EgammaPostRecoTools;  
cd  EgammaUser/EgammaPostRecoTools;  git checkout master;  cd -;  

scram b -j 16;  
git clone -b METv4 git@github.com:wadud001/aNTGC_gggNtuplizer.git
mv aNTGC_gggNtuplizer ggAnalysis
scram b -j16 