#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;



//// https://cmssdt.cern.ch/lxr/source/DataFormats/TauReco/interface/PFTau.h#0038

UShort_t 								nTau_;
vector<Float_t>                       	tauPt_;
vector<Float_t>                       	tauEta_;
vector<Float_t>                       	tauPhi_;
vector<Float_t>                       	tauEn_;
vector<Float_t>                       	tauDxy_;
// vector<Float_t>                       	tauDz_;
vector<vector<Char_t>>             		tauDMs_;
vector<Long64_t>						tauIDbits_;
vector<UInt_t>							tauIDbitsDeepTau2017v2p1_;
vector<UInt_t>							tauIDbitsDeepTau2017v1_;
vector<Float_t>                       	tauCombIsoDelBetaCorRaw3Hits_;
vector<Float_t>                       	tauChIsoPtSum_;
vector<Float_t>                       	tauNeuIsoPtSum_;
vector<Float_t>                       	tauPuCorrPtSum_;
vector<Float_t>                       	tauNeuIsoPtSumWeight_;
vector<Float_t>                       	tauFootPrCorr_;
vector<Float_t>                       	tauPhoPtSumOutSigCone_;
vector<UChar_t>                       	tauNSigPFChHadCands_;
vector<UChar_t>                       	tauNSigPFNeuHadCands_;
vector<UChar_t>                       	tauNSigPFPhoCands_;
vector<UChar_t>                       	tauNSigPFCands_;
vector<UChar_t>                       	tauNIsoPFChHadCands_;
vector<UChar_t>                       	tauNIsoPFNeuHadCands_;
vector<UChar_t>                       	tauNIsoPFPhoCands_;
vector<UChar_t>                       	tauNIsoPFCands_;
vector<Float_t>                       	tauLeadChEta_;
vector<Float_t>                       	tauLeadChPhi_;
vector<Float_t>                       	tauLeadChPt_;
vector<Float_t>                       	tauLeadChEn_;
vector<Float_t>                       	tauLeadChDxy_;
vector<Float_t>                       	tauLeadChDz_;
vector<Float_t>                       	tauLeadTrkNChi2_;


void ggNtuplizer::branchesTaus(TTree* tree) {

	tree->Branch("nTau",                 		 	&nTau_);
	tree->Branch("tauPt",                 	 		&tauPt_);
	tree->Branch("tauEta",                  		&tauEta_);
	tree->Branch("tauPhi",                  		&tauPhi_);
	tree->Branch("tauEn",                  			&tauEn_);
	tree->Branch("tauDxy",                  		&tauDxy_);
	// tree->Branch("tauDz",                  			&tauDz_);
	tree->Branch("tauDMs",                  		&tauDMs_);
	tree->Branch("tauIDbits",                  		&tauIDbits_);
	tree->Branch("tauIDbitsDeepTau2017v2p1",       	&tauIDbitsDeepTau2017v2p1_);
	tree->Branch("tauIDbitsDeepTau2017v1",          &tauIDbitsDeepTau2017v1_);
	tree->Branch("tauCombIsoDelBetaCorRaw3Hits",   	&tauCombIsoDelBetaCorRaw3Hits_);
	tree->Branch("tauChIsoPtSum",                  	&tauChIsoPtSum_);
	tree->Branch("tauNeuIsoPtSum",                 	&tauNeuIsoPtSum_);
	tree->Branch("tauPuCorrPtSum",                 	&tauPuCorrPtSum_);
	tree->Branch("tauNeuIsoPtSumWeight",           	&tauNeuIsoPtSumWeight_);
	tree->Branch("tauFootPrCorr",                  	&tauFootPrCorr_);
	tree->Branch("tauPhoPtSumOutSigCone",          	&tauPhoPtSumOutSigCone_);
	tree->Branch("tauNSigPFChHadCands",            	&tauNSigPFChHadCands_);
	tree->Branch("tauNSigPFNeuHadCands",           	&tauNSigPFNeuHadCands_);
	tree->Branch("tauNSigPFPhoCands",              	&tauNSigPFPhoCands_);
	tree->Branch("tauNSigPFCands",                 	&tauNSigPFCands_);
	tree->Branch("tauNIsoPFChHadCands",            	&tauNIsoPFChHadCands_);
	tree->Branch("tauNIsoPFNeuHadCands",           	&tauNIsoPFNeuHadCands_);
	tree->Branch("tauNIsoPFPhoCands",              	&tauNIsoPFPhoCands_);
	tree->Branch("tauNIsoPFCands",                 	&tauNIsoPFCands_);
	tree->Branch("tauLeadChEta",                   	&tauLeadChEta_);
	tree->Branch("tauLeadChPhi",                   	&tauLeadChPhi_);
	tree->Branch("tauLeadChPt",                   	&tauLeadChPt_);
	tree->Branch("tauLeadChEn",                    	&tauLeadChEn_);
	tree->Branch("tauLeadChDxy",                   	&tauLeadChDxy_);
	tree->Branch("tauLeadChDz",                    	&tauLeadChDz_);
	tree->Branch("tauLeadTrkNChi2",                	&tauLeadTrkNChi2_);

};

void ggNtuplizer::fillTaus(const edm::Event& e, const edm::EventSetup& es) {

	nTau_ 													= 		0;
	tauPt_ 													.clear();
	tauEta_ 												.clear();
	tauPhi_ 												.clear();
	tauEn_ 													.clear();
	tauDxy_ 												.clear();
	// tauDz_ 													.clear();
	tauDMs_ 												.clear();
	tauIDbits_												.clear();
	tauIDbitsDeepTau2017v2p1_ 								.clear();
	tauIDbitsDeepTau2017v1_ 								.clear();
	tauCombIsoDelBetaCorRaw3Hits_ 							.clear();
	tauChIsoPtSum_ 											.clear();
	tauNeuIsoPtSum_ 										.clear();
	tauPuCorrPtSum_ 										.clear();
	tauNeuIsoPtSumWeight_ 									.clear();
	tauFootPrCorr_ 											.clear();
	tauPhoPtSumOutSigCone_ 									.clear();
	tauNSigPFChHadCands_ 									.clear();
	tauNSigPFNeuHadCands_ 									.clear();
	tauNSigPFPhoCands_ 										.clear();
	tauNSigPFCands_ 										.clear();
	tauNIsoPFChHadCands_ 									.clear();
	tauNIsoPFNeuHadCands_ 									.clear();
	tauNIsoPFPhoCands_ 										.clear();
	tauNIsoPFCands_ 										.clear();
	tauLeadChEta_ 											.clear();
	tauLeadChPhi_ 											.clear();
	tauLeadChPt_ 											.clear();
	tauLeadChEn_ 											.clear();
	tauLeadChDxy_ 											.clear();
	tauLeadChDz_ 											.clear();
	tauLeadTrkNChi2_ 										.clear();

	edm::Handle<edm::View<pat::Tau>> tauHandle;
	e.getByToken(tauLabel_, tauHandle);

	if (!tauHandle.isValid()) {
		edm::LogWarning("ggNtuplizer") << "no pat::Tau in event";
		return;
	}

	edm::Handle<reco::VertexCollection> vertices;
	e.getByToken(vtxLabel_, vertices);

	for(edm::View<pat::Tau>::const_iterator iTau = tauHandle->begin(); iTau != tauHandle->end(); ++iTau){

		nTau_++;


		tauPt_ 													.push_back(iTau->pt());
		tauEta_ 												.push_back(iTau->eta());
		tauPhi_ 												.push_back(iTau->phi());
		tauEn_ 													.push_back(iTau->energy());
		tauDxy_ 												.push_back(iTau->dxy());
		// tauDz_ 													.push_back(iTau->leadTrack().isNonnull() ? iTau->leadTrack()->dz() : -99999.);

		tauDMs_ 												.push_back({
			(Char_t)iTau->decayMode(),
			(Char_t)iTau->tauID("decayModeFinding"),
			(Char_t)iTau->tauID("decayModeFindingNewDMs"),
			(Char_t)iTau->tauID("MVADM2017v1")			
		});

		Long64_t iTauIDbits = 0;
		if(iTau->tauID("againstElectronLooseMVA6")) setbit(iTauIDbits, 0);
		if(iTau->tauID("againstElectronMediumMVA6")) setbit(iTauIDbits, 1);
		if(iTau->tauID("againstElectronTightMVA6")) setbit(iTauIDbits, 2);
		if(iTau->tauID("againstElectronVLooseMVA6")) setbit(iTauIDbits, 3);
		if(iTau->tauID("againstElectronVTightMVA6")) setbit(iTauIDbits, 4);
		if(iTau->tauID("againstMuonLoose3")) setbit(iTauIDbits, 5);
		if(iTau->tauID("againstMuonTight3")) setbit(iTauIDbits, 6);
		if(iTau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits")) setbit(iTauIDbits, 7);
		if(iTau->tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 8);
		if(iTau->tauID("byLooseIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 9);
		if(iTau->tauID("byLooseIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 10);
		if(iTau->tauID("byLooseIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 11);
		if(iTau->tauID("byLooseIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 12);
		if(iTau->tauID("byLooseIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 13);
		if(iTau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits")) setbit(iTauIDbits, 14);
		if(iTau->tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 15);
		if(iTau->tauID("byMediumIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 16);
		if(iTau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 17);
		if(iTau->tauID("byMediumIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 18);
		if(iTau->tauID("byMediumIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 19);
		if(iTau->tauID("byMediumIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 20);
		if(iTau->tauID("byPhotonPtSumOutsideSignalCone")) setbit(iTauIDbits, 21);
		if(iTau->tauID("byTightCombinedIsolationDeltaBetaCorr3Hits")) setbit(iTauIDbits, 22);
		if(iTau->tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 23);
		if(iTau->tauID("byTightIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 24);
		if(iTau->tauID("byTightIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 25);
		if(iTau->tauID("byTightIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 26);
		if(iTau->tauID("byTightIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 27);
		if(iTau->tauID("byTightIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 28);
		if(iTau->tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 29);
		if(iTau->tauID("byVLooseIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 30);
		if(iTau->tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 31);
		if(iTau->tauID("byVLooseIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 32);
		if(iTau->tauID("byVLooseIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 33);
		if(iTau->tauID("byVLooseIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 34);
		if(iTau->tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 35);
		if(iTau->tauID("byVTightIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 36);
		if(iTau->tauID("byVTightIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 37);
		if(iTau->tauID("byVTightIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 38);
		if(iTau->tauID("byVTightIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 39);
		if(iTau->tauID("byVTightIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 40);
		if(iTau->tauID("byVVLooseIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 41);
		if(iTau->tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT")) setbit(iTauIDbits, 42);
		if(iTau->tauID("byVVTightIsolationMVArun2v1DBnewDMwLT")) setbit(iTauIDbits, 43);
		if(iTau->tauID("byVVTightIsolationMVArun2v1DBoldDMwLT")) setbit(iTauIDbits, 44);
		if(iTau->tauID("byVVTightIsolationMVArun2v1PWdR03oldDMwLT")) setbit(iTauIDbits, 45);
		if(iTau->tauID("byVVTightIsolationMVArun2v1PWnewDMwLT")) setbit(iTauIDbits, 46);
		if(iTau->tauID("byVVTightIsolationMVArun2v1PWoldDMwLT")) setbit(iTauIDbits, 47);
		tauIDbits_.push_back(iTauIDbits);
		

		UInt_t 	iTauIDbitsDeepTau2017v2p1 = 0;
		if(iTau->tauID("byVVVLooseDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 0);
		if(iTau->tauID("byVVLooseDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 1);
		if(iTau->tauID("byVLooseDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 2);
		if(iTau->tauID("byLooseDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 3);
		if(iTau->tauID("byMediumDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 4);
		if(iTau->tauID("byTightDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 5);
		if(iTau->tauID("byVTightDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 6);
		if(iTau->tauID("byVVTightDeepTau2017v2p1VSjet")) setbit(iTauIDbitsDeepTau2017v2p1, 7);
		if(iTau->tauID("byVVVLooseDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 8);
		if(iTau->tauID("byVVLooseDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 9);
		if(iTau->tauID("byVLooseDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 10);
		if(iTau->tauID("byLooseDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 11);
		if(iTau->tauID("byMediumDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 12);
		if(iTau->tauID("byTightDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 13);
		if(iTau->tauID("byVTightDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 14);
		if(iTau->tauID("byVVTightDeepTau2017v2p1VSe")) setbit(iTauIDbitsDeepTau2017v2p1, 15);
		if(iTau->tauID("byVLooseDeepTau2017v2p1VSmu")) setbit(iTauIDbitsDeepTau2017v2p1, 16);
		if(iTau->tauID("byLooseDeepTau2017v2p1VSmu")) setbit(iTauIDbitsDeepTau2017v2p1, 17);
		if(iTau->tauID("byMediumDeepTau2017v2p1VSmu")) setbit(iTauIDbitsDeepTau2017v2p1, 18);
		if(iTau->tauID("byTightDeepTau2017v2p1VSmu")) setbit(iTauIDbitsDeepTau2017v2p1, 19);
		tauIDbitsDeepTau2017v2p1_ 								.push_back(iTauIDbitsDeepTau2017v2p1);
		

		UInt_t iTauIDbitsDeepTau2017v1 = 0;
		if(iTau->tauID("byVVVLooseDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 0);
		if(iTau->tauID("byVVLooseDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 1);
		if(iTau->tauID("byVLooseDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 2);
		if(iTau->tauID("byLooseDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 3);
		if(iTau->tauID("byMediumDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 4);
		if(iTau->tauID("byTightDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 5);
		if(iTau->tauID("byVTightDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 6);
		if(iTau->tauID("byVVTightDeepTau2017v1VSjet")) setbit(iTauIDbitsDeepTau2017v1, 7);
		if(iTau->tauID("byVVVLooseDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 8);
		if(iTau->tauID("byVVLooseDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 9);
		if(iTau->tauID("byVLooseDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 10);
		if(iTau->tauID("byLooseDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 11);
		if(iTau->tauID("byMediumDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 12);
		if(iTau->tauID("byTightDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 13);
		if(iTau->tauID("byVTightDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 14);
		if(iTau->tauID("byVVTightDeepTau2017v1VSe")) setbit(iTauIDbitsDeepTau2017v1, 15);
		if(iTau->tauID("byVVVLooseDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 16);
		if(iTau->tauID("byVVLooseDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 17);
		if(iTau->tauID("byVLooseDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 18);
		if(iTau->tauID("byLooseDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 19);
		if(iTau->tauID("byMediumDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 20);
		if(iTau->tauID("byTightDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 21);
		if(iTau->tauID("byVTightDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 22);
		if(iTau->tauID("byVVTightDeepTau2017v1VSmu")) setbit(iTauIDbitsDeepTau2017v1, 23);
		// if(iTau->tauID("byTightDpfTau2016v0VSall")) setbit(iTauIDbitsDeepTau2017v1, 24);
		// if(iTau->tauID("byTightDpfTau2016v1VSall")) setbit(iTauIDbitsDeepTau2017v1, 25);
		tauIDbitsDeepTau2017v1_.push_back(iTauIDbitsDeepTau2017v1);

		tauCombIsoDelBetaCorRaw3Hits_ 							.push_back(iTau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits"));
		tauChIsoPtSum_ 											.push_back(iTau->tauID("chargedIsoPtSum"));
		tauNeuIsoPtSum_ 										.push_back(iTau->tauID("neutralIsoPtSum"));
		tauPuCorrPtSum_ 										.push_back(iTau->tauID("puCorrPtSum"));
		tauNeuIsoPtSumWeight_ 									.push_back(iTau->tauID("neutralIsoPtSumWeight"));
		tauFootPrCorr_ 											.push_back(iTau->tauID("footprintCorrection"));
		tauPhoPtSumOutSigCone_ 									.push_back(iTau->tauID("photonPtSumOutsideSignalCone"));

		tauNSigPFChHadCands_ 									.push_back(iTau->signalChargedHadrCands().size());
		tauNSigPFNeuHadCands_ 									.push_back(iTau->signalNeutrHadrCands().size());
		tauNSigPFPhoCands_ 										.push_back(iTau->signalGammaCands().size());
		tauNSigPFCands_ 										.push_back(iTau->signalCands().size());
		tauNIsoPFChHadCands_ 									.push_back(iTau->isolationChargedHadrCands().size());
		tauNIsoPFNeuHadCands_ 									.push_back(iTau->isolationNeutrHadrCands().size());
		tauNIsoPFPhoCands_ 										.push_back(iTau->isolationGammaCands().size());
		tauNIsoPFCands_ 										.push_back(iTau->isolationCands().size());

		if (vertices->size()>0) {
			pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(iTau->leadChargedHadrCand().get());
			if(packedLeadTauCand){
				tauLeadChEta_.push_back(packedLeadTauCand->eta());
				tauLeadChPhi_.push_back(packedLeadTauCand->phi());
				tauLeadChPt_.push_back(packedLeadTauCand->pt());	
				tauLeadChEn_.push_back(packedLeadTauCand->energy());
				tauLeadChDz_.push_back(packedLeadTauCand->dz());
				tauLeadChDxy_.push_back(packedLeadTauCand->dxy());

			} else{
				tauLeadChEta_.push_back(-9999);
				tauLeadChPhi_.push_back(-9999);
				tauLeadChPt_.push_back(-9999);	
				tauLeadChEn_.push_back(-9999);
				tauLeadChDz_.push_back(-9999);
				tauLeadChDxy_.push_back(-9999);
			}
		}
		
		tauLeadTrkNChi2_ 					.push_back(iTau->leadingTrackNormChi2());	

	}

};
