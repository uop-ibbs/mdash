//  $Id: log.cpp 107 2017-06-29 12:23:44Z dw $
//
//  Copyright (C) 2014 Centre for Molecular Design, University of Portsmouth.
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

#include "dash/log.h"

Log::Log(wxTextCtrl *ctrl, wxLog *old, bool verbose) {
    ctrl_ = ctrl;
    old_ = old;
    SetVerbose(verbose);
}

Log::~Log() {
    wxLog::SetActiveTarget(old_);
}

void
Log::DoLogRecord(wxLogLevel level,
                 const wxString& msg,
                 const wxLogRecordInfo& info)
{
    // log messages to history panel
    // pass everything else to default gui logger
    if (level == wxLOG_Message) {
        ctrl_->AppendText(wxString::Format("%9s %s", wxDateTime(info.timestamp).FormatISOTime(), msg + '\n'));
    } else {
        old_->LogRecord(level, msg, info);
        old_->Flush();
        return;
    }
}
