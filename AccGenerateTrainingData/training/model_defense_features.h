#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class RandomForestDefenseFeatures {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(int16_t *x) {
                        uint8_t votes[3] = { 0 };
                        // tree #1
                        if (x[7] <= -1114) {
                            if (x[5] <= 1397) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            if (x[12] <= -103) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #2
                        if (x[1] <= -705) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[3] <= 716) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #3
                        if (x[1] <= -689) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[4] <= 527) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[7] <= -1107) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #4
                        if (x[5] <= 1498) {
                            if (x[7] <= -972) {
                                votes[1] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #5
                        if (x[5] <= 1400) {
                            if (x[12] <= -270) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[6] <= -478) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #6
                        if (x[5] <= 1498) {
                            if (x[6] <= -489) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #7
                        if (x[3] <= 716) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[0] <= 351) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #8
                        if (x[3] <= 1873) {
                            if (x[0] <= -575) {
                                votes[2] += 1;
                            }

                            else {
                                if (x[1] <= -690) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #9
                        if (x[6] <= -201) {
                            if (x[9] <= 162) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #10
                        if (x[0] <= 351) {
                            if (x[3] <= 686) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #11
                        if (x[0] <= 360) {
                            if (x[5] <= 1473) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #12
                        if (x[7] <= -942) {
                            if (x[5] <= 1500) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #13
                        if (x[2] <= -79) {
                            if (x[7] <= -1070) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #14
                        if (x[2] <= -242) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[3] <= 1134) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #15
                        if (x[8] <= -1508) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[6] <= -216) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #16
                        if (x[6] <= -994) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[6] <= -168) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #17
                        if (x[0] <= 360) {
                            if (x[9] <= 167) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #18
                        if (x[1] <= -55) {
                            if (x[5] <= 1486) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #19
                        if (x[0] <= 354) {
                            if (x[14] <= -390) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #20
                        if (x[2] <= -251) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[0] <= -72) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #21
                        if (x[5] <= 1498) {
                            if (x[0] <= -72) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #22
                        if (x[6] <= -994) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[1] <= -705) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #23
                        if (x[8] <= -1525) {
                            if (x[3] <= 1064) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            if (x[0] <= 337) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #24
                        if (x[0] <= 351) {
                            if (x[9] <= 167) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #25
                        if (x[9] <= 162) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[1] <= -689) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #26
                        if (x[2] <= -34) {
                            if (x[8] <= -1525) {
                                votes[2] += 1;
                            }

                            else {
                                if (x[14] <= -267) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #27
                        if (x[3] <= 756) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[2] <= -185) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #28
                        if (x[0] <= -571) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[0] <= 360) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #29
                        if (x[2] <= -251) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[9] <= 212) {
                                votes[2] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #30
                        if (x[0] <= -583) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[6] <= -180) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
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
                            return "steal_features";
                            case 1:
                            return "stop_features";
                            case 2:
                            return "two_min_features";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }