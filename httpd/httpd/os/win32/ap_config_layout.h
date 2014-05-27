/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file win32/win32_config_layout.h
 * @brief This provides layout definitions for non-autoconf-based Windows
 * builds, and is copied to include/ap_config_layout.h during the build.
 */

#ifndef AP_CONFIG_LAYOUT_H
#define AP_CONFIG_LAYOUT_H

/* Check for definition of DEFAULT_REL_RUNTIMEDIR */
#ifndef DEFAULT_REL_RUNTIMEDIR
#define DEFAULT_REL_RUNTIMEDIR "logs"
#endif

/* SuExec root directory */
#undef AP_DOC_ROOT

/* Enable DTrace probes */
#undef AP_ENABLE_DTRACE

/* Allow modules to run hook after a fatal exception */
#undef AP_ENABLE_EXCEPTION_HOOK

/* Allow IPv4 connections on IPv6 listening sockets */
#undef AP_ENABLE_V4_MAPPED

/* Minimum allowed GID */
#undef AP_GID_MIN

/* Enable the APR hook probes capability, reading from ap_hook_probes.h */
#undef AP_HOOK_PROBES_ENABLED

/* User allowed to call SuExec */
#undef AP_HTTPD_USER

/* SuExec log file */
#undef AP_LOG_EXEC

/* Listening sockets are non-blocking when there are more than 1 */
#undef AP_NONBLOCK_WHEN_MULTI_LISTEN

/* safe shell path for SuExec */
#undef AP_SAFE_PATH

/* umask for suexec'd process */
#undef AP_SUEXEC_UMASK

/* Location of the MIME types config file, relative to the Apache root
   directory */
#undef AP_TYPES_CONFIG_FILE

/* Minimum allowed UID */
#undef AP_UID_MIN

/* User subdirectory */
#undef AP_USERDIR_SUFFIX

/* Using autoconf to configure Apache */
#undef AP_USING_AUTOCONF

/* Define to 1 if you have the `bindprocessor' function. */
#undef HAVE_BINDPROCESSOR

/* Define to 1 if you have the <bstring.h> header file. */
#undef HAVE_BSTRING_H

/* Define if distcache support is enabled */
#undef HAVE_DISTCACHE

/* Define to 1 if you have the <distcache/dc_client.h> header file. */
#undef HAVE_DISTCACHE_DC_CLIENT_H

/* Define to 1 if you have the `ENGINE_init' function. */
#undef HAVE_ENGINE_INIT

/* Define to 1 if you have the `ENGINE_load_builtin_engines' function. */
#undef HAVE_ENGINE_LOAD_BUILTIN_ENGINES

/* Define to 1 if you have the `epoll_create' function. */
#undef HAVE_EPOLL_CREATE

/* Define to 1 if you have the `fopen64' function. */
#undef HAVE_FOPEN64

/* Define to 1 if you have the `getgrnam' function. */
#undef HAVE_GETGRNAM

/* Define to 1 if you have the `getloadavg' function. */
#undef HAVE_GETLOADAVG

/* Define to 1 if you have the `getpgid' function. */
#undef HAVE_GETPGID

/* Define to 1 if you have the `getpwnam' function. */
#undef HAVE_GETPWNAM

/* Define if you have gettid() */
#undef HAVE_GETTID

/* Define if struct tm has a tm_gmtoff field */
#undef HAVE_GMTOFF

/* Define to 1 if you have the <grp.h> header file. */
#undef HAVE_GRP_H

/* Define to 1 if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* Define to 1 if you have the `killpg' function. */
#undef HAVE_KILLPG

/* Define to 1 if you have the `kqueue' function. */
#undef HAVE_KQUEUE

/* Define to 1 if you have the <limits.h> header file. */
#undef HAVE_LIMITS_H

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Define if OpenSSL is available */
#undef HAVE_OPENSSL

/* Define to 1 if you have the <openssl/engine.h> header file. */
#undef HAVE_OPENSSL_ENGINE_H

/* Define to 1 if you have the `port_create' function. */
#undef HAVE_PORT_CREATE

/* Define to 1 if you have the `prctl' function. */
#undef HAVE_PRCTL

/* Define to 1 if you have the <priv.h> header file. */
#undef HAVE_PRIV_H

/* Define to 1 if you have the `pthread_kill' function. */
#undef HAVE_PTHREAD_KILL

/* Define to 1 if you have the <pwd.h> header file. */
#undef HAVE_PWD_H

/* Define to 1 if you have the `setsid' function. */
#undef HAVE_SETSID

/* Define to 1 if you have the `SSLeay_version' function. */
#undef HAVE_SSLEAY_VERSION

/* Define to 1 if you have the `SSL_CTX_new' function. */
#undef HAVE_SSL_CTX_NEW

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if you have the `syslog' function. */
#undef HAVE_SYSLOG

/* Define to 1 if you have the <sys/ipc.h> header file. */
#undef HAVE_SYS_IPC_H

/* Define to 1 if you have the <sys/loadavg.h> header file. */
#undef HAVE_SYS_LOADAVG_H

/* Define to 1 if you have the <sys/prctl.h> header file. */
#undef HAVE_SYS_PRCTL_H

/* Define to 1 if you have the <sys/processor.h> header file. */
#undef HAVE_SYS_PROCESSOR_H

/* Define to 1 if you have the <sys/resource.h> header file. */
#undef HAVE_SYS_RESOURCE_H

/* Define to 1 if you have the <sys/sdt.h> header file. */
#undef HAVE_SYS_SDT_H

/* Define to 1 if you have the <sys/sem.h> header file. */
#undef HAVE_SYS_SEM_H

/* Define to 1 if you have the <sys/socket.h> header file. */
#undef HAVE_SYS_SOCKET_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/times.h> header file. */
#undef HAVE_SYS_TIMES_H

/* Define to 1 if you have the <sys/time.h> header file. */
#undef HAVE_SYS_TIME_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#undef HAVE_SYS_WAIT_H

/* Define to 1 if you have the `timegm' function. */
#undef HAVE_TIMEGM

/* Define to 1 if you have the `times' function. */
#undef HAVE_TIMES

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Root directory of the Apache install area */
#undef HTTPD_ROOT

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Location of the config file, relative to the Apache root directory */
#undef SERVER_CONFIG_FILE

/* This platform doesn't suffer from the thundering herd problem */
#undef SINGLE_LISTEN_UNSERIALIZED_ACCEPT

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Path to suexec binary */
#undef SUEXEC_BIN

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# undef _ALL_SOURCE
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# undef _GNU_SOURCE
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# undef _POSIX_PTHREAD_SEMANTICS
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# undef _TANDEM_SOURCE
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# undef __EXTENSIONS__
#endif


/* Define to 1 if on MINIX. */
#undef _MINIX

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
#undef _POSIX_1_SOURCE

/* Define to 1 if you need to in order for `stat' and other things to work. */
#undef _POSIX_SOURCE

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define to 'int' if <sys/resource.h> doesn't define it for us */
#undef rlim_t


#endif /* AP_CONFIG_LAYOUT_H */
