#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

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

      if(iXtalHit->energy() < iXtalHit->energyError() || iXtalHit->energy() < 1.) continue;

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


UShort_t necalSC_;
std::vector<Float_t> ecalSCeta_;
std::vector<Float_t> ecalSCphi_;
std::vector<Float_t> ecalSCEn_;
std::vector<Float_t> ecalSCRawEn_;
std::vector<Float_t> ecalSCetaWidth_;
std::vector<Float_t> ecalSCphiWidth_;
std::vector<Float_t> ecalSC_LICTD_;
std::vector<Float_t> ecalSC_seedTime_;
std::vector<Float_t> ecalSC_seedSwissCross_;
std::vector<Float_t> ecalSC_seedEtaWing_;
std::vector<UChar_t> ecalSC_seedBits_;
std::vector<Char_t> ecalSCseedIx_;
std::vector<Char_t> ecalSCseedIy_;
std::vector<Char_t> ecalSCseedIz_;


void ggNtuplizer::branchesECALSC(TTree* tree) {
  tree->Branch("necalSC",                       &necalSC_);
  tree->Branch("ecalSCeta",                     &ecalSCeta_);
  tree->Branch("ecalSCphi",                     &ecalSCphi_);
  tree->Branch("ecalSCEn",                      &ecalSCEn_);
  tree->Branch("ecalSCRawEn",                     &ecalSCRawEn_);
  tree->Branch("ecalSCetaWidth",                  &ecalSCetaWidth_);
  tree->Branch("ecalSCphiWidth",                  &ecalSCphiWidth_);
  tree->Branch("ecalSC_LICTD",                    &ecalSC_LICTD_);
  tree->Branch("ecalSC_seedTime",      &ecalSC_seedTime_);
  tree->Branch("ecalSC_seedSwissCross",    &ecalSC_seedSwissCross_);
  tree->Branch("ecalSC_seedEtaWing",                    &ecalSC_seedEtaWing_);
  tree->Branch("ecalSC_seedBits",      &ecalSC_seedBits_);
  tree->Branch("ecalSCseedIx",      &ecalSCseedIx_);
  tree->Branch("ecalSCseedIy",      &ecalSCseedIy_);
  tree->Branch("ecalSCseedIz",      &ecalSCseedIz_);
};


void ggNtuplizer::fillECALSC(const edm::Event& e, const edm::EventSetup& es){
  necalSC_ = 0;
  ecalSCindex_.clear();
  ecalSCeta_.clear();
  ecalSCphi_.clear();
  ecalSCEn_.clear();
  ecalSCRawEn_.clear();
  ecalSCetaWidth_.clear();
  ecalSCphiWidth_.clear();
  ecalSC_LICTD_.clear();
  ecalSC_seedTime_.clear();
  ecalSC_seedSwissCross_.clear();
  ecalSC_seedEtaWing_.clear();
  ecalSC_seedBits_.clear();
  ecalSCseedIx_.clear();
  ecalSCseedIy_.clear();
  ecalSCseedIz_.clear();

  edm::Handle<std::vector<reco::SuperCluster>> ecalSChandle;
  e.getByToken(ecalSCcollection_, ecalSChandle);

  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  if(!ecalSChandle.isValid()) return;

  for(std::vector<reco::SuperCluster>::const_iterator iSC = ecalSChandle->begin(); iSC != ecalSChandle->end(); iSC++){

    ecalSCindex_.push_back(necalSC_);
    ecalSCeta_.push_back(iSC->eta());
    ecalSCphi_.push_back(iSC->phi());
    ecalSCEn_.push_back(iSC->energy());
    ecalSCRawEn_.push_back(iSC->rawEnergy());
    ecalSCetaWidth_.push_back(iSC->etaWidth());
    ecalSCphiWidth_.push_back(iSC->phiWidth());
    ecalSC_LICTD_.push_back(getLICTD(&(*iSC), lazyToolnoZS));

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
    ecalSC_seedTime_.push_back(iSeedTime);
    ecalSC_seedSwissCross_.push_back(iSeedSwissX);
    ecalSC_seedEtaWing_.push_back(iSeedEtaW);
    ecalSC_seedBits_.push_back(iSeedBits);

    if(seedDetID.subdetId() == EcalBarrel){
      EBDetId seedEB = iSC->seed()->seed();
      ecalSCseedIx_.push_back(seedEB.ieta());
      ecalSCseedIy_.push_back(seedEB.iphi());
      ecalSCseedIz_.push_back(0);
    } else if (seedDetID.subdetId() == EcalEndcap){
      EEDetId seedEE = iSC->seed()->seed();
      ecalSCseedIx_.push_back(seedEE.ix());
      ecalSCseedIy_.push_back(seedEE.iy());
      ecalSCseedIz_.push_back(seedEE.zside());
    } else{
      ecalSCseedIx_.push_back(-116);
      ecalSCseedIy_.push_back(-116);
      ecalSCseedIz_.push_back(-116);
    }

    necalSC_++;
  }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////         OOT ECAL SC     ////////////////////////////////////////////////////////
UShort_t necalootSC_;
std::vector<Float_t> ecalootSCeta_;
std::vector<Float_t> ecalootSCphi_;
std::vector<Float_t> ecalootSCEn_;
std::vector<Float_t> ecalootSCRawEn_;
std::vector<Float_t> ecalootSCetaWidth_;
std::vector<Float_t> ecalootSCphiWidth_;
std::vector<Float_t> ecalootSC_LICTD_;
std::vector<Float_t> ecalootSC_seedTime_;
std::vector<Float_t> ecalootSC_seedSwissCross_;
std::vector<Float_t> ecalootSC_seedEtaWing_;
std::vector<UChar_t> ecalootSC_seedBits_;
std::vector<Char_t> ecalootSC_seedIx_;
std::vector<Char_t> ecalootSC_seedIy_;
std::vector<Char_t> ecalootSC_seedIz_;


void ggNtuplizer::branchesECALOOTSC(TTree* tree) {
  tree->Branch("necalootSC",                        &necalootSC_);
  tree->Branch("ecalootSC_eta",                     &ecalootSCeta_);
  tree->Branch("ecalootSC_phi",                     &ecalootSCphi_);
  tree->Branch("ecalootSC_En",                      &ecalootSCEn_);
  tree->Branch("ecalootSC_RawEn",                     &ecalootSCRawEn_);
  tree->Branch("ecalootSC_etaWidth",                  &ecalootSCetaWidth_);
  tree->Branch("ecalootSC_phiWidth",                  &ecalootSCphiWidth_);
  tree->Branch("ecalootSC_LICTD",                    &ecalootSC_LICTD_);
  tree->Branch("ecalootSC_seedTime",     &ecalootSC_seedTime_);
  tree->Branch("ecalootSC_seedSwissCross",   &ecalootSC_seedSwissCross_);
  tree->Branch("ecalSC_seedEtaWing",   &ecalSC_seedEtaWing_);
  tree->Branch("ecalootSC_seedBits",     &ecalootSC_seedBits_);
  tree->Branch("ecalootSC_seedIx",     &ecalootSC_seedIx_);
  tree->Branch("ecalootSC_seedIy",     &ecalootSC_seedIy_);
  tree->Branch("ecalootSC_seedIz",     &ecalootSC_seedIz_);
};


void ggNtuplizer::fillECALOOTSC(const edm::Event& e, const edm::EventSetup& es){
  necalootSC_ = 0;
  ecalootSCindex_.clear();
  ecalootSCeta_.clear();
  ecalootSCphi_.clear();
  ecalootSCEn_.clear();
  ecalootSCRawEn_.clear();
  ecalootSCetaWidth_.clear();
  ecalootSCphiWidth_.clear();
  ecalootSC_LICTD_.clear();
  ecalootSC_seedTime_.clear();
  ecalootSC_seedSwissCross_.clear();
  ecalootSC_seedEtaWing_.clear();
  ecalootSC_seedBits_.clear();
  ecalootSC_seedIx_.clear();
  ecalootSC_seedIy_.clear();
  ecalootSC_seedIz_.clear();


  edm::Handle<std::vector<reco::SuperCluster>> ecalootSChandle;
  e.getByToken(ecalSC_OOT_collection_, ecalootSChandle);

  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  if(!ecalootSChandle.isValid()) return;

  for(std::vector<reco::SuperCluster>::const_iterator iSC = ecalootSChandle->begin(); iSC != ecalootSChandle->end(); iSC++){

    ecalootSCindex_.push_back(necalootSC_);
    ecalootSCeta_.push_back(iSC->eta());
    ecalootSCphi_.push_back(iSC->phi());
    ecalootSCEn_.push_back(iSC->energy());
    ecalootSCRawEn_.push_back(iSC->rawEnergy());
    ecalootSCetaWidth_.push_back(iSC->etaWidth());
    ecalootSCphiWidth_.push_back(iSC->phiWidth());
    ecalootSC_LICTD_.push_back(getLICTD(&(*iSC), lazyToolnoZS));

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
