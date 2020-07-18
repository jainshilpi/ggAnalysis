#!/usr/bin/env python

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
import sys

config = config()


#**************************submit function***********************
from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException
def submit(config):
	try:
		crabCommand('submit', config = config)
	except HTTPException as hte:
		print "Failed submitting task: %s" % (hte.headers)
	except ClientException as cle:
		print "Failed submitting task: %s" % (cle)
#****************************************************************


workarea='/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/crab_submit/xsecJobs//SinglePhotonRun2017B31Mar2018v1MINIAOD/'

mainOutputDir = '#mainOutputDir'


config.General.requestName = 'SinglePhotonRun2017B31Mar2018v1MINIAOD'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = [#whitelist]
config.Site.blacklist = [#blacklist]


config.JobType.psetName  = '/afs/cern.ch/work/m/mwadud/private/naTGC/CMSSW_9_4_13/src/ggAnalysis/ggNtuplizer/test/run_data2017_94X.py'
config.JobType.pluginName  = 'Analysis'


config.Data.inputDBS = '#inputDBS'
config.Data.inputDataset = '/SinglePhoton/Run2017B-31Mar2018-v1/MINIAOD'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = '#splitting'
config.Data.unitsPerJob   = #unitsperjob
config.Data.ignoreLocality = True
#config.Data.totalUnits = #totalUnits
#config.Data.lumiMask = '#lumiMaskFile'
submit(config)
