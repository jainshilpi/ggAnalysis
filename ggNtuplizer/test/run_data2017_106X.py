import FWCore.ParameterSet.Config as cms

process = cms.Process('ggKit')

##########################################################################
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet(allowUnscheduled=cms.untracked.bool(True))
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
### https://docs.google.com/presentation/d/1YTANRT_ZeL5VubnFq7lNGHKsiD7D3sDiOPNgXUYVI0I/edit#slide=id.g8b904a5927_2_0
### Data: 102X_dataRun2_v13 (2016, 2017, 2018 A-C), 102X_dataRun2_Prompt_v16 (2018 D)
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v13')
process.maxEvents = cms.untracked.PSet(
    input=cms.untracked.int32(2000))
process.MessageLogger.cerr.FwkReport.reportEvery = 500
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov///store/data/Run2017B/SinglePhoton/MINIAOD/UL2017_MiniAODv2-v1/280000/C7C4BD22-E226-FD4F-8197-A39C873FEA01.root'))

print(process.source)

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")

process.TFileService = cms.Service("TFileService", fileName=cms.string("anTGCtree_data.root"))
##########################################################################


##########################################################################################################################
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )
##########################################################################################################################


##########################################################################
## https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       runVID=True,
                       era='2017-UL',
                       eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
                       phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                                     'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
                       )
##########################################################################

##########################################################################
# include jetToolbox to add various jets
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox
# https://github.com/cms-jet/JetToolbox/blob/jetToolbox_102X_v3/python/jetToolbox_cff.py
# https://twiki.cern.ch/twiki/bin/view/CMS/IntroToJEC
# https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/JetMETCorrections/Configuration/python/JetCorrectors_cff.py
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections
from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/QGDataBaseVersion
jetToolbox(         process, 'ak4', 'ak4JetSubs', 'noOutput',
                    PUMethod='CHS',
                    runOnMC=False,
                    JETCorrPayload='AK4PFchs',
                    JETCorrLevels=['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'],
                    addPUJetID=True,
                    addQGTagger=True,
                    bTagDiscriminators=None,
                    postFix='updated'
           )

### https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI
jetToolbox(process, 'ak4', 'ak4JetSubs', 'noOutput',
            PUMethod='Puppi',
            runOnMC=False,
            JETCorrPayload='AK4PFPuppi',
            JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute'],
            addPUJetID=False, # not supported for Puppi
            addQGTagger=False,
            bTagDiscriminators=None,
            postFix='updated'
)
##########################################################################

##########################################################################
# https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription
# https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/PhysicsTools/PatUtils/python/tools/runMETCorrectionsAndUncertainties.py
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                          isData=True,
                          metType="PF",
                          pfCandColl=cms.InputTag("packedPFCandidates"),
                          recoMetFromPFCs=True,
                          CHS = True,
                          reclusterJets = True,
                          postfix="ModifiedPFMET"
                           )
## https://twiki.cern.ch/twiki/bin/view/CMS/ChargedPUMet
#
## Followed https://github.com/ajgilbert/Acorn/blob/66b517a6be284ddde70f6c3b6a0ade49ccf26437/NTupler/test/wgamma_cfg.py#L151
from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
makePuppiesFromMiniAOD(process, True)

runMetCorAndUncFromMiniAOD(process,
                            isData=True,
                            metType="Puppi",
                            pfCandColl=cms.InputTag("puppiForMET"),
                            recoMetFromPFCs=True,
                            jetFlavor="AK4PFPuppi",
                            reclusterJets = True,
                            postfix="Puppi"
                            )
process.puppiNoLep.useExistingWeights = True
process.puppi.useExistingWeights = True
##########################################################################


##########################################################################
process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")

process.ggNtuplizer.year = cms.int32(2017)
process.ggNtuplizer.doGenParticles = cms.bool(False)
process.ggNtuplizer.dumpPDFSystWeight = cms.bool(False)
process.ggNtuplizer.dumpJets = cms.bool(True)
process.ggNtuplizer.dumpTaus = cms.bool(True)
process.ggNtuplizer.getECALprefiringWeights = cms.bool(False)
process.ggNtuplizer.pfMETLabel=cms.InputTag("slimmedMETsModifiedPFMET")
process.ggNtuplizer.puppiMETLabel=cms.InputTag("slimmedMETsPuppi")
process.ggNtuplizer.ak4PFJetsCHSSrc = cms.InputTag("selectedPatJetsAK4PFCHSupdated")
process.ggNtuplizer.ak4PFJetsCHSGenJetLabel = cms.InputTag("selectedPatJetsAK4PFCHSupdated", "genJets", "ggKit")
process.ggNtuplizer.ak4PFJetsPUPPISrc =  cms.InputTag("selectedPatJetsAK4PFPuppiupdated")
process.ggNtuplizer.runOnSherpa = cms.bool(False)
process.ggNtuplizer.triggerEvent = cms.InputTag("slimmedPatTrigger")
##########################################################################


##########################################################################
updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = [  "dR0p32017v2",
                                "newDM2017v2",
                                "deepTau2017v1",
                                "deepTau2017v2p1"
                              ])
tauIdEmbedder.runTauID()

process.ggNtuplizer.tauSrc                    = cms.InputTag(updatedTauName)
##########################################################################



##########################################################################
process.load('RecoMET.METFilters.ecalBadCalibFilter_cfi')

#### https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#How_to_run_ecal_BadCalibReducedM
#### https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
baddetEcallist = cms.vuint32(
  [872439604,872422825,872420274,872423218,872423215,872416066,872435036,872439336,
    872420273,872436907,872420147,872439731,872436657,872420397,872439732,872439339,
    872439603,872422436,872439861,872437051,872437052,872420649,872421950,872437185,
    872422564,872421566,872421695,872421955,872421567,872437184,872421951,872421694,
    872437056,872437057,872437313,872438182,872438951,872439990,872439864,872439609,
    872437181,872437182,872437053,872436794,872436667,872436536,872421541,872421413,
    872421414,872421031,872423083,872421439])

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
    "EcalBadCalibFilter",
    EcalRecHitSource=cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt=cms.double(50.),
    baddetEcal=baddetEcallist,
    taggingMode=cms.bool(True),
    debug=cms.bool(False)
)

process.ggNtuplizer.ecalBadCalibFilter = cms.InputTag("ecalBadCalibReducedMINIAODFilter")
##########################################################################

##########################################################################
process.p = cms.Path(
    process.puppiMETSequence *
    process.fullPatMetSequencePuppi *
    process.fullPatMetSequenceModifiedPFMET *
    process.egammaPostRecoSeq *
    process.rerunMvaIsolationSequence *
    getattr(process,updatedTauName) *
    process.ecalBadCalibReducedMINIAODFilter *
    process.ggNtuplizer
)

# print process.dumpPython()
##########################################################################
