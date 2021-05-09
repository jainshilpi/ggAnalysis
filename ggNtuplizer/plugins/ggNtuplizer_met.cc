#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

UShort_t metFilters_;
Float_t genMET_;
Float_t genMETPhi_;
Float_t pfMET_;
Float_t pfMETPhi_;
Float_t pfMET_T1Smear_;
Float_t pfMETPhi_T1Smear_;
Float_t pfMET_T1SmearJERUp_;
Float_t pfMET_T1SmearJERDo_;
Float_t pfMET_T1SmearJESUp_;
Float_t pfMET_T1SmearJESDo_;
Float_t pfMET_T1SmearUESUp_;
Float_t pfMET_T1SmearUESDo_;
Float_t pfMETPhi_T1SmearJERUp_;
Float_t pfMETPhi_T1SmearJERDo_;
Float_t pfMETPhi_T1SmearJESUp_;
Float_t pfMETPhi_T1SmearJESDo_;
Float_t pfMETPhi_T1SmearUESUp_;
Float_t pfMETPhi_T1SmearUESDo_;
Float_t pfMET_metSig_;
Float_t pfMET_EtSig_;
Float_t pfMET_metSigxx_;
Float_t pfMET_metSigxy_;
Float_t pfMET_metSigyy_;
Float_t pfMET_SumEtT1Smear_;

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
	tree->Branch("pfMET_T1Smear",    &pfMET_T1Smear_);
	tree->Branch("pfMETPhi_T1Smear",    &pfMETPhi_T1Smear_);
	tree->Branch("pfMET_T1SmearJERUp",    &pfMET_T1SmearJERUp_);
	tree->Branch("pfMET_T1SmearJERDo",    &pfMET_T1SmearJERDo_);
	tree->Branch("pfMET_T1SmearJESUp",    &pfMET_T1SmearJESUp_);
	tree->Branch("pfMET_T1SmearJESDo",    &pfMET_T1SmearJESDo_);
	tree->Branch("pfMET_T1SmearUESUp",    &pfMET_T1SmearUESUp_);
	tree->Branch("pfMET_T1SmearUESDo",    &pfMET_T1SmearUESDo_);
	tree->Branch("pfMETPhi_T1SmearJERUp", &pfMETPhi_T1SmearJERUp_);
	tree->Branch("pfMETPhi_T1SmearJERDo", &pfMETPhi_T1SmearJERDo_);
	tree->Branch("pfMETPhi_T1SmearJESUp", &pfMETPhi_T1SmearJESUp_);
	tree->Branch("pfMETPhi_T1SmearJESDo", &pfMETPhi_T1SmearJESDo_);
	tree->Branch("pfMETPhi_T1SmearUESUp", &pfMETPhi_T1SmearUESUp_);
	tree->Branch("pfMETPhi_T1SmearUESDo", &pfMETPhi_T1SmearUESDo_);
	tree->Branch("pfMET_metSig", &pfMET_metSig_);
	tree->Branch("pfMET_EtSig", &pfMET_EtSig_);
	tree->Branch("pfMET_metSigxx", &pfMET_metSigxx_);
	tree->Branch("pfMET_metSigxy", &pfMET_metSigxy_);
	tree->Branch("pfMET_metSigyy", &pfMET_metSigyy_);
	tree->Branch("pfMET_SumEtT1Smear", &pfMET_SumEtT1Smear_);
};

void ggNtuplizer::fillMET(const edm::Event& e, const edm::EventSetup& es) {
	metFilters_ = 0;
	if (addFilterInfoMINIAOD_) {
		edm::Handle<edm::TriggerResults> patFilterResultsHandle;
		e.getByToken(patTrgResultsLabel_, patFilterResultsHandle);
		edm::TriggerResults const& patFilterResults = *patFilterResultsHandle;

		auto&& filterNames = e.triggerNames(patFilterResults);

		for (unsigned iF = 0; iF < filterNamesToCheck.size(); iF++) {
			unsigned index = filterNames.triggerIndex(filterNamesToCheck[iF]);
			if ( index == filterNames.size()) LogDebug("METFilters") << filterNamesToCheck[iF] << " is missing, exiting";
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
	pfMET_T1Smear_     = -99;
	pfMETPhi_T1Smear_  = -99;

	if (!pfMETHandle.isValid()) return;

	const pat::MET *pfMET = &(pfMETHandle->front());

	if (!e.isRealData()) {
		genMET_    = pfMET->genMET()->et();
		genMETPhi_ = pfMET->genMET()->phi();
	}

	pfMET_    = pfMET->et();
	pfMETPhi_ = pfMET->phi();

	pfMET_T1Smear_ =	pfMET->corPt(pat::MET::Type1Smear);
	pfMETPhi_T1Smear_ =	pfMET->corPhi(pat::MET::Type1Smear);

	// std::cout<<pfMET->corPt(pat::MET::Type1) - pfMET->corPt(pat::MET::Type1Smear)<<"\t"<<pfMET->corPhi(pat::MET::Type1)-pfMET->corPhi(pat::MET::Type1Smear)<<std::endl;

	// Type1MET uncertainties =======================================
	pfMET_T1SmearJERUp_ = pfMET->shiftedPt(pat::MET::JetResUp, pat::MET::Type1Smear);
	pfMET_T1SmearJERDo_ = pfMET->shiftedPt(pat::MET::JetResDown, pat::MET::Type1Smear);
	pfMET_T1SmearJESUp_ = pfMET->shiftedPt(pat::MET::JetEnUp, pat::MET::Type1Smear);
	pfMET_T1SmearJESDo_ = pfMET->shiftedPt(pat::MET::JetEnDown, pat::MET::Type1Smear);
	pfMET_T1SmearUESUp_ = pfMET->shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
	pfMET_T1SmearUESDo_ = pfMET->shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);

	pfMETPhi_T1SmearJERUp_= pfMET->shiftedPhi(pat::MET::JetResUp, pat::MET::Type1Smear);
	pfMETPhi_T1SmearJERDo_ = pfMET->shiftedPhi(pat::MET::JetResDown, pat::MET::Type1Smear);
	pfMETPhi_T1SmearJESUp_ = pfMET->shiftedPhi(pat::MET::JetEnUp, pat::MET::Type1Smear);
	pfMETPhi_T1SmearJESDo_ = pfMET->shiftedPhi(pat::MET::JetEnDown, pat::MET::Type1Smear);
	pfMETPhi_T1SmearUESUp_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
	pfMETPhi_T1SmearUESDo_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);

	pfMET_metSig_ = pfMET->significance();
	pfMET_EtSig_ = pfMET->mEtSig();

	pfMET_metSigxx_ = pfMET->getSignificanceMatrix()(0,0);
	pfMET_metSigxy_ = pfMET->getSignificanceMatrix()(0,1);
	pfMET_metSigyy_ = pfMET->getSignificanceMatrix()(1,1);
	pfMET_SumEtT1Smear_ 	=	pfMET->corSumEt(pat::MET::Type1Smear);
};
