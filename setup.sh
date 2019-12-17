source /cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc494/Pre-Release/J19v1r0-Pre3/setup.sh
ThisScriptName=`readlink -f ${BASH_SOURCE[0]}`
ThisScriptPath=`dirname "$ThisScriptName"`
export CMTPROJECTPATH=$ThisScriptPath:$CMTPROJECTPATH

pushd $ThisScriptPath/Demo4nEXO/EvtBuild/cmt
if [ ! -e setup.sh ]; then
  cmt config
fi
source setup.sh
popd
