def get_parser():
  import argparse
  parser = argparse.ArgumentParser(description="Run DEMO")
  parser.add_argument("--evtmax", type=int, default=100, help="events to be processed")
  parser.add_argument("--source", type=str, default="PhyEvt", help="the name of the data source (Light or Charge?)")
  return parser

if __name__ == "__main__":

  parser = get_parser()
  args = parser.parse_args()

  filename = args.source + ".root"
  treename = "/Event/" + args.source

  import Sniper
  import BufferMemMgr
  import RootIOSvc
  import EvtBuild
  
  task = Sniper.Task("Task4" + args.source)
  task.setEvtMax(args.evtmax)
  task.setLogLevel(2)
  
  buf = task.createSvc("BufferMemMgr")
  buf.property("TimeWindow").set([0.0, 0.0])
  
  isvc = task.createSvc("RootInputSvc/InputSvc")
  isvc.property("InputFile").set( filename )
  
  alg = task.createAlg("ReadEventAlg")
  alg.property("HeaderName").set(args.source)
  
  task.run()
