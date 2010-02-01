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

#ifndef __NCTUNS_CONVO_CODE_H__
#define __NCTUNS_CONVO_CODE_H__

#define BITCOUNT(x)	(((BX_(x)+(BX_(x)>>4)) & 0x0F0F0F0F) % 255)
#define BX_(x)		((x) - (((x)>>1)&0x77777777)	\
                             - (((x)>>2)&0x33333333)	\
                             - (((x)>>3)&0x11111111))

struct EncoderLookupEntry {
	char x;
	char y;
	int nextState;
};

struct DecoderLookupEntry {
	char out;
	int nextState;
};

class ConvoCode {
      private:
	int GX, GY, GLen;	// Generator polynomials
	int PX, PY, PLen;	// Punctured patterns
	struct EncoderLookupEntry *encoderLookupTable;
	struct DecoderLookupEntry *decoderLookupTable;
	int encoderTableSize;
	int decoderTableSize;
	int encoderState;
	int *decoderState;

      public:
	 ConvoCode(int _GX, int _GY, int _GLen, int _PX, int _PY,
		   int _PLen);
	~ConvoCode();

	// It's the caller's responsibility to free tables generated by
	// genEncoderLookupTable() and genDecoderLookupTable().
	struct EncoderLookupEntry *genEncoderLookupTable();
	struct DecoderLookupEntry *genDecoderLookupTable();
	void setEncoderLookupTable(struct EncoderLookupEntry *lookupTable);
	void setDecoderLookupTable(struct DecoderLookupEntry *lookupTable);
	void resetEncoderState();
	void resetDecoderState();
	int encode(char *input, char *output, int inputLen);
	int decode(char *input, char *output, int inputLen, int lookahead =
		   0);
//  For develope
//      void setEncoderState(int s) { encoderState = s; }
//      void setDecoderState(int s[]) { for(int i=0;i<64;i++) decoderState[i] = s[i];}

};

#endif				/* __NCTUNS_CONVO_CODE_H__ */
