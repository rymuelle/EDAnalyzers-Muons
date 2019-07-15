# EDAnalyzers-Muons
crab stuff: https://uscms.org/uscms_at_work/physics/computing/setup/batch_systems.shtml#condor_1
edmDumpEventContent root://cmsxrootd.fnal.gov///store/data/Run2018D/SingleMuon/ALCARECO/MuAlCalIsolatedMu-PromptReco-v2/000/325/101/00000/A08AC773-2F42-744F-A8BB-3F580508181B.root

vector<reco::Muon>                    "ALCARECOMuAlCalIsolatedMu"   "SelectedMuons"   "RECO"

 dasgoclient -query="file dataset=/SingleMuon/Run2018D-MuAlCalIsolatedMu-PromptReco-v2/ALCARECO"

 For crab:

cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.sh
voms-proxy-init -voms cms

crab submit -c <crab_cfg>.py --dryrun