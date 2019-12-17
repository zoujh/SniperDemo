#include "ReadEventAlg.h"
#include "Event/DummyHeader.h"
#include "SniperKernel/AlgFactory.h"

DECLARE_ALGORITHM(ReadEventAlg);

ReadEventAlg::ReadEventAlg(const std::string& name)
  : AlgBase(name),
    m_count(0)
{
  declProp("HeaderName", m_hdname);
}

ReadEventAlg::~ReadEventAlg()
{
}

bool ReadEventAlg::initialize()
{
  return true;
}

bool ReadEventAlg::execute()
{
  ++m_count;
  LogDebug << "Loop count " << m_count << std::endl;

  SniperDataPtr<JM::NavBuffer> navBuf(getParent(), "/Event");
  JM::EvtNavigator* nav = navBuf->curEvt();

  if ( m_hdname == "PhyEvt" ) {
    auto vLight = nav->getHeaders("/Event/Light");
    auto vCharge = nav->getHeaders("/Event/Charge");
    LogInfo << "Read a candidate" << std::endl;
    std::cout << "  Light EventID [ ";
    for ( unsigned int i = 0; i < vLight.size(); ++i ) {
      std::cout << vLight[i]->EventID() << "; ";
    }
    std::cout << "]\n  Charge EventID [ ";
    for ( unsigned int i = 0; i < vCharge.size(); ++i ) {
      std::cout << vCharge[i]->EventID() << "; ";
    }
    std::cout << "]"<< std::endl;
  }
  else {
    DEMO::DummyHeader* aHeader = dynamic_cast<DEMO::DummyHeader*>( nav->getHeader("/Event/"+m_hdname) );
    LogDebug << "Get event with event ID " << aHeader->EventID() << std::endl;
  }

  return true;
}

bool ReadEventAlg::finalize()
{
  return true;
}
