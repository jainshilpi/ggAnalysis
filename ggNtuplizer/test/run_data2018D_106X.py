import FWCore.ParameterSet.Config as cms

process = cms.Process('ggKit')

##########################################################################
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet(allowUnscheduled=cms.untracked.bool(True))
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
### https://docs.google.com/presentation/d/1YTANRT_ZeL5VubnFq7lNGHKsiD7D3sDiOPNgXUYVI0I/edit#slide=id.gdb258dcfc1_1_7
### Data: 102X_dataRun2_v13 (2016, 2017, 2018 A-C), 102X_dataRun2_Prompt_v16 (2018 D)

### Recalibrate ECAL rechit timing https://hypernews.cern.ch/HyperNews/CMS/get/ecal-calibration/1633.html
### https://indico.cern.ch/event/966025/contributions/4170419/attachments/2170447/3664371/ECALDPG_2021_1_13.pdf
from CondCore.CondDB.CondDB_cfi import *
process.GlobalTag = cms.ESSource("PoolDBESSource",
                                 CondDB.clone(connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')),
                                 globaltag = cms.string('102X_dataRun2_Prompt_v16'),
                                 # Get time calibration (corrections) tag
                                 toGet = cms.VPSet(cms.PSet(record = cms.string("EcalTimeCalibConstantsRcd"),
                                                  tag = cms.string("EcalTimeCalibConstants_2018_RunD_UL_Corr_v2"),
                                                  connect = cms.string("sqlite_file:EcalTimeCalibConstants_2018_RunD_UL_Corr_v2.db"),
                                          )
                                 )
)

process.load("RecoLocalCalo.EcalRecProducers.ecalRecalibRecHit_cfi")
process.ecalRecalibRecHit.EBRecHitCollection        = cms.InputTag("reducedEgamma", "reducedEBRecHits")
process.ecalRecalibRecHit.EERecHitCollection        = cms.InputTag("reducedEgamma", "reducedEERecHits")
process.ecalRecalibRecHit.EBRecalibRecHitCollection = cms.string('recalibEcalRecHitsEB')
process.ecalRecalibRecHit.EERecalibRecHitCollection = cms.string('recalibEcalRecHitsEE')
process.ecalRecalibRecHit.doTimeCalib               = True
process.recalib_sequence                            = cms.Sequence(process.ecalRecalibRecHit)


process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(100))
process.MessageLogger.cerr.FwkReport.reportEvery = 5000
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('file:2018D_DatTest.root'))

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
# 2016ULpreVFP : era='2016preVFP-UL'
# 2016ULpostVFP : era='2016postVFP-UL'
# 2017 UL, era='2017-UL'
# 2018 UL, era='2018-UL'
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       runVID=True,
                       era='2018-UL',
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
                            postfix="PuppiUpdated"
                            )
process.puppiNoLep.useExistingWeights = True
process.puppi.useExistingWeights = True
##########################################################################


##########################################################################
process.load("ggAnalysis.ggNtuplizer.ggNtuplizer_miniAOD_cfi")

process.ggNtuplizer.year = cms.int32(2018)
process.ggNtuplizer.doGenParticles = cms.bool(False)
process.ggNtuplizer.dumpPDFSystWeight = cms.bool(False)
process.ggNtuplizer.dumpJets = cms.bool(True)
process.ggNtuplizer.dumpTaus = cms.bool(True)
process.ggNtuplizer.getECALprefiringWeights = cms.bool(False)
process.ggNtuplizer.pfMETLabel=cms.InputTag("slimmedMETsModifiedPFMET")
process.ggNtuplizer.puppiMETLabel=cms.InputTag("slimmedMETsPuppiUpdated")
process.ggNtuplizer.ak4PFJetsCHSSrc = cms.InputTag("selectedPatJetsAK4PFCHSupdated")
process.ggNtuplizer.ak4PFJetsCHSGenJetLabel = cms.InputTag("selectedPatJetsAK4PFCHSupdated", "genJets", "ggKit")
process.ggNtuplizer.ak4PFJetsPUPPISrc =  cms.InputTag("selectedPatJetsAK4PFPuppiupdated")
process.ggNtuplizer.runOnSherpa = cms.bool(False)
process.ggNtuplizer.triggerEvent = cms.InputTag("slimmedPatTrigger", "", "RECO")
process.ggNtuplizer.triggerResults = cms.InputTag("TriggerResults", "", "HLT")
process.ggNtuplizer.patTriggerResults = cms.InputTag("TriggerResults", "", "RECO")
process.ggNtuplizer.isoTrkSrc = cms.InputTag("isolatedTracks", "", "RECO")
process.ggNtuplizer.ebReducedRecHitCollection = cms.InputTag("ecalRecalibRecHit", "recalibEcalRecHitsEB")
process.ggNtuplizer.eeReducedRecHitCollection = cms.InputTag("ecalRecalibRecHit", "recalibEcalRecHitsEE")
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

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter("EcalBadCalibFilter",
                                                      # EcalRecHitSource=cms.InputTag("reducedEgamma:reducedEERecHits"),
                                                      EcalRecHitSource=cms.InputTag("ecalRecalibRecHit:recalibEcalRecHitsEE"),
                                                      ecalMinEt=cms.double(50.),
                                                      baddetEcal=baddetEcallist,
                                                      taggingMode=cms.bool(True),
                                                      debug=cms.bool(False)
                                                    )

process.ggNtuplizer.ecalBadCalibFilter = cms.InputTag("ecalBadCalibReducedMINIAODFilter")
##########################################################################


##########################################################################
process.triggerSelection = cms.EDFilter( "TriggerResultsFilter",
                            triggerConditions = cms.vstring(
                                                        "HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_v*",        ##0
                                                        "HLT_DoubleEle25_CaloIdL_MW_v*",                    ##1
                                                        # "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v*",            ##2
                                                        "HLT_DoubleEle33_CaloIdL_MW_v*",                    ##3
                                                        # "HLT_DoubleEle37_CaloIdL_GsfTrackIdVL_v*",          ##4
                                                        # "HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v*",      ##5
                                                        # "HLT_DoublePhoton60_v*",                            ##6
                                                        "HLT_DoublePhoton70_v*",                            ##7
                                                        # "hltEGL1SingleEGOrFilter",                         ##8
                                                        "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*",                 ##9
                                                        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*",     ##10
                                                        "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*",        ##11
                                                        # "HLT_Ele25_eta2p1_WPTight_Gsf_v*",                  ##12
                                                        "HLT_Ele27_WPTight_Gsf_v*",                         ##13
                                                        # "hltEle32L1DoubleEGWPTightGsfTrackIsoFilter",      ##14
                                                        "HLT_Ele32_WPTight_Gsf_L1DoubleEG_v*",              ##15
                                                        "HLT_Ele32_WPTight_Gsf_v*",                         ##16
                                                        "HLT_Ele35_WPTight_Gsf_v*",                         ##17
                                                        # "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v*", ##18
                                                        "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v*",         ##19
                                                        # "hltL1sSingleEGor",                                ##20
                                                        "HLT_Photon175_v*",                                 ##21
                                                        "HLT_Photon200_v*",                                 ##22

                                                        "HLT_IsoMu24_v*",                                   ##0
                                                        "HLT_IsoMu27_v*",                                   ##1
                                                        # "HLT_IsoTkMu24_v*",                                 ##2
                                                        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*",   ##3
                                                        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*",     ##4
                                                        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*",           ##5
                                                        "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*",              ##6
                                                        # "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",         ##7
                                                        # "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",            ##8
                                                        "HLT_Mu50_v*",                                      ##9
                                                        "HLT_Mu50_v*",                                      ##10
                                                        "HLT_OldMu100_v*",                                  ##11
                                                        "HLT_TkMu100_v*",                                   ##12
                                                        # "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*",       ##13
                                                        # "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*",          ##14
                                                        # "HLT_TkMu50_v*",                                    ##15

                                                        "HLT_AK4CaloJet100_v*",
                                                        "HLT_AK4CaloJet120_v*",
                                                        "HLT_AK4CaloJet30_v*",
                                                        "HLT_AK4CaloJet40_v*",
                                                        "HLT_AK4CaloJet50_v*",
                                                        "HLT_AK4CaloJet80_v*",
                                                        "HLT_AK4PFJet100_v*",
                                                        "HLT_AK4PFJet120_v*",
                                                        "HLT_AK4PFJet30_v*",
                                                        "HLT_AK4PFJet50_v*",
                                                        "HLT_AK4PFJet80_v*",
                                                        "HLT_CaloJet500_NoJetID_v*",
                                                        "HLT_CaloJet550_NoJetID_v*",
                                                        # "HLT_CaloMET250_NotCleanedHLT_CaloMET250_HBHECleanedHLT_CaloMET300_HBHECleanedHLT_CaloMET350_HBHECleaned_v*",
                                                        "HLT_DiPFJetAve100_HFJEC_v*",
                                                        "HLT_DiPFJetAve140_v*",
                                                        # "HLT_DiPFJetAve15_HFJECHLT_DiPFJetAve25_HFJECHLT_DiPFJetAve35_HFJECHLT_DiPFJetAve60_HFJECHLT_DiPFJetAve80_HFJECHLT_DiPFJetAve100_HFJECHLT_DiPFJetAve160_HFJECHLT_DiPFJetAve220_HFJECHLT_DiPFJetAve300_HFJEC_v*",
                                                        # "HLT_DiPFJetAve15_HFJEC_v*",
                                                        "HLT_DiPFJetAve160_HFJEC_v*",
                                                        "HLT_DiPFJetAve200_v*",
                                                        "HLT_DiPFJetAve220_HFJEC_v*",
                                                        # "HLT_DiPFJetAve25_HFJEC_v*",
                                                        "HLT_DiPFJetAve260_v*",
                                                        "HLT_DiPFJetAve300_HFJEC_v*",
                                                        # "HLT_DiPFJetAve320HLT_DiPFJetAve15_HFJEC_v*",
                                                        "HLT_DiPFJetAve320_v*",
                                                        # "HLT_DiPFJetAve35_HFJECHLT_DiPFJetAve60_HFJEC_v*",
                                                        # "HLT_DiPFJetAve35_HFJEC_v*",
                                                        "HLT_DiPFJetAve400_v*",
                                                        # "HLT_DiPFJetAve40HLT_DiPFJetAve60HLT_DiPFJetAve80HLT_DiPFJetAve140HLT_DiPFJetAve200HLT_DiPFJetAve260HLT_DiPFJetAve320HLT_DiPFJetAve400HLT_DiPFJetAve500_v*",
                                                        # "HLT_DiPFJetAve40HLT_DiPFJetAve60HLT_DiPFJetAve80_v*",
                                                        "HLT_DiPFJetAve40_v*",
                                                        "HLT_DiPFJetAve500_v*",
                                                        "HLT_DiPFJetAve60_HFJEC_v*",
                                                        "HLT_DiPFJetAve60_v*",
                                                        # "HLT_DiPFJetAve80_HFJECHLT_DiPFJetAve100_HFJECHLT_DiPFJetAve160_HFJECHLT_DiPFJetAve220_HFJEC_v*",
                                                        "HLT_DiPFJetAve80_HFJEC_v*",
                                                        "HLT_DiPFJetAve80_v*",
                                                        "HLT_PFJet140_v*",
                                                        # "HLT_PFJet15_NoCaloMatchedHLT_PFJet25_NoCaloMatchedHLT_PFJet40_v*",
                                                        "HLT_PFJet15_v*",
                                                        "HLT_PFJet200_v*",
                                                        "HLT_PFJet25_v*",
                                                        "HLT_PFJet260_v*",
                                                        "HLT_PFJet320_v*",
                                                        "HLT_PFJet400_v*",
                                                        # "HLT_PFJet40HLT_PFJet60HLT_PFJet80HLT_PFJet140_v*",
                                                        "HLT_PFJet40_v*",
                                                        # "HLT_PFJet450HLT_PFJet500_v*",
                                                        "HLT_PFJet450_v*",
                                                        "HLT_PFJet500_v*",
                                                        # "HLT_PFJet550HLT_PFJetFwd15_v*",
                                                        "HLT_PFJet60_v*",
                                                        # "HLT_PFJet80HLT_PFJet140HLT_PFJet200HLT_PFJet260HLT_PFJet320HLT_PFJet400HLT_PFJet450HLT_PFJet500_v*",
                                                        "HLT_PFJet80_v*",

                                                        "HLT_PFJetFwd140_v*",                                                                ##0
                                                        "HLT_PFJetFwd200_v*",                                                                ##1
                                                        "HLT_PFJetFwd25_v*",                                                                 ##2
                                                        "HLT_PFJetFwd260_v*",                                                                ##3
                                                        "HLT_PFJetFwd320_v*",                                                                ##4
                                                        "HLT_PFJetFwd400_v*",                                                                ##5
                                                        "HLT_PFJetFwd40_v*",                                                                 ##6
                                                        "HLT_PFJetFwd450_v*",                                                                ##7
                                                        "HLT_PFJetFwd500_v*",                                                                ##8
                                                        "HLT_PFJetFwd60_v*",                                                                 ##9
                                                        "HLT_PFJetFwd80_v*",                                                                 ##10
                                                        # "HLT_PFMET170_NoiseCleanedHLT_PFMET170_JetIdCleanedHLT_PFMET170_BeamHaloCleaned_v*", ##11
                                                        # "HLT_PFMET170_NotCleaned_v*",                                                        ##12
                                                        "HLT_PFMET200_HBHE_BeamHaloCleaned_v*",                                              ##13
                                                        "HLT_PFMET200_HBHECleaned_v*",                                                       ##14
                                                        "HLT_PFMET200_NotCleaned_v*",                                                        ##15
                                                        "HLT_PFMET250_HBHECleaned_v*",                                                       ##16
                                                        "HLT_PFMET300_HBHECleaned_v*",                                                       ##17
                                                        "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v*"                                        ##18
                            ),
                            hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
                            l1tResults = cms.InputTag(""),
                            throw = cms.bool(False)
)
##########################################################################


##########################################################################
process.p = cms.Path(
    process.triggerSelection *
    process.recalib_sequence *
    process.puppiMETSequence *
    process.fullPatMetSequencePuppiUpdated *
    process.fullPatMetSequenceModifiedPFMET *
    process.egammaPostRecoSeq *
    process.rerunMvaIsolationSequence *
    getattr(process,updatedTauName) *
    process.ecalBadCalibReducedMINIAODFilter *
    process.ggNtuplizer
)

# print process.dumpPython()
##########################################################################
