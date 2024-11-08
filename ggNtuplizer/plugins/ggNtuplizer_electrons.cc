#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;
using namespace reco;

// (local) variables associated with tree branches
UShort_t          nEle_;
vector<Char_t>    eleCharge_;
vector<float>  eleEn_;
vector<float>  eleEcalEn_;
vector<float>  eleSIP_;
vector<float>  elePt_;
vector<float>  elePtError_;
vector<float>  eleEta_;
vector<float>  elePhi_;
vector<float>  eleR9_;
vector<float>  eleCalibPt_;
vector<float>  eleCalibEn_;
vector<float>  eleHoverE_;
vector<float>  eleEoverP_;
vector<float>  eleEoverPout_;
vector<float>  eleEoverPInv_;
vector<float>  eleBrem_;
vector<float>  eledEtaAtVtx_;
vector<float>  eledPhiAtVtx_;
vector<float>  eleSigmaIEtaIEtaFull5x5_;
vector<float>  eleSigmaIPhiIPhiFull5x5_;
vector<UShort_t>   eleQualityBits_;
vector<UChar_t>    eleMissHits_;
vector<float>  eleESEffSigmaRR_;
vector<float>  elePFChIso_;
vector<float>  elePFPhoIso_;
vector<float>  elePFNeuIso_;
vector<float>  elePFPUIso_;
vector<float>  elePFClusEcalIso_;
vector<float>  elePFClusHcalIso_;
vector<float>  eleIDMVAIso_;
vector<float>  eleIDMVANoIso_;
vector<float>  eleR9Full5x5_;
vector<ULong64_t> eleFiredSingleTrgs_;
vector<ULong64_t> eleFiredDoubleTrgs_;
vector<ULong64_t> eleFiredL1Trgs_;
vector<UInt_t>  eleIDbit_;
vector<Short_t> eleGenIndex_;


void ggNtuplizer::branchesElectrons(TTree* tree) {

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("eleCharge",               &eleCharge_);
  tree->Branch("eleEn",                   &eleEn_);
  tree->Branch("eleEcalEn",               &eleEcalEn_);
  tree->Branch("elePt",                   &elePt_);
  tree->Branch("elePtError",              &elePtError_);
  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleR9",                   &eleR9_);
  tree->Branch("eleCalibPt",              &eleCalibPt_);
  tree->Branch("eleCalibEn",              &eleCalibEn_);
  tree->Branch("eleSCindex",              &eleSCindex_);
  tree->Branch("eleHoverE",               &eleHoverE_);
  tree->Branch("eleEoverP",               &eleEoverP_);
  tree->Branch("eleEoverPout",            &eleEoverPout_);
  tree->Branch("eleEoverPInv",            &eleEoverPInv_);
  tree->Branch("eleBrem",                 &eleBrem_);
  tree->Branch("eledEtaAtVtx",            &eledEtaAtVtx_);
  tree->Branch("eledPhiAtVtx",            &eledPhiAtVtx_);
  tree->Branch("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);
  tree->Branch("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5_);
  tree->Branch("eleQualityBits",             &eleQualityBits_);
  tree->Branch("eleMissHits",             &eleMissHits_);
  tree->Branch("eleESEffSigmaRR",         &eleESEffSigmaRR_);
  tree->Branch("elePFChIso",              &elePFChIso_);
  tree->Branch("elePFPhoIso",             &elePFPhoIso_);
  tree->Branch("elePFNeuIso",             &elePFNeuIso_);
  tree->Branch("elePFPUIso",              &elePFPUIso_);
  tree->Branch("elePFClusEcalIso",        &elePFClusEcalIso_);
  tree->Branch("elePFClusHcalIso",        &elePFClusHcalIso_);
  tree->Branch("eleIDMVAIso",             &eleIDMVAIso_);
  tree->Branch("eleIDMVANoIso",           &eleIDMVANoIso_);
  tree->Branch("eleR9Full5x5",                &eleR9Full5x5_);
  tree->Branch("eleFiredSingleTrgs",          &eleFiredSingleTrgs_);
  tree->Branch("eleFiredDoubleTrgs",          &eleFiredDoubleTrgs_);
  tree->Branch("eleFiredL1Trgs",              &eleFiredL1Trgs_);
  tree->Branch("eleIDbit",                    &eleIDbit_);
  if(doGenParticles_){
    tree->Branch("eleGenIndex",          &eleGenIndex_);
  }

}

void ggNtuplizer::fillElectrons(const edm::Event &e, const edm::EventSetup &es, math::XYZPoint &pv) {

  // cleanup from previous execution
  eleCharge_                  .clear();
  eleEn_                      .clear();
  eleEcalEn_                  .clear();
  elePt_                      .clear();
  elePtError_                 .clear();
  eleEta_                     .clear();
  elePhi_                     .clear();
  eleR9_                      .clear();
  eleCalibPt_                 .clear();
  eleCalibEn_                 .clear();
  eleSCindex_                 .clear();
  eleHoverE_                  .clear();
  eleEoverP_                  .clear();
  eleEoverPout_               .clear();
  eleEoverPInv_               .clear();
  eleBrem_                    .clear();
  eledEtaAtVtx_               .clear();
  eledPhiAtVtx_               .clear();
  eleSigmaIEtaIEtaFull5x5_    .clear();
  eleSigmaIPhiIPhiFull5x5_    .clear();
  eleQualityBits_.clear();
  eleMissHits_                .clear();
  eleESEffSigmaRR_            .clear();
  elePFChIso_                 .clear();
  elePFPhoIso_                .clear();
  elePFNeuIso_                .clear();
  elePFPUIso_                 .clear();
  elePFClusEcalIso_           .clear();
  elePFClusHcalIso_           .clear();
  eleIDMVAIso_                .clear();
  eleIDMVANoIso_              .clear();
  eleR9Full5x5_               .clear();
  eleFiredSingleTrgs_         .clear();
  eleFiredDoubleTrgs_         .clear();
  eleFiredL1Trgs_             .clear();
  eleIDbit_                   .clear();
  eleGenIndex_                .clear();
  nEle_ = 0;

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  e.getByToken(electronCollection_, electronHandle);

  if (!electronHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Electrons in event";
    return;
  }

  edm::Handle<std::vector<reco::SuperCluster>> ecalSChandle;
  e.getByToken(ecalSCcollection_, ecalSChandle);

  EcalClusterLazyTools       lazyTool    (e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  for (edm::View<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {

    eleCharge_          .push_back(iEle->charge());
    // eleChargeConsistent_.push_back(iEle->isGsfCtfScPixChargeConsistent());
    eleEn_              .push_back(iEle->energy());
    eleCalibEn_         .push_back(iEle->userFloat("ecalEnergyPostCorr"));
    elePt_              .push_back(iEle->pt());
    eleCalibPt_         .push_back(iEle->userFloat("ecalTrkEnergyPostCorr")*iEle->pt()/iEle->p());
    elePtError_         .push_back(iEle->userFloat("ecalTrkEnergyErrPostCorr")*iEle->pt()/iEle->p());
    eleEta_             .push_back(iEle->eta());
    elePhi_             .push_back(iEle->phi());
    eleR9_              .push_back(iEle->r9());
    // eleSCEn_            .push_back(iEle->superCluster()->energy());
    eleEcalEn_          .push_back(iEle->ecalEnergy());

    if(ecalSChandle.isValid()){
      const reco::SuperCluster * _tmpeleSC = (iEle->superCluster().isAvailable()) ? iEle->superCluster().get() : nullptr;
      Short_t tmpeleSCindex = (_tmpeleSC == nullptr) ? -999 : std::distance(ecalSChandle->begin(), (std::vector<reco::SuperCluster>::const_iterator) _tmpeleSC);
      eleSCindex_.push_back(tmpeleSCindex);
    }

    eleHoverE_          .push_back(iEle->hcalOverEcal());

    eleFiredSingleTrgs_ .push_back(matchSingleElectronTriggerFilters(iEle->pt(), iEle->eta(), iEle->phi()));
    eleFiredDoubleTrgs_ .push_back(matchDoubleElectronTriggerFilters(iEle->pt(), iEle->eta(), iEle->phi()));
    eleFiredL1Trgs_     .push_back(matchL1TriggerFilters(iEle->pt(), iEle->eta(), iEle->phi()));

    ///https://cmssdt.cern.ch/SDT/doxygen/CMSSW_7_2_2/doc/html/d8/dac/GsfElectron_8h_source.html
    eleEoverP_          .push_back(iEle->eSuperClusterOverP());
    eleEoverPout_       .push_back(iEle->eEleClusterOverPout());
    eleBrem_            .push_back(iEle->fbrem());
    eledEtaAtVtx_       .push_back(iEle->deltaEtaSuperClusterTrackAtVtx());
    eledPhiAtVtx_       .push_back(iEle->deltaPhiSuperClusterTrackAtVtx());
    UShort_t tmpeleQualityBits = 0;
    if(iEle->passConversionVeto()) setbit(tmpeleQualityBits, 0);
    if(iEle->ecalDrivenSeed()) setbit(tmpeleQualityBits, 1);
    if(iEle->ecalDriven()) setbit(tmpeleQualityBits, 2);
    if(iEle->trackerDrivenSeed()) setbit(tmpeleQualityBits, 4);
    if(iEle->isGsfCtfScPixChargeConsistent()) setbit(tmpeleQualityBits, 6);
    

    eleQualityBits_.push_back(tmpeleQualityBits);

    eleMissHits_        .push_back(iEle->gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS));
    eleESEffSigmaRR_    .push_back(lazyTool.eseffsirir(*((*iEle).superCluster())));

    // VID calculation of (1/E - 1/p)
    if (iEle->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iEle->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else  eleEoverPInv_.push_back((1.0 - iEle->eSuperClusterOverP())/iEle->ecalEnergy());

    reco::GsfElectron::PflowIsolationVariables pfIso = iEle->pfIsolationVariables();
    elePFChIso_         .push_back(pfIso.sumChargedHadronPt);
    elePFPhoIso_        .push_back(pfIso.sumPhotonEt);
    elePFNeuIso_        .push_back(pfIso.sumNeutralHadronEt);
    elePFPUIso_         .push_back(pfIso.sumPUPt);

    eleSigmaIEtaIEtaFull5x5_.push_back(iEle->full5x5_sigmaIetaIeta());
    eleSigmaIPhiIPhiFull5x5_.push_back(iEle->full5x5_sigmaIphiIphi());
    eleR9Full5x5_           .push_back(iEle->full5x5_r9());

    // VID decisions
    UInt_t tmpeleIDbit = 0;
    if (iEle->electronID("cutBasedElectronID-Fall17-94X-V2-veto"))   setbit(tmpeleIDbit, 0);
    if (iEle->electronID("cutBasedElectronID-Fall17-94X-V2-loose"))  setbit(tmpeleIDbit, 1);
    if (iEle->electronID("cutBasedElectronID-Fall17-94X-V2-medium")) setbit(tmpeleIDbit, 2);
    if (iEle->electronID("cutBasedElectronID-Fall17-94X-V2-tight"))  setbit(tmpeleIDbit, 3);
    if (iEle->electronID("heepElectronID-HEEPV70"))   setbit(tmpeleIDbit, 4);
    if (iEle->electronID("mvaEleID-Fall17-iso-V2-wp80"))   setbit(tmpeleIDbit, 5);
    if (iEle->electronID("mvaEleID-Fall17-iso-V2-wp90"))   setbit(tmpeleIDbit, 6);
    if (iEle->electronID("mvaEleID-Fall17-iso-V2-wpLoose"))   setbit(tmpeleIDbit, 7);
    if (iEle->electronID("mvaEleID-Fall17-iso-V2-wpHZZ"))   setbit(tmpeleIDbit, 8);
    if (iEle->electronID("mvaEleID-Fall17-noIso-V2-wp80"))   setbit(tmpeleIDbit, 9);
    if (iEle->electronID("mvaEleID-Fall17-noIso-V2-wp90"))   setbit(tmpeleIDbit, 10);
    if (iEle->electronID("mvaEleID-Fall17-noIso-V2-wpLoose"))   setbit(tmpeleIDbit, 11);

    eleIDbit_.push_back(tmpeleIDbit);

    eleIDMVAIso_  .push_back(iEle->userFloat("ElectronMVAEstimatorRun2Fall17IsoV2Values"));
    eleIDMVANoIso_.push_back(iEle->userFloat("ElectronMVAEstimatorRun2Fall17NoIsoV2Values"));
    elePFClusEcalIso_.push_back(iEle->ecalPFClusterIso());
    elePFClusHcalIso_.push_back(iEle->hcalPFClusterIso());


    if(doGenParticles_){
      edm::Handle<vector<reco::GenParticle>> genParticlesHandle;
      e.getByToken(genParticlesCollection_, genParticlesHandle);
      const reco::GenParticle * eleGen_ = iEle->genParticle();
      Short_t eleGenPos_ = (eleGen_ == nullptr) ? -999 : std::distance(genParticlesHandle->begin(), (vector<reco::GenParticle>::const_iterator) eleGen_);
      eleGenIndex_.push_back(eleGenPos_);
    }

    nEle_++;
  }
};


void ggNtuplizer::branchesEleECALSC(TTree* tree){
  tree->Branch("eleDirectEcalSCindex",                        &eleDirectEcalSCindex_);
};


void ggNtuplizer::resolveEleECALSCindex(){
  eleDirectEcalSCindex_.clear();
  for(Short_t scIndex : eleSCindex_){
    Short_t resolvedIndex = findSecondaryIndex(scIndex, ecalSCindex_);
    eleDirectEcalSCindex_.push_back(resolvedIndex);
  }
};