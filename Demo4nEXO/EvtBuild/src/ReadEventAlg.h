#ifndef EVT_INPUT_ALG
#define EVT_INPUT_ALG
#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include <TTimeStamp.h>

class ReadEventAlg : public AlgBase
{
  public :

    ReadEventAlg(const std::string& name);
    virtual ~ReadEventAlg();

    bool initialize();
    bool execute();
    bool finalize();

  private :

    int m_count;

    std::string  m_hdname;
};
#endif //EVT_INPUT_ALG
