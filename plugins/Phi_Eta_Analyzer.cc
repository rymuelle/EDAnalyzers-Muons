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
#include "TH2.h"
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


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      unsigned int minTracks;
      TH2D *demohisto;  //used to select what tracks to read from configuration file
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
   demohisto = fs->make<TH2D>("Phi_v_Eta", "Phi v. Eta;Phi;Eta", 100 , -3.14 , 3.14, 100 , -2.5 , 2.5 );
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
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
   	if (mu.pt() < 5 || !mu.isLooseMuon()) continue;
	demohisto->Fill(mu.phi(), mu.eta());
   }

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
