import FWCore.ParameterSet.Config as cms

process = cms.Process("GitTest")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('GitTest')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
            'file:/afs/cern.ch/work/r/rymuelle/public/MA_optimizer/CMSSW_10_6_8/src/MuAlPhysicsValidation/MuAlRefit/CRAB_MC_Zmumu_ideal_cosmics/D6EF7545-BA2E-034C-A995-C3F54077BF73.root'
                )
                            )

process.demo = cms.EDAnalyzer('Phi_Eta_Analyzer',
        muons = cms.InputTag("muons1Leg","", "RECO")
 )

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('TightMuonProfile.root')
                                   )
process.p = cms.Path(process.demo)
