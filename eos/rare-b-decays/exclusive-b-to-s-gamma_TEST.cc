/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Danny van Dyk
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

#include <test/test.hh>
#include <eos/observable.hh>
#include <eos/rare-b-decays/exclusive-b-to-s-gamma.hh>
#include <eos/utils/complex.hh>
#include <eos/utils/wilson-polynomial.hh>

#include <array>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

using namespace test;
using namespace eos;

class BToKstarGammaTest :
    public TestCase
{
    public:
        BToKstarGammaTest() :
            TestCase("b_to_kstar_gamma_test")
        {
        }

        virtual void run() const
        {
            /* QCDF */

            // Standard Model
            {
                Parameters p = Parameters::Defaults();
                p["c1"] = -0.32300000;
                p["c2"] = +1.00931000;
                p["c3"] = -0.00522869;
                p["c4"] = -0.08794730;
                p["c5"] = +0.00037476;
                p["c6"] = +0.00105859;
                p["Abs{c7}"] = 0.331;
                p["Arg{c7}"] = M_PI;
                p["Abs{c7'}"] = 0.008; // m_s(m_b) / m_b(m_b) * Abs{c7} = 105 / 4200 * Abs{c7}
                p["Arg{c7'}"] = M_PI;
                p["c8"] = -0.181;
                // PDG 2010 CKM parameters
                p["CKM::A"] = 0.812;
                p["CKM::lambda"] = 0.22543;
                p["CKM::rhobar"] = 0.144;
                p["CKM::etabar"] = 0.342;
                p["decay-constant::B_d"] = 0.200;
                p["mass::b(MSbar)"] = 4.2;

                Options oo;
                oo.set("model", "WilsonScan");
                oo.set("form-factors", "KMPW2010");

                BToKstarGamma d(p, oo);

                const double eps = 1e-4;

                TEST_CHECK_RELATIVE_ERROR(d.branching_ratio(),             +4.21541e-5, eps);
                TEST_CHECK_RELATIVE_ERROR(d.branching_ratio_cp_averaged(), +4.21541e-5, eps);
                TEST_CHECK_RELATIVE_ERROR(d.s_kstar_gamma(),               -2.98715e-2, eps);
                TEST_CHECK_NEARLY_EQUAL(d.c_kstar_gamma(),                  0.0,        eps);
            }

            // Benchmark Point (CPV)
            {
                Parameters p = Parameters::Defaults();
                p["c1"] = -0.32300000;
                p["c2"] = +1.00931000;
                p["c3"] = -0.00522869;
                p["c4"] = -0.08794730;
                p["c5"] = +0.00037476;
                p["c6"] = +0.00105859;
                p["Abs{c7}"] = 0.331;
                p["Arg{c7}"] = -M_PI / 2.0;
                p["Abs{c7'}"] = 0.008; // m_s(m_b) / m_b(m_b) * Abs{c7} = 105 / 4200 * Abs{c7}
                p["Arg{c7'}"] = -M_PI / 2.0;
                p["c8"] = -0.181;
                // PDG 2010 CKM parameters
                p["CKM::A"] = 0.812;
                p["CKM::lambda"] = 0.22543;
                p["CKM::rhobar"] = 0.144;
                p["CKM::etabar"] = 0.342;
                p["decay-constant::B_d"] = 0.200;
                p["mass::b(MSbar)"] = 4.2;

                Options oo;
                oo.set("model", "WilsonScan");
                oo.set("form-factors", "KMPW2010");

                BToKstarGamma d(p, oo);

                const double eps = 1e-4;

                TEST_CHECK_RELATIVE_ERROR(d.branching_ratio(),             +3.77936e-5, eps);
                TEST_CHECK_RELATIVE_ERROR(d.branching_ratio_cp_averaged(), +3.45819e-5, eps);
                TEST_CHECK_RELATIVE_ERROR(d.s_kstar_gamma(),               +3.66040e-2, eps);
                TEST_CHECK_NEARLY_EQUAL(d.c_kstar_gamma(),                 -9.28720e-2, eps);
            }
        }
} b_to_kstar_gamma_test;