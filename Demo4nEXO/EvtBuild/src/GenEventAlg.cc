#include "GenEventAlg.h"
#include "Event/DummyHeader.h"
#include "SniperKernel/AlgFactory.h"
#include <stdlib.h>
#include <time.h>

DECLARE_ALGORITHM(GenEventAlg);

GenEventAlg::GenEventAlg(const std::string& name)
  : AlgBase(name),
    m_count(0),
    m_time(0, 0)
{
  declProp("HeaderName", m_hdname);
}

GenEventAlg::~GenEventAlg()
{
}

bool GenEventAlg::initialize()
{
  srand(time(NULL));

  m_memMgr = SniperPtr<IDataMemMgr>(getParent(), "BufferMemMgr").data();

  return true;
}

bool GenEventAlg::execute()
{
  ++m_count;
  LogDebug << "Loop count " << m_count << std::endl;

  JM::EvtNavigator* nav = new JM::EvtNavigator();

  int r = rand()%9 + 1;
  int nanoSec = r * 100000000;  // 0.1 - 0.9s
  m_time.Add(TTimeStamp(0, nanoSec));
  nav->setTimeStamp(m_time);

  DEMO::DummyHeader* aHeader = new DEMO::DummyHeader();
  aHeader->setEventID(m_count);

  nav->addHeader("/Event/"+m_hdname, aHeader);

  m_memMgr->adopt( nav, "/Event" );
  LogDebug << "Save event with event ID " << aHeader->EventID() << std::endl;

  return true;
}

bool GenEventAlg::finalize()
{
  return true;
}
