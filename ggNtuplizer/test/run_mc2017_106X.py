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
### MC: 102X_mcRun2_asymptotic_v8 (2016), 102X_mc2017_realistic_v8 (2017), 102X_upgrade2018_realistic_v21 (2018)
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_mc2017_realistic_v8')
process.maxEvents = cms.untracked.PSet(
    input=cms.untracked.int32(100))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('file:test.root'))

print(process.source)

process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")

process.TFileService = cms.Service("TFileService", fileName=cms.string("anTGCtree_mc.root"))
##########################################################################


##########################################################################
from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
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
                    runOnMC=True,
                    JETCorrPayload='AK4PFchs',
                    JETCorrLevels=['L1FastJet', 'L2Relative', 'L3Absolute'],
                    addPUJetID=True,
                    addQGTagger=True,
                    bTagDiscriminators=None,
                    postFix='updated'
           )

### https://twiki.cern.ch/twiki/bin/viewauth/CMS/PUPPI
jetToolbox(process, 'ak4', 'ak4JetSubs', 'noOutput',
            PUMethod='Puppi',
            runOnMC=True,
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
                          isData=False,
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
                            isData=False,
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
# ECAL prefiring correction
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe#Call_the_producer_in_your_config
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe#Accessing_the_UL2017_maps
# https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/PhysicsTools/PatUtils/plugins/L1ECALPrefiringWeightProducer.cc
# https://github.com/cms-sw/cmssw-cfipython/blob/371ab6d166e50056cb14b4dc03b5876eb5fa5940/PhysicsTools/PatUtils/l1ECALPrefiringWeightProducer_cfi.py
from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
    TheJets = cms.InputTag("selectedPatJetsAK4PFCHSupdated"), 
    L1Maps = cms.string("root://cmsxrootd.fnal.gov//store/user/mwadud/aNTGC/ECALL1Prefiring/L1PrefiringMaps.root"),
    DataEra=cms.string("2017BtoF"),
    UseJetEMPt=cms.bool(False),
    PrefiringRateSystematicUncty=cms.double(0.2),
    SkipWarnings=False)
##########################################################################


##########################################################################
process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")

process.ggNtuplizer.year = cms.int32(2017)
process.ggNtuplizer.doGenParticles = cms.bool(True)
process.ggNtuplizer.dumpPDFSystWeight = cms.bool(True)
process.ggNtuplizer.dumpJets = cms.bool(True)
process.ggNtuplizer.dumpTaus = cms.bool(True)
process.ggNtuplizer.getECALprefiringWeights = cms.bool(True)
process.ggNtuplizer.pfMETLabel=cms.InputTag("slimmedMETsModifiedPFMET")
process.ggNtuplizer.puppiMETLabel=cms.InputTag("slimmedMETsPuppi")
process.ggNtuplizer.ak4PFJetsCHSSrc = cms.InputTag("selectedPatJetsAK4PFCHSupdated")
process.ggNtuplizer.ak4PFJetsCHSGenJetLabel = cms.InputTag("selectedPatJetsAK4PFCHSupdated", "genJets", "ggKit")
process.ggNtuplizer.ak4PFJetsPUPPISrc =  cms.InputTag("selectedPatJetsAK4PFPuppiupdated")
process.ggNtuplizer.runOnSherpa = cms.bool(False)
# process.ggNtuplizer.patTriggerResults = cms.InputTag("TriggerResults", "", "PAT")
process.ggNtuplizer.patTriggerResults = cms.InputTag("TriggerResults", "", "RECO")
# process.ggNtuplizer.triggerEvent=cms.InputTag("slimmedPatTrigger", "", "RECO")
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
    process.prefiringweight *
    process.ecalBadCalibReducedMINIAODFilter *
    process.ggNtuplizer
)

# print process.dumpPython()
##########################################################################
