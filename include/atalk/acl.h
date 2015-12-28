/*
   Copyright (c) 2009 Frank Lahm <franklahm@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */


#define O_NETATALK_ACL (O_NOFOLLOW << 1)

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/stat.h>

#define chmod_acl posix_chmod
#define fchmod_acl posix_fchmod

extern int posix_chmod(const char *name, mode_t mode);
extern int posix_fchmod(int fd, mode_t mode);

