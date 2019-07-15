from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.requestName = 'Phi_Eta_Analyzer_Test'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'

config.section_("Data")
config.Data.inputDataset = '/SingleMuon/Run2018D-22Jan2019-v2/MINIAOD'
config.Data.inputDBS = 'global' # global`
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase =  '/store/user/rymuelle/'
config.Data.publication = False

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
