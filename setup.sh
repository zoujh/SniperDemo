source /cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc494/Pre-Release/J19v1r0-Pre3/setup.sh
export CMTPROJECTPATH=/home/bes/zoujh/workfs/TestSniper:$CMTPROJECTPATH

pushd /home/bes/zoujh/workfs/TestSniper/Demo4nEXO/EvtBuild/cmt
if [ ! -e setup.sh ]; then
  cmt config
fi
source setup.sh
popd
