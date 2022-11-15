#include <rime/common.h>
#include <rime/context.h>
#include <rime/engine.h>
#include <rime/processor.h>
#include <rime/candidate.h>
#include <rime/key_event.h>
#include <rime/translation.h>
#include <rime/menu.h>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace rime;

class TodoProcessor : public Processor {
 public:
  explicit TodoProcessor(const Ticket& ticket)
    : Processor(ticket) {
    Context* context = engine_->context();
    update_connection_ = context->update_notifier()
      .connect([this](Context* ctx) { OnUpdate(ctx); });
  }

  virtual ~TodoProcessor() {
    update_connection_.disconnect();
  }

  virtual ProcessResult ProcessKeyEvent(const KeyEvent& key_event) {
    if (key_event.release() || key_event.ctrl() || key_event.alt())
      return kNoop;
    if(key_event.keycode() == XK_semicolon) {
      auto context = engine_->context();
      auto candidate = context->GetSelectedCandidate();
      auto scheme_host_port = "http://39.97.255.81:18888";
      auto res = httplib::Client(scheme_host_port).Get(("/test?string=" + candidate->text()).c_str());
      if (res) {
        json j = json::parse(res->body);
        auto segment = context->composition().back();
        auto result = New<SimpleCandidate>("cloud", segment.start, segment.end, j["data"].get<std::string>(), "(cloud)");
        segment.menu->ReplaceCandidates(candidate, result);
        return kAccepted;
      }
    }
    return kNoop;
  }

 private:
  void OnUpdate(Context* ctx) {}

  connection update_connection_;
};
