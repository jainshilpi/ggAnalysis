#!/usr/bin/env python

from CRABClient.UserUtilities import config
from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

from datetime import date

def submit(config):
    try:
        crabCommand('submit', config = config)
    except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
    except ClientException as cle:
        print "Failed submitting task: %s" % (cle)


workarea='/afs/hep.wisc.edu/home/rusack/private/CMSSW_10_6_24/src/ggAnalysis/ggNtuplizer/test/crab_submit//jobs//jobsUL2017v1//TTGJetsTuneCP513TeVamcatnloFXFXmadspinpythia8RunIISummer20UL17MiniAODv2106Xmc2017realisticv9v1/'

mainOutputDir = '/store/user/rusack/aNTGCmet/ntuples/UL2017/jobsUL2017v1'

config                                = config()

config.General.requestName = 'TTGJetsTuneCP513TeVamcatnloFXFXmadspinpythia8RunIISummer20UL17MiniAODv2106Xmc2017realisticv9v1'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = ['T3_US_UCR','T3_US_FNALLPC','T3_US_Rice','T3_US_Rutgers','T3_US_FIT','T3_US_PSC','T3_US_OSU','T3_US_TAMU','T3_US_UMD','T3_US_VC3_NotreDame','T3_US_SDSC','T3_US_Colorado','T3_US_OSG','T3_US_Princeton_ICSE','T3_US_NERSC','T3_US_Baylor','T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_US_MIT','T3_US_TACC','T3_US_UMiss','T2_US_Caltech','T2_US_Florida','T2_US_Vanderbilt']
config.Site.blacklist = ['T2_US_Purdue']


config.JobType.psetName  = '/afs/hep.wisc.edu/user/rusack/private/CMSSW_10_6_24/src/ggAnalysis/ggNtuplizer/test/run_mc2017_106X.py'
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['/afs/hep.wisc.edu/home/rusack/private/CMSSW_10_6_24/src/ggAnalysis/ggNtuplizer/test/L1PrefiringMaps.root']
config.JobType.maxMemoryMB             = 2600
config.JobType.maxJobRuntimeMin        = 2500

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = 'FileBased'
config.Data.unitsPerJob   = 4
config.Data.ignoreLocality = True
config.Data.totalUnits = 50000
#config.Data.lumiMask = '/afs/hep.wisc.edu/home/rusack/private/CMSSW_10_6_24/src/ggAnalysis/ggNtuplizer/test/crab_submit//Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
submit(config)
