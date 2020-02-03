#ifndef STOP_RUN_ALG_H
#define STOP_RUN_ALG_H

#include "SniperKernel/AlgBase.h"

class StopRunAlg : public AlgBase
{
  public :

    StopRunAlg(const std::string& name);
    virtual ~StopRunAlg();

    bool initialize();
    bool execute();
    bool finalize();

  private :

    int m_count;
    int m_mode;
};
#endif //GEN_EVENT_ALG_H
