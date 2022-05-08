//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2011-12-12 GONG Chen <chen.sst@gmail.com>
//
#ifndef TRIVIAL_FILTER_H_
#define TRIVIAL_FILTER_H_

#include <string>
#include <rime/common.h>
#include <rime/translation.h>
#include <rime/filter.h>

namespace sample {

using namespace rime;

class TrivialFilter : public Filter {
 public:
  TrivialFilter(const Ticket& ticket);

  virtual an<Translation> Apply(an<Translation> translation,
                                        CandidateList* candidates);
 private:
  string Translate(const string& input);
};

}  // namespace sample

#endif  // TRIVIAL_FILTER_H_
