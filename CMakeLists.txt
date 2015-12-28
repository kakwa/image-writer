cmake_minimum_required (VERSION 2.6)

project (iwh NONE)
enable_language(C)


# Project version (sematic versionning)
set(iwh_VERSION_MAJOR 2)
set(iwh_VERSION_MINOR 2)
set(iwh_VERSION_PATCH 5)

set(iwh_VERSION ${iwh_VERSION_MAJOR}.${iwh_VERSION_MINOR}.${iwh_VERSION_PATCH})
# set version as a definition
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -lacl -DVERSION='\"${iwh_VERSION}\"'")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES external-build)

# Options
option(DEBUG     "compile with debug symbol"          OFF)
option(STATIC    "compile statically"                 OFF)
option(USE_CLANG "build application with clang"       OFF)
option(USE_GCC   "build application with gcc"         OFF)
option(FORCELE   "force little endian architecture"   OFF)

if(USE_CLANG)
    set(CMAKE_CC_COMPILER  "clang"  )
endif(USE_CLANG)

if(USE_GCC)
    set(CMAKE_CC_COMPILER  "gcc")
endif(USE_GCC)

if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
    set(CMAKE_BUILD_TYPE Debug)
endif(DEBUG)

if(STATIC)
    set(SHARED "")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
else(STATIC)
    IF(${CMAKE_SYSTEM_NAME}    MATCHES "Darwin")
        set(SHARED "")
    ELSE(${CMAKE_SYSTEM_NAME}  MATCHES "Darwin")
        set(SHARED "SHARED")
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
endif(STATIC)

if(UNIX)
  link_libraries(m)
endif(UNIX)

IF(NOT FORCELE)
    include(TestBigEndian)
    TEST_BIG_ENDIAN(BIGENDIAN)
    IF(${BIGENDIAN})
        add_definitions(-DWORDS_BIGENDIAN)
    ENDIF(${BIGENDIAN})
endif(NOT FORCELE)

# linking directories
LINK_DIRECTORIES(
    ${CMAKE_BINARY_DIR}/
    /usr/local/lib
    /sw/lib/
    /usr/lib/
    ${ARGPLINKDIR}
    ${LIBICONVLINKDIR}
)

# headers directories
include_directories(
    ./sys/
    ./include/
    /usr/include/ 
    /sw/include/
    ${ARGPHEADERDIR}
    ${LIBICONVHEADERDIR}
)

# Compile the library
add_library(iwh
    ${SHARED}
    libatalk
    libatalk/acl/unix.c
    libatalk/atp
    libatalk/atp/atp_sresp.c
    libatalk/atp/atp_bufs.c
    libatalk/atp/atp_open.c
    libatalk/atp/atp_rreq.c
    libatalk/atp/atp_rsel.c
    libatalk/atp/atp_sreq.c
    libatalk/atp/atp_packet.c
    libatalk/atp/atp_close.c
    libatalk/atp/atp_rresp.c
    libatalk/atp/atp_internals.h
    libatalk/dsi
    libatalk/dsi/dsi_init.c
    libatalk/dsi/dsi_private.h
    libatalk/dsi/dsi_read.c
    libatalk/dsi/README
    libatalk/dsi/dsi_tcp.c
    libatalk/dsi/dsi_write.c
    libatalk/dsi/dsi_close.c
    libatalk/dsi/dsi_tickle.c
    libatalk/dsi/dsi_getsess.c
    libatalk/dsi/dsi_getstat.c
    libatalk/dsi/dsi_opensess.c
    libatalk/dsi/dsi_stream.c
    libatalk/dsi/dsi_cmdreply.c
    libatalk/dsi/dsi_attn.c
    libatalk/nbp
    libatalk/nbp/nbp_lkup.c
    libatalk/nbp/nbp_util.c
    libatalk/nbp/nbp_unrgstr.c
    libatalk/nbp/nbp_rgstr.c
    libatalk/nbp/nbp_conf.h
    libatalk/tdb
    libatalk/tdb/tdb.c
    libatalk/tdb/spinlock.c
    libatalk/tdb/spinlock.h
    libatalk/vfs
    libatalk/vfs/ea.c
    libatalk/vfs/acl.c
    libatalk/vfs/vfs.c
    libatalk/vfs/ea_sys.c
    libatalk/vfs/sys_ea.c
    libatalk/vfs/unix.c
    libatalk/cnid
    libatalk/cnid/cdb
    libatalk/cnid/cdb/cnid_cdb_close.c
    libatalk/cnid/cdb/cnid_cdb_lookup.c
    libatalk/cnid/cdb/README
    libatalk/cnid/cdb/cnid_cdb_private.h
    libatalk/cnid/cdb/cnid_cdb_add.c
    libatalk/cnid/cdb/cnid_cdb_get.c
    libatalk/cnid/cdb/cnid_cdb.h
    libatalk/cnid/cdb/cnid_cdb_update.c
    libatalk/cnid/cdb/cnid_cdb_meta.c
    libatalk/cnid/cdb/cnid_cdb_meta.h
    libatalk/cnid/cdb/cnid_cdb_open.c
    libatalk/cnid/cdb/cnid_cdb_rebuild_add.c
    libatalk/cnid/cdb/cnid_cdb_delete.c
    libatalk/cnid/cdb/cnid_cdb_resolve.c
    libatalk/cnid/cdb/cnid_cdb_nextid.c
    libatalk/cnid/dbd
    libatalk/cnid/dbd/cnid_dbd.c
    libatalk/cnid/dbd/cnid_dbd.h
    libatalk/cnid/tdb
    libatalk/cnid/tdb/cnid_tdb_open.c
    libatalk/cnid/tdb/cnid_tdb_add.c
    libatalk/cnid/tdb/cnid_tdb_get.c
    libatalk/cnid/tdb/cnid_tdb_delete.c
    libatalk/cnid/tdb/README
    libatalk/cnid/tdb/cnid_tdb_nextid.c
    libatalk/cnid/tdb/cnid_tdb_close.c
    libatalk/cnid/tdb/cnid_tdb_lookup.c
    libatalk/cnid/tdb/cnid_tdb.h
    libatalk/cnid/tdb/cnid_tdb_update.c
    libatalk/cnid/tdb/cnid_tdb_resolve.c
    libatalk/cnid/last
    libatalk/cnid/last/README
    libatalk/cnid/last/cnid_last.c
    libatalk/cnid/last/cnid_last.h
    libatalk/cnid/README
    libatalk/cnid/cnid.c
    libatalk/cnid/cnid_init.c
    libatalk/util
    libatalk/util/bprint.c
    libatalk/util/ftw.c
    libatalk/util/queue.c
    libatalk/util/strlcpy.c
    libatalk/util/strdicasecmp.c
    libatalk/util/server_lock.c
    libatalk/util/strcasestr.c
    libatalk/util/fault.c
    libatalk/util/module.c
    libatalk/util/server_ipc.c
    libatalk/util/cnid.c
    libatalk/util/atalk_addr.c
    libatalk/util/unix.c
    libatalk/util/server_child.c
    libatalk/util/logger.c
    libatalk/util/locking.c
    libatalk/util/getiface.c
    libatalk/util/volinfo.c
    libatalk/util/socket.c
    libatalk/dummy.c
    libatalk/netddp
    libatalk/netddp/netddp_open.c
    libatalk/netddp/netddp_sendto.c
    libatalk/netddp/netddp_recvfrom.c
    libatalk/adouble
    libatalk/adouble/ad_write.c
    libatalk/adouble/ad_attr.c
    libatalk/adouble/ad_date.c
    libatalk/adouble/ad_sendfile.c
    libatalk/adouble/ad_lock.c
    libatalk/adouble/ad_mmap.c
    libatalk/adouble/ad_open.c
    libatalk/adouble/ad_read.c
    libatalk/adouble/ad_size.c
    libatalk/adouble/ad_flush.c
    libatalk/adouble/ad_private.h
    libatalk/unicode
    libatalk/unicode/util_unistr.c
    libatalk/unicode/charsets
    libatalk/unicode/charsets/mac_hebrew.c
    libatalk/unicode/charsets/mac_hebrew.h
    libatalk/unicode/charsets/mac_japanese.c
    libatalk/unicode/charsets/mac_japanese.h
    libatalk/unicode/charsets/generic_mb.c
    libatalk/unicode/charsets/generic_mb.h
    libatalk/unicode/charsets/mac_centraleurope.c
    libatalk/unicode/charsets/mac_centraleurope.h
    libatalk/unicode/charsets/mac_roman.c
    libatalk/unicode/charsets/mac_roman.h
    libatalk/unicode/charsets/mac_chinese_simp.c
    libatalk/unicode/charsets/mac_chinese_simp.h
    libatalk/unicode/charsets/mac_chinese_trad.c
    libatalk/unicode/charsets/mac_chinese_trad.h
    libatalk/unicode/charsets/mac_cyrillic.c
    libatalk/unicode/charsets/mac_cyrillic.h
    libatalk/unicode/charsets/generic_cjk.c
    libatalk/unicode/charsets/generic_cjk.h
    libatalk/unicode/charsets/mac_korean.c
    libatalk/unicode/charsets/mac_korean.h
    libatalk/unicode/charsets/mac_turkish.c
    libatalk/unicode/charsets/mac_turkish.h
    libatalk/unicode/charsets/mac_greek.c
    libatalk/unicode/charsets/mac_greek.h
    libatalk/unicode/charcnv.c
    libatalk/unicode/byteorder.h
    libatalk/unicode/utf8.c
    libatalk/unicode/precompose.h
    libatalk/unicode/iconv.c
    libatalk/unicode/utf16_case.c
    libatalk/unicode/utf16_casetable.h
    libatalk/bstring
    libatalk/bstring/bstradd.c
    libatalk/bstring/bstrlib.c
)

set_target_properties(iwh 
    PROPERTIES 
    VERSION ${iwh_VERSION} 
    SOVERSION ${iwh_VERSION_MAJOR}
)

# Compile the executables
add_executable(iwh-nbplkup bin/nbp/nbplkup.c)
target_link_libraries(iwh-nbplkup iwh) 

add_executable(iwh-pap bin/pap/pap.c)
target_link_libraries(iwh-pap iwh) 

add_executable(iwh-papstatus bin/pap/papstatus.c)
target_link_libraries(iwh-papstatus iwh) 

add_executable(iwh-atalkd 
    bin/atalkd/aep.c
    bin/atalkd/nbp.c
    bin/atalkd/zip.c
    bin/atalkd/route.c
    bin/atalkd/config.c
    bin/atalkd/main.c
    bin/atalkd/rtmp.c
    bin/atalkd/multicast.c
)

target_link_libraries(iwh-atalkd iwh) 

# install binaries and library
INSTALL(TARGETS iwh iwh-nbplkup iwh-pap iwh-papstatus iwh-atalkd ${MEMSTREAMLIB}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
