#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class RandomForestDefense {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(int16_t *x) {
                        uint8_t votes[3] = { 0 };
                        // tree #1
                        if (x[59] <= 1943) {
                            if (x[105] <= -18) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #2
                        if (x[127] <= -853) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[160] <= -71) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #3
                        if (x[213] <= -497) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[63] <= 761) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #4
                        if (x[150] <= 467) {
                            if (x[210] <= -511) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #5
                        if (x[30] <= -68) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[82] <= -547) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #6
                        if (x[204] <= 426) {
                            if (x[210] <= -518) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #7
                        if (x[85] <= -375) {
                            if (x[214] <= -712) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #8
                        if (x[156] <= 435) {
                            if (x[219] <= -511) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #9
                        if (x[145] <= -666) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[141] <= 18) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #10
                        if (x[198] <= -510) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[206] <= 964) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #11
                        if (x[219] <= 404) {
                            if (x[211] <= -346) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #12
                        if (x[198] <= -494) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[211] <= -729) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #13
                        if (x[223] <= -705) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[175] <= -94) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #14
                        if (x[190] <= -684) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[178] <= -85) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #15
                        if (x[185] <= 920) {
                            if (x[208] <= -327) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #16
                        if (x[166] <= -67) {
                            if (x[196] <= -742) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #17
                        if (x[141] <= -520) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[185] <= 928) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #18
                        if (x[189] <= -517) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[39] <= -81) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #19
                        if (x[198] <= 414) {
                            if (x[114] <= -536) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #20
                        if (x[154] <= -685) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[38] <= 526) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #21
                        if (x[151] <= -58) {
                            if (x[136] <= -773) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #22
                        if (x[217] <= -140) {
                            if (x[174] <= 424) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #23
                        if (x[141] <= 470) {
                            if (x[180] <= -539) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #24
                        if (x[192] <= -523) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[104] <= 920) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #25
                        if (x[198] <= 419) {
                            if (x[172] <= -312) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #26
                        if (x[190] <= -78) {
                            if (x[187] <= -702) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #27
                        if (x[123] <= 431) {
                            if (x[127] <= -324) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #28
                        if (x[165] <= -503) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[179] <= 935) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #29
                        if (x[70] <= -680) {
                            if (x[27] <= 31) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #30
                        if (x[184] <= -679) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[118] <= 27) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // return argmax of votes
                        uint8_t classIdx = 0;
                        uint8_t maxVotes = votes[0];

                        for (uint8_t i = 1; i < 3; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(int16_t *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "steal";
                            case 1:
                            return "stop";
                            case 2:
                            return "two_min";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }