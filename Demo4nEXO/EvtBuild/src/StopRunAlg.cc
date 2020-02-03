#include "StopRunAlg.h"
#include "SniperKernel/SniperRunState.h"
#include "SniperKernel/AlgFactory.h"

DECLARE_ALGORITHM(StopRunAlg);

StopRunAlg::StopRunAlg(const std::string& name)
  : AlgBase(name),
    m_count(0),
    m_mode(0)
{
  declProp("StopMode", m_mode);
}

StopRunAlg::~StopRunAlg()
{
}

bool StopRunAlg::initialize()
{
  return true;
}

bool StopRunAlg::execute()
{
  ++m_count;
  LogDebug << "Loop count " << m_count << std::endl;

  if ( m_count == 3 ) {
      // stop in different ways according to m_mode

      if ( m_mode == 1 ) {
          // stop the eventloop without delay
          getRoot()->stop(Sniper::StopRun::Promptly);
      }
      else if ( m_mode == 2 ) {
          // stop the eventloop until current event is finished
          getRoot()->stop(Sniper::StopRun::Peacefully);
      }
      else if ( m_mode == 3 ) {
          // stop handling current event and continue the next event
          getRoot()->stop(Sniper::StopRun::ThisEvent);
      }

      // else {...} normal mode, do nothing
  }

  return true;
}

bool StopRunAlg::finalize()
{
  return true;
}
