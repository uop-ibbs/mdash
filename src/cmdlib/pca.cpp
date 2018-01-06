//  $Id: pca.cpp 116 2017-09-21 16:19:22Z dw $
//
//  Principal Components Analysis
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

#include "cmdlib/pca.h"
#include <iomanip>
#include <sstream>

namespace cmdlib
{

PCA::PCA(const Matrix& x, bool s) : autoscale_(s)
{
    /// \pre
    /// x.cols > 0
    CMDLIB_PRECONDITION( x.cols() > 0 );

    n_ = x.rows();
    p_ = x.cols();
    centre_ = x.colwise().mean();

    // mean-centred data
    Matrix xmc = x.rowwise() - centre_.transpose();

    if (autoscale_) {
        Eigen::ArrayXd s1 = xmc.cwiseProduct(xmc).colwise().sum();
        Eigen::ArrayXd s2 = xmc.colwise().sum();
        Eigen::ArrayXd var = (s1 - s2.square()/n_)/(n_-1);
        scale_ = var.sqrt();
        xmc = xmc.array().rowwise()/scale_.array().transpose();
    } else {
        scale_ = Vector::Ones(p_);
    }

    /*
      Matrix cov = (xmc.transpose() * xmc) / double (n_ - 1);
      Eigen::SelfAdjointEigenSolver<Matrix> solver_(cov);
      if (solver_.info() != Eigen::Success) abort();

      eigenvalues_ = solver_.eigenvalues().reverse();
      coefficients_ = solver_.eigenvectors().rowwise().reverse();
      scores_ = xmc * coefficients_;
      explained_ = 100 * eigenvalues_ / eigenvalues_.sum();
    */

    Eigen::JacobiSVD<Matrix> svd(xmc, Eigen::ComputeThinU | Eigen::ComputeThinV);
    var_ = svd.singularValues().array().square()/(n_-1);
    coefficients_ = svd.matrixV();
    scores_ = svd.matrixU()*svd.singularValues().asDiagonal();
    cumulative_ = explained_ = var_ / var_.sum();

    for (int i=1; i<explained_.size(); ++i) {
        cumulative_(i) = cumulative_(i-1) + cumulative_(i);
    }
}

Matrix
PCA::predict(const Matrix& m) const
{
    Matrix mcentred = m.rowwise() - centre_.transpose();
    Matrix mscaled = mcentred.array().rowwise()/scale_.array().transpose();
    return mscaled * coefficients_;
}

std::string
PCA::report_summary(int ncomp) const {
    CMDLIB_PRECONDITION(ncomp > 0 && ncomp <= p_);

    std::ostringstream os;

    os << std::fixed
       << std::setprecision(4)
       << "PCA Summary\n\n"
       << std::setw(22) << "PC1";

    for (int i=2; i<=ncomp; ++i) {
        os << std::setw(11) << "PC" << i;
    }

    os << "\nVariance  ";

    for (int i=0; i<ncomp; ++i) {
        os << std::setw(12) << var_(i);
    }

    os << "\nExplained ";

    for (int i=0; i<ncomp; ++i) {
        os << std::setw(12) << explained_(i);
    }

    os << "\nCumulative";

    for (int i=0; i<ncomp; ++i) {
        os << std::setw(12) << cumulative_(i);
    }

    os << "\n\n";

    return os.str();
}

std::string
PCA::report_coefficients(int ncomp) const {
    CMDLIB_PRECONDITION(ncomp > 0 && ncomp <= p_);

    std::ostringstream os;

    os << "PCA Coefficients\n\n";

    for (int i=1; i<=ncomp; ++i) {
        os << std::setw(11) << "PC" << i;
    }

    os << '\n'
       << std::scientific
       << std::setprecision(3);

    for (int i=0; i<p_; ++i) {
        for (int j=0; j<ncomp; ++j) {
            os << std::setw(12) << coefficients_(i,j);
        }

        os << '\n';
    }

    os << '\n';

    return os.str();
}

std::string
PCA::report_scores(int ncomp) const {
    CMDLIB_PRECONDITION(ncomp > 0 && ncomp <= p_);

    std::ostringstream os;

    os << "PCA Scores\n\n";

    for (int i=1; i<=ncomp; ++i) {
        os << std::setw(11) << "PC" << i;
    }

    os << '\n'
       << std::scientific
       << std::setprecision(3);

    for (int i=0; i<n_; ++i) {
        for (int j=0; j<ncomp; ++j) {
            os << std::setw(12) << scores_(i,j);
        }

        os << '\n';
    }

    os << '\n';

    return os.str();
}

std::string
PCA::report_scaling() const {
    std::ostringstream os;

    os << "PCA Centre\n\n";

    for (int i=1; i<=p_; ++i) {
        os << std::setw(11) << "PC" << i;
    }

    os << '\n'
       << std::scientific
       << std::setprecision(3);

    for (int i=0; i<p_; ++i) {
        os << std::setw(12) << centre_(i);
    }

    os  << "\n\n";

    if (autoscale_) {
        os << "PCA Scaling\n\n";

        for (int i=1; i<=p_; ++i) {
            os << std::setw(11) << "PC" << i;
        }

        os << '\n'
           << std::scientific
           << std::setprecision(3);

        for (int i=0; i<p_; ++i) {
            os << std::setw(12) << scale_(i);
        }

        os  << "\n\n";

    }

    return os.str();
}

std::string
PCA::report(int ncomp) const {
    CMDLIB_PRECONDITION(ncomp > 0 && ncomp <= p_);

    return report_summary(ncomp) + report_coefficients(ncomp) + report_scores(ncomp) + report_scaling();
}

} // namespace cmdlib
