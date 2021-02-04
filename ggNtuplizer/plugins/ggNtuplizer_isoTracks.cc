#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
using namespace std;


////// https://cmssdt.cern.ch/lxr/source/PhysicsTools/PatAlgos/plugins/PATIsolatedTrackProducer.cc

UShort_t            nTrks_;
vector<Char_t>      trkCharge_;
vector<Float_t>     trkPt_;
vector<Float_t>     trkEta_;
vector<Float_t>     trkPhi_;
vector<Float_t>     trkEn_;
// vector<Float_t>     trkDPt_;
// vector<Float_t>     trkDeta_;
// vector<Float_t>     trkDphi_;
vector<UShort_t>    trkFlags_;
vector<Short_t>     trkNhits_;
vector<Short_t>     trkNpixhits_;
vector<Short_t>     trkPxLyrWMsnt_;
vector<Short_t>     trkTkrLyrWMsnt_;
vector<Float_t>     trkRawCaloFrac_;
vector<Float_t>     trkRawHcalFrac_;
vector<Float_t>     trkNormChi2_;
vector<Char_t>      trkLostInnrHits_;
vector<Short_t>     trkPVAssocQual_;            //// 1=NotReconstructedPrimary, 2=OtherDeltaZ, 3=CompatibilityBTag, 4=CompatibilityDz, 5=UsedInFitLoose,  6=UsedInFitTight 
vector<Float_t>     trkDEdxPixel_;
vector<Float_t>     trkDEdxStrip_;
// vector<Int_t>       trkEcalDeta_;               ////// int deltaEta = int((trackDetInfo.trkGlobPosAtEcal.eta() - gentk.eta()) / 0.5 * 250);
// vector<Int_t>       trkEcalDphi_;               ////// int deltaPhi = int((trackDetInfo.trkGlobPosAtEcal.phi() - gentk.phi()) / 0.5 * 250);
vector<Float_t>     trkDxy_;
// vector<Float_t>     trkDxyError_;
vector<Float_t>     trkDz_;
// vector<Float_t>     trkDzError_;
vector<Char_t>      trkFromPV_;                 //// 0=NoPV 1=PVLoose  2=PVTight 3=PVUsedInFit
vector<Float_t>     trkMatchedCaloJetEmEnergy_;
vector<Float_t>     trkMatchedCaloJetHadEnergy_;
vector<Float_t>     trkPfMiniChIso_;
vector<Float_t>     trkPfMiniNhIso_;
vector<Float_t>     trkPfMiniPhIso_;
vector<Float_t>     trkPfMiniPuIso_;
vector<Float_t>     trk03ChIso_;
vector<Float_t>     trk03NhIso_;
vector<Float_t>     trk03PhIso_;
vector<Float_t>     trk03PuIso_;
vector<Float_t>     trkPfNeutralSum_;


void ggNtuplizer::branchesTracks(TTree* tree) {

    tree->Branch("nTrks",                           &nTrks_);
    tree->Branch("trkCharge",                       &trkCharge_);
    tree->Branch("trkPt",                           &trkPt_);
    tree->Branch("trkEta",                          &trkEta_);
    tree->Branch("trkPhi",                          &trkPhi_);
    tree->Branch("trkEn",                           &trkEn_);
    // tree->Branch("trkDPt",                         &trkDPt_);
    // tree->Branch("trkDeta",                        &trkDeta_);
    // tree->Branch("trkDphi",                        &trkDphi_);
    tree->Branch("trkFlags",                       &trkFlags_);
    tree->Branch("trkNhits",                       &trkNhits_);
    tree->Branch("trkNpixhits",                    &trkNpixhits_);
    tree->Branch("trkPxLyrWMsnt",                &trkPxLyrWMsnt_);
    tree->Branch("trkTkrLyrWMsnt",               &trkTkrLyrWMsnt_);
    tree->Branch("trkRawCaloFrac",                 &trkRawCaloFrac_);
    tree->Branch("trkRawHcalFrac",                 &trkRawHcalFrac_);
    tree->Branch("trkNormChi2",                     &trkNormChi2_);
    tree->Branch("trkLostInnrHits",                &trkLostInnrHits_);
    tree->Branch("trkPVAssocQual",                 &trkPVAssocQual_);
    tree->Branch("trkDEdxPixel",                    &trkDEdxPixel_);
    tree->Branch("trkDEdxStrip",                    &trkDEdxStrip_);
    // tree->Branch("trkEcalDeta",                         &trkEcalDeta_);
    // tree->Branch("trkEcalDphi",                         &trkEcalDphi_);
    tree->Branch("trkDxy",                          &trkDxy_);
    // tree->Branch("trkDxyError",                     &trkDxyError_);
    tree->Branch("trkDz",                           &trkDz_);
    // tree->Branch("trkDzError",                      &trkDzError_);
    tree->Branch("trkFromPV",                       &trkFromPV_);
    tree->Branch("trkMatchedCaloJetEmEnergy",       &trkMatchedCaloJetEmEnergy_);
    tree->Branch("trkMatchedCaloJetHadEnergy",      &trkMatchedCaloJetHadEnergy_);
    tree->Branch("trkPfMiniChIso",                  &trkPfMiniChIso_);
    tree->Branch("trkPfMiniNhIso",                   &trkPfMiniNhIso_);
    tree->Branch("trkPfMiniPhIso",                   &trkPfMiniPhIso_);
    tree->Branch("trkPfMiniPuIso",                   &trkPfMiniPuIso_);
    tree->Branch("trk03ChIso",                      &trk03ChIso_);
    tree->Branch("trk03NhIso",                      &trk03NhIso_);
    tree->Branch("trk03PhIso",                      &trk03PhIso_);
    tree->Branch("trk03PuIso",                      &trk03PuIso_);
    tree->Branch("trkPfNeutralSum",                  &trkPfNeutralSum_);
};


void ggNtuplizer::fillTracks(const edm::Event& e, const edm::EventSetup& es) {

    // cleanup from previous execution
    nTrks_                  =   0;
    trkCharge_                          .clear();
    trkPt_                              .clear();
    trkEta_                             .clear();
    trkPhi_                             .clear();
    trkEn_                              .clear();
    // trkDPt_                             .clear();
    // trkDeta_                            .clear();
    // trkDphi_                            .clear();
    trkFlags_                           .clear();
    trkNhits_                           .clear();
    trkNpixhits_                        .clear();
    trkPxLyrWMsnt_                    .clear();
    trkTkrLyrWMsnt_                   .clear();
    trkRawCaloFrac_                     .clear();
    trkRawHcalFrac_                     .clear();
    trkNormChi2_                         .clear();
    trkLostInnrHits_                    .clear();
    trkPVAssocQual_                     .clear();
    trkDEdxPixel_                       .clear();
    trkDEdxStrip_                       .clear();
    // trkEcalDeta_                            .clear();
    // trkEcalDphi_                            .clear();
    trkDxy_                             .clear();
    // trkDxyError_                        .clear();
    trkDz_                              .clear();
    // trkDzError_                         .clear();
    trkFromPV_                          .clear();
    trkMatchedCaloJetEmEnergy_          .clear();
    trkMatchedCaloJetHadEnergy_         .clear();
    trkPfMiniChIso_                     .clear();
    trkPfMiniNhIso_                      .clear();
    trkPfMiniPhIso_                      .clear();
    trkPfMiniPuIso_                      .clear();
    trk03ChIso_                         .clear();
    trk03NhIso_                         .clear();
    trk03PhIso_                         .clear();
    trk03PuIso_                         .clear();
    trkPfNeutralSum_                     .clear();

    edm::Handle<edm::View<pat::IsolatedTrack> > trackHandle;
    e.getByToken(tracksLabel_, trackHandle);

    if (!trackHandle.isValid()) {
        edm::LogWarning("ggNtuplizer") << "no pat::IsolatedTrack in event";
        return;
    }

    for(edm::View<pat::IsolatedTrack>::const_iterator iTrack = trackHandle->begin(); iTrack != trackHandle->end(); ++iTrack){

        nTrks_++;
        trkCharge_                          .push_back(iTrack->charge());
        trkPt_                              .push_back(iTrack->pt());
        trkEta_                             .push_back(iTrack->eta());
        trkPhi_                             .push_back(iTrack->phi());
        trkEn_                              .push_back(iTrack->energy());

        UShort_t      iTrkFlags = 0;
        if(iTrack->isHighPurityTrack()) setbit(iTrkFlags, 0);
        if(iTrack->isLooseTrack()) setbit(iTrkFlags, 1);
        if(iTrack->isTightTrack()) setbit(iTrkFlags, 2);
        
        const pat::PackedCandidateRef & iPcRef = iTrack->packedCandRef();

        if(iPcRef.isNonnull()){

            if(iPcRef->isMuon()) setbit(iTrkFlags, 3);
            if(iPcRef->isGlobalMuon()) setbit(iTrkFlags, 4);
            if(iPcRef->isCaloMuon()) setbit(iTrkFlags, 5);
            if(iPcRef->isStandAloneMuon()) setbit(iTrkFlags, 6);
            if(iPcRef->isTrackerMuon()) setbit(iTrkFlags, 7);
            if(iPcRef->isGoodEgamma()) setbit(iTrkFlags, 8);
            if(iPcRef->isPhoton()) setbit(iTrkFlags, 9);
            if(iPcRef->isElectron()) setbit(iTrkFlags, 10);
            if(iPcRef->isConvertedPhoton()) setbit(iTrkFlags, 11);
            if(iPcRef->isJet()) setbit(iTrkFlags, 12);
            if(iPcRef->isIsolatedChargedHadron()) setbit(iTrkFlags, 13);
            if(iPcRef->longLived()) setbit(iTrkFlags, 14);
            if(iTrack->pfLepOverlap()) setbit(iTrkFlags, 15);

            // trkDPt_                             .push_back(iPcRef->ptTrk() - iPcRef->pt());
            // trkDeta_                            .push_back(iPcRef->etaAtVtx() -  iPcRef->eta());
            // trkDphi_                            .push_back(iPcRef->phiAtVtx() -  iPcRef->phi());
            trkNhits_                           .push_back(iPcRef->numberOfHits());
            trkNpixhits_                        .push_back(iPcRef->numberOfPixelHits());
            trkPxLyrWMsnt_                      .push_back(iPcRef->pixelLayersWithMeasurement());
            trkTkrLyrWMsnt_                     .push_back(iPcRef->trackerLayersWithMeasurement());
            trkRawCaloFrac_                     .push_back(iPcRef->rawCaloFraction());
            trkRawHcalFrac_                     .push_back(iPcRef->rawHcalFraction());

            if(iPcRef->bestTrack()){
                trkNormChi2_                         .push_back(iPcRef->bestTrack()->normalizedChi2());
            } else{
                trkNormChi2_                         .push_back(-9999);
            }

            trkLostInnrHits_                    .push_back(iPcRef->lostInnerHits());
            trkPVAssocQual_                     .push_back(iPcRef->pvAssociationQuality());

        } else{

            // trkDPt_                             .push_back(-9999);
            // trkDeta_                            .push_back(-9999);
            // trkDphi_                            .push_back(-9999);
            trkNhits_                           .push_back(-99);
            trkNpixhits_                        .push_back(-99);
            trkPxLyrWMsnt_                      .push_back(-99);
            trkTkrLyrWMsnt_                     .push_back(-99);
            trkRawCaloFrac_                     .push_back(-9999);
            trkRawHcalFrac_                     .push_back(-9999);
            trkNormChi2_                         .push_back(-9999);
            trkLostInnrHits_                    .push_back(-99);
            trkPVAssocQual_                     .push_back(-99);
        }


        trkFlags_                           .push_back(iTrkFlags);
        trkDEdxPixel_                       .push_back(iTrack->dEdxPixel());
        trkDEdxStrip_                       .push_back(iTrack->dEdxStrip());
        // trkEcalDeta_                        .push_back(iTrack->deltaEta());
        // trkEcalDphi_                        .push_back(iTrack->deltaPhi());
        trkDxy_                             .push_back(iTrack-> dxy());
        // trkDxyError_                        .push_back(iTrack->dxyError());
        trkDz_                              .push_back(iTrack->dz());
        // trkDzError_                         .push_back(iTrack->dzError());
        trkFromPV_                          .push_back(iTrack->fromPV());
        trkMatchedCaloJetEmEnergy_          .push_back(iTrack->matchedCaloJetEmEnergy());
        trkMatchedCaloJetHadEnergy_         .push_back(iTrack->matchedCaloJetHadEnergy() );
        trkPfMiniChIso_                     .push_back(iTrack->miniPFIsolation().chargedHadronIso());
        trkPfMiniNhIso_                     .push_back(iTrack->miniPFIsolation().neutralHadronIso());
        trkPfMiniPhIso_                     .push_back(iTrack->miniPFIsolation().photonIso());
        trkPfMiniPuIso_                     .push_back(iTrack->miniPFIsolation().puChargedHadronIso());
        trk03ChIso_                         .push_back(iTrack->pfIsolationDR03().chargedHadronIso());
        trk03NhIso_                         .push_back(iTrack->pfIsolationDR03().neutralHadronIso());
        trk03PhIso_                         .push_back(iTrack->pfIsolationDR03().photonIso());
        trk03PuIso_                         .push_back(iTrack->pfIsolationDR03().puChargedHadronIso());
        trkPfNeutralSum_                     .push_back(iTrack->pfNeutralSum());

    }
};
