//  $Id: external.cpp 116 2017-09-21 16:19:22Z dw $
//
//  Copyright (C) 2017 School of Pharmacy and Biomedical Sciences, University of Portsmouth.
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

#include "dash/external.h"

#include <boost/asio.hpp>
#include <boost/process.hpp>

#include <string>
#include <system_error>
#include <vector>

namespace ba = boost::asio;
namespace bp = boost::process;

namespace external
{
int
execute(std::string path, std::vector<std::string> args,
        std::string std_in, std::string& std_out, std::string& std_err,
        std::error_code& ec)
{
    ba::io_service ios;
    std::future<void> fut_in;
    std::future<std::string> fut_out;
    std::future<std::string> fut_err;
    ba::streambuf in_buf;
    std::ostream ostr(&in_buf);

    ostr << std_in << std::endl;

    bp::child c(path, args,
                bp::std_in < in_buf > fut_in,
                bp::std_out > fut_out,
                bp::std_err > fut_err,
                ios, ec);

    if (!ec) {
        ios.run();
        std_out = fut_out.get();
        std_err = fut_err.get();
    }

    return c.exit_code();
}

bool
save(std::string s, std::string filename)
{
    if (s.empty()) return true;
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << s;
    return ofs.good();
}

bool
cpptraj(std::string in, std::string& out, std::string& err, std::string& msg)
{
    boost::filesystem::path cpptraj_path = bp::search_path("cpptraj");

    if (cpptraj_path.empty()) {
        msg = "cpptraj not found in PATH";
        return false;
    }

    std::vector<std::string> args = {"--interactive", "--log", "/dev/null"};
    std::error_code ec;

    int rtn = execute(cpptraj_path.string(), args, in, out, err, ec);

    if (ec) {
        msg = "error_code: " + std::string(ec.category().name()) + ": " + ec.message();
    }

    return (rtn == 0);
}
} // namespace external
