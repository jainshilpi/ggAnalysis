#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

UShort_t metFilters_;
Float_t genMET_;
Float_t genMETPhi_;
Float_t pfMET_;
Float_t pfMETPhi_;
Float_t pfMET_T1_;
Float_t pfMETPhi_T1_;
Float_t pfMET_T1JERUp_;
Float_t pfMET_T1JERDo_;
Float_t pfMET_T1JESUp_;
Float_t pfMET_T1JESDo_;
Float_t pfMET_T1UESUp_;
Float_t pfMET_T1UESDo_;
Float_t pfMETPhi_T1JERUp_;
Float_t pfMETPhi_T1JERDo_;
Float_t pfMETPhi_T1JESUp_;
Float_t pfMETPhi_T1JESDo_;
Float_t pfMETPhi_T1UESUp_;
Float_t pfMETPhi_T1UESDo_;
// Float_t pfMET_caloMetSig_;
Float_t pfMET_metSig_;
Float_t pfMET_EtSig_;
Float_t pfMET_metSigxx_;
Float_t pfMET_metSigxy_;
Float_t pfMET_metSigyy_;

const std::vector<std::string> filterNamesToCheck = {
	"Flag_goodVertices",
	"Flag_globalSuperTightHalo2016Filter",
	"Flag_HBHENoiseFilter",
	"Flag_HBHENoiseIsoFilter",
	"Flag_EcalDeadCellTriggerPrimitiveFilter",
	"Flag_BadPFMuonFilter",
	"Flag_BadChargedCandidateFilter"
	"Flag_eeBadScFilter",
	"Flag_ecalBadCalibFilter",
};

void ggNtuplizer::branchesMET(TTree* tree) {
	if (doGenParticles_) {
		tree->Branch("genMET",      &genMET_);
		tree->Branch("genMETPhi",   &genMETPhi_);
	}
	tree->Branch("metFilters",       &metFilters_);
	tree->Branch("pfMET",            &pfMET_);
	tree->Branch("pfMETPhi",         &pfMETPhi_);
	tree->Branch("pfMET_T1JERUp",    &pfMET_T1JERUp_);
	tree->Branch("pfMET_T1JERDo",    &pfMET_T1JERDo_);
	tree->Branch("pfMET_T1JESUp",    &pfMET_T1JESUp_);
	tree->Branch("pfMET_T1JESDo",    &pfMET_T1JESDo_);
	tree->Branch("pfMET_T1UESUp",    &pfMET_T1UESUp_);
	tree->Branch("pfMET_T1UESDo",    &pfMET_T1UESDo_);
	tree->Branch("pfMETPhi_T1JERUp", &pfMETPhi_T1JERUp_);
	tree->Branch("pfMETPhi_T1JERDo", &pfMETPhi_T1JERDo_);
	tree->Branch("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp_);
	tree->Branch("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo_);
	tree->Branch("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp_);
	tree->Branch("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo_);
	// tree->Branch("pfMET_caloMetSig", &pfMET_caloMetSig_);
	tree->Branch("pfMET_metSig", &pfMET_metSig_);
	tree->Branch("pfMET_EtSig", &pfMET_EtSig_);

	tree->Branch("pfMET_metSigxx", &pfMET_metSigxx_);
	tree->Branch("pfMET_metSigxy", &pfMET_metSigxy_);
	tree->Branch("pfMET_metSigyy", &pfMET_metSigyy_);
}

void ggNtuplizer::fillMET(const edm::Event& e, const edm::EventSetup& es) {
	metFilters_ = 0;
	if (addFilterInfoMINIAOD_) {
		edm::Handle<edm::TriggerResults> patFilterResultsHandle;
		e.getByToken(patTrgResultsLabel_, patFilterResultsHandle);
		edm::TriggerResults const& patFilterResults = *patFilterResultsHandle;

		auto&& filterNames = e.triggerNames(patFilterResults);

		for (unsigned iF = 0; iF < filterNamesToCheck.size(); iF++) {
			unsigned index = filterNames.triggerIndex(filterNamesToCheck[iF]);
			if ( index == filterNames.size() ) LogDebug("METFilters") << filterNamesToCheck[iF] << " is missing, exiting";
			else if (!patFilterResults.accept(index)) metFilters_ += std::pow(2, iF);
		}

		//////https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Accessing_the_filter_decision_in
		edm::Handle<bool> passecalBadCalibFilterUpdate ;
		e.getByToken(ecalBadCalibFilterUpdateToken_, passecalBadCalibFilterUpdate);
		Bool_t _passecalBadCalibFilterUpdate =  (*passecalBadCalibFilterUpdate );
		if (!_passecalBadCalibFilterUpdate) metFilters_ += std::pow(2, filterNamesToCheck.size());
	}

	edm::Handle<edm::View<pat::MET> > pfMETHandle;
	e.getByToken(pfMETlabel_, pfMETHandle);

	genMET_    = -99;
	genMETPhi_ = -99;
	pfMET_     = -99;
	pfMETPhi_  = -99;

	if (!pfMETHandle.isValid()) return;

	const pat::MET *pfMET = 0;
	pfMET     = &(pfMETHandle->front());
	pfMET_    = pfMET->et();
	pfMETPhi_ = pfMET->phi();

	// Type1MET uncertainties =======================================
	pfMET_T1JERUp_ = pfMET->shiftedPt(pat::MET::JetResUp);
	pfMET_T1JERDo_ = pfMET->shiftedPt(pat::MET::JetResDown);
	pfMET_T1JESUp_ = pfMET->shiftedPt(pat::MET::JetEnUp);
	pfMET_T1JESDo_ = pfMET->shiftedPt(pat::MET::JetEnDown);
	pfMET_T1UESUp_ = pfMET->shiftedPt(pat::MET::UnclusteredEnUp);
	pfMET_T1UESDo_ = pfMET->shiftedPt(pat::MET::UnclusteredEnDown);

	pfMETPhi_T1JERUp_= pfMET->shiftedPhi(pat::MET::JetResUp);
	pfMETPhi_T1JERDo_ = pfMET->shiftedPhi(pat::MET::JetResDown);
	pfMETPhi_T1JESUp_ = pfMET->shiftedPhi(pat::MET::JetEnUp);
	pfMETPhi_T1JESDo_ = pfMET->shiftedPhi(pat::MET::JetEnDown);
	pfMETPhi_T1UESUp_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp);
	pfMETPhi_T1UESDo_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown);

	// pfMET_caloMetSig_ = pfMET->caloMetSignificance();
	pfMET_metSig_ = pfMET->significance();
	pfMET_EtSig_ = pfMET->mEtSig();

	pfMET_metSigxx_ = pfMET->getSignificanceMatrix()(0,0);
	pfMET_metSigxy_ = pfMET->getSignificanceMatrix()(0,1);
	pfMET_metSigyy_ = pfMET->getSignificanceMatrix()(1,1);

	if (!e.isRealData()) {
		genMET_    = pfMET->genMET()->et();
		genMETPhi_ = pfMET->genMET()->phi();
	}
}
