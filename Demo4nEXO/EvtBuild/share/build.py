import Sniper
import DataRegistritionSvc
import BufferMemMgr
import RootIOSvc
import EvtBuild

Sniper.setLogLevel(3)
top_task = Sniper.TopTask("TopTask")
top_task.setEvtMax(1000)

top_task.createSvc("DataRegistritionSvc")
buf = top_task.createSvc("BufferMemMgr")
buf.property("TimeWindow").set([-0.5, 0.5])

alg1 = top_task.createAlg("EvtBuildAlg")
alg2 = top_task.createAlg("ReadEventAlg")
alg2.property("HeaderName").set("PhyEvt")

# configuration of sub tasks
for source in ["Light", "Charge"]:
  sub_task = top_task.createTask("Task/Task4" + source)

  buf = sub_task.createSvc("BufferMemMgr")
  buf.property("TimeWindow").set([-0.5, 1.0])

  isvc = sub_task.createSvc("RootInputSvc/InputSvc")
  isvc.property("InputFile").set( source + ".root" )

# configuration of output
#osvc = top_task.createSvc("RootOutputSvc/OutputSvc")
#osvc.property("OutputStreams").set( {
#"/Event/Light" : "PhyEvt.root",
#"/Event/Charge" : "PhyEvt.root"
#} )

top_task.run()
