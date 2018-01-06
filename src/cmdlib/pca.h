//  $Id: pca.h 130 2017-11-28 14:41:54Z dw $
//
//  Principal Components Analysis class header
//
//  Copyright (C) 2015 Centre for Molecular Design, University of Portsmouth.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef CMDLIB_PCA_H
#define CMDLIB_PCA_H

#include "cmdlib/cmdlib.h"
#undef Success
#include <Eigen/Dense>
#include <vector>

/// \ingroup CppLib
//@{

namespace cmdlib
{

    /// The PCA class performs Principal Components Analysis.

    /// PCA ...
    class PCA
    {
    public:
        /// Constructor for a data matrix \em x.

        /// The data is always mean-centred before the components are calculated.
        /// If autoscale = true, the columns of \em x are standardized to unit variance.
        PCA(const Matrix& x, bool autoscale=true);

        /// Default virtual destructor.
        virtual ~PCA(){}

        /// The number of cases (rows) in the data matrix.
        int n() const { return n_; }

        /// The number of variables (columns) in the data matrix.
        int p() const { return p_; }

        /// The component variances, in decreasing order.
        const Vector& var() const { return var_; }

        /// The variance of the ith component.
        double var(int i) const { return var_(i); }

        /// The component loadings.

        /// The ith column contains the coefficients, or loadings, for the ith component.
        /// The columns are the eigenvectors of the correlation matrix of \em x if autoscale = true,
        /// and the eigenvectors of the covariance matrix of \em x if autoscale = false.
        /// The components are ordered by decreasing variance.
        const Matrix& coefficients() const { return coefficients_; }

        /// The coefficients of the ith component.
        //const Vector& coefficients(int i) const { return coefficients_.col(i); }

        /// The proportion of variance explained by the components.
        const Vector& explained() const { return explained_; }

        /// The proportion of variance explained by the ith component.
        double explained(int i) const { return explained_(i); }

        /// The cumulative proportion of variance explained by the components.
        const Vector& cumulative() const { return cumulative_; }

        /// The cumulative proportion of variance explained by the ith component.
        double cumulative(int i) const { return cumulative_(i); }

        /// The column means of the the data matrix, used to mean-centre the data.
        const Vector& centre() const { return centre_; }

        /// The scaling used to standardize the columns of the data matrix.

        /// The standard deviations of the the data matrix, if autoscale = true; otherwise a vector of ones.
        const Vector& scale() const { return scale_; }

        /// The principal component scores.
        const Matrix& scores() const { return scores_; }

        /// The projection of the data matrix \em m onto the principal components.
        Matrix predict(const Matrix& m) const;

        /// The variance, proportion of variance explained and the cumulative
        /// proportion of variance explained for all the components.
        virtual std::string report_summary() const { return report_summary(p_); }

        /// The variance, proportion of variance explained and the cumulative
        /// proportion of variance explained for the first ncomp components.
        virtual std::string report_summary(int ncomp) const;

        /// A formatted string containing the coefficients (eigenvectors)
        /// for all the components.
        virtual std::string report_coefficients() const { return report_coefficients(p_); }

        /// A formatted string containing the coefficients (eigenvectors)
        /// for the first ncomp components.
        virtual std::string report_coefficients(int ncomp) const;

        /// A formatted string containing the scores for all the components.
        virtual std::string report_scores() const { return report_scores(p_); }

        /// A formatted string containing the scores for the first ncomp components.
        virtual std::string report_scores(int ncomp) const;

        /// A formatted string containing the centring and scaling used.
        virtual std::string report_scaling() const;

        /// The concatenation of report_summary, report_coefficients,
        /// report_scores and report_scaling for all the components.
        virtual std::string report() const { return report(p_); }

        /// The concatenation of report_summary, report_coefficients,
        /// report_scores and report_scaling for the first ncomp components.
        virtual std::string report(int ncomp) const;

    private:
        // inputs
        int n_;
        int p_;
        bool autoscale_;

        // outputs
        Vector centre_;
        Vector scale_;
        Matrix coefficients_;
        Vector var_;
        Vector explained_;
        Vector cumulative_;
        Matrix scores_;
    };

} // namespace cmdlib

//@}

#endif // CMDLIB_PCA_H
