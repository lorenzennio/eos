/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2022 Viktor Kuschke
 *
 * This file is part of the EOS project. EOS is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * EOS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <vector>
#include <test/test.hh>
#include <eos/maths/multiplepolylog-li22.hh>

using namespace test;
using namespace eos;

class MultiplePolylogarithmTest :
    public TestCase
{
    public:
        MultiplePolylogarithmTest() :
            TestCase("multiplepolylogarithm_test")
        {
        }

        void test_region(const std::vector<std::vector<complex<double>>> & input, const std::vector<complex<double>> & reference, const double & eps) const
        {
            // check that the C implementation uses the principal branch of the (complex) logarithm
            TEST_CHECK_RELATIVE_ERROR(+M_PI, imag(std::log(complex<double>(-1.0, 0.0))), eps);

            if ( input.size() != reference.size())
                TEST_CHECK_FAILED("Number of reference values does not match number of complex points");

            if ( input[0].size() != 2)
                TEST_CHECK_FAILED("The array of complex points does not have the correct number of columns");

            for (unsigned int i = 0; i < reference.size(); i++)
            {
                complex<double> x = input[i][0];
                complex<double> y = input[i][1];
                complex<double> li22_reference = reference[i];
                complex<double> li22_value = li22(x, y);

                TEST_CHECK_NEARLY_EQUAL(real(li22_reference),   real(li22_value),     eps);
                TEST_CHECK_NEARLY_EQUAL(imag(li22_reference),   imag(li22_value),     eps);
            }
        }

        virtual void run() const
        {
            // Testing region A
            {
                const std::vector<std::vector<complex<double>>> x_y_points = {
                    {{0.0, 0.0}, {0.0, 0.0}},                   {{0.0, 0.0}, {0.3, 0.0}},
                    {{0.0, 0.0}, {1.5, 0.0}},                   {{0.0, 0.0}, {5.0, 0.0}},
                    {{0.0, 0.0}, {50, 0.0}},                    {{0.0, 0.0}, {800, 0.0}},
                    {{0.16, 0.0}, {0.0, 0.0}},                  {{0.16, 0.0}, {0.3, 0.0}},
                    {{0.16, 0.0}, {1.5, 0.0}},                  {{0.16, 0.0}, {4.0, 0.0}},
                    {{0.35, 0.0}, {1.2, 0.0}},                  {{0.35, 0.0}, {1.5, 0.0}},
                    {{0.35, 0.0}, {1.7, 0.0}},                  {{0.35, 0.0}, {1.8, 0.0}},
                    {{0.5, 0.0}, {1.2, 0.0}},                   {{0.5, 0.0}, {1.8, 0.0}},
                    {{0.0003, 0.0}, {1500, 0.0}},               {{0.0, 0.0}, {-0.28935, 0.07924}},
                    {{0.0, 0.0}, {0.029333,-1.4997}},           {{0.0, 0.0}, {-4.7215, 1.6454}},
                    {{0.0, 0.0}, {-35.449,35.261}},             {{0.0, 0.0}, {-328.08, -729.63}},
                    {{0.16, 0.0}, {0.0,0.0}},                    {{0.16, 0.0}, {-0.28947, -0.07879}},
                    {{0.16, 0.0}, {-0.060793,-1.4988}},         {{0.16, 0.0}, {3.3019, 2.2577}},
                    {{0.35, 0.0}, {0.28478,1.1657}},            {{0.35, 0.0}, {1.4939, 0.13548}},
                    {{0.35, 0.0}, {0.2133,-1.6866}},            {{0.35, 0.0}, {-0.29534, 1.7756}},
                    {{0.5, 0.0}, {-0.32722,1.1545}},            {{0.5, 0.0}, {-1.7027, 0.5838}},
                    {{0.0003, 0.0}, {-1187.14, - 916.893}},     {{0.000175, 0.000244}, {1251.04, - 827.592}},
                    {{-0.15834, 0.022961}, {0.0, 0.0}},         {{0.020353, 0.1587}, {0.28868, -0.081619}},
                    {{0.074773, 0.14145}, {1.2915, -0.76287}},  {{0.1553, -0.0385}, {3.1237, 2.4985}},
                    {{0.2491, -0.24586}, {-0.50285, -1.0896}},  {{0.33194, -0.11099}, {1.1014, 1.0183}},
                    {{0.22294, 0.26981}, {0.41431, 1.6487}},    {{0.031092, 0.34862}, {-0.24654, 1.783}},
                    {{-0.33074, 0.37498}, {1.1671, -0.27924}},  {{-0.020469, -0.49958}, {-1.5476, -0.91925}}
                };

                const std::vector<complex<double>> li22_values = {
                    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0.002081645530457917, 0.0}, {0.010651696273675876, 0.0}, {0.030039829442010797, 0.0}, {0.04635897385686277, 0.0}, {0.05884713061848893, 0.0}, {0.06741927429845772, 0.0}, {0.07178642142151906, 0.0}, {0.10727377899617292, 0.0}, {0.1701767184161538, 0.0}, {3.567098698155471E-5, 0.0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {-0.0019879538929080446, -5.380986738117047E-4}, {-6.968004429581845E-4, -0.010303480373845512}, {0.023354855690842665, 0.01781048747466586}, {0.008386863823227531, 0.043462760293781426}, {0.05854320883808645, 0.005731913423855528}, {0.0035178299296248893, -0.06216402156165925}, {-0.014918156554264827, 0.06286811835616828}, {-0.03208004722066546, 0.09067923334907338}, {-0.12917467990172696, 0.04050101707796992}, {-2.6235017138206976E-5, -1.9159369420803295E-5}, {8.327568547787913E-6, 3.4570077614650976E-5}, {0, 0}, {-0.0017375127489347817, 8.488891936263332E-4}, {-0.0014781071218621642, 0.0100226570597535}, {0.028950758006117468, 0.006141292171766552}, {-0.03317905494549053, 0.020919980537159315}, {0.057409210598555145, 0.003844704121116567}, {-0.05422570788903269, -0.0070197437565258}, {0.005619024913061165, -0.051239352427759365}, {-0.010948576857822117, -0.06164866503987189}, {0.09746578054527927, 0.0322617807345509}
                };

                const double epsilon = 1e-12;
                test_region(x_y_points, li22_values, epsilon);
            }

            // Testing region B
            {
                const std::vector<std::vector<complex<double>>> x_y_points = {
                    {{0.3, 0.0}, {0.0, 0.0}},       {{1.0, 0.0}, {0.0, 0.0}},
                    {{7.3, 0.0}, {0.0, 0.0}},       {{89.0, 0.0}, {0.0, 0.0}},
                    {{929.0, 0.0}, {0.0, 0.0}},
                    {{0.3, 0.0}, {0.2, 0.0}},       {{0.67, 0.0}, {0.2, 0.0}},
                    {{1.05, 0.0}, {0.2, 0.0}},      {{1.3, 0.0}, {0.2, 0.0}},
                    {{2.8, 0.0}, {0.2, 0.0}},       {{3.3, 0.0}, {0.2, 0.0}},
                    {{0.3, 0.0}, {0.45, 0.0}},      {{0.67, 0.0}, {0.45, 0.0}},
                    {{1.05, 0.0}, {0.45, 0.0}},     {{1.3, 0.0}, {0.45, 0.0}},
                    {{0.28, 0.0}, {0.73, 0.0}},     {{0.48, 0.0}, {0.73, 0.0}},
                    {{0.73, 0.0}, {0.73, 0.0}},     {{0.94, 0.0}, {0.73, 0.0}},
                    {{0.31, 0.0}, {1.08, 0.0}},     {{0.42, 0.0}, {1.08, 0.0}},
                    {{0.56, 0.0}, {1.08, 0.0}},     {{0.61, 0.0}, {1.08, 0.0}}
                };

                const std::vector<complex<double>> li22_values = {
                    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0.00526276935063225, 0.0}, {0.03434245237309184, 0.0},     {0.16362368523104365, -0.032342409993916854}, {0.19361371318058962, -0.17391809914171896}, {-0.11651570511012121, -0.6825222643754504}, {-0.2572715751715331, -0.7914367707841685}, {0.011948733860527645, 0.0}, {0.07907798665721592, 0.0}, {0.3867526110902213, -0.07884647074685154}, {0.4525379945735788, -0.42398906942632786}, {0.016841121219089022, 0.0}, {0.057100914992508425, 0.0}, {0.1672733602085725, 0.0}, {0.38600998075669657, 0.0}, {0.0315959003992087, 0.0}, {0.06306554790669047, 0.0}, {0.12674432993356427, 0.0}, {0.15803099838966947, 0.0}
                };

                const double epsilon = 1e-12;
                test_region(x_y_points, li22_values, epsilon);
            }

            // Testing region C
            {
                const std::vector<std::vector<complex<double>>> x_y_points= {
                    {{1.9, 0.0}, {0.8, 0.0}},           {{2.4, 0.0}, {0.8, 0.0}},
                    {{2.9, 0.0}, {0.8, 0.0}},           {{3.5, 0.0}, {0.8, 0.0}},
                    {{2.1, 0.0}, {0.7, 0.0}},           {{2.6, 0.0}, {0.7, 0.0}},
                    {{3.1, 0.0}, {0.7, 0.0}},           {{3.5, 0.0}, {0.7, 0.0}},
                    {{15.3, 0.0}, {0.46, 0.0}},         {{92.0, 0.0}, {0.46, 0.0}},
                    {{485.0, 0.0}, {0.46, 0.0}},        {{2934.0, 0.0}, {0.46, 0.0}},
                    {{2.1, 0.0}, {0.7, 0.0}},           {{2.6, 0.0}, {0.7, 0.0}},
                    {{3.1, 0.0}, {0.7, 0.0}},           {{3.5, 0.0}, {0.7, 0.0}},
                    {{66.8191, 0.0}, {1714.38, 0.0}},   {{854.501, 0.0}, {2284.28, 0.0}},
                    {{3968.69, 0.0}, {4464.67, 0.0}},   {{4893.33, 0.0}, {3772.2, 0.0}},
                    {{1862.48, 0.0}, {768.447, 0.0}},   {{3751.05, 0.0}, {1422.75, 0.0}},
                    {{3528.37, 0.0}, {1204.62, 0.0}},   {{3644.34, 0.0}, {1397.47, 0.0}},
                    {{3376.79, 0.0}, {4309.79, 0.0}},   {{2185.94, 0.0}, {4821.93, 0.0}},
                    {{39.7149, 0.0}, {495.591, 0.0}},   {{111.063, 0.0}, {1696.5, 0.0}},
                    {{179.057, 0.0}, {2575.51, 0.0}},   {{331.342, 0.0}, {1602.03, 0.0}},
                    {{141.788, 0.0}, {1215.02, 0.0}},   {{289.046, 0.0}, {3751.41, 0.0}},
                    {{261.518, 0.0}, {2605.56, 0.0}},   {{229.026, 0.0}, {2187.99, 0.0}},
                    {{106.095, 0.0}, {3946.89, 0.0}},   {{199.371, 0.0}, {3706.25, 0.0}},
                    {{1657.03, 0.0}, {290.394, 0.0}},   {{1241.87, 0.0}, {341.499, 0.0}},
                    {{3503.81, 0.0}, {25.8186, 0.0}},   {{583.105, 0.0}, {327.216, 0.0}},
                    {{3546.98, 0.0}, {320.056, 0.0}},   {{4888.59, 0.0}, {55.0363, 0.0}},
                    {{2149.24, 0.0}, {390.111, 0.0}},   {{741.874, 0.0}, {94.1922, 0.0}},
                    {{4857.6, 0.0}, {357.294, 0.0}},    {{3701.55, 0.0}, {193.039, 0.0}}
                };

                const std::vector<complex<double>> li22_values = {
                    {0.1523595924359218, -2.053147079333523}, {-0.6560667548170103, -2.5900094655437456}, {-1.4823623486645983, -2.8863113904296815}, {-2.4361511091727936, -3.037705433119426}, {-0.04807422208794687, -2.000761542352614}, {-0.7480281710993575, -2.4281993787026837}, {-1.4624263752167321, -2.677133023307829}, {-2.021549280077421, -2.7850886279932774}, {-8.767087991009326, 0.33946742885188114}, {-20.80916429571243, 23.33133958387653}, {-20.841567260205117, 78.4731202475047}, {16.077451220880633, 191.68865150306652}, {-0.04807422208794687, -2.000761542352615}, {-0.7480281710993566, -2.4281993787026837}, {-1.4624263752167317, -2.6771330233078285}, {-2.021549280077421, -2.7850886279932774}, {29.352365209989557, 535.0747054064824}, {652.0120319364805, 1268.9973412426912}, {1522.6681688929118, 2036.697764399904}, {1596.1493397566317, 2074.700882646159}, {741.6285202761168, 1268.7357796132176}, {1171.190690819038, 1670.6648626728977}, {1099.875712965275, 1601.3102703190561}, {1152.7373548981973, 1654.7494045322962}, {1418.5305386494547, 1955.8572743634224}, {1211.4263404896024, 1807.0203273653804}, {-40.27025233259354, 317.7407902613236}, {103.95886662593813, 646.5153636198077}, {219.0271587280747, 826.8280284773728}, {323.91560209989115, 912.8736070458535}, {128.66186269125342, 656.9784552641069}, {369.902207625844, 1028.357792111617}, {309.2710589804688, 932.9573032855933}, {262.5264135590479, 866.262525939058}, {135.34500185844814, 753.3618388217735}, {270.8559030227396, 916.6829460580045}, {536.8432599819223, 1018.6200138408511}, {481.94453395848427, 974.9017871882245}, {356.0361532924716, 726.1045786607295}, {297.51226608345183, 779.7068008575457}, {796.0232298595636, 1258.8915461528768}, {550.1437637356295, 947.8340769954976}, {665.0860851985266, 1155.6243661583655}, {224.06652194096887, 630.382174099152}, {938.3911240663306, 1385.5034043283536}, {706.7164976519506, 1151.5354306916274}
                };

                const double epsilon = 5e-11;
                test_region(x_y_points, li22_values, epsilon);
            }

            // Testing region D
            {
                const std::vector<std::vector<complex<double>>> x_y_points= {
                    {{1.84,0.0},{4.63,0.0}},{{2.69,0.0},{9.8,0.0}},{{1.74,0.0},{2.11,0.0}},{{2.53,0.0},{3.28,0.0}},{{2.23,0.0},{4.97,0.0}},{{3.11,0.0},{8.32,0.0}},{{2.21,0.0},{5.99,0.0}},{{3.14,0.0},{1.53,0.0}},{{1.91,0.0},{0.874,0.0}},{{1.98,0.0},{2.13,0.0}},{{2.74,0.0},{2.18,0.0}},{{2.2,0.0},{4.18,0.0}},{{1.97,0.0},{4.45,0.0}},{{1.85,0.0},{8.15,0.0}},{{3.31,0.0},{1.76,0.0}},{{3.47,0.0},{1.73,0.0}},{{2.34,0.0},{1.66,0.0}},{{2.32,0.0},{9.14,0.0}},{{2.37,0.0},{8.66,0.0}},{{3.12,0.0},{4.18,0.0}},{{3.37,0.0},{1448.60,0.0}},{{1.99,0.0},{2655.90,0.0}},{{3.32,0.0},{1830.00,0.0}},{{3.21,0.0},{67.03,0.0}},{{3.12,0.0},{969.08,0.0}},{{3.02,0.0},{357.84,0.0}},
                    {{2.79,0.0},{4898.00,0.0}},{{2.23,0.0},{2809.20,0.0}},{{2.26,0.0},{493.86,0.0}},{{1.84,0.0},{3100.40,0.0}},{{1.69,0.0},{1786.20,0.0}},{{1.73,0.0},{3169.30,0.0}},{{2.12,0.0},{1550.60,0.0}},{{2.03,0.0},{817.70,0.0}},{{2.94,0.0},{2205.90,0.0}},{{1.73,0.0},{4076.30,0.0}},{{3.34,0.0},{888.26,0.0}},{{3.03,0.0},{1944.90,0.0}},{{2.97,0.0},{1715.00,0.0}},{{1.78,0.0},{431.59,0.0}},
                    {{0.164215,0.0},{11.0561,0.0}},{{0.164215,0.0},{12.5675,0.0}},{{0.164215,0.0},{12.9002,0.0}},{{0.164215,0.0},{25.7391,0.0}},{{0.164215,0.0},{39.2696,0.0}},{{0.164215,0.0},{39.9814,0.0}},{{0.164215,0.0},{60.1693,0.0}},{{0.164215,0.0},{70.5265,0.0}},{{0.164215,0.0},{83.8777,0.0}},{{0.164215,0.0},{85.5156,0.0}},{{0.164215,0.0},{98.4431,0.0}},{{0.164215,0.0},{406.29,0.0}},{{0.164215,0.0},{655.463,0.0}},{{0.164215,0.0},{1742.86,0.0}},{{0.164215,0.0},{1756.87,0.0}},{{0.164215,0.0},{1933.57,0.0}},{{0.164215,0.0},{2070.8,0.0}},{{0.164215,0.0},{3610.01,0.0}},{{0.164215,0.0},{4355.04,0.0}},{{0.164215,0.0},{4939.46,0.0}},
                    {{0.492645,0.0},{9.9692,0.0}},{{0.492645,0.0},{41.2165,0.0}},{{0.492645,0.0},{43.5295,0.0}},{{0.492645,0.0},{52.2695,0.0}},{{0.492645,0.0},{58.1329,0.0}},{{0.492645,0.0},{63.1639,0.0}},{{0.492645,0.0},{65.2156,0.0}},{{0.492645,0.0},{88.542,0.0}},{{0.492645,0.0},{91.1837,0.0}},{{0.492645,0.0},{97.4534,0.0}},{{0.492645,0.0},{1012.05,0.0}},{{0.492645,0.0},{1022.33,0.0}},{{0.492645,0.0},{1161.04,0.0}},{{0.492645,0.0},{1907.48,0.0}},{{0.492645,0.0},{2544.2,0.0}},{{0.492645,0.0},{2668.51,0.0}},{{0.492645,0.0},{3354.94,0.0}},{{0.492645,0.0},{3634.28,0.0}},{{0.492645,0.0},{4497.56,0.0}},{{0.492645,0.0},{4867.53,0.0}},
                    {{0.821075,0.0},{28.983,0.0}},{{0.821075,0.0},{49.7849,0.0}},{{0.821075,0.0},{58.1025,0.0}},{{0.821075,0.0},{59.6563,0.0}},{{0.821075,0.0},{61.1824,0.0}},{{0.821075,0.0},{64.9382,0.0}},{{0.821075,0.0},{74.2389,0.0}},{{0.821075,0.0},{85.6865,0.0}},{{0.821075,0.0},{85.8905,0.0}},{{0.821075,0.0},{85.8973,0.0}},{{0.821075,0.0},{128.905,0.0}},{{0.821075,0.0},{311.534,0.0}},{{0.821075,0.0},{437.078,0.0}},{{0.821075,0.0},{464.413,0.0}},{{0.821075,0.0},{726.516,0.0}},{{0.821075,0.0},{1361.19,0.0}},{{0.821075,0.0},{2141.25,0.0}},{{0.821075,0.0},{3520.59,0.0}},{{0.821075,0.0},{3940.32,0.0}},{{0.821075,0.0},{4768.36,0.0}},
                    {{1.14951,0.0},{3.30421,0.0}},{{1.14951,0.0},{7.46497,0.0}},{{1.14951,0.0},{14.5266,0.0}},{{1.14951,0.0},{25.3756,0.0}},{{1.14951,0.0},{42.8173,0.0}},{{1.14951,0.0},{51.4839,0.0}},{{1.14951,0.0},{69.1304,0.0}},{{1.14951,0.0},{86.5328,0.0}},{{1.14951,0.0},{90.4354,0.0}},{{1.14951,0.0},{96.2415,0.0}},{{1.14951,0.0},{287.868,0.0}},{{1.14951,0.0},{469.682,0.0}},{{1.14951,0.0},{595.145,0.0}},{{1.14951,0.0},{1385.55,0.0}},{{1.14951,0.0},{1738.4,0.0}},{{1.14951,0.0},{2120.01,0.0}},{{1.14951,0.0},{2384.44,0.0}},{{1.14951,0.0},{2551.88,0.0}},{{1.14951,0.0},{2650.28,0.0}},{{1.14951,0.0},{3651.51,0.0}},
                    {{1.47794,0.0},{9.54098,0.0}},{{1.47794,0.0},{14.3083,0.0}},{{1.47794,0.0},{17.6018,0.0}},{{1.47794,0.0},{26.5127,0.0}},{{1.47794,0.0},{27.4424,0.0}},{{1.47794,0.0},{53.0386,0.0}},{{1.47794,0.0},{58.2122,0.0}},{{1.47794,0.0},{59.6236,0.0}},{{1.47794,0.0},{71.1118,0.0}},{{1.47794,0.0},{82.1192,0.0}},{{1.47794,0.0},{1031.06,0.0}},{{1.47794,0.0},{1080.9,0.0}},{{1.47794,0.0},{1588.37,0.0}},{{1.47794,0.0},{2314.36,0.0}},{{1.47794,0.0},{2391.17,0.0}},{{1.47794,0.0},{2970.34,0.0}},{{1.47794,0.0},{3895.74,0.0}},{{1.47794,0.0},{3979.36,0.0}},{{1.47794,0.0},{4086.82,0.0}},{{1.47794,0.0},{4217.14,0.0}}
                };

                const std::vector<complex<double>> li22_values = {
                    {-4.39131242273384, -7.0460060813405345}, {-15.921737311470512, -6.165351646756168}, {-0.8413729332902768, -4.503826313565111}, {-6.39312506441334, -5.858044289012671}, {-7.416286984771917, -6.937647505110364}, {-16.7754953503346, -4.732982867715663}, {-8.559404967951394, -7.301710180629588}, {-4.341275437868532, -4.224628055637825}, {0.07637790662384303, -2.275161160594363}, {-1.9086227148457802, -4.840895287671575}, {-4.925826637892774, -4.99071578515751}, {-6.149931105106237, -6.6212392074085535}, {-5.078824020098429, -6.914806860729641}, {-7.826187320301152, -8.554306519617576}, {-5.5109863533012255, -4.363275683613498}, {-5.8342081130360075, -4.247966268635963}, {-2.37935983721359, -4.385779817244646}, {-12.672190433798335, -7.5296760503259215}, {-12.579942305281236, -7.331465075531936}, {-10.675942508175979, -5.212413906209573}, {-104.9270655109705, 54.203319482383804}, {-96.21468404276203, 10.898430829900647}, {-109.90255860463637, 57.54241004233515}, {-44.23920093550241, 6.234000005688237}, {-93.59365708797228, 39.10061532207993}, {-71.95626633081585, 21.329421070458764}, {-127.98596600168423, 57.38801067140453}, {-103.8983967505794, 22.71887588803756}, {-67.68710023103895, 5.954426384534102}, {-94.72183768447545, 4.805472529069789}, {-77.38741987723884, -5.822456950563804}, {-90.94805972395511, -0.7482142850428772}, {-87.91693963434545, 11.487845757405665}, {-72.52399967556028, 2.7876104919430986}, {-110.34724583172388, 48.10752738228463}, {-96.47131634375828, 0.8686043398782459}, {-93.74990511537499, 43.67769218681559}, {-108.43027644818312, 48.959015057035515}, {-104.80849486116907, 44.52751922659073}, {-54.17255152796927, -8.32925548248491},
                    {0.11220289527456373, -0.015617135646444284}, {0.1293378625795505, -0.026188044535815625}, {0.13290157121067425, -0.028735445028317298}, {0.22160059872176768, -0.14551938107690712}, {0.2564525475632421, -0.26072422050320915}, {0.2574290618162469, -0.2662676952215147}, {0.2665980019711754, -0.40478398700647156}, {0.2629252076137877, -0.46436181324194464}, {0.2539887260713328, -0.5325750452166231}, {0.2526661039969409, -0.5403753911599369}, {0.24103501647987308, -0.5982375730999682}, {-0.0793994482082494, -1.257034112403625}, {-0.27176250352410924, -1.498771635668149}, {-0.7951526559426288, -2.0074502581035905}, {-0.800149434363328, -2.01166817773819}, {-0.8608489482785598, -2.0622048131972184}, {-0.9052840502280268, -2.0984157014429554}, {-1.2962709046541698, -2.3932759790110882}, {-1.440585370462422, -2.4932508533513107}, {-1.5409117325765187, -2.5604437926140435}, {0.8292010298031058, -0.6918068255104239}, {0.6796805828855084, -2.473380725873371}, {0.650250831358832, -2.5549841077554722}, {0.5381390372521386, -2.833229479677101}, {0.4634246628920342, -2.9980260252904283}, {0.4001974036190614, -3.128137753751779}, {0.37470066206035724, -3.1785701879271473}, {0.09859177526157104, -3.669208274453081}, {0.06897424279315345, -3.71709671880887}, {-2.2324729929135145E-6, -3.8258347736189195}, {-4.1475807579975745, -7.867823266216009}, {-4.172601568205713, -7.885761388901273}, {-4.492732731873451, -8.11175136207637}, {-5.832633592343824, -8.995992988673319}, {-6.675924960083873, -9.510365123925467}, {-6.820247572440794, -9.595631072136808}, {-7.531172861704716, -10.00504488982147}, {-7.786714504245174, -10.148174257327248}, {-8.485764116356993, -10.529782021144454},
                    {-8.751732554656286, -10.67139203176159}, {0.9736912441984953, -5.796771120241236}, {0.02698982144106621, -7.494588728012842}, {-0.30877441991406807, -7.993659174095059}, {-0.3690231780538289, -8.07943452038079}, {-0.4274790089238465, -8.161669093108866}, {-0.5684062933340268, -8.356135575305203}, {-0.9006605320361896, -8.7955319662341}, {-1.280565117056339, -9.269793364432529}, {-1.287072766317658, -9.277685833962797}, {-1.2872895383250103, -9.27794860865771}, {-2.497231974368479, -10.637009005572507}, {-5.799013244256429, -13.650045060492467}, {-7.306907388531219, -14.819940367675596}, {-7.591039911861503, -15.030089143428304}, {-9.817616897571622, -16.584412856204793}, {-13.327328478700345, -18.774264608375837}, {-16.137767453854895, -20.358607235941093}, {-19.489443370794657, -22.100149575714024}, {-20.287376128799163, -22.494914686450496}, {-21.671214819168497, -23.1636176249727}, {1.7137168172491908, -3.7531201324470658}, {0.5975741199355671, -6.955733788714474}, {-1.4083242642226494, -9.861710419692006}, {-3.859213119246668, -12.367510615513652}, {-6.790597388944715, -14.714115638789089}, {-7.96776226008847, -15.532530965223991}, {-10.004740842113783, -16.82709326744452}, {-11.683524963623896, -17.79943747436693}, {-12.026187419092746, -17.988894921418822}, {-12.516695974813647, -18.255217043793916}, {-22.51096971165566, -22.741016277755676}, {-27.79792686035608, -24.604974168140167}, {-30.53491784491242, -25.472588060753218}, {-41.25672013665092, -28.38259061460711}, {-44.38759810933081, -29.113037538366434}, {-47.2137374678434, -29.734106745032683}, {-48.926041673321, -30.094047095995144}, {-49.92767734021635, -30.2991771825845}, {-50.490215134103984, -30.412680287662276},
                    {-55.373665901374, -31.34945476397575}, {-4.746471349624331, -9.269026911086383}, {-7.14511869208183, -10.66304895433844}, {-8.539552338561943, -11.33969145067011}, {-11.628247048538839, -12.588169926588613}, {-11.908055693047363, -12.687216629349681}, {-17.844618748972028, -14.378018239397928}, {-18.772258390739566, -14.583658913759017}, {-19.014559994420424, -14.635186717829033}, {-20.841057939594048, -14.996252151097647}, {-22.39063998475655, -15.267337343581332}, {-57.92105475642891, -16.221547974278295}, {-58.73071260873853, -16.16764962284966}, {-65.53097045276216, -15.627646801736581}, {-72.5226186672572, -14.92580938306078}, {-73.14493338509601, -14.856816955976086}, {-77.34333599825469, -14.365545470347044}, {-82.75029511407517, -13.670574861611186}, {-83.18106802236971, -13.61236519408034}, {-83.72306559556668, -13.538551711244494}, {-84.3637171042341, -13.450485043624226}
                };

                const double epsilon = 8e-12;
                test_region(x_y_points, li22_values, epsilon);
            }

            // Testing regions Ea, Eb, Ec and Ed
            {

                const std::vector<std::vector<complex<double>>> x_y_points = {
                    {{0.505655, 0.0}, {2.59658, 0.0}},       {{0.255197, 0.0}, {5.14494, 0.0}},
                    {{0.695389, 0.0}, {1.88811, 0.0}},       {{0.308169, 0.0}, {4.26056, 0.0}},
                    {{0.156575, 0.0}, {8.3856, 0.0}},        {{0.522395, 0.0}, {2.51337, 0.0}},
                    {{0.496703, 0.0}, {2.64338, 0.0}},       {{0.606517, 0.0}, {2.16477, 0.0}},
                    {{0.586386, 0.0}, {2.23909, 0.0}},       {{0.403183, 0.0}, {3.25652, 0.0}},
                    {{0.505655, 0.0}, {1.7441, 0.0}},        {{0.255197, 0.0}, {3.45581, 0.0}},
                    {{0.695389, 0.0}, {1.26823, 0.0}},       {{0.308169, 0.0}, {2.86178, 0.0}},
                    {{0.156575, 0.0}, {5.63254, 0.0}},       {{0.522395, 0.0}, {1.68821, 0.0}},
                    {{0.496703, 0.0}, {1.77553, 0.0}},       {{0.606517, 0.0}, {1.45406, 0.0}},
                    {{0.586386, 0.0}, {1.50398, 0.0}},       {{0.403183, 0.0}, {2.18738, 0.0}},
                    {{0.505655, 0.0}, {2.33937, 0.0}},       {{0.255197, 0.0}, {4.63529, 0.0}},
                    {{0.695389, 0.0}, {1.70108, 0.0}},       {{0.308169, 0.0}, {3.83852, 0.0}},
                    {{0.156575, 0.0}, {7.55494, 0.0}},       {{0.522395, 0.0}, {2.2644, 0.0}},
                    {{0.496703, 0.0}, {2.38153, 0.0}},       {{0.606517, 0.0}, {1.95034, 0.0}},
                    {{0.586386, 0.0}, {2.01729, 0.0}},       {{0.403183, 0.0}, {2.93394, 0.0}},

                    {{18.6101, 0.0}, {0.0564046, 0.0}},     {{2.08132, 0.0}, {0.50434, 0.0}},
                    {{18.6641, 0.0}, {0.0562415, 0.0}},     {{6.76049, 0.0}, {0.155269, 0.0}},
                    {{1.50772, 0.0}, {0.696211, 0.0}},      {{4.36459, 0.0}, {0.240503, 0.0}},
                    {{4.29293, 0.0}, {0.244517, 0.0}},      {{8.32422, 0.0}, {0.126101, 0.0}},
                    {{3.60256, 0.0}, {0.291375, 0.0}},      {{2.5693, 0.0}, {0.408553, 0.0}},
                    {{24.0677, 0.0}, {0.0564046, 0.0}},     {{2.69169, 0.0}, {0.50434, 0.0}},
                    {{24.1375, 0.0}, {0.0562415, 0.0}},     {{8.74308, 0.0}, {0.155269, 0.0}},
                    {{1.94988, 0.0}, {0.696211, 0.0}},      {{5.64455, 0.0}, {0.240503, 0.0}},
                    {{5.55187, 0.0}, {0.244517, 0.0}},      {{10.7654, 0.0}, {0.126101, 0.0}},
                    {{4.65905, 0.0}, {0.291375, 0.0}},      {{3.32277, 0.0}, {0.408553, 0.0}},
                    {{12.5658, 0.0}, {0.0564046, 0.0}},     {{1.40534, 0.0}, {0.50434, 0.0}},
                    {{12.6023, 0.0}, {0.0562415, 0.0}},     {{4.56479, 0.0}, {0.155269, 0.0}},
                    {{1.01804, 0.0}, {0.696211, 0.0}},      {{2.94704, 0.0}, {0.240503, 0.0}},
                    {{2.89865, 0.0}, {0.244517, 0.0}},      {{5.62065, 0.0}, {0.126101, 0.0}},
                    {{2.4325, 0.0}, {0.291375, 0.0}},       {{1.73483, 0.0}, {0.408553, 0.0}},

                    {{1.82885, 0.0}, {0.64269, 0.0}},       {{1.60388, 0.0}, {0.732836, 0.0}},
                    {{1.90091, 0.0}, {0.618327, 0.0}},      {{1.82885, 0.0}, {0.70907, 0.0}},
                    {{1.60388, 0.0}, {0.808526, 0.0}},      {{1.90091, 0.0}, {0.68219, 0.0}},

                    {{0.593606, 0.0}, {1.93261, 0.0}},      {{0.65611, 0.0}, {1.7485, 0.0}},
                    {{0.764874, 0.0}, {1.49986, 0.0}},      {{0.685393, 0.0}, {1.93261, 0.0}},
                    {{0.757562, 0.0}, {1.7485, 0.0}},       {{0.883144, 0.0}, {1.49986, 0.0}}
                };

                const std::vector<complex<double>> li22_values = {
                    {0.28430906801447176, -0.008421755457385842}, {0.1211701267401113, -0.0030402737517390955}, {0.4637316172512538, -0.01664330974338289}, {0.15109917230063785, -0.003906047430641674}, {0.07030478034857879, -0.001677856023727695}, {0.2976134822080616, -0.008939134452426507}, {0.27734947745503336, -0.008156323078269169}, {0.370996577676471, -0.012042604160392885}, {0.35234426509832417, -0.011212030242349898}, {0.2103474924828026, -0.005773305141739673}, {0.1686890851453892, 0.0}, {0.07250655025895895, 0.0}, {0.2724553887314359, 0.0}, {0.09027818273134139, 0.0}, {0.04217689088655046, 0.0}, {0.17645752288754155, 0.0}, {0.16462027452348652, 0.0}, {0.21909408928814697, 0.0}, {0.2082909346398506, 0.0}, {0.1252939956470777, 0.0}, {0.2459232669771465, -0.002164265193420144}, {0.10505079394864358, -7.619819675261725E-4}, {0.4002053752913035, -0.004439758487501052}, {0.13094242031022185, -9.82965762801462E-4}, {0.06099686119240033, -4.1784356175606304E-4}, {0.2573845442234788, -0.0023026361750676113}, {0.23992551425145114, -0.0020934408896456855}, {0.3205397389568958, -0.003146593124554218}, {0.3044959188953915, -0.002918326930068194}, {0.18213414073753542, -0.0014655980914849683},
                    {-1.219922192476564, -0.5255127337596961}, {0.09950503550217693, -1.3545442497121158}, {-1.2201714255747822, -0.5244901353940187}, {-0.9823955657228463, -0.9710721910148715}, {0.6170423928968156, -1.1386663146730935}, {-0.7230742521340536, -1.1885044551510593}, {-0.7104473994097158, -1.196192924310304}, {-1.0639949677853298, -0.8675218112165057}, {-0.5620258240822353, -1.271876815909998}, {-0.19167159815889234, -1.3642922456436837}, {-1.6695598685250126, -0.5560888938280396}, {-0.43355433734919013, -1.8034456997887554}, {-1.669700141267774, -0.5549326909636257}, {-1.4808231520328492, -1.0845639940520926}, {0.1503791206551388, -1.8144613415073827}, {-1.2467749450729622, -1.37715870399393}, {-1.2350427069360435, -1.3884788499888525}, {-1.5506846311152631, -0.9561007218717168}, {-1.0953414184138168, -1.5072176699532478}, {-0.7330379127631468, -1.713135644945238}, {-0.7569375289097257, -0.4549781373386546}, {0.4896465862927395, -0.6288702673930138}, {-0.757314185312226, -0.4541632008510234}, {-0.4704690237974809, -0.7715764673833464}, {0.5738414761918529, -0.0495904989906628}, {-0.1999475837284327, -0.8718020777158744}, {-0.18739320948033755, -0.873817869124017}, {-0.5618541131649819, -0.7068091535952747}, {-0.043750606455733365, -0.882202650570478}, {0.28069339706696295, -0.7965552366833291},
                    {0.30481842380191715, -1.5010261170360355}, {0.550966830632813, -1.3988713402966413}, {0.2350884590619784, -1.5201111690956834}, {0.29466674343516086, -1.6918494909034492}, {0.5703852935885241, -1.58832334678286}, {0.21699866587164474, -1.710463215978975},
                    {0.29719243281141505, -0.0016922760453697723}, {0.34771731219875246, -0.0021551800434250284}, {0.4554604122714423, -0.003421408105465903}, {0.4579115618625682, -0.017465496251575632}, {0.5485225088151866, -0.02306130282590044}, {0.7673626298880905, -0.041190359917272046}
                };

                const double epsilon = 1e-12;
                test_region(x_y_points, li22_values, epsilon);
            }

            // Testing regions F, G and H
            {
                const std::vector<std::vector<complex<double>>> x_y_points = {
                    {{0.913148, 0.0}, {0.906048, 0.0}},     {{0.881196, 0.0}, {0.938901, 0.0}},
                    {{1.189, 0.0}, {0.70132, 0.0}},         {{0.768063, 0.0}, {1.0772, 0.0}},
                    {{1.12417, 0.0}, {0.735973, 0.0}},      {{0.913148, 0.0}, {1.00895, 0.0}},
                    {{0.881196, 0.0}, {1.04553, 0.0}},      {{1.189, 0.0}, {0.774868, 0.0}},
                    {{0.768063, 0.0}, {1.19954, 0.0}},      {{1.12417, 0.0}, {0.819559, 0.0}},
                    {{0.913148, 0.0}, {1.16872, 0.0}},      {{0.881196, 0.0}, {1.2111, 0.0}},
                    {{1.189, 0.0}, {0.897573, 0.0}},        {{0.768063, 0.0}, {1.38949, 0.0}},
                    {{1.12417, 0.0}, {0.949342, 0.0}},      {{0.913148, 0.0}, {1.40294, 0.0}},
                    {{0.881196, 0.0}, {1.2839, 0.0}},       {{1.189, 0.0}, {1.14163, 0.0}},
                    {{0.768063, 0.0}, {1.0357, 0.0}},       {{1.12417, 0.0}, {1.20748, 0.0}}
                };

                const std::vector<complex<double>> li22_values = {
                    {0.4419958572037096, 0.0}, {0.40310586453967534, 0.0}, {0.738927787468957, -0.48492324493010136}, {0.3013035215086935, 0.0}, {0.7561067400674579, -0.35035852312356913}, {0.5045165399680003, 0.0}, {0.45975365575848176, 0.0}, {0.8299504630169596, -0.5576409766147369}, {0.34300324804620463, 0.0}, {0.8613316133568851, -0.40995236316805067}, {0.6143785369243933, -0.0011143627827529957}, {0.5586461062108317, -8.441583062034771E-4}, {0.9844796563156657, -0.7023749302111061}, {0.4147674045806786, -4.1896848466985295E-4}, {1.0330581576029418, -0.5271373662176849}, {0.802233113938307, -0.036131185122208524}, {0.6078776559155337, -0.004872831208819474}, {1.2391387406613381, -1.0635597474929155}, {0.28769637316218544, 0.0}, {1.3303883308111266, -0.8464867294055418}
                };

                const double epsilon = 1e-12;
                test_region(x_y_points, li22_values, epsilon);
            }

        }

} multiplepolylogarithm_test;