#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"

using namespace std;

UShort_t          nAK4PUPPIJet_;
vector<Char_t>    AK4PUPPIJet_Charge_;
vector<float>     AK4PUPPIJet_Pt_;
vector<float>     AK4PUPPIJet_En_;
vector<float>     AK4PUPPIJet_Eta_;
vector<float>     AK4PUPPIJet_Phi_;
vector<float>     AK4PUPPIJet_RawPt_;
vector<float>     AK4PUPPIJet_RawEn_;
vector<float>     AK4PUPPIJet_Mt_;
vector<float>     AK4PUPPIJet_Area_;
vector<float>     AK4PUPPIJet_LeadTrackPt_;
vector<float>     AK4PUPPIJet_LeadTrackEta_;
vector<float>     AK4PUPPIJet_LeadTrackPhi_;
vector<int>       AK4PUPPIJet_LepTrackPID_;
vector<float>     AK4PUPPIJet_LepTrackPt_;
vector<float>     AK4PUPPIJet_LepTrackEta_;
vector<float>     AK4PUPPIJet_LepTrackPhi_;
vector<float>     AK4PUPPIJet_ConsituentEtaPhiSpread_;
vector<float>     AK4PUPPIJet_MaxConstituentDistance_;
vector<float>     AK4PUPPIJet_constituentPtDistribution_;
vector<float>     AK4PUPPIJet_CHF_;
vector<float>     AK4PUPPIJet_NHF_;
vector<float>     AK4PUPPIJet_CEF_;
vector<float>     AK4PUPPIJet_NEF_;
vector<UShort_t>  AK4PUPPIJet_NCH_;
vector<UShort_t>  AK4PUPPIJet_NNP_;
vector<float>     AK4PUPPIJet_MUF_;
vector<int>       AK4PUPPIJet_PartonFlavour_;
vector<int>       AK4PUPPIJet_HadronFlavour_;
vector<Char_t>    AK4PUPPIJet_ID_;
vector<float>     AK4PUPPIJet_JECUnc_;
// vector<float>     AK4PUPPIJet_JECUncDn_;
vector<Float_t>   AK4PUPPIJet_JER_ptRes_;
vector<Float_t>   AK4PUPPIJet_JER_phiRes_;
vector<Float_t>   AK4PUPPIJet_JER_SF_;
vector<Float_t>   AK4PUPPIJet_JER_SFup_;
vector<Float_t>   AK4PUPPIJet_JER_SFdown_;
vector<ULong64_t> AK4PUPPIJet_FiredTrgs_;
vector<Short_t>   AK4PUPPIJet_GenPartonIndex_;

void ggNtuplizer::branchesAK4PUPPIJets(TTree* tree) {
	tree->Branch("nAK4PUPPIJet",                          & nAK4PUPPIJet_);
	tree->Branch("AK4PUPPIJet_Charge",                    & AK4PUPPIJet_Charge_);
	tree->Branch("AK4PUPPIJet_Pt",                        & AK4PUPPIJet_Pt_);
	tree->Branch("AK4PUPPIJet_En",                        & AK4PUPPIJet_En_);
	tree->Branch("AK4PUPPIJet_Eta",                       & AK4PUPPIJet_Eta_);
	tree->Branch("AK4PUPPIJet_Phi",                       & AK4PUPPIJet_Phi_);
	tree->Branch("AK4PUPPIJet_RawPt",                     & AK4PUPPIJet_RawPt_);
	tree->Branch("AK4PUPPIJet_RawEn",                     & AK4PUPPIJet_RawEn_);
	tree->Branch("AK4PUPPIJet_Mt",                        & AK4PUPPIJet_Mt_);
	tree->Branch("AK4PUPPIJet_Area",                      & AK4PUPPIJet_Area_);
	tree->Branch("AK4PUPPIJet_LeadTrackPt",               & AK4PUPPIJet_LeadTrackPt_);
	tree->Branch("AK4PUPPIJet_LeadTrackEta",              & AK4PUPPIJet_LeadTrackEta_);
	tree->Branch("AK4PUPPIJet_LeadTrackPhi",              & AK4PUPPIJet_LeadTrackPhi_);
	tree->Branch("AK4PUPPIJet_LepTrackPID",               & AK4PUPPIJet_LepTrackPID_);
	tree->Branch("AK4PUPPIJet_LepTrackPt",                & AK4PUPPIJet_LepTrackPt_);
	tree->Branch("AK4PUPPIJet_LepTrackEta",               & AK4PUPPIJet_LepTrackEta_);
	tree->Branch("AK4PUPPIJet_LepTrackPhi",               & AK4PUPPIJet_LepTrackPhi_);
	tree->Branch("AK4PUPPIJet_ConsituentEtaPhiSpread",    & AK4PUPPIJet_ConsituentEtaPhiSpread_);
	tree->Branch("AK4PUPPIJet_constituentPtDistribution", & AK4PUPPIJet_constituentPtDistribution_);
	tree->Branch("AK4PUPPIJet_MaxConstituentDistance",    & AK4PUPPIJet_MaxConstituentDistance_);

	if (doGenParticles_) {
		tree->Branch("AK4PUPPIJet_PartonFlavour",  & AK4PUPPIJet_PartonFlavour_);
		tree->Branch("AK4PUPPIJet_HadronFlavour",  & AK4PUPPIJet_HadronFlavour_);
		tree->Branch("AK4PUPPIJet_GenPartonIndex", & AK4PUPPIJet_GenPartonIndex_);

	}

	tree->Branch("AK4PUPPIJet_ID",         & AK4PUPPIJet_ID_);
	tree->Branch("AK4PUPPIJet_JECUnc",   & AK4PUPPIJet_JECUnc_);
	// tree->Branch("AK4PUPPIJet_JECUncDn",   & AK4PUPPIJet_JECUncDn_);
	tree->Branch("AK4PUPPIJet_JER_ptRes",  & AK4PUPPIJet_JER_ptRes_);
	tree->Branch("AK4PUPPIJet_JER_phiRes", & AK4PUPPIJet_JER_phiRes_);
	tree->Branch("AK4PUPPIJet_JER_SF",     & AK4PUPPIJet_JER_SF_);
	tree->Branch("AK4PUPPIJet_JER_SFup",   & AK4PUPPIJet_JER_SFup_);
	tree->Branch("AK4PUPPIJet_JER_SFdown", & AK4PUPPIJet_JER_SFdown_);
	tree->Branch("AK4PUPPIJet_FiredTrgs",  & AK4PUPPIJet_FiredTrgs_);
	tree->Branch("AK4PUPPIJet_CHF",        & AK4PUPPIJet_CHF_);
	tree->Branch("AK4PUPPIJet_NHF",        & AK4PUPPIJet_NHF_);
	tree->Branch("AK4PUPPIJet_CEF",        & AK4PUPPIJet_CEF_);
	tree->Branch("AK4PUPPIJet_NEF",        & AK4PUPPIJet_NEF_);
	tree->Branch("AK4PUPPIJet_NCH",        & AK4PUPPIJet_NCH_);
	tree->Branch("AK4PUPPIJet_NNP",        & AK4PUPPIJet_NNP_);
	tree->Branch("AK4PUPPIJet_MUF",        & AK4PUPPIJet_MUF_);
}


void ggNtuplizer::fillAK4PUPPIJets(const edm::Event& e, const edm::EventSetup& es) {
	AK4PUPPIJet_Charge_                       . clear();
	AK4PUPPIJet_Pt_                           . clear();
	AK4PUPPIJet_En_                           . clear();
	AK4PUPPIJet_Eta_                          . clear();
	AK4PUPPIJet_Phi_                          . clear();
	AK4PUPPIJet_RawPt_                        . clear();
	AK4PUPPIJet_RawEn_                        . clear();
	AK4PUPPIJet_Mt_                           . clear();
	AK4PUPPIJet_Area_                         . clear();
	AK4PUPPIJet_LeadTrackPt_                  . clear();
	AK4PUPPIJet_LeadTrackEta_                 . clear();
	AK4PUPPIJet_LeadTrackPhi_                 . clear();
	AK4PUPPIJet_LepTrackPt_                   . clear();
	AK4PUPPIJet_LepTrackPID_                  . clear();
	AK4PUPPIJet_LepTrackEta_                  . clear();
	AK4PUPPIJet_LepTrackPhi_                  . clear();
	AK4PUPPIJet_ConsituentEtaPhiSpread_		  . clear();
	AK4PUPPIJet_MaxConstituentDistance_		  . clear();
	AK4PUPPIJet_constituentPtDistribution_	  . clear();
	AK4PUPPIJet_PartonFlavour_                . clear();
	AK4PUPPIJet_HadronFlavour_                . clear();
	AK4PUPPIJet_GenPartonIndex_               . clear();
	AK4PUPPIJet_ID_                           . clear();
	AK4PUPPIJet_JECUnc_                       . clear();
	// AK4PUPPIJet_JECUncDn_                       . clear();
	AK4PUPPIJet_JER_ptRes_                    . clear();
	AK4PUPPIJet_JER_phiRes_                   . clear();
	AK4PUPPIJet_JER_SF_                       . clear();
	AK4PUPPIJet_JER_SFup_                     . clear();
	AK4PUPPIJet_JER_SFdown_                   . clear();
	AK4PUPPIJet_FiredTrgs_                    . clear();
	AK4PUPPIJet_CHF_                          . clear();
	AK4PUPPIJet_NHF_                          . clear();
	AK4PUPPIJet_CEF_                          . clear();
	AK4PUPPIJet_NEF_                          . clear();
	AK4PUPPIJet_NCH_                          . clear();
	AK4PUPPIJet_NNP_                          . clear();
	AK4PUPPIJet_MUF_                          . clear();
	nAK4PUPPIJet_ = 0;


	edm::Handle<edm::View<pat::Jet> > ak4PFJetsPuppiHandle;
	e.getByToken(ak4PFJetsPuppiLabel_, ak4PFJetsPuppiHandle);

	edm::Handle<double> rhoHandle;
	e.getByToken(rhoLabel_, rhoHandle);
	float rho_ = *(rhoHandle.product());

	edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
	if (doGenParticles_)e.getByToken(genParticlesCollection_, genParticlesHandle);

	if (!ak4PFJetsPuppiHandle.isValid()) {
		edm::LogWarning("ggNtuplizer") << "no pat::Jets (AK4) in event";
		return;
	}

	edm::Handle<reco::VertexCollection> vtxHandle;
	e.getByToken(vtxLabel_, vtxHandle);
	if (!vtxHandle.isValid()) edm::LogWarning("ggNtuplizer") << "Primary vertices info not unavailable";

	//// https://twiki.cern.ch/twiki/bin/view/CMS/IntroToJEC
	// Accessing the JEC uncertainties
	edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
	es.get<JetCorrectionsRecord>().get("AK4PFPuppi",JetCorParColl);
	JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
	JetCorrectionUncertainty *jecUnc=0;
	jecUnc = new JetCorrectionUncertainty(JetCorPar);

	// Access JER
	// https://cmsjetmettools.web.cern.ch/cmsjetmettools/JECViewer/
	// https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#Smearing_procedures
	JME::JetResolution jet_pt_resolution_ = JME::JetResolution::get(es, "AK4PFPuppi_pt");
	JME::JetResolution jet_phi_resolution_ = JME::JetResolution::get(es, "AK4PFPuppi_phi");
	JME::JetResolutionScaleFactor resolution_sf_ = JME::JetResolutionScaleFactor::get(es, "AK4PFPuppi");
	JME::JetParameters jet_parameters;

	for (edm::View<pat::Jet>::const_iterator iJet = ak4PFJetsPuppiHandle->begin(); iJet != ak4PFJetsPuppiHandle->end(); ++iJet) {

		AK4PUPPIJet_Charge_.push_back(    iJet->charge());
		AK4PUPPIJet_Pt_.push_back(    iJet->pt());
		AK4PUPPIJet_En_.push_back(    iJet->energy());
		AK4PUPPIJet_Eta_.push_back(   iJet->eta());
		AK4PUPPIJet_Phi_.push_back(   iJet->phi());
		AK4PUPPIJet_RawPt_.push_back( iJet->correctedJet("Uncorrected").pt());
		AK4PUPPIJet_RawEn_.push_back( iJet->correctedJet("Uncorrected").energy());
		AK4PUPPIJet_Mt_.push_back(    iJet->mt());
		AK4PUPPIJet_Area_.push_back(  iJet->jetArea());
		AK4PUPPIJet_CEF_.push_back(   iJet->chargedEmEnergyFraction());
		AK4PUPPIJet_NEF_.push_back(   iJet->neutralEmEnergyFraction());
		AK4PUPPIJet_CHF_.push_back(   iJet->chargedHadronEnergyFraction());
		AK4PUPPIJet_NHF_.push_back(   iJet->neutralHadronEnergyFraction());
		AK4PUPPIJet_NNP_.push_back(   iJet->neutralMultiplicity());
		AK4PUPPIJet_MUF_.push_back(   iJet->muonEnergyFraction());

		jecUnc->setJetEta(iJet->eta());
		jecUnc->setJetPt(iJet->pt());
		jecUnc->setJetPhi(iJet->phi());
		jecUnc->setJetE(iJet->energy());
		AK4PUPPIJet_JECUnc_.push_back(jecUnc->getUncertainty(true));

		// jecUnc->setJetEta(iJet->eta());
		// jecUnc->setJetPt(iJet->pt());
		// jecUnc->setJetPhi(iJet->phi());
		// jecUnc->setJetE(iJet->energy());
		// AK4PUPPIJet_JECUncDn_.push_back(jecUnc->getUncertainty(false));

		AK4PUPPIJet_FiredTrgs_.push_back(matchJetTriggerFilters(iJet->pt(), iJet->eta(), iJet->phi()));

		float leadTrkPt  = -99;
		float leadTrkEta = -99;
		float leadTrkPhi = -99;
		int   lepTrkPID  = -99;
		float lepTrkPt   = -99;
		float lepTrkEta  = -99;
		float lepTrkPhi  = -99;

		for (unsigned id = 0; id < iJet->getJetConstituents().size(); id++) {

			const edm::Ptr<reco::Candidate> daughter = iJet->getJetConstituents().at(id);

			if (daughter.isNonnull() && daughter.isAvailable()) {
				if (daughter->charge() != 0 && daughter->pt() > leadTrkPt) {
					leadTrkPt  = daughter->pt();
					leadTrkEta = daughter->eta();
					leadTrkPhi = daughter->phi();
				}

				if (abs(daughter->pdgId()) == 11 || abs(daughter->pdgId()) == 13) {
					if (daughter->pt() > lepTrkPt) {
						lepTrkPID = daughter->pdgId();
						lepTrkPt  = daughter->pt();
						lepTrkEta = daughter->eta();
						lepTrkPhi = daughter->phi();
					}
				}
			}
		}

		AK4PUPPIJet_LeadTrackPt_ .push_back(leadTrkPt);
		AK4PUPPIJet_LeadTrackEta_.push_back(leadTrkEta);
		AK4PUPPIJet_LeadTrackPhi_.push_back(leadTrkPhi);
		AK4PUPPIJet_LepTrackPID_ .push_back(lepTrkPID);
		AK4PUPPIJet_LepTrackPt_  .push_back(lepTrkPt);
		AK4PUPPIJet_LepTrackEta_ .push_back(lepTrkEta);
		AK4PUPPIJet_LepTrackPhi_ .push_back(lepTrkPhi);

		AK4PUPPIJet_ConsituentEtaPhiSpread_.push_back(iJet->constituentEtaPhiSpread());
		AK4PUPPIJet_MaxConstituentDistance_.push_back(iJet->maxDistance());
		AK4PUPPIJet_constituentPtDistribution_.push_back(iJet->constituentPtDistribution());

		//parton id
		AK4PUPPIJet_PartonFlavour_.push_back(iJet->partonFlavour());
		AK4PUPPIJet_HadronFlavour_.push_back(iJet->hadronFlavour());

		double NHF      = iJet->neutralHadronEnergyFraction();
		double NEMF     = iJet->neutralEmEnergyFraction();
		double CHF      = iJet->chargedHadronEnergyFraction();
		Int_t CHM      = iJet->chargedMultiplicity();
		Int_t NNP      = iJet->neutralMultiplicity();
		Int_t NumConst = CHM + NNP;
		double CEMF     = iJet->chargedEmEnergyFraction();
		double MUF      = iJet->muonEnergyFraction();

		AK4PUPPIJet_NCH_.push_back( CHM);

		//https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017?rev=7
		bool looseJetID = false;
		bool tightJetID = false;
		Bool_t tightLeptVetoID = false;
		if (fabs(iJet->eta()) <= 2.7) {
			looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
			tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0) || fabs(iJet->eta())>2.4);
			tightLeptVetoID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF < 0.8) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.8) || fabs(iJet->eta())>2.4);
		} else if (fabs(iJet->eta()) <= 3.0) {
			looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
			tightJetID = (NEMF>0.02 && NEMF <0.99 && NNP>2);
			tightLeptVetoID = tightJetID;
		} else {
			looseJetID = (NEMF<0.90 && NNP>10);
			tightJetID = (NEMF<0.90 && NNP>10 && NHF > 0.02);
			tightLeptVetoID = tightJetID;
		}
		Char_t jetIDdecision = 0;
		if (looseJetID) setbit(jetIDdecision, 0);
		if (tightJetID) setbit(jetIDdecision, 1);
		if (tightLeptVetoID) setbit(jetIDdecision, 2);
		AK4PUPPIJet_ID_.push_back(jetIDdecision);

		// gen jet and parton
		if (doGenParticles_) {
			int jetGenPartonIndex = -99;
			if (iJet->genParton() && genParticlesHandle.isValid()) {
				jetGenPartonIndex = std::distance(genParticlesHandle->begin(), (vector<reco::GenParticle>::const_iterator) iJet->genParton());
			}
			AK4PUPPIJet_GenPartonIndex_.push_back(jetGenPartonIndex);
		}

		// JER https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyResolution
		jet_parameters.setJetPt(iJet->pt()).setJetEta(iJet->eta()).setRho(rho_);

		Float_t _jer_ptRes = jet_pt_resolution_.getResolution(jet_parameters);
		Float_t _jer_phiRes = jet_phi_resolution_.getResolution(jet_parameters);
		Float_t _jer_sf = resolution_sf_.getScaleFactor(jet_parameters);
		Float_t _jersf_up = resolution_sf_.getScaleFactor(jet_parameters, Variation::UP);
		Float_t _jersf_down = resolution_sf_.getScaleFactor(jet_parameters, Variation::DOWN);

		AK4PUPPIJet_JER_ptRes_.push_back(_jer_ptRes);
		AK4PUPPIJet_JER_phiRes_.push_back(_jer_phiRes);
		AK4PUPPIJet_JER_SF_.push_back(_jer_sf);
		AK4PUPPIJet_JER_SFup_.push_back(_jersf_up);
		AK4PUPPIJet_JER_SFdown_.push_back(_jersf_down);

		nAK4PUPPIJet_++;
	}

	delete jecUnc;
}