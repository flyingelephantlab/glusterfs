/*
   Copyright (c) 2007, 2008 Z RESEARCH, Inc. <http://www.zresearch.com>
   This file is part of GlusterFS.

   GlusterFS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.

   GlusterFS is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/


#ifndef _AFR_H
#define _AFR_H

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "scheduler.h"
#include "call-stub.h"

enum {
  AFR_FOP_WRITEV,
  AFR_FOP_FTRUNCATE,
};

/* afr file descriptor structure */
typedef struct _afrfd {
  char *fdstate;
  char *fdsuccess;
  int32_t write;
  int32_t create;
  int32_t rchild;       
  char *path;           /* pathname */
} afrfd_t;

typedef struct _afr_selfheal_private {
  int32_t error, i;
  dir_entry_t *entries;
  int32_t label, dents_count;
  loc_t *loc;
} afr_selfheal_private_t;

typedef struct _afr_selfheal {
  struct list_head clist;
  xlator_t *xl;
  inode_t *inode;
  struct stat stat;
  int32_t repair;
  uint32_t version;
  uint32_t ctime;
  int32_t op_errno;
  dict_t *dict;
} afr_selfheal_t;

typedef struct _afr_local {
  int32_t call_count;
  int32_t op_ret;
  int32_t op_errno;
  int32_t size;
  int32_t flags;
  int32_t latest;
  int32_t stat_child;
  int32_t rmelem_status;
  int32_t child;
  int32_t close;
  uid_t uid, gid;
  ino_t ino;
  off_t offset;
  char *path, *name;
  inode_t *inode;
  call_frame_t *orig_frame;
  fd_t *fd;
  struct list_head *list;
  dict_t *ctx;
  xlator_list_t *xlnodeptr;
  struct timespec *tspec;
  struct stat stbuf;
  struct flock lock, lockp;
  call_stub_t *stub;
  afr_selfheal_t *source, *ashptr;
  struct stat *statptr;
  int32_t shcalled;
  loc_t *loc, *loc2;
  dir_entry_t *entry, *last;;
  int32_t count;
  xlator_t *lock_node;
  int32_t sh_return_error;
  afrfd_t *afrfdp;
  mode_t mode;
  dev_t dev;
  afr_selfheal_private_t *asp;
  uint32_t latest_ctime, latest_version;
  dict_t *latest_xattr;
  loc_t locsrc, locdst;
} afr_local_t;

typedef struct _afr_statfs_local {
  struct statvfs statvfs;
  int32_t op_ret, op_errno;
  int32_t call_count;
  int32_t stat_child;
} afr_statfs_local_t;

/* afr_lock_locak_t used by fops needing to gf_lk */

typedef struct _afr_lock_local {
  /* used by wrft and open-selfheal*/
  fd_t *fd;
  int32_t label;
  int32_t op_errno;
  int32_t op_ret;
  int32_t call_count;
  int32_t error;
  int32_t fop;
  off_t length;
  void *returnfn;
  struct stat stbuf;
  char *locked;

  /* used by wrft */
  struct iovec *vector;
  off_t offset;
  int32_t count;
  /* char *callres; */
  dict_t *req_refs;

  /* used by open selfheal */
  fd_t *shfd;
  loc_t *loc;
  char *writecnt;
  int32_t latest;
  int32_t flags;
  size_t size;
  int32_t uid, gid;
  int32_t sh, shclose, lock, unlock;
} afr_lock_local_t;

typedef enum {
  AFR_WRFT_1,
  AFR_WRFT_2,
  AFR_WRFT_3,
  AFR_WRFT_4,
  AFR_WRFT_5,
} afr_wrft_label_t;

typedef enum {
  AFR_SELFHEAL_1,
  AFR_SELFHEAL_2,
  AFR_SELFHEAL_3,
  AFR_SELFHEAL_4,
  AFR_SELFHEAL_5,
  AFR_SELFHEAL_6,
  AFR_SELFHEAL_7,
  AFR_SELFHEAL_8,
  AFR_SELFHEAL_9,
} afr_selfheal_label_t;

typedef enum {
  AFR_OPEN_1,
  AFR_OPEN_2,
  AFR_OPEN_3,
  AFR_OPEN_4,
  AFR_OPEN_5,
  AFR_OPEN_6,
  AFR_OPEN_7,
  AFR_OPEN_8,
  AFR_OPEN_9,
  AFR_OPEN_10,
  AFR_OPEN_11,
} afr_open_label_t;

typedef struct _pattern_info {
  char *pattern;
  int copies;
} pattern_info_t;

/* afr private structure. initialiazed once per instance of afr initialiazation */
typedef struct _afr_private {
  xlator_t *lock_node;
  int32_t child_count;
  int32_t debug;
  int32_t self_heal;       /* read as 'self heal required' if self_heal == 1 */
  int32_t read_node;
  xlator_t **children;     /* array of pointers, to point to xlator_t object of the child nodes */
  char *state;
  char *xattr_check;
  dict_t **shdict;
} afr_private_t;

#endif
