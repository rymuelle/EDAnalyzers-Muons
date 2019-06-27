// -*- C++ -*-
//
// Package:    EDAnalyzer2D/Phi_Eta_Analyzer
// Class:      Phi_Eta_Analyzer
//
/**\class Phi_Eta_Analyzer Phi_Eta_Analyzer.cc EDAnalyzer2D/Phi_Eta_Analyzer/plugins/Phi_Eta_Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Greyson Nikolai Newton
//         Created:  Fri, 14 Jun 2019 22:32:43 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TPaveText.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using pat::MuonCollection;

class Phi_Eta_Analyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit Phi_Eta_Analyzer(const edm::ParameterSet&);
      ~Phi_Eta_Analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      bool isGlobalMuon(const pat::Muon& mu, int numGlobalMuons);
      bool isStandAloneMuon(const pat::Muon& mu, int  numStandAloneMuons);
      bool isValidPTMuon(const pat::Muon& mu, int  numPTMuons);
      bool isValidMatchedStationsMuon(const pat::Muon& mu, int numMatchedStationsMuons);
      bool isValidNormalizedChiMuon(const pat::Muon& mu, int numNormalizedChiMuons);
//      bool isValidNumberOfHitMuon(const pat::Muon &mu, int numOfValidHitsMuons);
      bool isValidDBMuon(const pat::Muon& mu, int numValidDBMuons);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      unsigned int minTracks;
      TH1D *tightMuonProfile;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Phi_Eta_Analyzer::Phi_Eta_Analyzer(const edm::ParameterSet& iConfig)
 :
  muonToken_(consumes<pat::MuonCollection>(edm::InputTag("slimmedMuons")))

{
   edm::Service<TFileService> fs;
   tightMuonProfile = fs->make<TH1D>("TightMuons", "Tight Muons", 7  , 0 , 7);
// now do what ever initialization is needed

}


Phi_Eta_Analyzer::~Phi_Eta_Analyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

bool isGlobalMuon(const pat::Muon& mu, int numGlobalMuons)
{
   if(mu.isGlobalMuon())
   {
	numGlobalMuons++;
	return true;
   }
   return false;
}
bool isStandAloneMuon(const pat::Muon& mu, int numStandAloneMuons){
        if(mu.isStandAloneMuon()){numStandAloneMuons++;return true;}return false;}
bool isValidPTMuon(const pat::Muon& mu, int numPTMuons){
        if((mu.pt()>20) & (mu.pt()<200)){numPTMuons++;return true;}return false;}
bool isValidMatchedStationsMuon(const pat::Muon& mu, int numMatchedStationsMuons){
        if(mu.numberOfMatchedStations()>= 2){numMatchedStationsMuons++;return true;}return false;}
bool isValidNormalizedChiMuon(const pat::Muon& mu, int numNormalizedChiMuons){
        if(mu.globalTrack()->normalizedChi2()<10){numNormalizedChiMuons++;return true;}return false;}
//bool isValidNumberOfHitMuon(const pat::Muon &mu,  numOfValidHitMuons){
//      if(mu.innerTrack()->hitPattern().trackerLayerWithMeasurement() > 10){numOfValidHitMuons++;return true;}return false;}
bool isValidDBMuon(const pat::Muon& mu, int numDBMuons){
        if(mu.dB() < 0.2){numDBMuons++;return true;}return false;}
       
// ------------ method called for each event  ------------
void
Phi_Eta_Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using pat::MuonCollection;
   int numGlobalMuons, numStandAloneMuons, numPTMuons, numMatchedStationsMuons,  numNormalizedChiMuons, numValidDBMuons;
   numGlobalMuons = numStandAloneMuons = numPTMuons = numMatchedStationsMuons = numNormalizedChiMuons = numValidDBMuons = 0; 
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
	if(isGlobalMuon(mu, numGlobalMuons))continue;
	if(isStandAloneMuon(mu, numStandAloneMuons))continue;
	if(isValidPTMuon(mu, numPTMuons))continue;
	if(isValidMatchedStationsMuon(mu, numMatchedStationsMuons))continue;
	if(isValidNormalizedChiMuon(mu, numNormalizedChiMuons))continue;
//	if(!isValidNumberOfHitMuons(mu, numValidHitMuons))continue;
	if(isValidDBMuon(mu, numValidDBMuons))continue;
   }
//setting up data & data labels
   const Int_t nx = 6;
   const char *labels[nx] = {"Global", "StandAlone", "PT", "Stations", "Chi2", "ValidDB"};
//setting up histogram
   tightMuonProfile->SetStats(0);
   tightMuonProfile->SetFillColor(38);
   tightMuonProfile->SetCanExtend(TH1::kAllAxes);
//Filling Histogram
   tightMuonProfile->Fill(labels[0], numGlobalMuons);
   tightMuonProfile->Fill(labels[1], numStandAloneMuons);
   tightMuonProfile->Fill(labels[2], numPTMuons);
   tightMuonProfile->Fill(labels[3], numMatchedStationsMuons);
   tightMuonProfile->Fill(labels[4], numNormalizedChiMuons);
   tightMuonProfile->Fill(labels[5], numValidDBMuons);


   tightMuonProfile->LabelsDeflate();
   tightMuonProfile->Draw();
   TPaveText *pt = new TPaveText(0.7,0.85,0.98,0.98,"brNDC");
   pt->SetFillColor(18);
   pt->SetTextAlign(12);
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}
// ------------ method called once each job just before starting event loop  ------------
void
Phi_Eta_Analyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
Phi_Eta_Analyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Phi_Eta_Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Phi_Eta_Analyzer);
