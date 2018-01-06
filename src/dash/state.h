//  $Id: state.h 52 2015-07-20 14:16:45Z dw $
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

#ifndef DASH_STATE_H
#define DASH_STATE_H

#include <map>
#include <ostream>
#include <set>
#include <vector>

typedef std::vector<int> state;
typedef std::set<state> state_set;
typedef state_set::iterator state_set_iter;
typedef state_set::const_iterator state_set_const_iter;
typedef std::vector<state_set_const_iter> state_sequence;

struct StateData {
    int index;
    int freq;
    std::vector<int> bouts;
    std::vector<double> mean;
    std::vector<double> sdev;
    int frame;
    double rmsd;
};

class StateComparison {
 public:
    bool operator() (state_set_const_iter s1, state_set_const_iter s2) const {
        return *s1 < *s2;
    }
};

typedef std::map<state_set_const_iter, StateData, StateComparison> state_map;

struct RepexState {
    state_set_const_iter state;
    int freq;
    std::vector<double> mean;
    std::vector<double> sdev;
    int frame;
    double rmsd;

    RepexState(state_set_const_iter s, const StateData& sd) {
        state = s;
        freq = sd.freq;
        mean = sd.mean;
        sdev = sd.sdev;
        frame = sd.frame;
        rmsd = sd.rmsd;
    }
};

class RepexFreqComparison {
 public:
    bool operator() (const RepexState* s1, const RepexState* s2) const {
        return s1->freq > s2->freq;
    }
};

typedef std::vector<RepexState*> repex_state_set;
typedef repex_state_set::const_iterator repex_state_set_const_iter;

#endif // DASH_STATE_H
