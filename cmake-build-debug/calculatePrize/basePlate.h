//
// Created by Admin on 2023/5/22.
//
#include<vector>
#ifndef UNTITLED9_BASEPLATE_H
#define UNTITLED9_BASEPLATE_H
using namespace std;
using namespace std;
class BasePlate
{
public:
    /**
     * 最大拼板宽高 （不加咬口尺寸）
     */
    const double maxWidth = 1000;
    const double maxHeight = 700;
//    const double maxArea = 1000*700*0.7;
    const double maxArea = 490000;
    /*
     * 大度开纸
     */
    const vector<double> BigDegree { 1194, 889};
    /*
     * 正度开纸
     */
    const vector<double> PositiveDegree{ 1092, 797};
    /*
     * 平装纸尺寸
     */
    const vector<vector<double>> PaperBackPapers
            {
                    { 398, 295 },
                    { 443, 298 },
                    { 392, 364 },
                    { 595, 295 },
                    { 443, 398 },
                    { 545, 392 },
                    { 595, 443 },
                    { 787, 364 },
                    { 887, 398 },
                    { 787, 545 },
                    { 887, 595 },
                    { 1000, 700 }
            };
    const vector<vector<double>> PaperBackPapersWidthOrder
            {
                    { 392, 364 },
                    { 398, 295 },
                    { 443, 298 },
                    { 443, 398 },
                    { 545, 392 },
                    { 595, 295 },
                    { 595, 443 },
                    { 787, 364 },
                    { 787, 545 },
                    { 887, 398 },
                    { 887, 595 },
                    { 1000, 700 }
            };
    /*
     * 平装纸尺寸 - 大度纸 1194*889
     */
    const vector<vector<double>> BigDegreePaperBackPapers
            {
                    { 889, 596 }, // 大度对开
                    { 889, 393 }, // 大度三开
                    { 740, 440 }, // 大度丁三开
                    { 596, 444 } // 大度四开
            };

    /*
     * 平装纸尺寸 - 正度纸 1092 *797
     */
    const vector<vector<double>> PositiveDegreePaper
            {
                    { 787, 546 }, // 正度对开
                    { 787, 364 }, // 正度三开
                    { 690, 390 }, // 正度丁三开
                    { 546, 393 } // 正度四开
            };
    /*
     * 分切纸尺寸
     */
    const vector<double> cuttingPaper
            {
                    262, 273, 280, 298, 317, 320, 321, 330, 333, 350, 355,
                    364, 370, 393, 398, 420, 444, 480, 482, 500, 546, 597,
                    635, 660, 700, 711, 740, 787, 840, 889, 960, 965, 1000
            };
    /*
     * 对开机最大 最小尺寸 范围 { 720*1020 360*520 }
     */
    const vector<vector<double>> doubleMachineSize
            {
                    { 1020, 369 },
                    { 1030, 370 },
                    { 940, 320 },
                    { 1040, 370 }
            };
    const vector<vector<double>> fourMachineSize
            {
                    { 759, 310 },
                    { 740, 297 },
                    { 745, 297 },
                    { 750, 300 }
            };
};


#endif //UNTITLED9_BASEPLATE_H
