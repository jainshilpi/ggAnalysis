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


workarea='#workarea'

mainOutputDir = '#mainOutputDir'

config                                = config()

config.General.requestName = '#jobname'
config.General.transferLogs = True
config.General.workArea = '%s' % workarea


config.Site.storageSite = '#storageSite'
config.Site.whitelist = [#whitelist]
config.Site.blacklist = [#blacklist]


config.JobType.psetName  = '#psetname'
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['#prefiringweights']
config.JobType.maxMemoryMB             = 2600
config.JobType.maxJobRuntimeMin        = 2500

config.Data.inputDBS = '#inputDBS'
config.Data.inputDataset = '#inputDataset'
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Data.outLFNDirBase = '%s' % mainOutputDir
config.Data.splitting     = '#splitting'
config.Data.unitsPerJob   = #unitsperjob
config.Data.ignoreLocality = True
#config.Data.totalUnits = #totalUnits
#config.Data.lumiMask = '#lumiMaskFile'
submit(config)
