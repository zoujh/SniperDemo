def get_parser():
  import argparse
  parser = argparse.ArgumentParser(description="Run DEMO")
  parser.add_argument("--evtmax", type=int, default=100, help="events to be processed")
  parser.add_argument("--source", type=str, default="Light", help="the name of the data source (Light or Charge?)")
  return parser

if __name__ == "__main__":

  parser = get_parser()
  args = parser.parse_args()

  filename = args.source + ".root"
  treename = "/Event/" + args.source

  import Sniper
  import DataRegistritionSvc
  import BufferMemMgr
  import RootIOSvc
  import EvtBuild
  
  task = Sniper.Task("Task4" + args.source)
  task.setEvtMax(args.evtmax)
  task.setLogLevel(2)
  
  task.createSvc("DataRegistritionSvc")
  buf = task.createSvc("BufferMemMgr")
  buf.property("TimeWindow").set([0.0, 0.0])
  
  osvc = task.createSvc("RootOutputSvc/OutputSvc")
  osvc.property("OutputStreams").set( { treename : filename } )
  
  alg = task.createAlg("GenEventAlg")
  alg.property("HeaderName").set(args.source)
  
  task.run()
