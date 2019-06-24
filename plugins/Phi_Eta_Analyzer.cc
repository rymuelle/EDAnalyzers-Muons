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
#include "TH1.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

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
      bool isGoodGlobalMuon(const pat::Muon &mu, int numGlobalMuons);
      bool isGoodStandAloneMuon(const pat::Muon &mu, int numStandAloneMuons);
      bool isValidPTMuon(const pat::Muon &mu, int numPTMuons);
      bool isValidMatchedStationsMuon(const pat::Muon &mu, int numMatchedStationsMuons);
      bool isValidNormalizedChiMuon(const pat::Muon &mu, int numNormalizedChiMuons);
      bool isValidNumberOfHitsMuon(const pat::Muon &mu, int numOfValidHitsMuons);
      bool isValidDBMuon(const pat::Muon &mu, int numValidDBMuons);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      unsigned int minTracks;
      TH1D *demohisto;  //used to select what tracks to read from configuration file
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
   demohisto = fs->make<TGraph>("TightMuons", "Tight Muons", 7  , 0 , 1);
   //now do what ever initialization is needed

}


Phi_Eta_Analyzer::~Phi_Eta_Analyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Phi_Eta_Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   int count, numGlobalMuons, numStandAloneMuons, numPTMuons, numNormalizedChiMuons, numValidHitMuons, numValidDBMuons;
   count = numGlobalMuons = numStandAloneMuons = numPTMuons = numNormalizedChiMuons = numValidHitMuons = numValidDBMuons = 0; 
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
	if(!isGoodGlobalMuon(mu, numGlobalMuons))continue;
	if(!isStandAloneMuon(mu, numStandAloneMuons))continue;
	if(!isValidPTMuon(mu, numStandAloneMuons))continue;
	if(!isValidMatchedStationsMuon(mu, numMatchedStations))continue;
	if(!isValidNormalizedChiMuon(mu, numNormalizedChiMuons))continue;
	if(!isValidNumberOfHitsMuons(mu, numValidHitsMuons)continue;
	if(!isValidDBMuon(mu, numValidDBMuons))continue;
   }
   Int_t n = 20;
   Double_t x[n], y[n];
   for(Int_t i=0;i<n;i++){

   demohisto->Fill()
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}
bool isGoodGlobalMuon(const pat::Muon &mu, int numGlobalMuons){
	if(mu.isGlobalMuon()){numGlobalMuons++;return true;}return false;}
bool isGoodStandAloneMuon(const pat::Muon &mu, int numStandAloneMuons){
	if(mu.isStandAloneMuon()){numStandAloneMuons++;return true;}return false;}
bool isValidPTMuon(const pat::Muon &mu, int numPTMuons){
	if((mu.pt()>20) & (mu.pt()<200)){numPTMuons++;return true;}return false;}
bool isValidMatchedStationsMuon(const pat::Muon &mu, int numMatchedStationsMuons){
	if(mu.numberOfMatchedStations > 5){numMatchedStationsMuons++;return true;}return false;}
bool isValidNormalizedChiMuon(const pat::Muon &mu, int numNormalizedChiMuons){
	if(mu.globalTrack()->normalizedChi2()<2){numNormalizedChi++;return true}return false;}
bool isValidNumberOfHitsMuon(const pat::Muon &mu, int numOfValidHitMuons){
	if(mu.globalTrack()->hitPattern().numberOfValidMuonHits() > 0){numOfValidHitMuons++;return true;}return false;}
bool isValidDBMuon(const pat::Muon &mu, int numDBMuons)

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
