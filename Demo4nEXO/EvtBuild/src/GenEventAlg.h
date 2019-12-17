#ifndef GEN_EVENT_ALG_H
#define GEN_EVENT_ALG_H

#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include <TTimeStamp.h>

class GenEventAlg : public AlgBase
{
  public :

    GenEventAlg(const std::string& name);
    virtual ~GenEventAlg();

    bool initialize();
    bool execute();
    bool finalize();

  private :

    int m_count;

    IDataMemMgr* m_memMgr;

    TTimeStamp   m_time;
    std::string  m_hdname;
};
#endif //GEN_EVENT_ALG_H
