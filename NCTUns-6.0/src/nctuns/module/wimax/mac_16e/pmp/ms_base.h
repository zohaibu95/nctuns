/*
 * Copyright (c) from 2000 to 2009
 * 
 * Network and System Laboratory 
 * Department of Computer Science 
 * College of Computer Science
 * National Chiao Tung University, Taiwan
 * All Rights Reserved.
 * 
 * This source code file is part of the NCTUns 6.0 network simulator.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation is hereby granted (excluding for commercial or
 * for-profit use), provided that both the copyright notice and this
 * permission notice appear in all copies of the software, derivative
 * works, or modified versions, and any portions thereof, and that
 * both notices appear in supporting documentation, and that credit
 * is given to National Chiao Tung University, Taiwan in all publications 
 * reporting on direct or indirect use of this code or its derivatives.
 *
 * National Chiao Tung University, Taiwan makes no representations 
 * about the suitability of this software for any purpose. It is provided 
 * "AS IS" without express or implied warranty.
 *
 * A Web site containing the latest NCTUns 6.0 network simulator software 
 * and its documentations is set up at http://NSL.csie.nctu.edu.tw/nctuns.html.
 *
 * Project Chief-Technology-Officer
 * 
 * Prof. Shie-Yuan Wang <shieyuan@csie.nctu.edu.tw>
 * National Chiao Tung University, Taiwan
 *
 * 09/01/2009
 */

#ifndef __NCTUNS_80216E_MS_BASE_H__
#define __NCTUNS_80216E_MS_BASE_H__

#include "../mac802_16e.h"

using namespace mobileMac80216e;

namespace mobileMSbase {
	class mac802_16MSbase : public mac802_16e {
		public:
			uint16_t    BasicCID;
			uint16_t    PriCID;
			uint16_t    SecCID;
			uint8_t     AttrARQ;

		public:
			explicit mac802_16MSbase();
			explicit mac802_16MSbase(uint32_t, uint32_t, plist*, const char*);
	};
}

#endif /* __NCTUNS_80216E_MS_BASE_H__ */
