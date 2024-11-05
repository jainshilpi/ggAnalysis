from CRABClient.UserUtilities import config
import sys

config = config()


#**************************submit function***********************
from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
#****************************************************************


config.General.workArea     = 'crab_projects_ntuples'
config.JobType.pluginName   = 'Analysis' # PrivateMC
config.JobType.psetName     = 'run_mc2022_133X.py'
config.Data.inputDBS        = 'global'    
config.Data.splitting       = 'FileBased' # EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
config.Data.totalUnits      = -1
config.Data.publication     = False
config.Site.storageSite     = 'T2_CH_CERN'

# dataset dependent configuration

config.General.requestName = 'G_4jet_100To200'
config.Data.unitsPerJob    = 10
config.Data.inputDataset   = '/G-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/'




config.General.requestName = 'G_4jet_200To400'
config.Data.unitsPerJob    = 10
config.Data.inputDataset   = '/G-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/'



config.General.requestName = 'G_4jet_400To600'
config.Data.unitsPerJob    = 10
config.Data.inputDataset   = '/G-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/'


config.General.requestName = 'G_4jet_600'
config.Data.unitsPerJob    = 10
config.Data.inputDataset   = '/G-4Jets_HT-600_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/'




#############G+jet samples
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/GJetPtBin'
config.Data.unitsPerJob    = 10

#config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/GJetPtBin/fullMotherInfo'
#config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/GJetPtBin/fullMotherInfo/v1'
#config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/GJetPtBin/v1'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/GJetPtBin/v2'
config.General.requestName = 'G_jet_pt100to200'
config.Data.inputDataset   = '/GJ_PTG-100to200_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v3/MINIAODSIM'

####


#####

config.General.requestName = 'G_jet_pt200to400'
config.Data.inputDataset   = '/GJ_PTG-200to400_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v3/MINIAODSIM'


'''
config.General.requestName = 'G_jet_pt400to600'
config.Data.inputDataset   = '/GJ_PTG-400to600_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v1/MINIAODSIM'


config.General.requestName = 'G_jet_pt600'
config.Data.inputDataset   = '/GJ_PTG-600_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v1/MINIAODSIM'



#config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/QCDHTBin/'
config.Data.outLFNDirBase  = '/store/user/shilpi/highPtPhotonID/QCDHTBin/v1'
config.Data.unitsPerJob    = 2

config.General.requestName = 'qcd_100to200'
config.Data.inputDataset = '/QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_200to400'
config.Data.inputDataset = '/QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_400to600'
config.Data.inputDataset = '/QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_600to800'
config.Data.inputDataset ='/QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_800to1000'
config.Data.inputDataset = '/QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_1000to1200'
config.Data.inputDataset = '/QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_1200to1500'
config.Data.inputDataset = '/QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_1500to2000'
config.Data.inputDataset = '/QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'


config.General.requestName = 'qcd_2000toinf'
config.Data.inputDataset = '/QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM'
'''


'''
/QCD-4Jets_HT-40to70_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM

/QCD-4Jets_HT-70to100_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2/MINIAODSIM
'''
