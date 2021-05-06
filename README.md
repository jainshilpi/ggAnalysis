Step 1: Set Up CMSSW
====================
**To skip this step, download setup.sh and run it in the desired directory.**<br>
export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git <br>
cmsrel CMSSW_10_6_18 <br>
cd CMSSW_10_6_18/src <br>
cmsenv <br>
git cms-init<br>
git cms-addpkg CondFormats/JetMETObjects<br>
git cms-addpkg JetMETCorrections/Modules;<br>
git cms-addpkg RecoBTag/Combined;  <br> 
git cms-addpkg JetMETCorrections/Type1MET;  <br> 
git cms-addpkg RecoMET/METFilters;  <br> 
git cms-addpkg RecoEgamma/PhotonIdentification/;  <br> 
git cms-addpkg RecoEgamma/ElectronIdentification/;  <br> 
git cms-addpkg CommonTools/PileupAlgos;  <br>
git cms-merge-topic -u cms-tau-pog:CMSSW_10_6_X_tau-pog_MVAdm
git cms-merge-topic -u cms-tau-pog:CMSSW_10_2_X_tau-pog_DeepTau2017v2p1_nanoAOD
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_102X_v3;  <br>
git cms-merge-topic -u cms-tau-pog:CMSSW_10_6_X_tau-pog_MVAdm; <br>
scram b -j 16;  <br>
git clone git@github.com:cms-egamma/EgammaPostRecoTools.git  EgammaUser/EgammaPostRecoTools;  <br>
cd  EgammaUser/EgammaPostRecoTools;  git checkout master;  cd -;  <br>

scram b -j 16;  <br>
git clone -b METv4 git@github.com:wadud001/aNTGC_gggNtuplizer.git<br>
mv aNTGC_gggNtuplizer ggAnalysis<br>
scram b -j16 <br>


Step 2: Edit crab script & submit
=================================
cd $CMSSW_BASE/src/ggAnalysis/ggNtuplizer/test/crab_submit/<br>
Open submit_crab_jobs.sh in text editor <br>
Modify the variables: <br>
* *input_datasets* - text file listing datasets <br>
* *writedir* - common directory for temporary crab files <br>
* *psetname* - python script for cmsRun <br>
* *writeSite* - site to write crab jobs <br>
* *mainOutputDir* - path to write crab outputs <br>

___Submit___ ./submit_crab_jobs.sh<br>
A log file named *crab_submitted_datasets_[date-time].log* will be created in *writedir* for the submissions. <br>


Step 3: Resubmit failed jobs
============================
./resubmit_crab_jobs __[log file from previous step]__


To-do
======
Add reco::CSCHaloData ("CSCHaloData") http://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_4_13/doc/html/d0/d04/classreco_1_1CSCHaloData.html
Add reco::CaloJet ("slimmedCaloJets") http://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_4_13/doc/html/d4/ddc/classreco_1_1CaloJet.html
