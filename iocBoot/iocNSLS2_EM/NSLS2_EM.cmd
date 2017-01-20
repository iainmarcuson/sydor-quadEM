epicsEnvSet("PREFIX",    "quadEMTest:")
epicsEnvSet("RECORD",    "NSLS2_EM:")
epicsEnvSet("PORT",      "NSLS2_EM")
epicsEnvSet("TEMPLATE",  "NSLS2_EM")
epicsEnvSet("QSIZE",     "20")
epicsEnvSet("RING_SIZE", "10000")
epicsEnvSet("TSPOINTS",  "1000")
epicsEnvSet("MODULE_ID", "0")

# Load asynRecord record
dbLoadRecords("$(ASYN)/db/asynRecord.db", "P=$(PREFIX), R=asyn1,PORT=TCP_Command_$(PORT),ADDR=0,OMAX=256,IMAX=256")

drvNSLS2_EMConfigure("$(PORT)", $(MODULE_ID), $(RING_SIZE))

asynSetTraceIOMask("$(PORT)", 0, 2)
# Uncomment this line to enable asynPrint statements with ASYN_TRACEIO_DRIVER
#asynSetTraceMask("$(PORT)", 0, 9)

dbLoadRecords("$(QUADEM)/db/$(TEMPLATE).template", "P=$(PREFIX), R=$(RECORD), PORT=$(PORT)")

# Comment out this line to suppress loading the plugins
< $(QUADEM)/iocBoot/commonPlugins.cmd

#< $(QUADEM)/iocBoot/saveRestore.cmd

iocInit()

# save settings every thirty seconds
#create_monitor_set("auto_settings.req",30,"P=$(PREFIX), R=$(RECORD)")
