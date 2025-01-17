/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Frederik Beaujean
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

#ifndef EOS_GUARD_SRC_STATISTICS_LOG_POSTERIOR_TEST_HH
#define EOS_GUARD_SRC_STATISTICS_LOG_POSTERIOR_TEST_HH 1

#include <eos/statistics/log-posterior.hh>
#include <eos/utils/observable_stub.hh>
#include <eos/utils/qualified-name.hh>
#include <test/test.hh>

using namespace test;

namespace eos
{
    struct TestObservable :
        public Observable
    {
            Parameters p;

            Kinematics k;

            Options o;

            QualifiedName n, mass_name;

            UsedParameter mass;

            TestObservable(const Parameters & p, const Kinematics & k, const QualifiedName & mass_name) :
                p(p),
                k(k),
                o(),
                n(mass_name),
                mass_name(mass_name),
                mass(p[mass_name.str()], *this)
            {
            }

            virtual ~TestObservable()
            {
            }

            virtual double evaluate() const
            {
                return mass();
            }

            virtual ObservablePtr clone() const
            {
                return ObservablePtr(new TestObservable(p.clone(), k.clone(), mass_name));
            }

            virtual ObservablePtr clone(const Parameters & parameters) const
            {
                return ObservablePtr(new TestObservable(parameters, k.clone(), mass_name));
            }

            virtual Parameters parameters()
            {
                return p;
            }

            virtual Kinematics kinematics()
            {
                return k;
            }

            virtual Options options()
            {
                return o;
            }

            const QualifiedName & name() const
            {
                return n;
            }

            void set_option(const std::string & key, const std::string & value = "")
            {
                o.declare(key, value);
            }
    };

    struct AbsoluteTestObservable :
        public TestObservable
    {
            AbsoluteTestObservable(const Parameters & p, const Kinematics & k, const QualifiedName & mass_name) :
                TestObservable(p, k, mass_name)
            {
            }

            virtual ~AbsoluteTestObservable()
            {
            }

            virtual double evaluate() const
            {
                return std::fabs(mass());
            }

            virtual ObservablePtr clone() const
            {
                return ObservablePtr(new AbsoluteTestObservable(p.clone(), k.clone(), mass_name));
            }

            virtual ObservablePtr clone(const Parameters & parameters) const
            {
                return ObservablePtr(new AbsoluteTestObservable(parameters, k.clone(), mass_name));
            }
    };

    /*
     * Create log posterior with gaussian likelihood and gaussian prior
     * The posterior is also a Gaussian with central value 4.3
     * and standard deviation sqrt(0.005)=0.070710678118654752
     *
     * flat = true turns Gaussian prior into flat prior
     */
    LogPosterior make_log_posterior(bool flat)
    {
        Parameters parameters = Parameters::Defaults();

        LogLikelihood llh(parameters);
        llh.add(ObservablePtr(new ObservableStub(parameters, "mass::b(MSbar)")), 4.1, 4.2, 4.3);

        LogPriorPtr prior = flat ?
            LogPrior::Flat(parameters, "mass::b(MSbar)", ParameterRange{3.7, 4.9} ) :
            LogPrior::CurtailedGauss(parameters, "mass::b(MSbar)", ParameterRange{3.7, 4.9}, 4.3, 4.4, 4.5);

        LogPosterior result(llh);
        result.add(prior);

        return result;
    }
}

#endif
