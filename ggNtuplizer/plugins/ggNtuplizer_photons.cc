#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "Math/VectorUtil.h"

using namespace std;

UShort_t             nPho_;
vector<Float_t>      phoE_;
vector<Float_t>      phoSigmaE_;
vector<Float_t>      phoEt_;
vector<Float_t>      phoEta_;
vector<Float_t>      phoPhi_;
vector<Float_t>      phoCalibE_;
vector<Float_t>      phoSigmaCalibE_;
vector<Float_t>      phoCalibEt_;
vector<Float_t>      phoESEnP1_;
vector<Float_t>      phoESEnP2_;
vector<UChar_t>      phoFiducialRegion_;
vector<UChar_t>      phoQualityBits_;
vector<Float_t>      phoR9_;
vector<Float_t>      phoHoverE_;
vector<Float_t>      phoE2x5BottomFull5x5_;
vector<Float_t>      phoE2x5LeftFull5x5_;
vector<Float_t>      phoE2x5MaxFull5x5_;
vector<Float_t>      phoE2x5RightFull5x5_;
vector<Float_t>      phoE2x5TopFull5x5_;
vector<Float_t>      phoEBottomFull5x5_;
vector<Float_t>      phoELeftFull5x5_;
vector<Float_t>      phoERightFull5x5_;
vector<Float_t>      phoETopFull5x5_;
vector<Float_t>      phoHcalDepth1OverEcal_;
vector<Float_t>      phoHcalDepth1OverEcalBc_;
vector<Float_t>      phoHcalDepth2OverEcal_;
vector<Float_t>      phoHcalDepth2OverEcalBc_;
vector<Float_t>      phoSmAlphaFull5x5_;              // alpha, major, minor defs: https://indico.cern.ch/event/67588/contributions/2073413/attachments/1021729/1454360/cern_20091023.pdf
vector<Float_t>      phoSmMajorFull5x5_;              // https://indico.cern.ch/event/417820/contributions/1890757/attachments/864496/1209890/Franzoni090604.pdf
vector<Float_t>      phoSmMinorFull5x5_;              // https://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_10_6_24/doc/html/da/db1/EcalClusterTools_8h_source.html#l01258
vector<Float_t>      phoESEffSigmaRR_;
vector<Float_t>      phoSigmaIEtaIEtaFull5x5_;
vector<Float_t>      phoSigmaIEtaIPhiFull5x5_;
vector<Float_t>      phoSigmaIPhiIPhiFull5x5_;
vector<Float_t>      phoE3x3Full5x5_;
vector<Float_t>      phoE2x2Full5x5_;
vector<Float_t>      phoE5x5Full5x5_;
vector<Float_t>      phoMaxEnergyXtal;
vector<Float_t>      phoE2ndFull5x5_;
vector<Float_t>      phoE1x3Full5x5_;
vector<Float_t>      phoE1x5Full5x5_;
vector<Float_t>      phoE2x5Full5x5_;
vector<Float_t>      phoR9Full5x5_;
vector<Float_t>      phoPFChIso_;
vector<Float_t>      phoPFPhoIso_;
vector<Float_t>      phoPFNeuIso_;
vector<Float_t>      phoPFChWorstIso_;
vector<Float_t>      phoPFClusEcalIso_;
vector<Float_t>      phoPFClusHcalIso_;
vector<UChar_t>      nPhoTrkHollowConeDR04_;
vector<UChar_t>      nPhoTrkSolidConeDR04_;
vector<Float_t>      phoTrkSumPtSolidConeDR04_;
vector<Float_t>      phoTrkSumPtHollowConeDR04_;
vector<UChar_t>      nPhoTrkHollowConeDR03_;
vector<UChar_t>      nPhoTrkSolidConeDR03_;
vector<Float_t>      phoTrkSumPtSolidConeDR03_;
vector<Float_t>      phoTrkSumPtHollowConeDR03_;
vector<Float_t>      phoECALIso_;
vector<Float_t>      phoHCALIso_;
vector<Float_t>      phoSeedBCE_;
vector<Float_t>      phoSeedBCEta_;
vector<Float_t>      phoSeedBCPhi_;
std::vector<UChar_t> phoSeedSaturationBit_;
std::vector<Int_t>   phonSaturatedXtals_;
vector<Float_t>      phoIDMVA_;
vector<ULong64_t>    phoFiredSingleTrgs_;
vector<ULong64_t>    phoFiredDoubleTrgs_;
vector<ULong64_t>    phoFiredTripleTrgs_;
vector<ULong64_t>    phoFiredL1Trgs_;
vector<Float_t>      phoSeedTime_;
vector<Float_t>      phoSeedEnergy_;
vector<Float_t>      phoMIPChi2_;
vector<Float_t>      phoMIPTotEnergy_;
vector<Float_t>      phoMIPSlope_;
vector<Float_t>      phoMIPIntercept_;
vector<Short_t>      phoMIPNhitCone_;
vector<UChar_t>      phoIDbit_;
vector<Float_t>      phoScale_stat_up_;
vector<Float_t>      phoScale_stat_dn_;
vector<Float_t>      phoScale_syst_up_;
vector<Float_t>      phoScale_syst_dn_;
vector<Float_t>      phoScale_gain_up_;
vector<Float_t>      phoScale_gain_dn_;
vector<Float_t>      phoResol_rho_up_;
vector<Float_t>      phoResol_rho_dn_;
vector<Float_t>      phoResol_phi_up_;
vector<Float_t>      phoResol_phi_dn_;
vector<Short_t>      pho_gen_index_;
vector<int>          phoNConvLegs_;
vector<float>        phoZVtxWithConv_;

//Necessary for the Photon Footprint removal
template <class T, class U>
bool isInFootprint(const T& thefootprint, const U& theCandidate) {
	for ( auto itr = thefootprint.begin(); itr != thefootprint.end(); ++itr ) {

		if( itr.key() == theCandidate.key() ) return true;

	}
	return false;
};


void ggNtuplizer::branchesPhotons(TTree* tree) {
	
	tree->Branch("nPho",                      & nPho_);
	tree->Branch("phoE",                      & phoE_);
	tree->Branch("phoSigmaE",                 & phoSigmaE_);
	tree->Branch("phoEt",                     & phoEt_);
	tree->Branch("phoEta",                    & phoEta_);
	tree->Branch("phoPhi",                    & phoPhi_);
	tree->Branch("phoCalibE",                 & phoCalibE_);
	tree->Branch("phoSigmaCalibE",            & phoSigmaCalibE_);
	tree->Branch("phoCalibEt",                & phoCalibEt_);
	tree->Branch("phoSCindex",                & phoSCindex_);
	tree->Branch("phoESEnP1",                 & phoESEnP1_);
	tree->Branch("phoESEnP2",                 & phoESEnP2_);
	tree->Branch("phoFiducialRegion",         & phoFiducialRegion_);
	tree->Branch("phoQualityBits",            & phoQualityBits_);
	tree->Branch("phoR9",                     & phoR9_);
	tree->Branch("phoHoverE",                 & phoHoverE_);
	tree->Branch("phoE2x5BottomFull5x5",      & phoE2x5BottomFull5x5_);
	tree->Branch("phoE2x5LeftFull5x5",        & phoE2x5LeftFull5x5_);
	tree->Branch("phoE2x5MaxFull5x5",         & phoE2x5MaxFull5x5_);
	tree->Branch("phoE2x5RightFull5x5",       & phoE2x5RightFull5x5_);
	tree->Branch("phoE2x5TopFull5x5",         & phoE2x5TopFull5x5_);
	tree->Branch("phoEBottomFull5x5",         & phoEBottomFull5x5_);
	tree->Branch("phoELeftFull5x5",           & phoELeftFull5x5_);
	tree->Branch("phoERightFull5x5",          & phoERightFull5x5_);
	tree->Branch("phoETopFull5x5",            & phoETopFull5x5_);
	tree->Branch("phoHcalDepth1OverEcal",     & phoHcalDepth1OverEcal_);
	tree->Branch("phoHcalDepth1OverEcalBc",   & phoHcalDepth1OverEcalBc_);
	tree->Branch("phoHcalDepth2OverEcal",     & phoHcalDepth2OverEcal_);
	tree->Branch("phoHcalDepth2OverEcalBc",   & phoHcalDepth2OverEcalBc_);
	tree->Branch("phoSmAlphaFull5x5",         & phoSmAlphaFull5x5_);
	tree->Branch("phoSmMajorFull5x5",         & phoSmMajorFull5x5_);
	tree->Branch("phoSmMinorFull5x5",         & phoSmMinorFull5x5_);
	tree->Branch("phoESEffSigmaRR",           & phoESEffSigmaRR_);
	tree->Branch("phoSigmaIEtaIEtaFull5x5",   & phoSigmaIEtaIEtaFull5x5_);
	tree->Branch("phoSigmaIEtaIPhiFull5x5",   & phoSigmaIEtaIPhiFull5x5_);
	tree->Branch("phoSigmaIPhiIPhiFull5x5",   & phoSigmaIPhiIPhiFull5x5_);
	tree->Branch("phoE3x3Full5x5",            & phoE3x3Full5x5_);
	tree->Branch("phoE2x2Full5x5",            & phoE2x2Full5x5_);
	tree->Branch("phoE5x5Full5x5",            & phoE5x5Full5x5_);
	tree->Branch("phoMaxEnergyXtal",          & phoMaxEnergyXtal);
	tree->Branch("phoE2ndFull5x5",            & phoE2ndFull5x5_);
	tree->Branch("phoE1x3Full5x5",            & phoE1x3Full5x5_);
	tree->Branch("phoE1x5Full5x5",            & phoE1x5Full5x5_);
	tree->Branch("phoE2x5Full5x5",            & phoE2x5Full5x5_);
	tree->Branch("phoR9Full5x5",              & phoR9Full5x5_);
	tree->Branch("phoSeedBCE",                & phoSeedBCE_);
	tree->Branch("phoSeedBCEta",              & phoSeedBCEta_);
	tree->Branch("phoSeedBCPhi",              & phoSeedBCPhi_);
	tree->Branch("phoSeedSaturationBit",      & phoSeedSaturationBit_);
	tree->Branch("phonSaturatedXtals",        & phonSaturatedXtals_);
	tree->Branch("phoPFChIso",                & phoPFChIso_);
	tree->Branch("phoPFPhoIso",               & phoPFPhoIso_);
	tree->Branch("phoPFNeuIso",               & phoPFNeuIso_);
	tree->Branch("phoPFChWorstIso",           & phoPFChWorstIso_);
	tree->Branch("phoPFClusEcalIso",          & phoPFClusEcalIso_);
	tree->Branch("phoPFClusHcalIso",          & phoPFClusHcalIso_);
	tree->Branch("nPhoTrkSolidConeDR03",      & nPhoTrkSolidConeDR03_);
	tree->Branch("nPhoTrkHollowConeDR03",     & nPhoTrkHollowConeDR03_);
	tree->Branch("phoTrkSumPtSolidConeDR03",  & phoTrkSumPtSolidConeDR03_);
	tree->Branch("phoTrkSumPtHollowConeDR03", & phoTrkSumPtHollowConeDR03_);
	tree->Branch("nPhoTrkSolidConeDR04",      & nPhoTrkSolidConeDR04_);
	tree->Branch("nPhoTrkHollowConeDR04",     & nPhoTrkHollowConeDR04_);
	tree->Branch("phoTrkSumPtSolidConeDR04",  & phoTrkSumPtSolidConeDR04_);
	tree->Branch("phoTrkSumPtHollowConeDR04", & phoTrkSumPtHollowConeDR04_);
	tree->Branch("phoECALIso",                & phoECALIso_);
	tree->Branch("phoHCALIso",                & phoHCALIso_);
	tree->Branch("phoIDMVA",                  & phoIDMVA_);
	tree->Branch("phoFiredSingleTrgs",        & phoFiredSingleTrgs_);
	tree->Branch("phoFiredDoubleTrgs",        & phoFiredDoubleTrgs_);
	tree->Branch("phoFiredTripleTrgs",        & phoFiredTripleTrgs_);
	tree->Branch("phoFiredL1Trgs",            & phoFiredL1Trgs_);
	tree->Branch("phoSeedTime",               & phoSeedTime_);
	tree->Branch("phoSeedEnergy",             & phoSeedEnergy_);
	tree->Branch("phoMIPChi2",                & phoMIPChi2_);
	tree->Branch("phoMIPTotEnergy",           & phoMIPTotEnergy_);
	tree->Branch("phoMIPSlope",               & phoMIPSlope_);
	tree->Branch("phoMIPIntercept",           & phoMIPIntercept_);
	tree->Branch("phoMIPNhitCone",            & phoMIPNhitCone_);
	tree->Branch("phoIDbit",                  & phoIDbit_);
	tree->Branch("phoScale_stat_up",          & phoScale_stat_up_);
	tree->Branch("phoScale_stat_dn",          & phoScale_stat_dn_);
	tree->Branch("phoScale_syst_up",          & phoScale_syst_up_);
	tree->Branch("phoScale_syst_dn",          & phoScale_syst_dn_);
	tree->Branch("phoScale_gain_up",          & phoScale_gain_up_);
	tree->Branch("phoScale_gain_dn",          & phoScale_gain_dn_);
	tree->Branch("phoResol_rho_up",           & phoResol_rho_up_);
	tree->Branch("phoResol_rho_dn",           & phoResol_rho_dn_);
	tree->Branch("phoResol_phi_up",           & phoResol_phi_up_);
	tree->Branch("phoResol_phi_dn",           & phoResol_phi_dn_);
	tree->Branch("phoNConvLegs",              & phoNConvLegs_);
	tree->Branch("phoZVtxWithConv",           & phoZVtxWithConv_);
	if(doGenParticles_){
		tree->Branch("pho_gen_index",         & pho_gen_index_);
	}
}


void ggNtuplizer::fillPhotons(const edm::Event& e, const edm::EventSetup& es) {

	// cleanup from previous execution
	phoE_                           . clear();
	phoSigmaE_                      . clear();
	phoEt_                          . clear();
	phoEta_                         . clear();
	phoPhi_                         . clear();
	phoCalibE_                      . clear();
	phoSigmaCalibE_                 . clear();
	phoCalibEt_                     . clear();
	phoSCindex_                     . clear();
	phoESEnP1_                      . clear();
	phoESEnP2_                      . clear();
	phoFiducialRegion_              . clear();
	phoQualityBits_                 . clear();
	phoR9_                          . clear();
	phoHoverE_                      . clear();
	phoE2x5BottomFull5x5_           . clear();
	phoE2x5LeftFull5x5_             . clear();
	phoE2x5MaxFull5x5_              . clear();
	phoE2x5RightFull5x5_            . clear();
	phoE2x5TopFull5x5_              . clear();
	phoEBottomFull5x5_              . clear();
	phoELeftFull5x5_                . clear();
	phoERightFull5x5_               . clear();
	phoETopFull5x5_                 . clear();
	phoHcalDepth1OverEcal_   . clear();
	phoHcalDepth1OverEcalBc_ . clear();
	phoHcalDepth2OverEcal_   . clear();
	phoHcalDepth2OverEcalBc_ . clear();
	phoSmAlphaFull5x5_              . clear();
	phoSmMajorFull5x5_              . clear();
	phoSmMinorFull5x5_              . clear();
	phoESEffSigmaRR_                . clear();
	phoSigmaIEtaIEtaFull5x5_        . clear();
	phoSigmaIEtaIPhiFull5x5_        . clear();
	phoSigmaIPhiIPhiFull5x5_        . clear();
	phoE3x3Full5x5_                 . clear();
	phoE2x2Full5x5_                 . clear();
	phoE5x5Full5x5_                 . clear();
	phoR9Full5x5_                   . clear();
	phoPFChIso_                     . clear();
	phoPFPhoIso_                    . clear();
	phoPFNeuIso_                    . clear();
	phoPFChWorstIso_                . clear();
	phoPFClusEcalIso_               . clear();
	phoPFClusHcalIso_               . clear();
	nPhoTrkHollowConeDR03_          . clear();
	nPhoTrkSolidConeDR03_           . clear();
	phoTrkSumPtSolidConeDR03_       . clear();
	phoTrkSumPtHollowConeDR03_      . clear();
	nPhoTrkHollowConeDR04_          . clear();
	nPhoTrkSolidConeDR04_           . clear();
	phoTrkSumPtSolidConeDR04_       . clear();
	phoTrkSumPtHollowConeDR04_      . clear();
	phoMaxEnergyXtal                . clear();
	phoE2ndFull5x5_                 . clear();
	phoE1x3Full5x5_                 . clear();
	phoE1x5Full5x5_                 . clear();
	phoE2x5Full5x5_                 . clear();
	phoECALIso_                     . clear();
	phoHCALIso_                     . clear();
	phoSeedBCE_                     . clear();
	phoSeedBCEta_                   . clear();
	phoSeedBCPhi_                   . clear();
	phoSeedSaturationBit_. clear();
	phonSaturatedXtals_. clear();
	phoIDMVA_                       . clear();
	phoFiredSingleTrgs_             . clear();
	phoFiredDoubleTrgs_             . clear();
	phoFiredTripleTrgs_             . clear();
	phoFiredL1Trgs_                 . clear();
	phoSeedTime_                    . clear();
	phoSeedEnergy_                  . clear();
	phoMIPChi2_                     . clear();
	phoMIPTotEnergy_                . clear();
	phoMIPSlope_                    . clear();
	phoMIPIntercept_                . clear();
	phoMIPNhitCone_                 . clear();
	phoIDbit_                       . clear();
	phoScale_stat_up_               . clear();
	phoScale_stat_dn_               . clear();
	phoScale_syst_up_               . clear();
	phoScale_syst_dn_               . clear();
	phoScale_gain_up_               . clear();
	phoScale_gain_dn_               . clear();
	phoResol_rho_up_                . clear();
	phoResol_rho_dn_                . clear();
	phoResol_phi_up_                . clear();
	phoResol_phi_dn_                . clear();
	pho_gen_index_                  . clear();
	phoZVtxWithConv_                . clear();
	phoNConvLegs_                   . clear();
	nPho_ = 0;

	edm::Handle<edm::View<pat::Photon> > photonHandle;
	e.getByToken(photonCollection_, photonHandle);

	if (!photonHandle.isValid()) {
		edm::LogWarning("ggNtuplizer") << "no pat::Photons in event";
		return;
	}

	edm::Handle<vector<reco::GenParticle>> genParticlesHandle;
	if(doGenParticles_) e.getByToken(genParticlesCollection_, genParticlesHandle);

	edm::Handle<std::vector<reco::SuperCluster>> ecalSChandle;
	e.getByToken(ecalSCcollection_, ecalSChandle);

	noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

	//reco::BeamSpot beamSpot;
	math::XYZPoint beamSpot;
	edm::Handle<reco::BeamSpot> beamSpotHandle;
	e.getByToken(offlinebeamSpot_, beamSpotHandle);

	if (beamSpotHandle.isValid()) {
		beamSpot = beamSpotHandle->position();
	} else {
		std::cout << "No beam spot available!!!" << std::endl;
	}

	edm::Handle<edm::View<reco::Conversion> > conversionHandle;
	e.getByToken(convPhotonTag_, conversionHandle);

	if (!conversionHandle.isValid()) {
		std::cout << "No Conv not available!!!" << std::endl;
	}

	///single leg conv
	edm::Handle<edm::View<reco::Conversion> > conversionHandleSL;
	e.getByToken(convPhotonTagSL_, conversionHandleSL);

	if (!conversionHandleSL.isValid()) {
		std::cout << "No ConvSL not available!!!" << std::endl;
	}

	for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho){

		phoE_           . push_back(iPho->energy());
		phoCalibE_      . push_back(iPho->userFloat("ecalEnergyPostCorr"));
		phoEt_          . push_back(iPho->et());
		phoCalibEt_     . push_back(iPho->et()*iPho->userFloat("ecalEnergyPostCorr")/iPho->energy());
		phoSigmaE_      . push_back(iPho->userFloat("ecalEnergyErrPreCorr"));
		phoSigmaCalibE_ . push_back(iPho->userFloat("ecalEnergyErrPostCorr"));
		phoEta_         . push_back(iPho->eta());
		phoPhi_         . push_back(iPho->phi());
		phoESEnP1_      . push_back(iPho->superCluster()->preshowerEnergyPlane1());
		phoESEnP2_      . push_back(iPho->superCluster()->preshowerEnergyPlane2());

		UChar_t _phoQualityBits = 0;
		if(iPho->hasPixelSeed()) setbit(_phoQualityBits, 0);
		if(iPho->passElectronVeto()) setbit(_phoQualityBits, 1);
		phoQualityBits_                 . push_back(_phoQualityBits);

		phoR9_                     . push_back(iPho->r9());
		phoHoverE_                 . push_back(iPho->hadTowOverEm());

		phoE2x5BottomFull5x5_      . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5Bottom);
		phoE2x5LeftFull5x5_        . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5Left);
		phoE2x5MaxFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5Max);
		phoE2x5RightFull5x5_       . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5Right);
		phoE2x5TopFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5Top);
		phoEBottomFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . eBottom);
		phoELeftFull5x5_           . push_back(iPho->full5x5_showerShapeVariables()                       . eLeft);
		phoERightFull5x5_          . push_back(iPho->full5x5_showerShapeVariables()                       . eRight);
		phoETopFull5x5_            . push_back(iPho->full5x5_showerShapeVariables()                       . eTop);
		phoHcalDepth1OverEcal_     . push_back(iPho->showerShapeVariables()                       . hcalDepth1OverEcal);
		phoHcalDepth1OverEcalBc_   . push_back(iPho->showerShapeVariables()                       . hcalDepth1OverEcalBc);
		phoHcalDepth2OverEcal_     . push_back(iPho->showerShapeVariables()                       . hcalDepth2OverEcal);
		phoHcalDepth2OverEcalBc_   . push_back(iPho->showerShapeVariables()                       . hcalDepth2OverEcalBc);
		phoSmAlphaFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . smAlpha);
		phoSmMajorFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . smMajor);
		phoSmMinorFull5x5_         . push_back(iPho->full5x5_showerShapeVariables()                       . smMinor);

		phoESEffSigmaRR_           . push_back(iPho->full5x5_showerShapeVariables()                       . effSigmaRR);
		phoPFChIso_                . push_back(iPho->chargedHadronIso());
		phoPFPhoIso_               . push_back(iPho->photonIso());
		phoPFNeuIso_               . push_back(iPho->neutralHadronIso());
		phoPFChWorstIso_           . push_back(iPho->chargedHadronWorstVtxIso());

		phoPFClusEcalIso_          . push_back(iPho->ecalPFClusterIso());
		phoPFClusHcalIso_          . push_back(iPho->hcalPFClusterIso());
		phoTrkSumPtSolidConeDR04_  . push_back(iPho->trkSumPtSolidConeDR04() );
		phoTrkSumPtSolidConeDR03_  . push_back(iPho->trkSumPtSolidConeDR03());
		phoTrkSumPtHollowConeDR04_ . push_back(iPho->trkSumPtHollowConeDR04());
		phoTrkSumPtHollowConeDR03_ . push_back(iPho->trkSumPtHollowConeDR03());

		nPhoTrkHollowConeDR04_     . push_back(iPho->nTrkHollowConeDR04());
		nPhoTrkSolidConeDR04_      . push_back(iPho->nTrkSolidConeDR04());
		nPhoTrkHollowConeDR03_     . push_back(iPho->nTrkHollowConeDR03());
		nPhoTrkSolidConeDR03_      . push_back(iPho->nTrkSolidConeDR03());
		phoMaxEnergyXtal           . push_back(iPho->full5x5_maxEnergyXtal());
		phoE2ndFull5x5_            . push_back(iPho->full5x5_showerShapeVariables()                       . e2nd);
		phoE1x3Full5x5_            . push_back(iPho->full5x5_showerShapeVariables()                       . e1x3);
		phoE1x5Full5x5_            . push_back(iPho->full5x5_showerShapeVariables()                       . e1x5);
		phoE2x5Full5x5_            . push_back(iPho->full5x5_showerShapeVariables()                       . e2x5);
		
		phoECALIso_                . push_back(iPho->ecalIso());
		phoHCALIso_                . push_back(iPho->hcalIso());

		phoIDMVA_                  . push_back(iPho->userFloat("PhotonMVAEstimatorRunIIFall17v2Values"));

		phoSeedBCE_                . push_back(iPho->superCluster()->seed()->energy());
		phoSeedBCEta_              . push_back(iPho->superCluster()->seed()->eta());
		phoSeedBCPhi_              . push_back(iPho->superCluster()->seed()->phi());
		phoMIPChi2_                . push_back(iPho->mipChi2());
		phoMIPTotEnergy_           . push_back(iPho->mipTotEnergy());
		phoMIPSlope_               . push_back(iPho->mipSlope());
		phoMIPIntercept_           . push_back(iPho->mipIntercept());
		phoMIPNhitCone_            . push_back(iPho->mipNhitCone());


		// get photon supercluster index (for looking up from the SC branches)
		if(ecalSChandle.isValid()){
			const reco::SuperCluster * _tmpPhoSC = (iPho->superCluster().isAvailable()) ? iPho->superCluster().get() : nullptr;
			Short_t tmpPhoSCindex = (_tmpPhoSC == nullptr) ? -999 : std::distance(ecalSChandle->begin(), (std::vector<reco::SuperCluster>::const_iterator) _tmpPhoSC);
			phoSCindex_.push_back(tmpPhoSCindex);
		}

		UChar_t tmpphoFiducialRegion = 0;
		if(iPho->isEB()) setbit(tmpphoFiducialRegion, 0);
		if(iPho->isEE()) setbit(tmpphoFiducialRegion, 1);
		if(iPho->isEBEEGap()) setbit(tmpphoFiducialRegion, 2);
		if(iPho->isEBEtaGap ()) setbit(tmpphoFiducialRegion, 3);
		if(iPho->isEBPhiGap ()) setbit(tmpphoFiducialRegion, 4);
		if(iPho->isEEDeeGap ()) setbit(tmpphoFiducialRegion, 5);
		if(iPho->isEERingGap()) setbit(tmpphoFiducialRegion, 6);
		phoFiducialRegion_  .push_back(tmpphoFiducialRegion);


		// VID decisions
		UShort_t tmpphoIDbit = 0;
		// if(year_ == 2017){
		//// https://twiki.cern.ch/twiki/bin/view/CMS/EgammaRunIIRecommendations?rev=9#Fall17v2_AN1
		if (iPho->photonID("cutBasedPhotonID-Fall17-94X-V2-loose"))  setbit(tmpphoIDbit, 0);
		if (iPho->photonID("cutBasedPhotonID-Fall17-94X-V2-medium")) setbit(tmpphoIDbit, 1);
		if (iPho->photonID("cutBasedPhotonID-Fall17-94X-V2-tight"))  setbit(tmpphoIDbit, 2);
		if (iPho->photonID("mvaPhoID-RunIIFall17-v2-wp80"))  setbit(tmpphoIDbit, 3);
		if (iPho->photonID("mvaPhoID-RunIIFall17-v2-wp90"))  setbit(tmpphoIDbit, 4);
		if (!(iPho->mipIsHalo()))  setbit(tmpphoIDbit, 7);

		phoIDbit_.push_back(tmpphoIDbit);

		// systematics for energy scale and resolution
		phoScale_stat_up_ . push_back(iPho->userFloat("energyScaleStatUp"));
		phoScale_stat_dn_ . push_back(iPho->userFloat("energyScaleStatDown"));
		phoScale_syst_up_ . push_back(iPho->userFloat("energyScaleSystUp"));
		phoScale_syst_dn_ . push_back(iPho->userFloat("energyScaleSystDown"));
		phoScale_gain_up_ . push_back(iPho->userFloat("energyScaleGainUp"));
		phoScale_gain_dn_ . push_back(iPho->userFloat("energyScaleGainDown"));
		phoResol_rho_up_  . push_back(iPho->userFloat("energySigmaRhoUp"));
		phoResol_rho_dn_  . push_back(iPho->userFloat("energySigmaRhoDown"));
		phoResol_phi_up_  . push_back(iPho->userFloat("energySigmaPhiUp"));
		phoResol_phi_dn_  . push_back(iPho->userFloat("energySigmaPhiDown"));

		bool isBarrel = (iPho->superCluster()->seed()->seed().subdetId() == EcalBarrel);
		const EcalRecHitCollection * rechits = (isBarrel ? lazyToolnoZS.getEcalEBRecHitCollection() : lazyToolnoZS.getEcalEERecHitCollection());
		DetId seed = lazyToolnoZS.getMaximum(*(iPho->superCluster()->seed())).first;
		EcalRecHitCollection::const_iterator theSeedHit = rechits->find(seed);
		if (theSeedHit != rechits->end()) {
			phoSeedTime_.push_back(theSeedHit->time());
			phoSeedEnergy_.push_back(theSeedHit->energy());
		} else{
			phoSeedTime_  .push_back(-99.);
			phoSeedEnergy_.push_back(-99.);
		}

		phoFiredSingleTrgs_      . push_back(matchSinglePhotonTriggerFilters(iPho->et(), iPho->eta(), iPho->phi()));
		phoFiredDoubleTrgs_      . push_back(matchDoublePhotonTriggerFilters(iPho->et(), iPho->eta(), iPho->phi()));
		phoFiredTripleTrgs_      . push_back(matchTriplePhotonTriggerFilters(iPho->et(), iPho->eta(), iPho->phi()));
		phoFiredL1Trgs_          . push_back(matchL1TriggerFilters(iPho->et(), iPho->eta(), iPho->phi()));

		phoSigmaIEtaIEtaFull5x5_ . push_back(iPho->full5x5_sigmaIetaIeta());
		phoSigmaIEtaIPhiFull5x5_ . push_back(iPho->full5x5_showerShapeVariables()                                    . sigmaIetaIphi);
		phoSigmaIPhiIPhiFull5x5_ . push_back(iPho->full5x5_showerShapeVariables()                                    . sigmaIphiIphi);
		phoE3x3Full5x5_          . push_back(iPho->full5x5_showerShapeVariables()                                    . e3x3);
		phoE2x2Full5x5_          . push_back(iPho->full5x5_showerShapeVariables()                                    . e2x2);
		phoE5x5Full5x5_          . push_back(iPho->full5x5_e5x5());
		phoR9Full5x5_            . push_back(iPho->full5x5_r9());

		if(doGenParticles_){
		  const reco::GenParticle * phoGen_ = iPho->genParticle(); // I don't know what matching algoritm is used - https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2017#MC_Truth
		  Short_t phoGenPos_ = (phoGen_ == nullptr) ? -999 : std::distance(genParticlesHandle->begin(), (std::vector<reco::GenParticle>::const_iterator) phoGen_);
		  // if(phoGenPos_>=0) std::cout<<"pho->genParticle->pdgID "<<phoGen_->pdgId()<<" prunedGenParticle("<<phoGenPos_<<")->pdgid() "<< (&*genParticlesHandle->begin()+phoGenPos_)->pdgId()<<std::endl;
		  pho_gen_index_.push_back(phoGenPos_);
		}

		phoSeedSaturationBit_.push_back(iPho->isSeedSaturated());
		phonSaturatedXtals_.push_back(iPho->nSaturatedXtals());

		///conv pho info
		/////reconstruct the Z vertex of the photons to reject beam halo from the converted ones
		std::vector<int> vIndexMatchedConversion;
		vIndexMatchedConversion = IndexMatchedConversion( iPho, conversionHandle->ptrs(), conversionHandleSL->ptrs() );
		int IndexMatchedConversion = vIndexMatchedConversion[0];

		int nConvLegs = vIndexMatchedConversion[1];
		double zconv = -99;

		if(nConvLegs>0){

			if(nConvLegs==2){
				const std::vector<edm::Ptr<reco::Conversion> > & conversions = conversionHandle->ptrs();
				zconv = vtxZFromConv( iPho, conversions[IndexMatchedConversion], beamSpot);   
			}

			if(nConvLegs==1){
				const std::vector<edm::Ptr<reco::Conversion> > & conversions = conversionHandleSL->ptrs();
				zconv = vtxZFromConv( iPho, conversions[IndexMatchedConversion], beamSpot);   
			}


		}
		
		phoNConvLegs_.push_back(nConvLegs);
		phoZVtxWithConv_.push_back(zconv);

		nPho_++;
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////         OOT Photons     ////////////////////////////////////////////////////////
UShort_t             nootPho_;
vector<Float_t>      ootPho_E_;
vector<Float_t>      ootPho_Et_;
vector<Float_t>      ootPho_SigmaE_;
vector<Float_t>      ootPho_CalibE_;
vector<Float_t>      ootPho_SigmaCalibE_;
vector<Float_t>      ootPho_CalibEt_;
vector<Float_t>      ootPho_Eta_;
vector<Float_t>      ootPho_Phi_;
vector<UChar_t>      ootPho_FiducialRegion_;
vector<UChar_t>      ootPho_QualityBits_;
vector<Float_t>      ootPho_R9_;
vector<Float_t>      ootPho_HoverE_;
vector<Float_t>      ootPho_E2x5BottomFull5x5_;
vector<Float_t>      ootPho_E2x5LeftFull5x5_;
vector<Float_t>      ootPho_E2x5MaxFull5x5_;
vector<Float_t>      ootPho_E2x5RightFull5x5_;
vector<Float_t>      ootPho_E2x5TopFull5x5_;
vector<Float_t>      ootPho_EBottomFull5x5_;
vector<Float_t>      ootPho_ELeftFull5x5_;
vector<Float_t>      ootPho_ERightFull5x5_;
vector<Float_t>      ootPho_ETopFull5x5_;
vector<Float_t>      ootPho_HcalDepth1OverEcal_;
vector<Float_t>      ootPho_HcalDepth1OverEcalBc_;
vector<Float_t>      ootPho_HcalDepth2OverEcal_;
vector<Float_t>      ootPho_HcalDepth2OverEcalBc_;
vector<Float_t>      ootPho_SmAlphaFull5x5_;
vector<Float_t>      ootPho_SmMajorFull5x5_;
vector<Float_t>      ootPho_SmMinorFull5x5_;
vector<Float_t>      ootPho_ESEffSigmaRR_;
vector<Float_t>      ootPho_SigmaIEtaIEtaFull5x5_;
vector<Float_t>      ootPho_SigmaIEtaIPhiFull5x5_;
vector<Float_t>      ootPho_SigmaIPhiIPhiFull5x5_;
vector<Float_t>      ootPho_R9Full5x5_;
vector<ULong64_t>    ootPho_FiredSingleTrgs_;
vector<ULong64_t>    ootPho_FiredDoubleTrgs_;
vector<ULong64_t>    ootPho_FiredTripleTrgs_;
vector<ULong64_t>    ootPho_FiredL1Trgs_;
vector<Float_t>      ootPho_SeedTime_;
vector<Float_t>      ootPho_SeedEnergy_;
vector<Float_t>      ootPho_MIPChi2_;
vector<Float_t>      ootPho_MIPTotEnergy_;
vector<Float_t>      ootPho_MIPSlope_;
vector<Float_t>      ootPho_MIPIntercept_;
vector<Short_t>      ootPho_MIPNhitCone_;
vector<UChar_t>      ootPho_IDbit_;
vector<Float_t>      ootPho_ESEnP1_;
vector<Float_t>      oootPho_ESEnP2_;
vector<Float_t>      ootPho_E3x3Full5x5_;
vector<Float_t>      ootPho_E2x2Full5x5_;
vector<Float_t>      ootPho_E5x5Full5x5_;
vector<Float_t>      ootPho_MaxEnergyXtal;
vector<Float_t>      ootPho_E2ndFull5x5_;
vector<Float_t>      ootPho_E1x3Full5x5_;
vector<Float_t>      ootPho_E1x5Full5x5_;
vector<Float_t>      ootPho_E2x5Full5x5_;
vector<Float_t>      ootPho_PFClusEcalIso_;
vector<Float_t>      ootPho_PFClusHcalIso_;
vector<UChar_t>      nootPho_TrkHollowConeDR04_;
vector<UChar_t>      nootPho_TrkSolidConeDR04_;
vector<Float_t>      ootPho_TrkSumPtSolidConeDR04_;
vector<Float_t>      ootPho_TrkSumPtHollowConeDR04_;
vector<UChar_t>      nootPho_TrkHollowConeDR03_;
vector<UChar_t>      nootPho_TrkSolidConeDR03_;
vector<Float_t>      ootPho_TrkSumPtSolidConeDR03_;
vector<Float_t>      ootPho_TrkSumPtHollowConeDR03_;
vector<Float_t>      ootPho_ECALIso_;
vector<Float_t>      ootPho_HCALIso_;
vector<Float_t>      ootPho_SeedBCE_;
vector<Float_t>      ootPho_SeedBCEta_;
vector<Float_t>      ootPho_SeedBCPhi_;
std::vector<UChar_t> ootPho_SeedSaturationBit_;
std::vector<Int_t>   ootPho_SaturatedXtals_;

void ggNtuplizer::branchesPhotonsOOT(TTree* tree) {
	tree->Branch("nootPho",                            & nootPho_);
	tree->Branch("ootPho_E",                           & ootPho_E_);
	tree->Branch("ootPho_SigmaE",                      & ootPho_SigmaE_);
	tree->Branch("ootPho_Et",                          & ootPho_Et_);
	tree->Branch("ootPho_CalibE",                      & ootPho_CalibE_);
	tree->Branch("ootPho_SigmaCalibE",                 & ootPho_SigmaCalibE_);
	tree->Branch("ootPho_CalibEt",                     & ootPho_CalibEt_);
	tree->Branch("ootPho_Eta",                         & ootPho_Eta_);
	tree->Branch("ootPho_Phi",                         & ootPho_Phi_);
	tree->Branch("ootPho_SCindex",                     & ootPho_SCindex_);
	tree->Branch("ootPho_ESEnP1",                      & ootPho_ESEnP1_);
	tree->Branch("oootPho_ESEnP2",                     & oootPho_ESEnP2_);
	tree->Branch("ootPho_FiducialRegion",              & ootPho_FiducialRegion_);
	tree->Branch("ootPho_QualityBits",                 & ootPho_QualityBits_);
	tree->Branch("ootPho_R9",                          & ootPho_R9_);
	tree->Branch("ootPho_HoverE",                      & ootPho_HoverE_);
	tree->Branch("ootPho_E2x5BottomFull5x5",           & ootPho_E2x5BottomFull5x5_);
	tree->Branch("ootPho_E2x5LeftFull5x5",             & ootPho_E2x5LeftFull5x5_);
	tree->Branch("ootPho_E2x5MaxFull5x5",              & ootPho_E2x5MaxFull5x5_);
	tree->Branch("ootPho_E2x5RightFull5x5",            & ootPho_E2x5RightFull5x5_);
	tree->Branch("ootPho_E2x5TopFull5x5",              & ootPho_E2x5TopFull5x5_);
	tree->Branch("ootPho_EBottomFull5x5",              & ootPho_EBottomFull5x5_);
	tree->Branch("ootPho_ELeftFull5x5",                & ootPho_ELeftFull5x5_);
	tree->Branch("ootPho_ERightFull5x5",               & ootPho_ERightFull5x5_);
	tree->Branch("ootPho_ETopFull5x5",                 & ootPho_ETopFull5x5_);
	tree->Branch("ootPho_HcalDepth1OverEcal",   & ootPho_HcalDepth1OverEcal_);
	tree->Branch("ootPho_HcalDepth1OverEcalBc", & ootPho_HcalDepth1OverEcalBc_);
	tree->Branch("ootPho_HcalDepth2OverEcal",   & ootPho_HcalDepth2OverEcal_);
	tree->Branch("ootPho_HcalDepth2OverEcalBc", & ootPho_HcalDepth2OverEcalBc_);
	tree->Branch("ootPho_SmAlphaFull5x5",              & ootPho_SmAlphaFull5x5_);
	tree->Branch("ootPho_SmMajorFull5x5",              & ootPho_SmMajorFull5x5_);
	tree->Branch("ootPho_SmMinorFull5x5",              & ootPho_SmMinorFull5x5_);
	tree->Branch("ootPho_ESEffSigmaRR",                & ootPho_ESEffSigmaRR_);
	tree->Branch("ootPho_SigmaIEtaIEtaFull5x5",        & ootPho_SigmaIEtaIEtaFull5x5_);
	tree->Branch("ootPho_SigmaIEtaIPhiFull5x5",        & ootPho_SigmaIEtaIPhiFull5x5_);
	tree->Branch("ootPho_SigmaIPhiIPhiFull5x5",        & ootPho_SigmaIPhiIPhiFull5x5_);
	tree->Branch("ootPho_E3x3Full5x5",                 & ootPho_E3x3Full5x5_);
	tree->Branch("ootPho_E2x2Full5x5",                 & ootPho_E2x2Full5x5_);
	tree->Branch("ootPho_E5x5Full5x5",                 & ootPho_E5x5Full5x5_);
	tree->Branch("ootPho_R9Full5x5",                   & ootPho_R9Full5x5_);
	tree->Branch("ootPho_MaxEnergyXtal",               & ootPho_MaxEnergyXtal);
	tree->Branch("ootPho_E2ndFull5x5",                 & ootPho_E2ndFull5x5_);
	tree->Branch("ootPho_E1x3Full5x5",                 & ootPho_E1x3Full5x5_);
	tree->Branch("ootPho_E1x5Full5x5",                 & ootPho_E1x5Full5x5_);
	tree->Branch("ootPho_E2x5Full5x5",                 & ootPho_E2x5Full5x5_);
	tree->Branch("ootPho_PFClusEcalIso",               & ootPho_PFClusEcalIso_);
	tree->Branch("ootPho_PFClusHcalIso",               & ootPho_PFClusHcalIso_);
	tree->Branch("nootPho_TrkHollowConeDR03",          & nootPho_TrkHollowConeDR03_);
	tree->Branch("nootPho_TrkSolidConeDR03",           & nootPho_TrkSolidConeDR03_);
	tree->Branch("ootPho_TrkSumPtSolidConeDR03",       & ootPho_TrkSumPtSolidConeDR03_);
	tree->Branch("ootPho_TrkSumPtHollowConeDR03",      & ootPho_TrkSumPtHollowConeDR03_);
	tree->Branch("nootPho_TrkHollowConeDR04",          & nootPho_TrkHollowConeDR04_);
	tree->Branch("nootPho_TrkSolidConeDR04",           & nootPho_TrkSolidConeDR04_);
	tree->Branch("ootPho_TrkSumPtSolidConeDR04",       & ootPho_TrkSumPtSolidConeDR04_);
	tree->Branch("ootPho_TrkSumPtHollowConeDR04",      & ootPho_TrkSumPtHollowConeDR04_);
	tree->Branch("ootPho_ECALIso",                     & ootPho_ECALIso_);
	tree->Branch("ootPho_HCALIso",                     & ootPho_HCALIso_);
	tree->Branch("ootPho_SeedBCE",                     & ootPho_SeedBCE_);
	tree->Branch("ootPho_SeedBCEta",                   & ootPho_SeedBCEta_);
	tree->Branch("ootPho_SeedBCPhi",                   & ootPho_SeedBCPhi_);
	tree->Branch("ootPho_SeedSaturationBit",           & ootPho_SeedSaturationBit_);
	tree->Branch("ootPho_SaturatedXtals",              & ootPho_SaturatedXtals_);
	tree->Branch("ootPho_FiredSingleTrgs",             & ootPho_FiredSingleTrgs_);
	tree->Branch("ootPho_FiredDoubleTrgs",             & ootPho_FiredDoubleTrgs_);
	tree->Branch("ootPho_FiredTripleTrgs",             & ootPho_FiredTripleTrgs_);
	tree->Branch("ootPho_FiredL1Trgs",                 & ootPho_FiredL1Trgs_);
	tree->Branch("ootPho_SeedTime",                    & ootPho_SeedTime_);
	tree->Branch("ootPho_SeedEnergy",                  & ootPho_SeedEnergy_);
	tree->Branch("ootPho_MIPChi2",                     & ootPho_MIPChi2_);
	tree->Branch("ootPho_MIPTotEnergy",                & ootPho_MIPTotEnergy_);
	tree->Branch("ootPho_MIPSlope",                    & ootPho_MIPSlope_);
	tree->Branch("ootPho_MIPIntercept",                & ootPho_MIPIntercept_);
	tree->Branch("ootPho_MIPNhitCone",                 & ootPho_MIPNhitCone_);
	tree->Branch("ootPho_IDbit",                       & ootPho_IDbit_);
}


void ggNtuplizer::fillPhotonsOOT(const edm::Event& e, const edm::EventSetup& es) {

	// cleanup from previous execution
	ootPho_E_                           . clear();
	ootPho_Et_                          . clear();
	ootPho_SigmaE_                       . clear();
	ootPho_CalibE_                       . clear();
	ootPho_SigmaCalibE_                  . clear();
	ootPho_CalibEt_                      . clear();
	ootPho_Eta_                         . clear();
	ootPho_Phi_                         . clear();
	ootPho_SCindex_                     . clear();
	ootPho_FiducialRegion_              . clear();
	ootPho_QualityBits_                 . clear();
	ootPho_R9_                          . clear();
	ootPho_HoverE_                      . clear();
	ootPho_E2x5BottomFull5x5_           . clear();
	ootPho_E2x5LeftFull5x5_             . clear();
	ootPho_E2x5MaxFull5x5_              . clear();
	ootPho_E2x5RightFull5x5_            . clear();
	ootPho_E2x5TopFull5x5_              . clear();
	ootPho_EBottomFull5x5_              . clear();
	ootPho_ELeftFull5x5_                . clear();
	ootPho_ERightFull5x5_               . clear();
	ootPho_ETopFull5x5_                 . clear();
	ootPho_HcalDepth1OverEcal_   . clear();
	ootPho_HcalDepth1OverEcalBc_ . clear();
	ootPho_HcalDepth2OverEcal_   . clear();
	ootPho_HcalDepth2OverEcalBc_ . clear();
	ootPho_SmAlphaFull5x5_              . clear();
	ootPho_SmMajorFull5x5_              . clear();
	ootPho_SmMinorFull5x5_              . clear();
	ootPho_ESEffSigmaRR_                . clear();
	ootPho_SigmaIEtaIEtaFull5x5_        . clear();
	ootPho_SigmaIEtaIPhiFull5x5_        . clear();
	ootPho_SigmaIPhiIPhiFull5x5_        . clear();
	ootPho_R9Full5x5_                   . clear();
	nootPho_TrkHollowConeDR04_           . clear();
	nootPho_TrkSolidConeDR04_            . clear();
	nootPho_TrkHollowConeDR03_           . clear();
	nootPho_TrkSolidConeDR03_            . clear();
	ootPho_TrkSumPtHollowConeDR03_       . clear();
	ootPho_TrkSumPtSolidConeDR03_        . clear();
	ootPho_TrkSumPtHollowConeDR04_       . clear();
	ootPho_TrkSumPtSolidConeDR04_        . clear();
	ootPho_MaxEnergyXtal                 . clear();
	ootPho_E2ndFull5x5_                  . clear();
	ootPho_E1x3Full5x5_                  . clear();
	ootPho_E1x5Full5x5_                  . clear();
	ootPho_E2x5Full5x5_                  . clear();
	ootPho_FiredSingleTrgs_             . clear();
	ootPho_FiredDoubleTrgs_             . clear();
	ootPho_FiredTripleTrgs_             . clear();
	ootPho_FiredL1Trgs_                 . clear();
	ootPho_SeedTime_                    . clear();
	ootPho_SeedEnergy_                  . clear();
	ootPho_MIPChi2_                     . clear();
	ootPho_MIPTotEnergy_                . clear();
	ootPho_MIPSlope_                    . clear();
	ootPho_MIPIntercept_                . clear();
	ootPho_MIPNhitCone_                 . clear();
	ootPho_IDbit_                       . clear();
	ootPho_ESEnP1_                       . clear();
	oootPho_ESEnP2_                       . clear();
	ootPho_E3x3Full5x5_                  . clear();
	ootPho_E2x2Full5x5_                  . clear();
	ootPho_E5x5Full5x5_                  . clear();
	ootPho_PFClusEcalIso_                . clear();
	ootPho_PFClusHcalIso_                . clear();
	ootPho_ECALIso_                      . clear();
	ootPho_HCALIso_                      . clear();
	ootPho_SeedBCE_                      . clear();
	ootPho_SeedBCEta_                    . clear();
	ootPho_SeedBCPhi_                    . clear();
	ootPho_SeedSaturationBit_                    . clear();
	ootPho_SaturatedXtals_                    . clear();
	nootPho_ = 0;

	edm::Handle<edm::View<pat::Photon> > photonOOT_Handle;
	e.getByToken(photonOOTCollection_, photonOOT_Handle);

	if (!photonOOT_Handle.isValid()) {
		edm::LogWarning("ggNtuplizer") << "no OOT pat::Photons in event";
		return;
	}

	edm::Handle<std::vector<reco::SuperCluster>> ecalSC_OOT_handle;
	e.getByToken(ecalSC_OOT_collection_, ecalSC_OOT_handle);

	// EcalClusterLazyTools       lazyTool    (e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
	noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

	for (edm::View<pat::Photon>::const_iterator iootPho = photonOOT_Handle->begin(); iootPho != photonOOT_Handle->end(); ++iootPho){

		ootPho_E_   . push_back(iootPho->energy());
		ootPho_Et_  . push_back(iootPho->et());
		ootPho_Eta_ . push_back(iootPho->eta());
		ootPho_Phi_ . push_back(iootPho->phi());

		UChar_t _ootPho_QualityBits = 0;
		if(iootPho->hasPixelSeed()) setbit(_ootPho_QualityBits, 0);
		if(iootPho->passElectronVeto()) setbit(_ootPho_QualityBits, 1);
		ootPho_QualityBits_                 . push_back(_ootPho_QualityBits);

		ootPho_R9_                          . push_back(iootPho->r9());
		ootPho_HoverE_                      . push_back(iootPho->hadTowOverEm());

		ootPho_E2x5BottomFull5x5_           . push_back(iootPho->full5x5_showerShapeVariables().e2x5Bottom);
		ootPho_E2x5LeftFull5x5_             . push_back(iootPho->full5x5_showerShapeVariables().e2x5Left);
		ootPho_E2x5MaxFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().e2x5Max);
		ootPho_E2x5RightFull5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e2x5Right);
		ootPho_E2x5TopFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().e2x5Top);
		ootPho_EBottomFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().eBottom);
		ootPho_ELeftFull5x5_                . push_back(iootPho->full5x5_showerShapeVariables().eLeft);
		ootPho_ERightFull5x5_               . push_back(iootPho->full5x5_showerShapeVariables().eRight);
		ootPho_ETopFull5x5_                 . push_back(iootPho->full5x5_showerShapeVariables().eTop);
		ootPho_HcalDepth1OverEcal_   . push_back(iootPho->showerShapeVariables().hcalDepth1OverEcal);
		ootPho_HcalDepth1OverEcalBc_ . push_back(iootPho->showerShapeVariables().hcalDepth1OverEcalBc);
		ootPho_HcalDepth2OverEcal_   . push_back(iootPho->showerShapeVariables().hcalDepth2OverEcal);
		ootPho_HcalDepth2OverEcalBc_ . push_back(iootPho->showerShapeVariables().hcalDepth2OverEcalBc);
		ootPho_SmAlphaFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().smAlpha);
		ootPho_SmMajorFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().smMajor);
		ootPho_SmMinorFull5x5_              . push_back(iootPho->full5x5_showerShapeVariables().smMinor);

		ootPho_ESEffSigmaRR_                . push_back(iootPho->full5x5_showerShapeVariables().effSigmaRR);
		ootPho_MIPChi2_                     . push_back(iootPho->mipChi2());
		ootPho_MIPTotEnergy_                . push_back(iootPho->mipTotEnergy());
		ootPho_MIPSlope_                    . push_back(iootPho->mipSlope());
		ootPho_MIPIntercept_                . push_back(iootPho->mipIntercept());
		ootPho_MIPNhitCone_                 . push_back(iootPho->mipNhitCone());


		// get ootPho_ton supercluster index (for looking up from the SC branches)
		if(ecalSC_OOT_handle.isValid()){
			const reco::SuperCluster * _tmpootPho_SC = (iootPho->superCluster().isAvailable()) ? iootPho->superCluster().get() : nullptr;
			Short_t tmpootPho_SCindex = (_tmpootPho_SC == nullptr) ? -999 : std::distance(ecalSC_OOT_handle->begin(), (std::vector<reco::SuperCluster>::const_iterator) _tmpootPho_SC);
			ootPho_SCindex_.push_back(tmpootPho_SCindex);
		  //check
		  // if(tmpootPho_SCindex>=0){
		  //   std::cout<<_tmpootPho_SC->eta()<<" "<<(ecalSChandle->begin()+tmpootPho_SCindex)->eta()<<" "<<_tmpootPho_SC->phi()<<" "<<(ecalSChandle->begin()+tmpootPho_SCindex)->phi()<<std::endl;
		  // }
		}

		UChar_t tmpootPho_FiducialRegion = 0;
		if(iootPho->isEB()) setbit(tmpootPho_FiducialRegion, 0);
		if(iootPho->isEE()) setbit(tmpootPho_FiducialRegion, 1);
		if(iootPho->isEBEEGap()) setbit(tmpootPho_FiducialRegion, 2);
		if(iootPho->isEBEtaGap ()) setbit(tmpootPho_FiducialRegion, 3);
		if(iootPho->isEBPhiGap ()) setbit(tmpootPho_FiducialRegion, 4);
		if(iootPho->isEEDeeGap ()) setbit(tmpootPho_FiducialRegion, 5);
		if(iootPho->isEERingGap()) setbit(tmpootPho_FiducialRegion, 6);
		ootPho_FiducialRegion_  .push_back(tmpootPho_FiducialRegion);

		// VID decisions
		UShort_t tmpootPho_IDbit = 0;

		if (!(iootPho->mipIsHalo()))  setbit(tmpootPho_IDbit, 7);

		ootPho_IDbit_.push_back(tmpootPho_IDbit);

		bool isBarrel = (iootPho->superCluster()->seed()->seed().subdetId() == EcalBarrel);
		const EcalRecHitCollection * rechits = isBarrel ? lazyToolnoZS.getEcalEBRecHitCollection() : lazyToolnoZS.getEcalEERecHitCollection();

		DetId seed = lazyToolnoZS.getMaximum(*(iootPho->superCluster()->seed())).first;

		EcalRecHitCollection::const_iterator theSeedHit = rechits->find(seed);
		if (theSeedHit != rechits->end()) {
			ootPho_SeedTime_.push_back(theSeedHit->time());
			ootPho_SeedEnergy_.push_back(theSeedHit->energy());
		} else{
			ootPho_SeedTime_  .push_back(-99.);
			ootPho_SeedEnergy_.push_back(-99.);
		}

		ootPho_FiredSingleTrgs_        . push_back(matchSinglePhotonTriggerFilters(iootPho->et(), iootPho->eta(), iootPho->phi()));
		ootPho_FiredDoubleTrgs_        . push_back(matchDoublePhotonTriggerFilters(iootPho->et(), iootPho->eta(), iootPho->phi()));
		ootPho_FiredTripleTrgs_        . push_back(matchTriplePhotonTriggerFilters(iootPho->et(), iootPho->eta(), iootPho->phi()));
		ootPho_FiredL1Trgs_            . push_back(matchL1TriggerFilters(iootPho->et(), iootPho->eta(), iootPho->phi()));
		
		ootPho_SigmaIEtaIEtaFull5x5_   . push_back(iootPho->full5x5_sigmaIetaIeta());

		ootPho_SigmaIEtaIPhiFull5x5_   . push_back(iootPho->full5x5_showerShapeVariables().sigmaIetaIphi);
		ootPho_SigmaIPhiIPhiFull5x5_   . push_back(iootPho->full5x5_showerShapeVariables().sigmaIphiIphi);

		ootPho_R9Full5x5_              . push_back(iootPho->full5x5_r9());

		nootPho_TrkHollowConeDR04_     . push_back(iootPho->nTrkHollowConeDR04());
		nootPho_TrkSolidConeDR04_      . push_back(iootPho->nTrkSolidConeDR04());
		nootPho_TrkHollowConeDR03_     . push_back(iootPho->nTrkHollowConeDR03());
		nootPho_TrkSolidConeDR03_      . push_back(iootPho->nTrkHollowConeDR04());
		ootPho_MaxEnergyXtal           . push_back(iootPho->full5x5_maxEnergyXtal());
		ootPho_E2ndFull5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e2nd);
		ootPho_E1x3Full5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e1x3);
		ootPho_E1x5Full5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e1x5);
		ootPho_E2x5Full5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e2x5);

		ootPho_ESEnP1_                 . push_back(iootPho->superCluster()->preshowerEnergyPlane1());
		oootPho_ESEnP2_                . push_back(iootPho->superCluster()->preshowerEnergyPlane2());
		ootPho_E3x3Full5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e3x3);
		ootPho_E2x2Full5x5_            . push_back(iootPho->full5x5_showerShapeVariables().e2x2);
		ootPho_E5x5Full5x5_            . push_back(iootPho->full5x5_e5x5());

		ootPho_PFClusEcalIso_          . push_back(iootPho->ecalPFClusterIso());
		ootPho_PFClusHcalIso_          . push_back(iootPho->hcalPFClusterIso());
		ootPho_TrkSumPtSolidConeDR04_  . push_back(iootPho->trkSumPtSolidConeDR04());
		ootPho_TrkSumPtSolidConeDR03_  . push_back(iootPho->trkSumPtSolidConeDR03());
		ootPho_TrkSumPtHollowConeDR04_ . push_back(iootPho->trkSumPtHollowConeDR04());
		ootPho_TrkSumPtHollowConeDR03_ . push_back(iootPho->trkSumPtHollowConeDR03());

		ootPho_ECALIso_                . push_back(iootPho->ecalIso());
		ootPho_HCALIso_                . push_back(iootPho->hcalIso());

		ootPho_SeedBCE_                . push_back(iootPho->superCluster()->seed()->energy());
		ootPho_SeedBCEta_              . push_back(iootPho->superCluster()->seed()->eta());
		ootPho_SeedBCPhi_              . push_back(iootPho->superCluster()->seed()->phi());

		ootPho_SeedSaturationBit_      . push_back(iootPho->isSeedSaturated());
		ootPho_SaturatedXtals_         . push_back(iootPho->nSaturatedXtals());

		nootPho_++;
	}
};


void ggNtuplizer::branchesPhoECALSC(TTree* tree) {
	tree->Branch("phoDirectEcalSCindex",                        &phoDirectEcalSCindex_);
};


void ggNtuplizer::branchesootPhoECALSC(TTree* tree) {
	tree->Branch("ootPhoDirectEcalSCindex",                        &ootPhoDirectEcalSCindex_);
};


void ggNtuplizer::resolvePhoECALSCindex(){
	phoDirectEcalSCindex_.clear();
	for(Short_t scIndex : phoSCindex_){
		Short_t resolvedIndex = findSecondaryIndex(scIndex, ecalSCindex_);
		phoDirectEcalSCindex_.push_back(resolvedIndex);
	}
};


void ggNtuplizer::resolveootPhoECALSCindex(){
	ootPhoDirectEcalSCindex_.clear();
	for(Short_t ootSCIndex : ootPho_SCindex_){
		Short_t resolvedIndex = findSecondaryIndex(ootSCIndex, ecalootSCindex_);
		ootPhoDirectEcalSCindex_.push_back(resolvedIndex);
	}
}; 



////converted vertex info
////conversion from https://github.com/cms-analysis/flashgg/blob/dev_legacy_runII/MicroAOD/plugins/LegacyVertexSelector.cc#L111

double ggNtuplizer::vtxZFromConvOnly(  edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &conversion,
	const math::XYZPoint &beamSpot ) const
{
	double dz = 0;
	if( conversion->nTracks() == 2 ) {
		double r = sqrt( conversion->refittedPairMomentum().perp2() );
		dz = ( conversion->conversionVertex().z() - beamSpot.z() )
		-
		( ( conversion->conversionVertex().x() - beamSpot.x() ) * conversion->refittedPair4Momentum().x() + ( conversion->conversionVertex().y() - beamSpot.y() ) *
			conversion->refittedPair4Momentum().y() ) / r * conversion->refittedPair4Momentum().z() / r;
	}
	if( conversion->nTracks() == 1 ) {
		double r = sqrt( conversion->tracksPin()[0].x() * conversion->tracksPin()[0].x() + conversion->tracksPin()[0].y() * conversion->tracksPin()[0].y() );
		dz = ( conversion->conversionVertex().z() - beamSpot.z() )
		-
		( ( conversion->conversionVertex().x() - beamSpot.x() ) * conversion->tracksPin()[0].x() + ( conversion->conversionVertex().y() - beamSpot.y() ) *
			conversion->tracksPin()[0].y() ) / r * conversion->tracksPin()[0].z() / r;
	}
	return dz + beamSpot.z();
}

double ggNtuplizer::vtxZFromConvSuperCluster( edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &conversion, const math::XYZPoint &beamSpot ) const{
  // get the z from conversion plus SuperCluster
	double deltaX1 =  pho->caloPosition().x() - conversion->conversionVertex().x();
	double deltaY1 =  pho->caloPosition().y() - conversion->conversionVertex().y();
	double deltaZ1 =  pho->caloPosition().z() - conversion->conversionVertex().z();
	double R1 = sqrt( deltaX1 * deltaX1 + deltaY1 * deltaY1 );
	double tantheta = R1 / deltaZ1;

	double deltaX2 = conversion->conversionVertex().x() - beamSpot.x();
	double deltaY2 = conversion->conversionVertex().y() - beamSpot.y();
	double R2 = sqrt( deltaX2 * deltaX2 + deltaY2 * deltaY2 );
	double deltaZ2 = R2 / tantheta;
	double higgsZ =  pho->caloPosition().z() - deltaZ1 - deltaZ2;
	return higgsZ;
}

double ggNtuplizer::vtxZFromConv( edm::View<pat::Photon>::const_iterator pho, const edm::Ptr<reco::Conversion> &conversion,	const math::XYZPoint &beamSpot) const {
	double ReturnValue = 0;

	double perp = sqrt( conversion->conversionVertex().x() * conversion->conversionVertex().x() + conversion->conversionVertex().y() *
		conversion->conversionVertex().y() );

	float nTracksConv = conversion->nTracks();

	if( nTracksConv == 2 ) {
		if( fabs( pho->superCluster()->eta() ) < 1.5 ) {
			if( perp <= 15.0 ) {
				if( sigma1Pix < sigma2Pix )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else if( perp > 15 && perp <= 60.0 ) {

				if( sigma1Tib < sigma2Tib )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else {

				if( sigma1Tob < sigma2Tob )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			}
		} else {
			if( fabs( conversion->conversionVertex().z() ) <= 50.0 ) {

				if( sigma1PixFwd < sigma2PixFwd )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else if( fabs( conversion->conversionVertex().z() ) > 50.0 && fabs( conversion->conversionVertex().z() ) <= 100.0 ) {
				if( sigma1Tid < sigma2Tid )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else {

				if( sigma1Tec < sigma2Tec )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			}
		}
	}
	if( nTracksConv == 1 ) {
		if( fabs( pho->superCluster()->eta() ) < 1.5 ) {
			if( perp <= 15.0 ) {

				if( singlelegsigma1Pix < singlelegsigma2Pix )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else if( perp > 15 && perp <= 60.0 ) {

				if( singlelegsigma1Tib < singlelegsigma2Tib )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else {

				if( singlelegsigma1Tob < singlelegsigma2Tob )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			}
		} else {
			if( fabs( conversion->conversionVertex().z() ) <= 50.0 ) {

				if( singlelegsigma1PixFwd < singlelegsigma2PixFwd )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else if( fabs( conversion->conversionVertex().z() ) > 50.0 && fabs( conversion->conversionVertex().z() ) <= 100.0 ) {

				if( singlelegsigma1Tid < singlelegsigma2Tid )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			} else {

				if( singlelegsigma1Tec < singlelegsigma2Tec )
					{ ReturnValue = vtxZFromConvOnly( pho, conversion, beamSpot ); }
				else
					{ ReturnValue = vtxZFromConvSuperCluster( pho, conversion, beamSpot ); }
			}
		}
	}
	return ReturnValue;
}

///select the conversion index
std::vector<int> ggNtuplizer::IndexMatchedConversion( edm::View<pat::Photon>::const_iterator g, 
	const  std::vector<edm::Ptr<reco::Conversion> > & conversionsVector,
	const std::vector<edm::Ptr<reco::Conversion> > & conversionsVectorSL
	) const
{
	double mindR = 999;
	int nConvLegs = 0;
	bool doOneLeg = true;

	std::vector<int> result;
	int selected_conversion_index = -1;
	if( g->hasConversionTracks()){

		for( unsigned int i = 0; i < conversionsVector.size(); i++ ) {
			edm::Ptr<reco::Conversion> conv = conversionsVector[i];
			if( conv->nTracks() == 2 ) {
				if( !conv->isConverted() ) { continue; }
				if( conv->refittedPair4Momentum().pt() < 10. ) { continue; }
				if( TMath::Prob( conv->conversionVertex().chi2(), conv->conversionVertex().ndof() ) < 1e-6 ) { continue; }

				TVector3 VtxtoSC;
				VtxtoSC.SetXYZ( g->superCluster()->position().x() - conv->conversionVertex().x(),
					g->superCluster()->position().y() - conv->conversionVertex().y(),
					g->superCluster()->position().z() - conv->conversionVertex().z() );

				TVector3 RefPairMo;
				RefPairMo.SetXYZ( conv->refittedPairMomentum().x(), conv->refittedPairMomentum().y(), conv->refittedPairMomentum().z() );
				double dR = 0;
				dR = VtxtoSC.DeltaR( RefPairMo );
				if( dR < mindR ) {
					mindR = dR;
					selected_conversion_index = i;
				}
			}
		}

		if( mindR < 0.1 ) {
			result.push_back( selected_conversion_index );
			nConvLegs = 2;
			result.push_back( nConvLegs );
			doOneLeg = false;
		}
		if( doOneLeg ) {
			mindR = 999;
			for( unsigned int j = 0; j < conversionsVectorSL.size(); j++ ) {
				edm::Ptr<reco::Conversion> conv = conversionsVectorSL[j];

				if( conv->nTracks() == 1 ) {
					TVector3 VtxtoSC;
					VtxtoSC.SetXYZ( g->superCluster()->position().x() - conv->conversionVertex().x(),
						g->superCluster()->position().y() - conv->conversionVertex().y(),
						g->superCluster()->position().z() - conv->conversionVertex().z() );
					TVector3 RefPairMo;
					float oneLegTrack_X = conv->tracksPin()[0].x();
					float oneLegTrack_Y = conv->tracksPin()[0].y();
					float oneLegTrack_Z = conv->tracksPin()[0].z();
					RefPairMo.SetXYZ( oneLegTrack_X, oneLegTrack_Y, oneLegTrack_Z );
					double dR = 0;
					dR = VtxtoSC.DeltaR( RefPairMo );
					if( dR < mindR ) {
						mindR = dR;
						selected_conversion_index = j;
					}                  
				}
			}

			if( mindR < 0.1 ) {
				result.push_back( selected_conversion_index );
				nConvLegs = 1;
				result.push_back( nConvLegs );
			}
		}
	}

	if( mindR < 0.1 ){
		return result;
	} else {
		result.push_back( -1 );
		result.push_back( -1 );
		return result;
	}
}
