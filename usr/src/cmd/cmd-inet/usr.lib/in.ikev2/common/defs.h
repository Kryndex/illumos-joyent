
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2010 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright 2014 Jason King.
 */

#ifndef _IKEV2D_DEFS_H
#define _IKEV2D_DEFS_H

#include <sys/types.h>
#include <sys/socket.h>

#if 0
#include <ikedoor.h>
#include <cryptoutil.h>
#endif

#include <security/cryptoki.h>
#include <stdio.h>
#include <assert.h>
#include <umem.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef SOCKADDR_U_T
#define	SOCKADDR_U_T
typedef union sockaddr_u_s {
	struct sockaddr_storage *sau_ss;
	struct sockaddr_in	*sau_sin;
	struct sockaddr_in6	*sau_sin6;
} sockaddr_u_t;
#endif /* SOCKADDR_U_T */

/*
 * Compare two AF_INET{,6} sockaddrs (no port).  Assume sockaddr_storage
 * pointers are passed, and also verifies the address families match and
 * are either AF_INET or AF_INET6.
 */
#define SA_ADDR_EQ(sa1, sa2)                                            \
        (((sa1)->ss_family == (sa2)->ss_family) &&                      \
            ((((sa1)->ss_family == AF_INET) &&                          \
                ((struct sockaddr_in *)(sa1))->sin_addr.s_addr ==       \
                ((struct sockaddr_in *)(sa2))->sin_addr.s_addr) ||      \
                ((sa1)->ss_family == AF_INET6) &&                       \
                IN6_ARE_ADDR_EQUAL(&((struct sockaddr_in6 *)(sa1))->sin6_addr,\
                    &((struct sockaddr_in6 *)(sa2))->sin6_addr)))

/*
 * Compare two AF_INET{,6} sockaddr ports.  Exploit the identical offsets for
 * sin_port/sin6_port.  (Does not check sockaddr families a priori.)
 */
#define SA_PORT_EQ(sa1, sa2) (((struct sockaddr_in *)(sa1))->sin_port == \
            ((struct sockaddr_in *)(sa2))->sin_port)

/*
 * Compare two AF_INET{,6} sockaddrs (including ports).  Exploit the
 * identical offsets for sin_port/sin6_port.
 */
#define SA_FULL_EQ(sa1, sa2) (SA_ADDR_EQ(sa1, sa2) && SA_PORT_EQ(sa1, sa2))


#ifdef  __cplusplus
}
#endif

#endif  /* _IKEV2D_DEFS_H */

