/*
 * Copyright (c) 2015, Joseph deBlaquiere
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "big32.h"

#if 1
const uint16_t div_lut_5_16[1024] = { 
	0x0400, 0x03E0, 0x03C3, 0x03A8, 0x038E, 0x0375, 0x035E, 0x0348, 
	0x0333, 0x031F, 0x030C, 0x02FA, 0x02E8, 0x02D8, 0x02C8, 0x02B9, 
	0x02AA, 0x029C, 0x028F, 0x0282, 0x0276, 0x026A, 0x025E, 0x0253, 
	0x0249, 0x023E, 0x0234, 0x022B, 0x0222, 0x0219, 0x0210, 0x0208, 
	0x0420, 0x0400, 0x03E1, 0x03C5, 0x03AA, 0x0391, 0x0379, 0x0362, 
	0x034C, 0x0338, 0x0324, 0x0311, 0x0300, 0x02EE, 0x02DE, 0x02CE, 
	0x02C0, 0x02B1, 0x02A3, 0x0296, 0x0289, 0x027D, 0x0271, 0x0266, 
	0x025B, 0x0250, 0x0246, 0x023C, 0x0233, 0x0229, 0x0221, 0x0218, 
	0x0440, 0x041F, 0x0400, 0x03E2, 0x03C7, 0x03AC, 0x0394, 0x037C, 
	0x0366, 0x0351, 0x033C, 0x0329, 0x0317, 0x0305, 0x02F4, 0x02E4, 
	0x02D5, 0x02C6, 0x02B8, 0x02AA, 0x029D, 0x0290, 0x0284, 0x0279, 
	0x026D, 0x0262, 0x0258, 0x024E, 0x0244, 0x023A, 0x0231, 0x0228, 
	0x0460, 0x043E, 0x041E, 0x0400, 0x03E3, 0x03C8, 0x03AF, 0x0396, 
	0x0380, 0x036A, 0x0355, 0x0341, 0x032E, 0x031C, 0x030B, 0x02FA, 
	0x02EA, 0x02DB, 0x02CC, 0x02BE, 0x02B1, 0x02A4, 0x0297, 0x028B, 
	0x0280, 0x0274, 0x0269, 0x025F, 0x0255, 0x024B, 0x0242, 0x0238, 
	0x0480, 0x045D, 0x043C, 0x041D, 0x0400, 0x03E4, 0x03CA, 0x03B1, 
	0x0399, 0x0383, 0x036D, 0x0359, 0x0345, 0x0333, 0x0321, 0x0310, 
	0x0300, 0x02F0, 0x02E1, 0x02D2, 0x02C4, 0x02B7, 0x02AA, 0x029E, 
	0x0292, 0x0286, 0x027B, 0x0270, 0x0266, 0x025C, 0x0252, 0x0249, 
	0x04A0, 0x047C, 0x045A, 0x043A, 0x041C, 0x0400, 0x03E5, 0x03CB, 
	0x03B3, 0x039C, 0x0386, 0x0371, 0x035D, 0x0349, 0x0337, 0x0326, 
	0x0315, 0x0305, 0x02F5, 0x02E6, 0x02D8, 0x02CA, 0x02BD, 0x02B0, 
	0x02A4, 0x0298, 0x028D, 0x0282, 0x0277, 0x026D, 0x0263, 0x0259, 
	0x04C0, 0x049B, 0x0478, 0x0457, 0x0438, 0x041B, 0x0400, 0x03E5, 
	0x03CC, 0x03B5, 0x039E, 0x0388, 0x0374, 0x0360, 0x034D, 0x033B, 
	0x032A, 0x031A, 0x030A, 0x02FA, 0x02EC, 0x02DE, 0x02D0, 0x02C3, 
	0x02B6, 0x02AA, 0x029E, 0x0293, 0x0288, 0x027D, 0x0273, 0x0269, 
	0x04E0, 0x04BA, 0x0496, 0x0475, 0x0455, 0x0437, 0x041A, 0x0400, 
	0x03E6, 0x03CE, 0x03B6, 0x03A0, 0x038B, 0x0377, 0x0364, 0x0351, 
	0x0340, 0x032F, 0x031E, 0x030F, 0x0300, 0x02F1, 0x02E3, 0x02D6, 
	0x02C9, 0x02BC, 0x02B0, 0x02A4, 0x0299, 0x028E, 0x0284, 0x0279, 
	0x0500, 0x04D9, 0x04B4, 0x0492, 0x0471, 0x0453, 0x0435, 0x041A, 
	0x0400, 0x03E7, 0x03CF, 0x03B8, 0x03A2, 0x038E, 0x037A, 0x0367, 
	0x0355, 0x0343, 0x0333, 0x0323, 0x0313, 0x0304, 0x02F6, 0x02E8, 
	0x02DB, 0x02CE, 0x02C2, 0x02B6, 0x02AA, 0x029F, 0x0294, 0x028A, 
	0x0520, 0x04F8, 0x04D2, 0x04AF, 0x048E, 0x046E, 0x0450, 0x0434, 
	0x0419, 0x0400, 0x03E7, 0x03D0, 0x03BA, 0x03A4, 0x0390, 0x037D, 
	0x036A, 0x0358, 0x0347, 0x0337, 0x0327, 0x0318, 0x0309, 0x02FB, 
	0x02ED, 0x02E0, 0x02D3, 0x02C7, 0x02BB, 0x02B0, 0x02A5, 0x029A, 
	0x0540, 0x0517, 0x04F0, 0x04CC, 0x04AA, 0x048A, 0x046B, 0x044E, 
	0x0433, 0x0418, 0x0400, 0x03E8, 0x03D1, 0x03BB, 0x03A6, 0x0393, 
	0x0380, 0x036D, 0x035C, 0x034B, 0x033B, 0x032B, 0x031C, 0x030D, 
	0x0300, 0x02F2, 0x02E5, 0x02D8, 0x02CC, 0x02C1, 0x02B5, 0x02AA, 
	0x0560, 0x0536, 0x050F, 0x04EA, 0x04C7, 0x04A6, 0x0486, 0x0469, 
	0x044C, 0x0431, 0x0418, 0x0400, 0x03E8, 0x03D2, 0x03BD, 0x03A8, 
	0x0395, 0x0382, 0x0370, 0x035F, 0x034E, 0x033E, 0x032F, 0x0320, 
	0x0312, 0x0304, 0x02F7, 0x02EA, 0x02DD, 0x02D1, 0x02C6, 0x02BA, 
	0x0580, 0x0555, 0x052D, 0x0507, 0x04E3, 0x04C1, 0x04A1, 0x0483, 
	0x0466, 0x044A, 0x0430, 0x0417, 0x0400, 0x03E9, 0x03D3, 0x03BE, 
	0x03AA, 0x0397, 0x0385, 0x0373, 0x0362, 0x0352, 0x0342, 0x0333, 
	0x0324, 0x0316, 0x0308, 0x02FB, 0x02EE, 0x02E2, 0x02D6, 0x02CB, 
	0x05A0, 0x0574, 0x054B, 0x0524, 0x0500, 0x04DD, 0x04BC, 0x049D, 
	0x0480, 0x0463, 0x0449, 0x042F, 0x0417, 0x0400, 0x03E9, 0x03D4, 
	0x03C0, 0x03AC, 0x0399, 0x0387, 0x0376, 0x0365, 0x0355, 0x0345, 
	0x0336, 0x0328, 0x031A, 0x030D, 0x0300, 0x02F3, 0x02E7, 0x02DB, 
	0x05C0, 0x0593, 0x0569, 0x0541, 0x051C, 0x04F9, 0x04D7, 0x04B7, 
	0x0499, 0x047C, 0x0461, 0x0447, 0x042E, 0x0416, 0x0400, 0x03EA, 
	0x03D5, 0x03C1, 0x03AE, 0x039B, 0x0389, 0x0378, 0x0368, 0x0358, 
	0x0349, 0x033A, 0x032C, 0x031E, 0x0311, 0x0304, 0x02F7, 0x02EB, 
	0x05E0, 0x05B2, 0x0587, 0x055F, 0x0538, 0x0514, 0x04F2, 0x04D2, 
	0x04B3, 0x0495, 0x0479, 0x045F, 0x0445, 0x042D, 0x0416, 0x0400, 
	0x03EA, 0x03D6, 0x03C2, 0x03AF, 0x039D, 0x038C, 0x037B, 0x036B, 
	0x035B, 0x034C, 0x033D, 0x032F, 0x0322, 0x0314, 0x0308, 0x02FB, 
	0x0600, 0x05D1, 0x05A5, 0x057C, 0x0555, 0x0530, 0x050D, 0x04EC, 
	0x04CC, 0x04AE, 0x0492, 0x0477, 0x045D, 0x0444, 0x042C, 0x0415, 
	0x0400, 0x03EB, 0x03D7, 0x03C3, 0x03B1, 0x039F, 0x038E, 0x037D, 
	0x036D, 0x035E, 0x034F, 0x0341, 0x0333, 0x0325, 0x0318, 0x030C, 
	0x0620, 0x05F0, 0x05C3, 0x0599, 0x0571, 0x054C, 0x0528, 0x0506, 
	0x04E6, 0x04C7, 0x04AA, 0x048E, 0x0474, 0x045B, 0x0442, 0x042B, 
	0x0415, 0x0400, 0x03EB, 0x03D7, 0x03C4, 0x03B2, 0x03A1, 0x0390, 
	0x0380, 0x0370, 0x0361, 0x0352, 0x0344, 0x0336, 0x0329, 0x031C, 
	0x0640, 0x060F, 0x05E1, 0x05B6, 0x058E, 0x0567, 0x0543, 0x0520, 
	0x0500, 0x04E0, 0x04C3, 0x04A6, 0x048B, 0x0471, 0x0459, 0x0441, 
	0x042A, 0x0414, 0x0400, 0x03EB, 0x03D8, 0x03C6, 0x03B4, 0x03A2, 
	0x0392, 0x0382, 0x0372, 0x0363, 0x0355, 0x0347, 0x0339, 0x032C, 
	0x0660, 0x062E, 0x0600, 0x05D4, 0x05AA, 0x0583, 0x055E, 0x053B, 
	0x0519, 0x04F9, 0x04DB, 0x04BE, 0x04A2, 0x0488, 0x046F, 0x0457, 
	0x0440, 0x0429, 0x0414, 0x0400, 0x03EC, 0x03D9, 0x03C7, 0x03B5, 
	0x03A4, 0x0394, 0x0384, 0x0375, 0x0366, 0x0358, 0x034A, 0x033C, 
	0x0680, 0x064D, 0x061E, 0x05F1, 0x05C7, 0x059F, 0x0579, 0x0555, 
	0x0533, 0x0512, 0x04F3, 0x04D6, 0x04BA, 0x049F, 0x0485, 0x046C, 
	0x0455, 0x043E, 0x0428, 0x0414, 0x0400, 0x03EC, 0x03DA, 0x03C8, 
	0x03B6, 0x03A6, 0x0396, 0x0386, 0x0377, 0x0368, 0x035A, 0x034D, 
	0x06A0, 0x066C, 0x063C, 0x060E, 0x05E3, 0x05BA, 0x0594, 0x056F, 
	0x054C, 0x052B, 0x050C, 0x04EE, 0x04D1, 0x04B6, 0x049B, 0x0482, 
	0x046A, 0x0453, 0x043D, 0x0428, 0x0413, 0x0400, 0x03ED, 0x03DA, 
	0x03C9, 0x03B8, 0x03A7, 0x0397, 0x0388, 0x0379, 0x036B, 0x035D, 
	0x06C0, 0x068B, 0x065A, 0x062B, 0x0600, 0x05D6, 0x05AF, 0x0589, 
	0x0566, 0x0544, 0x0524, 0x0505, 0x04E8, 0x04CC, 0x04B2, 0x0498, 
	0x0480, 0x0468, 0x0451, 0x043C, 0x0427, 0x0413, 0x0400, 0x03ED, 
	0x03DB, 0x03CA, 0x03B9, 0x03A9, 0x0399, 0x038A, 0x037B, 0x036D, 
	0x06E0, 0x06AA, 0x0678, 0x0649, 0x061C, 0x05F2, 0x05CA, 0x05A4, 
	0x0580, 0x055D, 0x053C, 0x051D, 0x0500, 0x04E3, 0x04C8, 0x04AE, 
	0x0495, 0x047D, 0x0466, 0x0450, 0x043B, 0x0426, 0x0412, 0x0400, 
	0x03ED, 0x03DC, 0x03CB, 0x03BA, 0x03AA, 0x039B, 0x038C, 0x037D, 
	0x0700, 0x06C9, 0x0696, 0x0666, 0x0638, 0x060D, 0x05E5, 0x05BE, 
	0x0599, 0x0576, 0x0555, 0x0535, 0x0517, 0x04FA, 0x04DE, 0x04C4, 
	0x04AA, 0x0492, 0x047A, 0x0464, 0x044E, 0x0439, 0x0425, 0x0412, 
	0x0400, 0x03EE, 0x03DC, 0x03CB, 0x03BB, 0x03AC, 0x039C, 0x038E, 
	0x0720, 0x06E8, 0x06B4, 0x0683, 0x0655, 0x0629, 0x0600, 0x05D8, 
	0x05B3, 0x058F, 0x056D, 0x054D, 0x052E, 0x0511, 0x04F4, 0x04D9, 
	0x04C0, 0x04A7, 0x048F, 0x0478, 0x0462, 0x044D, 0x0438, 0x0425, 
	0x0412, 0x0400, 0x03EE, 0x03DD, 0x03CC, 0x03BC, 0x03AD, 0x039E, 
	0x0740, 0x0707, 0x06D2, 0x06A0, 0x0671, 0x0645, 0x061A, 0x05F2, 
	0x05CC, 0x05A8, 0x0586, 0x0565, 0x0545, 0x0527, 0x050B, 0x04EF, 
	0x04D5, 0x04BC, 0x04A3, 0x048C, 0x0476, 0x0460, 0x044B, 0x0437, 
	0x0424, 0x0411, 0x0400, 0x03EE, 0x03DD, 0x03CD, 0x03BD, 0x03AE, 
	0x0760, 0x0726, 0x06F0, 0x06BE, 0x068E, 0x0660, 0x0635, 0x060D, 
	0x05E6, 0x05C1, 0x059E, 0x057D, 0x055D, 0x053E, 0x0521, 0x0505, 
	0x04EA, 0x04D0, 0x04B8, 0x04A0, 0x0489, 0x0473, 0x045E, 0x044A, 
	0x0436, 0x0423, 0x0411, 0x0400, 0x03EE, 0x03DE, 0x03CE, 0x03BE, 
	0x0780, 0x0745, 0x070F, 0x06DB, 0x06AA, 0x067C, 0x0650, 0x0627, 
	0x0600, 0x05DA, 0x05B6, 0x0594, 0x0574, 0x0555, 0x0537, 0x051B, 
	0x0500, 0x04E5, 0x04CC, 0x04B4, 0x049D, 0x0487, 0x0471, 0x045D, 
	0x0449, 0x0435, 0x0423, 0x0411, 0x0400, 0x03EF, 0x03DE, 0x03CF, 
	0x07A0, 0x0764, 0x072D, 0x06F8, 0x06C7, 0x0698, 0x066B, 0x0641, 
	0x0619, 0x05F3, 0x05CF, 0x05AC, 0x058B, 0x056C, 0x054D, 0x0531, 
	0x0515, 0x04FA, 0x04E1, 0x04C8, 0x04B1, 0x049A, 0x0484, 0x046F, 
	0x045B, 0x0447, 0x0434, 0x0422, 0x0411, 0x0400, 0x03EF, 0x03DF, 
	0x07C0, 0x0783, 0x074B, 0x0715, 0x06E3, 0x06B3, 0x0686, 0x065B, 
	0x0633, 0x060C, 0x05E7, 0x05C4, 0x05A2, 0x0582, 0x0564, 0x0546, 
	0x052A, 0x050F, 0x04F5, 0x04DC, 0x04C4, 0x04AD, 0x0497, 0x0482, 
	0x046D, 0x0459, 0x0446, 0x0434, 0x0422, 0x0410, 0x0400, 0x03EF, 
	0x07E0, 0x07A2, 0x0769, 0x0733, 0x0700, 0x06CF, 0x06A1, 0x0676, 
	0x064C, 0x0625, 0x0600, 0x05DC, 0x05BA, 0x0599, 0x057A, 0x055C, 
	0x0540, 0x0524, 0x050A, 0x04F0, 0x04D8, 0x04C1, 0x04AA, 0x0494, 
	0x0480, 0x046B, 0x0458, 0x0445, 0x0433, 0x0421, 0x0410, 0x0400}; 
#endif