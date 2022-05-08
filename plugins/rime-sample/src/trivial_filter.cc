//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2011-12-12 GONG Chen <chen.sst@gmail.com>
//
#include <rime/candidate.h>
#include <rime/segmentation.h>
#include <rime/common.h>
#include <rime/filter.h>
#include "trivial_filter.h"
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
namespace sample {

TrivialFilter::TrivialFilter(const Ticket& ticket)
    : Filter(ticket) {
}

an<Translation> TrivialFilter::Apply(an<Translation> translation, CandidateList* candidates) {
  string output = Translate(translation->Peek()->text());
  if (output.empty()) {
    return translation;
  }
  auto candidate = New<ShadowCandidate>(
      translation->Peek(),
      "cloud",
      output,
      "cloud");
  return New<UniqueTranslation>(candidate);
}

string TrivialFilter::Translate(const string& input) {
  string result = string();
  auto scheme_host_port = "http://39.97.255.81:18888";
  auto res = httplib::Client(scheme_host_port).Get(("/test?string=" + input).c_str());
  if (res) {
    json j = json::parse(res->body);
    if (j["data"] != input) {
      result = j["data"].get<std::string>();
    }
  }
  return result;
}

}  // namespace sample
