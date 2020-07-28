Step 1: Set Up CMSSW
====================
**To skip this step, download setup.sh and run it in the desired directory.**<br>
export CMSSW_GIT_REFERENCE=/afs/cern.ch/cms/git-cmssw-mirror/cmssw.git <br>
cmsrel CMSSW_9_4_13 <br>
cd CMSSW_9_4_13/src <br>
cmsenv <br>
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
git cms-merge-topic cms-egamma:PhotonIDValueMapSpeedup1029;
scram b -j 16;
git clone git@github.com:cms-egamma/EgammaPostRecoTools.git  EgammaUser/EgammaPostRecoTools;
cd  EgammaUser/EgammaPostRecoTools; git checkout master; cd -;

git clone -b METv4 git@github.com:wadud001/aNTGC_gggNtuplizer.git
mv aNTGC_gggNtuplizer ggAnalysis
scram b -j8 <br>


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