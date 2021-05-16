#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"


//// https://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_4_13/doc/html/d8/dc9/classEcalRecHit.html

const EcalRecHit * ggNtuplizer::getECALrecHit(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS){
  const EcalRecHitCollection *recHits = (id.subdetId() == EcalBarrel) ? ltNoZS.getEcalEBRecHitCollection() : ltNoZS.getEcalEERecHitCollection();
  EcalRecHitCollection::const_iterator idRecHitIterator = recHits->find(id);
  return ((idRecHitIterator!= recHits->end()) ? &(*(idRecHitIterator)) : nullptr);
};

Float_t ggNtuplizer::ECALrecHitE(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS, int di, int dj){
  DetId nid;
  if(di == 0 && dj == 0) nid = id;
  else if(id.subdetId() == EcalBarrel) nid = EBDetId::offsetBy(id, di, dj);
  else if(id.subdetId() == EcalEndcap) nid = EEDetId::offsetBy(id, di, dj);
  const EcalRecHit * nidRH = getECALrecHit(nid, ltNoZS);
  return ((nidRH) ? nidRH->energy() : 0.);
};


Float_t ggNtuplizer::ECALrecHitT(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS){
  const EcalRecHit *idRecHit  = getECALrecHit(id, ltNoZS);
  return ((idRecHit) ? idRecHit->time() : -9999);  
};


Float_t ggNtuplizer::etaWing(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS){
  Float_t e0 = ECALrecHitE(id, ltNoZS);
  Float_t eL = ECALrecHitE(id, ltNoZS,  -1,  0);
  Float_t eR = ECALrecHitE(id, ltNoZS,  1,  0);
  return (std::max(eL, eR)/e0);
};


Float_t ggNtuplizer::swissCross(const DetId & id, noZS::EcalClusterLazyTools & ltNoZS){
  Float_t e1 = ECALrecHitE(id, ltNoZS);
  Float_t s4 = 0.;
  s4 += ECALrecHitE(id, ltNoZS,  1,  0);
  s4 += ECALrecHitE(id, ltNoZS, -1,  0);
  s4 += ECALrecHitE(id, ltNoZS,  0,  1);
  s4 += ECALrecHitE(id, ltNoZS,  0, -1);
  return (1 - s4/e1);
};


Float_t ggNtuplizer::getLICTD(const reco::SuperCluster *sc, noZS::EcalClusterLazyTools & ltNoZS){

  if(sc->clustersSize()<1) return -9999.;
  if(!sc->clusters().isAvailable()) return -9999.;

  DetId seedDetID = sc->seed()->seed();

  const EcalRecHit *seedRecHit  = getECALrecHit(seedDetID, ltNoZS);

  if(!seedRecHit) return -9999;;

  Float_t maxTime = - std::numeric_limits<Float_t>::max();
  Float_t minTime = std::numeric_limits<Float_t>::max();

  Bool_t timeValid = 0;
  for(reco::CaloCluster_iterator cluster = sc->clustersBegin(); cluster != sc->clustersEnd(); cluster++){
    if((*cluster)->size()<1) continue;

    for(const std::pair<DetId, Float_t> & iXtal : (*cluster)->hitsAndFractions()){

      const EcalRecHit * iXtalHit = getECALrecHit(iXtal.first, ltNoZS);

      if(!iXtalHit) continue;

      //// https://cmssdt.cern.ch/lxr/source/RecoLocalCalo/EcalRecAlgos/interface/EcalRecHitSimpleAlgo.h#L0042
      //// rh.setEnergyError(uncalibRH.amplitudeError() * adcToGeVConstant_ * intercalibConstant);
      // std::cout<<"RH Energy: "<<iXtalHit->energy()<<" +- "<<iXtalHit->energyError()<<"("<<100.*iXtalHit->energyError()/iXtalHit->energy()<<"%)\n";
      if(iXtalHit->energy() < iXtalHit->energyError() || iXtalHit->energy() < 1.) continue;
      // if(std::abs(iXtalHit->time()) < iXtalHit->timeError() || iXtalHit->energy() < 1.) continue;

      if(iXtalHit->time() > maxTime) maxTime = iXtalHit->time();
      if(iXtalHit->time() < minTime) minTime = iXtalHit->time();
      timeValid = 1.;
    }
  };

  Float_t LICTD = -99999.;
  if(timeValid){
    Float_t maxT = maxTime - seedRecHit->time();
    Float_t minT = minTime - seedRecHit->time();
    LICTD = (std::abs(maxT) > std::abs(minT)) ? maxT : minT;
  }

  return LICTD;
};


UShort_t             necalSC_;
std::vector<Float_t> ecalSC_eta_;
std::vector<Float_t> ecalSC_phi_;
std::vector<Float_t> ecalSC_En_;
std::vector<Float_t> ecalSC_RawEn_;
std::vector<Float_t> ecalSC_etaWidth_;
std::vector<Float_t> ecalSC_phiWidth_;
std::vector<Float_t> ecalSC_LICTD_;
std::vector<Float_t> ecalSC_seedTime_;
std::vector<Float_t> ecalSC_seedSwissCross_;
std::vector<Float_t> ecalSC_seedEtaWing_;
std::vector<UChar_t> ecalSC_seedBits_;
std::vector<Char_t>  ecalSC_seedIx_;
std::vector<Char_t>  ecalSC_seedIy_;
std::vector<Char_t>  ecalSC_seedIz_;
std::vector<UInt_t>  ecalSC_nXtals_;


void ggNtuplizer::branchesECALSC(TTree* tree) {
  tree->Branch("necalSC",               & necalSC_);
  tree->Branch("ecalSC_eta",            & ecalSC_eta_);
  tree->Branch("ecalSC_phi",            & ecalSC_phi_);
  tree->Branch("ecalSC_En",             & ecalSC_En_);
  tree->Branch("ecalSC_RawEn",          & ecalSC_RawEn_);
  tree->Branch("ecalSC_etaWidth",       & ecalSC_etaWidth_);
  tree->Branch("ecalSC_phiWidth",       & ecalSC_phiWidth_);
  tree->Branch("ecalSC_LICTD",          & ecalSC_LICTD_);
  tree->Branch("ecalSC_seedTime",       & ecalSC_seedTime_);
  tree->Branch("ecalSC_seedSwissCross", & ecalSC_seedSwissCross_);
  tree->Branch("ecalSC_seedEtaWing",    & ecalSC_seedEtaWing_);
  tree->Branch("ecalSC_seedBits",       & ecalSC_seedBits_);
  tree->Branch("ecalSC_seedIx",         & ecalSC_seedIx_);
  tree->Branch("ecalSC_seedIy",         & ecalSC_seedIy_);
  tree->Branch("ecalSC_seedIz",         & ecalSC_seedIz_);
  tree->Branch("ecalSC_nXtals",         & ecalSC_nXtals_);
};


void ggNtuplizer::fillECALSC(const edm::Event& e, const edm::EventSetup& es){
  necalSC_ = 0;
  ecalSCindex_           . clear();
  ecalSC_eta_            . clear();
  ecalSC_phi_            . clear();
  ecalSC_En_             . clear();
  ecalSC_RawEn_          . clear();
  ecalSC_etaWidth_       . clear();
  ecalSC_phiWidth_       . clear();
  ecalSC_LICTD_          . clear();
  ecalSC_seedTime_       . clear();
  ecalSC_seedSwissCross_ . clear();
  ecalSC_seedEtaWing_    . clear();
  ecalSC_seedBits_       . clear();
  ecalSC_seedIx_         . clear();
  ecalSC_seedIy_         . clear();
  ecalSC_seedIz_         . clear();
  ecalSC_nXtals_         . clear();

  edm::Handle<std::vector<reco::SuperCluster>> ecalSChandle;
  e.getByToken(ecalSCcollection_, ecalSChandle);

  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  if(!ecalSChandle.isValid()) return;

  for(std::vector<reco::SuperCluster>::const_iterator iSC = ecalSChandle->begin(); iSC != ecalSChandle->end(); iSC++){

    ecalSCindex_     . push_back(necalSC_);
    ecalSC_eta_      . push_back(iSC->eta());
    ecalSC_phi_      . push_back(iSC->phi());
    ecalSC_En_       . push_back(iSC->energy());
    ecalSC_RawEn_    . push_back(iSC->rawEnergy());
    ecalSC_etaWidth_ . push_back(iSC->etaWidth());
    ecalSC_phiWidth_ . push_back(iSC->phiWidth());
    ecalSC_LICTD_    . push_back(getLICTD(&(*iSC), lazyToolnoZS));

    DetId seedDetID = iSC->seed()->seed();
    const EcalRecHit *seedRecHit  =getECALrecHit(seedDetID, lazyToolnoZS);
    Float_t iSeedTime = -9999;
    Float_t iSeedSwissX = -9999;
    Float_t iSeedEtaW = -9999;
    UChar_t iSeedBits    = 0;
    if(seedRecHit){
      iSeedTime= ECALrecHitT(seedDetID, lazyToolnoZS);
      iSeedSwissX = swissCross(seedDetID, lazyToolnoZS);
      iSeedEtaW = etaWing(seedDetID, lazyToolnoZS);
      if(seedRecHit->checkFlag(EcalRecHit::kDiWeird)) setbit(iSeedBits, 0);
      if(seedRecHit->checkFlag(EcalRecHit::kWeird)) setbit(iSeedBits, 1);
      if(seedRecHit->checkFlag(EcalRecHit::kSaturated)) setbit(iSeedBits, 2);
      if(seedRecHit->checkFlag(EcalRecHit::kOutOfTime)) setbit(iSeedBits, 3);

    }
    ecalSC_seedTime_       . push_back(iSeedTime);
    ecalSC_seedSwissCross_ . push_back(iSeedSwissX);
    ecalSC_seedEtaWing_    . push_back(iSeedEtaW);
    ecalSC_seedBits_       . push_back(iSeedBits);

    if(seedDetID.subdetId() == EcalBarrel){
      EBDetId seedEB = iSC->seed()->seed();
      ecalSC_seedIx_.push_back(seedEB.ieta());
      ecalSC_seedIy_.push_back(seedEB.iphi());
      ecalSC_seedIz_.push_back(0);
    } else if (seedDetID.subdetId() == EcalEndcap){
      EEDetId seedEE = iSC->seed()->seed();
      ecalSC_seedIx_.push_back(seedEE.ix());
      ecalSC_seedIy_.push_back(seedEE.iy());
      ecalSC_seedIz_.push_back(seedEE.zside());
    } else{
      ecalSC_seedIx_.push_back(-116);
      ecalSC_seedIy_.push_back(-116);
      ecalSC_seedIz_.push_back(-116);
    }

    ecalSC_nXtals_.push_back(iSC->hitsAndFractions().size());

    necalSC_++;
  }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////         OOT ECAL SC     ////////////////////////////////////////////////////////
UShort_t             necalootSC_;
std::vector<Float_t> ecalootSC_eta_;
std::vector<Float_t> ecalootSC_phi_;
std::vector<Float_t> ecalootSC_En_;
std::vector<Float_t> ecalootSC_RawEn_;
std::vector<Float_t> ecalootSC_etaWidth_;
std::vector<Float_t> ecalootSC_phiWidth_;
std::vector<Float_t> ecalootSC_LICTD_;
std::vector<Float_t> ecalootSC_seedTime_;
std::vector<Float_t> ecalootSC_seedSwissCross_;
std::vector<Float_t> ecalootSC_seedEtaWing_;
std::vector<UChar_t> ecalootSC_seedBits_;
std::vector<Char_t>  ecalootSC_seedIx_;
std::vector<Char_t>  ecalootSC_seedIy_;
std::vector<Char_t>  ecalootSC_seedIz_;
std::vector<UInt_t>  ecalootSC_nXtals_;

void ggNtuplizer::branchesECALOOTSC(TTree* tree) {
  tree->Branch("necalootSC",               & necalootSC_);
  tree->Branch("ecalootSC_eta",            & ecalootSC_eta_);
  tree->Branch("ecalootSC_phi",            & ecalootSC_phi_);
  tree->Branch("ecalootSC_En",             & ecalootSC_En_);
  tree->Branch("ecalootSC_RawEn",          & ecalootSC_RawEn_);
  tree->Branch("ecalootSC_etaWidth",       & ecalootSC_etaWidth_);
  tree->Branch("ecalootSC_phiWidth",       & ecalootSC_phiWidth_);
  tree->Branch("ecalootSC_LICTD",          & ecalootSC_LICTD_);
  tree->Branch("ecalootSC_seedTime",       & ecalootSC_seedTime_);
  tree->Branch("ecalootSC_seedSwissCross", & ecalootSC_seedSwissCross_);
  tree->Branch("ecalSC_seedEtaWing",       & ecalSC_seedEtaWing_);
  tree->Branch("ecalootSC_seedBits",       & ecalootSC_seedBits_);
  tree->Branch("ecalootSC_seedIx",         & ecalootSC_seedIx_);
  tree->Branch("ecalootSC_seedIy",         & ecalootSC_seedIy_);
  tree->Branch("ecalootSC_seedIz",         & ecalootSC_seedIz_);
  tree->Branch("ecalootSC_nXtals",         & ecalootSC_nXtals_);
};


void ggNtuplizer::fillECALOOTSC(const edm::Event& e, const edm::EventSetup& es){
  necalootSC_ = 0;
  ecalootSCindex_           . clear();
  ecalootSC_eta_            . clear();
  ecalootSC_phi_            . clear();
  ecalootSC_En_             . clear();
  ecalootSC_RawEn_          . clear();
  ecalootSC_etaWidth_       . clear();
  ecalootSC_phiWidth_       . clear();
  ecalootSC_LICTD_          . clear();
  ecalootSC_seedTime_       . clear();
  ecalootSC_seedSwissCross_ . clear();
  ecalootSC_seedEtaWing_    . clear();
  ecalootSC_seedBits_       . clear();
  ecalootSC_seedIx_         . clear();
  ecalootSC_seedIy_         . clear();
  ecalootSC_seedIz_         . clear();
  ecalootSC_nXtals_         . clear();

  edm::Handle<std::vector<reco::SuperCluster>> ecalootSChandle;
  e.getByToken(ecalSC_OOT_collection_, ecalootSChandle);

  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  if(!ecalootSChandle.isValid()) return;

  for(std::vector<reco::SuperCluster>::const_iterator iSC = ecalootSChandle->begin(); iSC != ecalootSChandle->end(); iSC++){

    ecalootSCindex_     . push_back(necalootSC_);
    ecalootSC_eta_      . push_back(iSC->eta());
    ecalootSC_phi_      . push_back(iSC->phi());
    ecalootSC_En_       . push_back(iSC->energy());
    ecalootSC_RawEn_    . push_back(iSC->rawEnergy());
    ecalootSC_etaWidth_ . push_back(iSC->etaWidth());
    ecalootSC_phiWidth_ . push_back(iSC->phiWidth());
    ecalootSC_LICTD_    . push_back(getLICTD(&(*iSC), lazyToolnoZS));

    DetId seedDetID = iSC->seed()->seed();
    const EcalRecHit *seedRecHit  =getECALrecHit(seedDetID, lazyToolnoZS);
    Float_t iSeedTime = -9999;
    Float_t iSeedSwissX = -9999;
    Float_t iSeedEtaW = -9999;
    UChar_t iSeedBits    = 0;
    if(seedRecHit){
      iSeedTime= ECALrecHitT(seedDetID, lazyToolnoZS);
      iSeedSwissX = swissCross(seedDetID, lazyToolnoZS);
      iSeedEtaW = etaWing(seedDetID, lazyToolnoZS);
      if(seedRecHit->checkFlag(EcalRecHit::kDiWeird)) setbit(iSeedBits, 0);
      if(seedRecHit->checkFlag(EcalRecHit::kWeird)) setbit(iSeedBits, 1);
      if(seedRecHit->checkFlag(EcalRecHit::kSaturated)) setbit(iSeedBits, 2);
      if(seedRecHit->checkFlag(EcalRecHit::kOutOfTime)) setbit(iSeedBits, 3);

    }
    ecalootSC_seedTime_.push_back(iSeedTime);
    ecalootSC_seedSwissCross_.push_back(iSeedSwissX);
    ecalootSC_seedEtaWing_.push_back(iSeedEtaW);
    ecalootSC_seedBits_.push_back(iSeedBits);

    if(seedDetID.subdetId() == EcalBarrel){
      EBDetId seedEB = iSC->seed()->seed();
      ecalootSC_seedIx_.push_back(seedEB.ieta());
      ecalootSC_seedIy_.push_back(seedEB.iphi());
      ecalootSC_seedIz_.push_back(0);
    } else if (seedDetID.subdetId() == EcalEndcap){
      EEDetId seedEE = iSC->seed()->seed();
      ecalootSC_seedIx_.push_back(seedEE.ix());
      ecalootSC_seedIy_.push_back(seedEE.iy());
      ecalootSC_seedIz_.push_back(seedEE.zside());
    } else{
      ecalootSC_seedIx_.push_back(-116);
      ecalootSC_seedIy_.push_back(-116);
      ecalootSC_seedIz_.push_back(-116);
    }
    
    ecalootSC_nXtals_.push_back(iSC->hitsAndFractions().size());

    necalootSC_++;
  }
};



Short_t ggNtuplizer::findSecondaryIndex(const Short_t & searchIndex, const std::vector<UShort_t> & container){
  Short_t secondaryIndex = -999;
  for(UInt_t i = 0; i < container.size(); i++){
    if( container[i] ==  searchIndex) {
      secondaryIndex = i;
      break;
    }
  }
  return secondaryIndex;
};
