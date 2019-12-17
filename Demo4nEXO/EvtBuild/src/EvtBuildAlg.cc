#include "EvtBuildAlg.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/Incident.h"

DECLARE_ALGORITHM(EvtBuildAlg);

EvtBuildAlg::EvtBuildAlg(const std::string& name)
  : AlgBase(name),
    m_count(0)
{
}

EvtBuildAlg::~EvtBuildAlg()
{
}

bool EvtBuildAlg::initialize()
{
  m_memMgr = SniperPtr<IDataMemMgr>(getParent(), "BufferMemMgr").data();

  return true;
}

bool EvtBuildAlg::execute()
{
  ++m_count;
  LogDebug << "Loop count " << m_count << std::endl;

  if ( m_count == 1 ) { // be sure that the Light/Charge buffers are not empty
    //Incident::fire(*getRoot(), "Task4Light");
    Incident::fire(*getRoot(), "Task4Charge");
  }

  SniperDataPtr<JM::NavBuffer> lightBuf(getParent(), "Task4Light:/Event");
  SniperDataPtr<JM::NavBuffer> chargeBuf(getParent(), "Task4Charge:/Event");

  std::vector<JM::EvtNavigator*> vLight;
  std::vector<JM::EvtNavigator*> vCharge;

  while ( true ) {
    Incident::fire(*getRoot(), "Task4Light");

    JM::EvtNavigator* light = lightBuf->curEvt();
    JM::EvtNavigator* charge = chargeBuf->curEvt();

    LogDebug << "S1 light time " << light->TimeStamp() << " and charge time " << charge->TimeStamp() << std::endl;

    while ( charge->TimeStamp() <= light->TimeStamp() ) {
      Incident::fire(*getRoot(), "Task4Charge");
      charge = chargeBuf->curEvt();
    }

    LogDebug << "S2 light time " << light->TimeStamp() << " and charge time " << charge->TimeStamp() << std::endl;

    TTimeStamp diff = timeDiff(light->TimeStamp(), charge->TimeStamp());
    if ( diff > TTimeStamp(0, 300000000) /*0.3s*/ ) {
      continue;
    }

    // a simple event candidate is found
    vLight.push_back(light);
    vCharge.push_back(charge);

    // whether it's a pileup event
    for ( JM::NavBuffer::Iterator it = lightBuf->current()+1; it != lightBuf->end(); ++it) {
      JM::EvtNavigator* light_more = (*it).get();
      TTimeStamp diff = timeDiff(light_more->TimeStamp(), charge->TimeStamp());
      if ( diff <= TTimeStamp(0, 0) ) {
        break;
      }
      vLight.push_back(light_more);
    }

    for ( JM::NavBuffer::Iterator it = chargeBuf->current()+1; it != chargeBuf->end(); ++it) {
      JM::EvtNavigator* charge_more = (*it).get();
      TTimeStamp diff = timeDiff(vLight.back()->TimeStamp(), charge_more->TimeStamp());
      if ( diff > TTimeStamp(0, 300000000) /*0.3s*/ ) {
        break;
      }
      vCharge.push_back(charge_more);
    }

    break;
  }

  // save to the physics event buffer
  JM::EvtNavigator* phyEvt = new JM::EvtNavigator();
  phyEvt->setTimeStamp(vLight[0]->TimeStamp());
  m_memMgr->adopt( phyEvt, "/Event" );

  // FIXME: multiple headers can be added to the same PATH, but only one can be saved to file
  for ( unsigned int i = 0; i < vLight.size(); ++i ) {
    phyEvt->copyHeader(vLight[i], "/Event/Light");
  }

  for ( unsigned int i = 0; i < vCharge.size(); ++i ) {
    phyEvt->copyHeader(vCharge[i], "/Event/Charge");
  }

  // dump information of the candidate
  LogInfo << "Found a candidate:" << std::endl;
  std::cout << "  Light time  [ ";
  for ( unsigned int i = 0; i < vLight.size(); ++i ) {
    std::cout << vLight[i]->TimeStamp() << "; ";
  }
  std::cout << "]\n  Charge time [ ";
  for ( unsigned int i = 0; i < vCharge.size(); ++i ) {
    std::cout << vCharge[i]->TimeStamp() << "; ";
  }
  std::cout << "]"<< std::endl;

  // in case of a pileup event, move the time-window of lightBuf to the proper place
  for ( unsigned int i = 1; i < vLight.size(); ++i ) {
    Incident::fire(*getRoot(), "Task4Light");
  }

  return true;
}

bool EvtBuildAlg::finalize()
{
  return true;
}

TTimeStamp EvtBuildAlg::timeDiff(const TTimeStamp& t1, const TTimeStamp& t2)
{
  return TTimeStamp(t2.GetSec()-t1.GetSec(), t2.GetNanoSec()-t1.GetNanoSec());
}
