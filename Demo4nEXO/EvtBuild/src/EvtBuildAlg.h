#ifndef EVT_BUILDING_ALG
#define EVT_BUILDING_ALG
#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "TTimeStamp.h"

class EvtBuildAlg : public AlgBase
{
  public :
    EvtBuildAlg(const std::string& name);
    virtual ~EvtBuildAlg();

    bool initialize();
    bool execute();
    bool finalize();

  private :

    TTimeStamp timeDiff(const TTimeStamp& t1, const TTimeStamp& t2);

    int m_count;
    IDataMemMgr* m_memMgr;
};
#endif //EVT_BUILDING_ALG
