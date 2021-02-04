#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

edm::EDGetTokenT<edm::View<pat::Tau>>        tauLabel_;

//// https://cmssdt.cern.ch/lxr/source/DataFormats/TauReco/interface/PFTau.h#0038

vector<Float_t>                       tauPt_;
vector<Float_t>                       tauEta_;
vector<Float_t>                       tauPhi_;
vector<Float_t>                       tauEn_;
vector<Float_t>                       tauDxy_;
vector<Float_t>                       tauDz_;

vector<Float_t>                       tauChIsoPtSum_;
vector<Float_t>                       tauNeuIsoPtSum_;
vector<Float_t>                       tauPuCorrPtSum_;
vector<Float_t>                       tauNeuIsoPtSumWeight_;
vector<Float_t>                       tauFPCorr_;
vector<Float_t>                       tauPhoPtSumOutSigCone_;

vector<UChar_t>                     tauNSigPFChHadCands_;
vector<UChar_t>                     tauNSigPFNeuHadCands_;
vector<UChar_t>                     tauNSigPFPhoCands_;
vector<UChar_t>                     tauNSigPFCands_;
vector<UChar_t>                     tauNIsoPFChHadCands_;
vector<UChar_t>                     tauNIsoPFNeuHadCands_;
vector<UChar_t>                     tauNIsoPFPhoCands_;
vector<UChar_t>                     tauNIsoPFCands_;

vector<Float_t>                       tauLeadChEta_;
vector<Float_t>                       tauLeadChPhi_;
vector<Float_t>                       tauLeadChPt_;
vector<Float_t>                       tauLeadChDz_;
vector<Float_t>                       tauLeadChDxy_;


// void ggNtuplizer::branchesTaus(TTree* tree) {

// };

// void ggNtuplizer::fillTaus(const edm::Event& e, const edm::EventSetup& es) {
    
// };
