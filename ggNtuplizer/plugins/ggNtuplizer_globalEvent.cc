#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

Int_t       run_;
Long64_t    event_;
UShort_t    lumis_;
Bool_t      isData_;
UChar_t     nVtx_;
UChar_t     nGoodVtx_;
Bool_t      isPVGood_;
Float_t     vtx_;
Float_t     vty_;
Float_t     vtz_;
Float_t     rho_;
Float_t     rhoCentral_;
ULong64_t   HLTMuX_;
ULong64_t   HLTPho_;
ULong64_t   HLTPhoRejectedByPS_;
ULong64_t   HLTJet_;
ULong64_t   HLTMetFWjet_;
ULong64_t   HLTMuXIsPrescaled_;
ULong64_t   HLTPhoIsPrescaled_;
ULong64_t   HLTJetIsPrescaled_;
ULong64_t   HLTMetFWjetIsPrescaled_;
Float_t     ecalPrefireW_;
Float_t     ecalPrefireWup_;
Float_t     ecalPrefireWdn_;
UShort_t    beamHaloSummary_;

void ggNtuplizer::branchesGlobalEvent(TTree* tree) {

  tree->Branch("run",                    & run_);
  tree->Branch("event",                  & event_);
  tree->Branch("lumis",                  & lumis_);
  tree->Branch("nVtx",                   & nVtx_);
  tree->Branch("nGoodVtx",               & nGoodVtx_);
  tree->Branch("isPVGood",               & isPVGood_);
  tree->Branch("vtx",                    & vtx_);
  tree->Branch("vty",                    & vty_);
  tree->Branch("vtz",                    & vtz_);
  tree->Branch("rho",                    & rho_);
  tree->Branch("rhoCentral",             & rhoCentral_);
  tree->Branch("HLTMuX",                 & HLTMuX_);
  tree->Branch("HLTPho",                 & HLTPho_);
  tree->Branch("HLTPhoRejectedByPS",     & HLTPhoRejectedByPS_);
  tree->Branch("HLTJet",                 & HLTJet_);
  tree->Branch("HLTMetFWjet",            & HLTMetFWjet_);
  tree->Branch("HLTMuXIsPrescaled",      & HLTMuXIsPrescaled_);
  tree->Branch("HLTPhoIsPrescaled",      & HLTPhoIsPrescaled_);
  tree->Branch("HLTJetIsPrescaled",      & HLTJetIsPrescaled_);
  tree->Branch("HLTMetFWjetIsPrescaled", & HLTMetFWjetIsPrescaled_);
  if (getECALprefiringWeights_) {
    tree->Branch("ecalPrefireW",         & ecalPrefireW_);
    tree->Branch("ecalPrefireWup",       & ecalPrefireWup_);
    tree->Branch("ecalPrefireWdn",       & ecalPrefireWdn_);
  }
  tree->Branch("beamHaloSummary",        & beamHaloSummary_);

}

void ggNtuplizer::fillGlobalEvent(const edm::Event& e, const edm::EventSetup& es) {

  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  e.getByToken(rhoCentralLabel_, rhoCentralHandle);

  run_    = e.id().run();
  event_  = e.id().event();
  lumis_  = e.luminosityBlock();
  isData_ = e.isRealData();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) rhoCentral_ = *(rhoCentralHandle.product());
  else rhoCentral_ = -99.;

  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// beam halo summary ///////////////////////////////////////////////////
  edm::Handle<reco::BeamHaloSummary> beamHaloSummaryHandle;
  e.getByToken(beamHaloSummaryToken_, beamHaloSummaryHandle);

  beamHaloSummary_ = 0;
  if (beamHaloSummaryHandle.isValid()) {
    if (beamHaloSummaryHandle->CSCLooseHaloId()) setbit(beamHaloSummary_, 0);
    if (beamHaloSummaryHandle->CSCTightHaloId()) setbit(beamHaloSummary_, 1);
    if (beamHaloSummaryHandle->CSCTightHaloId2015()) setbit(beamHaloSummary_, 2);
    if (beamHaloSummaryHandle->CSCTightHaloIdTrkMuUnveto()) setbit(beamHaloSummary_, 3);
    if (beamHaloSummaryHandle->EcalLooseHaloId()) setbit(beamHaloSummary_, 4);
    if (beamHaloSummaryHandle->EcalTightHaloId()) setbit(beamHaloSummary_, 5);
    if (beamHaloSummaryHandle->EventSmellsLikeHalo()) setbit(beamHaloSummary_, 6);
    if (beamHaloSummaryHandle->ExtremeTightId()) setbit(beamHaloSummary_, 7);
    if (beamHaloSummaryHandle->GlobalLooseHaloId()) setbit(beamHaloSummary_, 8);
    if (beamHaloSummaryHandle->GlobalSuperTightHaloId2016()) setbit(beamHaloSummary_, 9);
    if (beamHaloSummaryHandle->GlobalTightHaloId()) setbit(beamHaloSummary_, 10);
    if (beamHaloSummaryHandle->GlobalTightHaloId2016()) setbit(beamHaloSummary_, 11);
    if (beamHaloSummaryHandle->HcalLooseHaloId()) setbit(beamHaloSummary_, 12);
    if (beamHaloSummaryHandle->HcalTightHaloId()) setbit(beamHaloSummary_, 13);
    if (beamHaloSummaryHandle->LooseId()) setbit(beamHaloSummary_, 14);
    if (beamHaloSummaryHandle->TightId()) setbit(beamHaloSummary_, 15);
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  nVtx_     = -1;
  nGoodVtx_ = -1;
  if (vtxHandle.isValid()) {
    nVtx_     = 0;
    nGoodVtx_ = 0;

    for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {

      if (nVtx_ == 0) {
        vtx_     = v->x();
        vty_     = v->y();
        vtz_     = v->z();

        isPVGood_ = false;
        if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) isPVGood_ = true;
      }

      if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) nGoodVtx_++;
      nVtx_++;

    }
  } else edm::LogWarning("ggNtuplizer") << "Primary vertices info not unavailable";

  edm::Handle<edm::TriggerResults> trgResultsHandle;
  e.getByToken(trgResultsLabel_, trgResultsHandle);
  if (!trgResultsHandle.isValid()) e.getByToken(patTrgResultsLabel_, trgResultsHandle);
  if (!trgResultsHandle.isValid()) e.getByToken(patTrgResultsLabel2_, trgResultsHandle);



  bool cfg_changed = true;
  hltPrescaleProvider_.init(e.getRun(), es, trgResultsProcess_, cfg_changed);
  HLTConfigProvider const&  hltCfg = hltPrescaleProvider_.hltConfigProvider();
  const int prescaleSet = hltPrescaleProvider_.prescaleSet(e,es);

  const edm::TriggerNames &trgNames = e.triggerNames(*trgResultsHandle);

  HLTMuX_                 = 0;
  HLTPho_                 = 0;
  HLTPhoRejectedByPS_     = 0;
  HLTJet_                 = 0;
  HLTMetFWjet_            = 0;
  HLTMuXIsPrescaled_      = 0;
  HLTPhoIsPrescaled_      = 0;
  HLTJetIsPrescaled_      = 0;
  HLTMetFWjetIsPrescaled_ = 0;

  for (size_t i = 0; i < trgNames.size(); i++) {

    const string &name = trgNames.triggerName(i);

    ULong64_t isPrescaled = (hltCfg.prescaleValue(prescaleSet, name)!=1) ? 1 : 0;
    ULong64_t isFired     = (trgResultsHandle->accept(i)) ? 1 : 0;
    ULong64_t isrejectedByHLTPS = (hltCfg.moduleType(hltCfg.moduleLabel(i,trgResultsHandle->index(i)))=="HLTPrescaler") ? 1: 0;

    int bitMu       = -1;
    int bitPho      = -1;
    int bitJet      = -1;
    int bitMetFwjet = -1;

    for (UInt_t iTrigPath = 0; iTrigPath < muTriggerPathsRunII.size(); iTrigPath++) {
      if (name.find(muTriggerPathsRunII[iTrigPath])!= string::npos) {
        bitMu =  iTrigPath;
        break;
      }
    }

    if (bitMu >= 0) {
      HLTMuX_            |= (isFired << bitMu);
      HLTMuXIsPrescaled_ |= (isPrescaled << bitMu);
      continue;
    }

    for (UInt_t iTrigPath = 0; iTrigPath < phoTriggerPathsRunII.size(); iTrigPath++) {
      if (name.find(phoTriggerPathsRunII[iTrigPath])!= string::npos) {
        bitPho =  iTrigPath;
        break;
      }
    }

    if (bitPho >= 0) {
      HLTPho_            |= (isFired << bitPho);
      HLTPhoIsPrescaled_ |= (isPrescaled << bitPho);
      HLTPhoRejectedByPS_|= (isrejectedByHLTPS << bitPho);
      continue;
    }

    for (UInt_t iTrigPath = 0; iTrigPath < jetTriggerPathsRunII.size(); iTrigPath++) {
      if (name.find(jetTriggerPathsRunII[iTrigPath])!= string::npos) {
        bitJet =  iTrigPath;
        break;
      }
    }

    if (bitJet >= 0) {
      HLTJet_            |= (isFired << bitJet);
      HLTJetIsPrescaled_ |= (isPrescaled << bitJet);
      continue;
    }

    for (UInt_t iTrigPath = 0; iTrigPath < metFWjetTriggerPathsRunII.size(); iTrigPath++) {
      if (name.find(metFWjetTriggerPathsRunII[iTrigPath])!= string::npos) {
        bitMetFwjet =  iTrigPath;
        break;
      }
    }

    if (bitMetFwjet >= 0) {
      HLTMetFWjet_            |= (isFired << bitMetFwjet);
      HLTMetFWjetIsPrescaled_ |= (isPrescaled << bitMetFwjet);
      continue;
    }
  }

  if (getECALprefiringWeights_) {
    edm::Handle<double> theprefweight;
    e.getByToken(prefweight_token, theprefweight ) ;
    ecalPrefireW_ = (*theprefweight);

    edm::Handle<double> theprefweightup;
    e.getByToken(prefweightup_token, theprefweightup ) ;
    ecalPrefireWup_ = (*theprefweightup);

    edm::Handle<double> theprefweightdown;
    e.getByToken(prefweightdown_token, theprefweightdown ) ;
    ecalPrefireWdn_ = (*theprefweightdown);
  }
}