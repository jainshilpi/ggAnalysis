#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

UShort_t metFilters_;
Float_t genMET_;
Float_t genMETPhi_;
Float_t pfMET_;
Float_t pfMETPhi_;
Float_t pfMET_Corr_;
Float_t pfMETPhi_Corr_;
Float_t pfMET_JERUp_;
Float_t pfMET_JERDo_;
Float_t pfMET_JESUp_;
Float_t pfMET_JESDo_;
Float_t pfMET_UESUp_;
Float_t pfMET_UESDo_;
Float_t pfMETPhi_JERUp_;
Float_t pfMETPhi_JERDo_;
Float_t pfMETPhi_JESUp_;
Float_t pfMETPhi_JESDo_;
Float_t pfMETPhi_UESUp_;
Float_t pfMETPhi_UESDo_;
Float_t pfMET_metSig_;
Float_t pfMET_EtSig_;
Float_t pfMET_metSigxx_;
Float_t pfMET_metSigxy_;
Float_t pfMET_metSigyy_;
Float_t pfMET_SumEt_;


Float_t puppiMET_;
Float_t puppiMETPhi_;
Float_t puppiMET_Corr_;
Float_t puppiMETPhi_Corr_;
Float_t puppiMET_JERUp_;
Float_t puppiMET_JERDo_;
Float_t puppiMET_JESUp_;
Float_t puppiMET_JESDo_;
Float_t puppiMET_UESUp_;
Float_t puppiMET_UESDo_;
Float_t puppiMETPhi_JERUp_;
Float_t puppiMETPhi_JERDo_;
Float_t puppiMETPhi_JESUp_;
Float_t puppiMETPhi_JESDo_;
Float_t puppiMETPhi_UESUp_;
Float_t puppiMETPhi_UESDo_;
Float_t puppiMET_metSig_;
Float_t puppiMET_EtSig_;
Float_t puppiMET_metSigxx_;
Float_t puppiMET_metSigxy_;
Float_t puppiMET_metSigyy_;
Float_t puppiMET_SumEt_;

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
    "Flag_BadPFMuonDzFilter",
    "Flag_hfNoisyHitsFilter"
};

void ggNtuplizer::branchesMET(TTree* tree) {
    if (doGenParticles_) {
        tree->Branch("genMET",    & genMET_);
        tree->Branch("genMETPhi", & genMETPhi_);
    }
    tree->Branch("metFilters",         & metFilters_);
    tree->Branch("pfMET",              & pfMET_);
    tree->Branch("pfMETPhi",           & pfMETPhi_);
    tree->Branch("pfMET_Corr",         & pfMET_Corr_);
    tree->Branch("pfMETPhi_Corr",      & pfMETPhi_Corr_);
    tree->Branch("pfMET_JERUp",        & pfMET_JERUp_);
    tree->Branch("pfMET_JERDo",        & pfMET_JERDo_);
    tree->Branch("pfMET_JESUp",        & pfMET_JESUp_);
    tree->Branch("pfMET_JESDo",        & pfMET_JESDo_);
    tree->Branch("pfMET_UESUp",        & pfMET_UESUp_);
    tree->Branch("pfMET_UESDo",        & pfMET_UESDo_);
    tree->Branch("pfMETPhi_JERUp",     & pfMETPhi_JERUp_);
    tree->Branch("pfMETPhi_JERDo",     & pfMETPhi_JERDo_);
    tree->Branch("pfMETPhi_JESUp",     & pfMETPhi_JESUp_);
    tree->Branch("pfMETPhi_JESDo",     & pfMETPhi_JESDo_);
    tree->Branch("pfMETPhi_UESUp",     & pfMETPhi_UESUp_);
    tree->Branch("pfMETPhi_UESDo",     & pfMETPhi_UESDo_);
    tree->Branch("pfMET_metSig",       & pfMET_metSig_);
    tree->Branch("pfMET_EtSig",        & pfMET_EtSig_);
    tree->Branch("pfMET_metSigxx",     & pfMET_metSigxx_);
    tree->Branch("pfMET_metSigxy",     & pfMET_metSigxy_);
    tree->Branch("pfMET_metSigyy",     & pfMET_metSigyy_);
    tree->Branch("pfMET_SumEt", & pfMET_SumEt_);


    tree->Branch("puppiMET",              & puppiMET_);
    tree->Branch("puppiMETPhi",           & puppiMETPhi_);
    tree->Branch("puppiMET_Corr",         & puppiMET_Corr_);
    tree->Branch("puppiMETPhi_Corr",      & puppiMETPhi_Corr_);
    tree->Branch("puppiMET_JERUp",        & puppiMET_JERUp_);
    tree->Branch("puppiMET_JERDo",        & puppiMET_JERDo_);
    tree->Branch("puppiMET_JESUp",        & puppiMET_JESUp_);
    tree->Branch("puppiMET_JESDo",        & puppiMET_JESDo_);
    tree->Branch("puppiMET_UESUp",        & puppiMET_UESUp_);
    tree->Branch("puppiMET_UESDo",        & puppiMET_UESDo_);
    tree->Branch("puppiMETPhi_JERUp",     & puppiMETPhi_JERUp_);
    tree->Branch("puppiMETPhi_JERDo",     & puppiMETPhi_JERDo_);
    tree->Branch("puppiMETPhi_JESUp",     & puppiMETPhi_JESUp_);
    tree->Branch("puppiMETPhi_JESDo",     & puppiMETPhi_JESDo_);
    tree->Branch("puppiMETPhi_UESUp",     & puppiMETPhi_UESUp_);
    tree->Branch("puppiMETPhi_UESDo",     & puppiMETPhi_UESDo_);
    tree->Branch("puppiMET_metSig",       & puppiMET_metSig_);
    tree->Branch("puppiMET_EtSig",        & puppiMET_EtSig_);
    tree->Branch("puppiMET_metSigxx",     & puppiMET_metSigxx_);
    tree->Branch("puppiMET_metSigxy",     & puppiMET_metSigxy_);
    tree->Branch("puppiMET_metSigyy",     & puppiMET_metSigyy_);
    tree->Branch("puppiMET_SumEt", & puppiMET_SumEt_);
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

    edm::Handle<edm::View<pat::MET> > puppiMETHandle;
    e.getByToken(puppiMETlabel_, puppiMETHandle);

    genMET_    = -99;
    genMETPhi_ = -99;

    pfMET_     = -99;
    pfMETPhi_  = -99;
    pfMET_Corr_     = -99;
    pfMETPhi_Corr_  = -99;

    puppiMET_     = -99;
    puppiMETPhi_  = -99;
    puppiMET_Corr_     = -99;
    puppiMETPhi_Corr_  = -99;

    const pat::MET *pfMET = &(pfMETHandle->front());

    const pat::MET *puppiMET = &(puppiMETHandle->front());

    if (!e.isRealData()) {
        if (pfMETHandle.isValid()) {
            genMET_    = pfMET->genMET()->et();
            genMETPhi_ = pfMET->genMET()->phi();
        } else if (pfMETHandle.isValid()) {
            genMET_    = puppiMET->genMET()->et();
            genMETPhi_ = puppiMET->genMET()->phi();
        }
    }

    //// https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections
    if (pfMETHandle.isValid()) {
        pfMET_    = pfMET->et();
        pfMETPhi_ = pfMET->phi();

        if (e.isRealData())  {
            pfMET_Corr_         = pfMET->corPt(pat::MET::Type1);
            pfMETPhi_Corr_      = pfMET->corPhi(pat::MET::Type1);

            pfMET_JERUp_        = pfMET->shiftedPt(pat::MET::JetResUp, pat::MET::Type1);
            pfMET_JERDo_        = pfMET->shiftedPt(pat::MET::JetResDown, pat::MET::Type1);
            pfMET_JESUp_        = pfMET->shiftedPt(pat::MET::JetEnUp, pat::MET::Type1);
            pfMET_JESDo_        = pfMET->shiftedPt(pat::MET::JetEnDown, pat::MET::Type1);
            pfMET_UESUp_        = pfMET->shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1);
            pfMET_UESDo_        = pfMET->shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1);

            pfMETPhi_JERUp_     = pfMET->shiftedPhi(pat::MET::JetResUp, pat::MET::Type1);
            pfMETPhi_JERDo_     = pfMET->shiftedPhi(pat::MET::JetResDown, pat::MET::Type1);
            pfMETPhi_JESUp_     = pfMET->shiftedPhi(pat::MET::JetEnUp, pat::MET::Type1);
            pfMETPhi_JESDo_     = pfMET->shiftedPhi(pat::MET::JetEnDown, pat::MET::Type1);
            pfMETPhi_UESUp_     = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp, pat::MET::Type1);
            pfMETPhi_UESDo_     = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown, pat::MET::Type1);
            pfMET_SumEt_ = pfMET->corSumEt(pat::MET::Type1);

        } else {
            pfMET_Corr_         = pfMET->corPt(pat::MET::Type1Smear);
            pfMETPhi_Corr_      = pfMET->corPhi(pat::MET::Type1Smear);

            pfMET_JERUp_        = pfMET->shiftedPt(pat::MET::JetResUp, pat::MET::Type1Smear);
            pfMET_JERDo_        = pfMET->shiftedPt(pat::MET::JetResDown, pat::MET::Type1Smear);
            pfMET_JESUp_        = pfMET->shiftedPt(pat::MET::JetEnUp, pat::MET::Type1Smear);
            pfMET_JESDo_        = pfMET->shiftedPt(pat::MET::JetEnDown, pat::MET::Type1Smear);
            pfMET_UESUp_        = pfMET->shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
            pfMET_UESDo_        = pfMET->shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);

            pfMETPhi_JERUp_     = pfMET->shiftedPhi(pat::MET::JetResUp, pat::MET::Type1Smear);
            pfMETPhi_JERDo_     = pfMET->shiftedPhi(pat::MET::JetResDown, pat::MET::Type1Smear);
            pfMETPhi_JESUp_     = pfMET->shiftedPhi(pat::MET::JetEnUp, pat::MET::Type1Smear);
            pfMETPhi_JESDo_     = pfMET->shiftedPhi(pat::MET::JetEnDown, pat::MET::Type1Smear);
            pfMETPhi_UESUp_     = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
            pfMETPhi_UESDo_     = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);
            pfMET_SumEt_ = pfMET->corSumEt(pat::MET::Type1Smear);
        }

        pfMET_metSig_   = pfMET->significance();
        pfMET_EtSig_    = pfMET->mEtSig();

        pfMET_metSigxx_ = pfMET->getSignificanceMatrix()(0,0);
        pfMET_metSigxy_ = pfMET->getSignificanceMatrix()(0,1);
        pfMET_metSigyy_ = pfMET->getSignificanceMatrix()(1,1);
    }

    if (puppiMETHandle.isValid()) {

        puppiMET_    = puppiMET->et();
        puppiMETPhi_ = puppiMET->phi();

        if (e.isRealData())  {

            puppiMET_Corr_         = puppiMET->corPt(pat::MET::Type1);
            puppiMETPhi_Corr_      = puppiMET->corPhi(pat::MET::Type1);

            puppiMET_JERUp_        = puppiMET->shiftedPt(pat::MET::JetResUp, pat::MET::Type1);
            puppiMET_JERDo_        = puppiMET->shiftedPt(pat::MET::JetResDown, pat::MET::Type1);
            puppiMET_JESUp_        = puppiMET->shiftedPt(pat::MET::JetEnUp, pat::MET::Type1);
            puppiMET_JESDo_        = puppiMET->shiftedPt(pat::MET::JetEnDown, pat::MET::Type1);
            puppiMET_UESUp_        = puppiMET->shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1);
            puppiMET_UESDo_        = puppiMET->shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1);

            puppiMETPhi_JERUp_     = puppiMET->shiftedPhi(pat::MET::JetResUp, pat::MET::Type1);
            puppiMETPhi_JERDo_     = puppiMET->shiftedPhi(pat::MET::JetResDown, pat::MET::Type1);
            puppiMETPhi_JESUp_     = puppiMET->shiftedPhi(pat::MET::JetEnUp, pat::MET::Type1);
            puppiMETPhi_JESDo_     = puppiMET->shiftedPhi(pat::MET::JetEnDown, pat::MET::Type1);
            puppiMETPhi_UESUp_     = puppiMET->shiftedPhi(pat::MET::UnclusteredEnUp, pat::MET::Type1);
            puppiMETPhi_UESDo_     = puppiMET->shiftedPhi(pat::MET::UnclusteredEnDown, pat::MET::Type1);
            puppiMET_SumEt_ = puppiMET->corSumEt(pat::MET::Type1);
        } else {

            puppiMET_Corr_         = puppiMET->corPt(pat::MET::Type1Smear);
            puppiMETPhi_Corr_      = puppiMET->corPhi(pat::MET::Type1Smear);

            puppiMET_JERUp_        = puppiMET->shiftedPt(pat::MET::JetResUp, pat::MET::Type1Smear);
            puppiMET_JERDo_        = puppiMET->shiftedPt(pat::MET::JetResDown, pat::MET::Type1Smear);
            puppiMET_JESUp_        = puppiMET->shiftedPt(pat::MET::JetEnUp, pat::MET::Type1Smear);
            puppiMET_JESDo_        = puppiMET->shiftedPt(pat::MET::JetEnDown, pat::MET::Type1Smear);
            puppiMET_UESUp_        = puppiMET->shiftedPt(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
            puppiMET_UESDo_        = puppiMET->shiftedPt(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);

            puppiMETPhi_JERUp_     = puppiMET->shiftedPhi(pat::MET::JetResUp, pat::MET::Type1Smear);
            puppiMETPhi_JERDo_     = puppiMET->shiftedPhi(pat::MET::JetResDown, pat::MET::Type1Smear);
            puppiMETPhi_JESUp_     = puppiMET->shiftedPhi(pat::MET::JetEnUp, pat::MET::Type1Smear);
            puppiMETPhi_JESDo_     = puppiMET->shiftedPhi(pat::MET::JetEnDown, pat::MET::Type1Smear);
            puppiMETPhi_UESUp_     = puppiMET->shiftedPhi(pat::MET::UnclusteredEnUp, pat::MET::Type1Smear);
            puppiMETPhi_UESDo_     = puppiMET->shiftedPhi(pat::MET::UnclusteredEnDown, pat::MET::Type1Smear);
            puppiMET_SumEt_ = puppiMET->corSumEt(pat::MET::Type1Smear);
        }

        puppiMET_metSig_   = puppiMET->significance();
        puppiMET_EtSig_    = puppiMET->mEtSig();

        puppiMET_metSigxx_ = puppiMET->getSignificanceMatrix()(0,0);
        puppiMET_metSigxy_ = puppiMET->getSignificanceMatrix()(0,1);
        puppiMET_metSigyy_ = puppiMET->getSignificanceMatrix()(1,1);
    }


};
