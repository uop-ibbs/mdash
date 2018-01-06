# $Id: CMakeLists.txt 125 2017-11-06 14:16:36Z dw $

message("-- Configuring examples")

set(examples
  avp.nc
  avp.out
  avp.parm7
  avp.tor
  hUII.in
  hUII.out
  repex.in.bz2
  repex.out
  tzd.in.gz
  tzd.out
)

install(FILES ${examples} DESTINATION share/doc/mdash-${PROJECT_VERSION}/examples)
