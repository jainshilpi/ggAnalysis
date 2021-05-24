#ifndef ggNtuplizer_h
#define ggNtuplizer_h

#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/METReco/interface/BeamHaloSummary.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
//#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"

#include "iterator"

using namespace std;

template <typename typeA, typename typeB>
void setbit(typeA & x, typeB bit) {
  typeA a = 1;
  x |= (a << bit);
}


const std::vector<std::string>    muTriggerPathsRunII = {

  //https://twiki.cern.ch/twiki/bin/view/CMS/MuonHLT2016#Recommended_trigger_paths_for_20
  //https://twiki.cern.ch/twiki/bin/view/CMS/MuonHLT2017#Recommendations_for_2017_data_an
  //https://twiki.cern.ch/twiki/bin/view/CMS/MuonHLT2018#Recommended_trigger_paths_for_20
  "HLT_IsoMu24_v",                                   //0
  "HLT_IsoMu27_v",                                   //2
  "HLT_IsoTkMu24_v",                                 //1
  "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v",   //5
  "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v",     //6
  "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",           //13
  "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",              //10
  "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",         //14
  "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",            //11
  "HLT_Mu50_v",                                      //7
  "HLT_Mu50_v",                                      //8
  "HLT_OldMu100_v",                                  //3
  "HLT_TkMu100_v",                                   //4
  "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v",       //15
  "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",          //12
  "HLT_TkMu50_v",                                    //9
};


const std::vector<std::string>    phoTriggerPathsRunII = {

  //https://twiki.cern.ch/twiki/bin/view/CMS/EgHLTRunIISummary#Short_Summary_Recommended_Trigge
  //https://indico.cern.ch/event/662751/contributions/2778365/attachments/1561439/2458438/egamma_workshop_triggerTalk.pdf
  //https://github.com/GhentAnalysis/heavyNeutrino/blob/0ac0591cea7a323356e5cc367c65213dbf1cfa44/multilep/src/TriggerAnalyzer.cc#L195-L215
  //https://github.com/Sam-Harper/usercode/blob/106XNtup/TrigTools/plugins/Ele32DoubleL1ToSingleL1Example.cc#L113

  "HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_v",        //15
  "HLT_DoubleEle25_CaloIdL_MW_v",                    //14
  "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v",            //22
  "HLT_DoubleEle33_CaloIdL_MW_v",                    //21
  "HLT_DoubleEle37_CaloIdL_GsfTrackIdVL_v",          //2
  "HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v",      //3
  "HLT_DoublePhoton60_v",                            //4
  "HLT_DoublePhoton70_v",                            //16
  "hltEGL1SingleEGOrFilter",                         //8
  "HLT_Ele115_CaloIdVT_GsfTrkIdT_v",                 //10
  "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v",     //20
  "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v",        //13
  "HLT_Ele25_eta2p1_WPTight_Gsf_v",                  //1
  "HLT_Ele27_WPTight_Gsf_v",                         //0
  "hltEle32L1DoubleEGWPTightGsfTrackIsoFilter",      //6
  "HLT_Ele32_WPTight_Gsf_L1DoubleEG_v",              //5
  "HLT_Ele32_WPTight_Gsf_v",                         //11
  "HLT_Ele35_WPTight_Gsf_v",                         //9
  "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v", //17
  "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v",         //18
  "hltL1sSingleEGor",                                //7
  "HLT_Photon175_v",                                 //19
  "HLT_Photon200_v",                                 //12
};

const std::vector<std::string>    jetTriggerPathsRunII = {

  // https://twiki.cern.ch/twiki/bin/view/CMS/JetMETPathsRun2

  "HLT_AK4CaloJet100_v",
  "HLT_AK4CaloJet120_v",
  "HLT_AK4CaloJet30_v",
  "HLT_AK4CaloJet40_v",
  "HLT_AK4CaloJet50_v",
  "HLT_AK4CaloJet80_v",
  "HLT_AK4PFJet100_v",
  "HLT_AK4PFJet120_v",
  "HLT_AK4PFJet30_v",
  "HLT_AK4PFJet50_v",
  "HLT_AK4PFJet80_v",
  "HLT_CaloJet500_NoJetID_v",
  "HLT_CaloJet550_NoJetID_v",
  "HLT_CaloMET250_NotCleanedHLT_CaloMET250_HBHECleanedHLT_CaloMET300_HBHECleanedHLT_CaloMET350_HBHECleaned_v",
  "HLT_DiPFJetAve100_HFJEC_v",
  "HLT_DiPFJetAve140_v",
  "HLT_DiPFJetAve15_HFJECHLT_DiPFJetAve25_HFJECHLT_DiPFJetAve35_HFJECHLT_DiPFJetAve60_HFJECHLT_DiPFJetAve80_HFJECHLT_DiPFJetAve100_HFJECHLT_DiPFJetAve160_HFJECHLT_DiPFJetAve220_HFJECHLT_DiPFJetAve300_HFJEC_v",
  "HLT_DiPFJetAve15_HFJEC_v",
  "HLT_DiPFJetAve160_HFJEC_v",
  "HLT_DiPFJetAve200_v",
  "HLT_DiPFJetAve220_HFJEC_v",
  "HLT_DiPFJetAve25_HFJEC_v",
  "HLT_DiPFJetAve260_v",
  "HLT_DiPFJetAve300_HFJEC_v",
  "HLT_DiPFJetAve320HLT_DiPFJetAve15_HFJEC_v",
  "HLT_DiPFJetAve320_v",
  "HLT_DiPFJetAve35_HFJECHLT_DiPFJetAve60_HFJEC_v",
  "HLT_DiPFJetAve35_HFJEC_v",
  "HLT_DiPFJetAve400_v",
  "HLT_DiPFJetAve40HLT_DiPFJetAve60HLT_DiPFJetAve80HLT_DiPFJetAve140HLT_DiPFJetAve200HLT_DiPFJetAve260HLT_DiPFJetAve320HLT_DiPFJetAve400HLT_DiPFJetAve500_v",
  "HLT_DiPFJetAve40HLT_DiPFJetAve60HLT_DiPFJetAve80_v",
  "HLT_DiPFJetAve40_v",
  "HLT_DiPFJetAve500_v",
  "HLT_DiPFJetAve60_HFJEC_v",
  "HLT_DiPFJetAve60_v",
  "HLT_DiPFJetAve80_HFJECHLT_DiPFJetAve100_HFJECHLT_DiPFJetAve160_HFJECHLT_DiPFJetAve220_HFJEC_v",
  "HLT_DiPFJetAve80_HFJEC_v",
  "HLT_DiPFJetAve80_v",
  "HLT_PFJet140_v",
  "HLT_PFJet15_NoCaloMatchedHLT_PFJet25_NoCaloMatchedHLT_PFJet40_v",
  "HLT_PFJet15_v",
  "HLT_PFJet200_v",
  "HLT_PFJet25_v",
  "HLT_PFJet260_v",
  "HLT_PFJet320_v",
  "HLT_PFJet400_v",
  "HLT_PFJet40HLT_PFJet60HLT_PFJet80HLT_PFJet140_v",
  "HLT_PFJet40_v",
  "HLT_PFJet450HLT_PFJet500_v",
  "HLT_PFJet450_v",
  "HLT_PFJet500_v",
  "HLT_PFJet550HLT_PFJetFwd15_v",
  "HLT_PFJet60_v",
  "HLT_PFJet80HLT_PFJet140HLT_PFJet200HLT_PFJet260HLT_PFJet320HLT_PFJet400HLT_PFJet450HLT_PFJet500_v",
  "HLT_PFJet80_v",
};

const std::vector<std::string>    metFWjetTriggerPathsRunII = {

  // https://twiki.cern.ch/twiki/bin/view/CMS/JetMETPathsRun2

  "HLT_PFJetFwd140_v",
  "HLT_PFJetFwd200_v",
  "HLT_PFJetFwd25_v",
  "HLT_PFJetFwd260_v",
  "HLT_PFJetFwd320_v",
  "HLT_PFJetFwd400_v",
  "HLT_PFJetFwd40_v",
  "HLT_PFJetFwd450_v",
  "HLT_PFJetFwd500_v",
  "HLT_PFJetFwd60_v",
  "HLT_PFJetFwd80_v",
  "HLT_PFMET170_NoiseCleanedHLT_PFMET170_JetIdCleanedHLT_PFMET170_BeamHaloCleaned_v",
  "HLT_PFMET170_NotCleaned_v",
  "HLT_PFMET200_HBHE_BeamHaloCleaned_v",
  "HLT_PFMET200_HBHECleaned_v",
  "HLT_PFMET200_NotCleaned_v",
  "HLT_PFMET250_HBHECleaned_v",
  "HLT_PFMET300_HBHECleaned_v",
  "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v",
};


class ggNtuplizer : public edm::EDAnalyzer {
 public:

  explicit ggNtuplizer(const edm::ParameterSet&);
  ~ggNtuplizer();

  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 private:

  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  void initTriggerFilters(const edm::Event&);
  ULong64_t matchSingleElectronTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchDoubleElectronTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchSinglePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchDoublePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchTriplePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchMuonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchJetTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchL1TriggerFilters(double pt, double eta, double phi);
  Double_t deltaPhi(Double_t phi1, Double_t phi2);
  Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);

  Short_t findSecondaryIndex(const Short_t & searchIndex, const std::vector<UShort_t> & container);

  void branchesTrigObj(TTree*);
  void branchesGlobalEvent(TTree*);
  void branchesGenInfo    (TTree*, edm::Service<TFileService>&);
  void branchesGenPart    (TTree*);
  void branchesMET        (TTree*);
  void branchesPhotons    (TTree*);
  void branchesPhotonsOOT(TTree*);
  void branchesElectrons  (TTree*);
  // void branchesHFElectrons(TTree*);
  void branchesMuons      (TTree*);
  void branchesAK4CHSJets       (TTree*);
  void branchesAK4PUPPIJets       (TTree*);
  void branchesAK8PUPPIJets    (TTree*);

  void fillGlobalEvent(const edm::Event&, const edm::EventSetup&);
  void fillGenInfo    (const edm::Event&);
  void fillGenPart    (const edm::Event&);
  void fillMET        (const edm::Event&, const edm::EventSetup&);
  void fillPhotons    (const edm::Event&, const edm::EventSetup&);
  void fillPhotonsOOT    (const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
  void fillMuons      (const edm::Event&, math::XYZPoint&, const reco::Vertex);
  void fillAK8PUPPIJets(const edm::Event&, const edm::EventSetup&);
  void branchesGenAK8JetPart(TTree*);

  void fillAK4CHSJets       (const edm::Event&, const edm::EventSetup&);
  void fillAK4PUPPIJets       (const edm::Event&, const edm::EventSetup&);

  void branchesGenAK4JetPart(TTree*);
  void fillGenAK4JetInfo(const edm::Event&, Float_t );
  void fillGenAK8JetInfo(const edm::Event&, Float_t );

  const EcalRecHit * getECALrecHit(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS, int di=0, int dj=0);
  Float_t ECALrecHitE(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS, int di=0, int dj=0);
  Float_t ECALrecHitT(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS);
  Float_t swissCross(const DetId& id, noZS::EcalClusterLazyTools & ltNoZS);

  std::vector<int> IndexMatchedConversion( edm::View<pat::Photon>::const_iterator g, const std::vector<edm::Ptr<reco::Conversion> > &, const std::vector<edm::Ptr<reco::Conversion> > &) const;
  double vtxZFromConv( edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &, const math::XYZPoint &beamSpot) const;
  double vtxZFromConvSuperCluster( edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &conversion, const math::XYZPoint &beamSpot ) const ;
  double vtxZFromConvOnly(  edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &conversion, const math::XYZPoint &beamSpot ) const;


  std::vector<Short_t> phoSCindex_;
  std::vector<Short_t> ootPho_SCindex_;
  std::vector<UShort_t> ecalSCindex_;
  std::vector<UShort_t> ecalootSCindex_;
  std::vector<Short_t> eleSCindex_;
  std::vector<Short_t> phoDirectEcalSCindex_;
  std::vector<Short_t> ootPhoDirectEcalSCindex_;
  std::vector<Short_t> eleDirectEcalSCindex_;

  void branchesECALSC(TTree* tree);
  void branchesECALOOTSC(TTree* tree);
  void branchesPhoECALSC(TTree* tree);
  void branchesEleECALSC(TTree* tree);
  void branchesootPhoECALSC(TTree* tree);
  void fillECALSC(const edm::Event& e, const edm::EventSetup& es);
  void fillECALOOTSC(const edm::Event& e, const edm::EventSetup& es);
  void resolvePhoECALSCindex();
  void resolveootPhoECALSCindex();
  void resolveEleECALSCindex();
  Float_t getLICTD(const reco::SuperCluster *sc, noZS::EcalClusterLazyTools & ltNoZS);
  Float_t etaWing(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS);

  // void fillAK4PUPPIJets       (const edm::Event&, const edm::EventSetup&);

  void branchesTracks(TTree* tree);
  void fillTracks(const edm::Event& e, const edm::EventSetup& es);
  edm::EDGetTokenT<edm::View<pat::IsolatedTrack>>        tracksLabel_;


  void branchesTaus(TTree* tree);
  void fillTaus(const edm::Event& e, const edm::EventSetup& es);
  edm::EDGetTokenT<edm::View<pat::Tau>>        tauLabel_;


  Bool_t development_;
  Bool_t addFilterInfoAOD_;
  Bool_t addFilterInfoMINIAOD_;
  Bool_t doGenParticles_;
  Bool_t runOnParticleGun_;
  Bool_t doGenJets_;
  Bool_t runOnSherpa_;
  Bool_t dumpPFPhotons_;
  Bool_t dumpTaus_;
  Bool_t dumpJets_;
  Bool_t dumpAK8Jets_;
  Bool_t dumpSoftDrop_;
  Bool_t dumpPDFSystWeight_;
  Bool_t doOOTphotons_;
  Bool_t doTrks_;

  int  year_;

  vector<int> newparticles_;

  double trgFilterDeltaPtCut_;
  double trgFilterDeltaRCut_;


  edm::EDGetTokenT<reco::BeamHaloSummary>           beamHaloSummaryToken_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxLabel_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxBSLabel_;
  edm::EDGetTokenT<double>                         rhoLabel_;
  edm::EDGetTokenT<double>                         rhoCentralLabel_;
  edm::EDGetTokenT<trigger::TriggerEvent>          trgEventLabel_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsLabel_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  string                                           trgResultsProcess_;
  edm::EDGetTokenT<edm::TriggerResults>            patTrgResultsLabel_;
  edm::EDGetTokenT<GenEventInfoProduct>            generatorLabel_;
  edm::EDGetTokenT<LHEEventProduct>                lheEventLabel_;
  edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
  edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesCollection_;
  edm::EDGetTokenT<edm::View<pat::MET> >           pfMETlabel_;
  edm::EDGetTokenT<edm::View<pat::MET> >           puppiMETlabel_;
  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >        photonCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >        photonOOTCollection_;
  edm::EDGetTokenT<edm::View<pat::Muon> >          muonCollection_;
  edm::EDGetTokenT<vector<pat::Tau> >              tauCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           esReducedRecHitCollection_;
  edm::EDGetTokenT<std::vector<reco::SuperCluster>>           ecalSCcollection_;
  edm::EDGetTokenT<std::vector<reco::SuperCluster>>           ecalSC_OOT_collection_;
  edm::EDGetTokenT<reco::PhotonCollection>         recophotonCollection_;
  edm::EDGetTokenT<reco::TrackCollection>          tracklabel_;
  edm::EDGetTokenT<reco::GsfElectronCollection>     gsfElectronlabel_;
  edm::EDGetTokenT<edm::View<reco::GsfTrack> >      gsfTracks_;
  edm::EDGetTokenT<reco::PFCandidateCollection>     pfAllParticles_;
  edm::EDGetTokenT<vector<pat::PackedCandidate> >   pckPFCdsLabel_;
  edm::EDGetTokenT<edm::View<reco::Candidate> >     recoCdsLabel_;
  edm::EDGetTokenT<edm::View<pat::Jet> >            ak4PFJetsCHSLabel_;
  edm::EDGetTokenT<edm::View<pat::Jet> >            ak4PFJetsPuppiLabel_;
  edm::EDGetTokenT<edm::View<pat::Jet> >            ak8JetsPUPPILabel_;
  edm::EDGetTokenT<std::vector<reco::GenJet> >      ak4PFJetsCHSGenJetLabel_;
  edm::EDGetTokenT<std::vector<reco::GenJet> >      ak8GenJetLabel_;
  edm::EDGetTokenT<reco::JetTagCollection>          boostedDoubleSVLabel_;
  edm::EDGetTokenT<pat::PackedCandidateCollection>  pckPFCandidateCollection_;
  edm::EDGetTokenT<Bool_t>                          ecalBadCalibFilterUpdateToken_;

  Bool_t                                            getECALprefiringWeights_;
  edm::EDGetTokenT<double>                          prefweight_token;
  edm::EDGetTokenT<double>                          prefweightup_token;
  edm::EDGetTokenT<double>                          prefweightdown_token;

  // for MET filters
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;

  //check
  edm::EDGetToken gsfEle_;

  edm::EDGetTokenT<reco::BeamSpot> offlinebeamSpot_;
  edm::EDGetTokenT<edm::View<reco::Conversion> > convPhotonTag_;
  edm::EDGetTokenT<edm::View<reco::Conversion> > convPhotonTagSL_;

  double sigma1Pix;
  double sigma1Tib;
  double sigma1Tob;
  double sigma1PixFwd;
  double sigma1Tid;
  double sigma1Tec;
  double sigma2Pix;
  double sigma2Tib;
  double sigma2Tob;
  double sigma2PixFwd;
  double sigma2Tid;
  double sigma2Tec;
  double singlelegsigma1Pix;
  double singlelegsigma1Tib;
  double singlelegsigma1Tob;
  double singlelegsigma1PixFwd;
  double singlelegsigma1Tid;
  double singlelegsigma1Tec;
  double singlelegsigma2Pix;
  double singlelegsigma2Tib;
  double singlelegsigma2Tob;
  double singlelegsigma2PixFwd;
  double singlelegsigma2Tid;
  double singlelegsigma2Tec;

  TTree   *tree_;
  TH1F    *hEvents_;
  TH1F    *hPU_;
  TH1F    *hPUTrue_;
  TH1F    *hPUw_;
  TH1F    *hPUTruew_;
  TH1F    *hGenWeightSign_;
  TH1F    *hSumGenWeightSign_;
  TH1F    *hSumGenWeight_;

  HLTPrescaleProvider hltPrescaleProvider_;
};

#endif
