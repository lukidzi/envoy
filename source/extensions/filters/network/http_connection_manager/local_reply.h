#pragma once

#include <string>
#include <vector>
#include <list>
#include "absl/strings/string_view.h"

#include "envoy/config/filter/network/http_connection_manager/v2/http_connection_manager.pb.validate.h"
#include "common/common/logger.h"
#include "envoy/http/codes.h"
#include "common/common/enum_to_int.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace HttpConnectionManager {


    // bool isMatching(Http::Code status, absl::string_view body) const{
    //     if(status_ != 0 && status_ != enumToInt(status)){
    //         return false;
    //     }
    //     if(message_.empty() == true){
    //         return true;
    //     }
    //     if(message_.empty() == false && body.find(message_) != absl::string_view::npos){
    //         return true;
    //     }

    //     return false;
    // };

    // void rewriteStatusCodeIfMatches (Http::Code& code, absl::string_view& body) const{
    //     for (auto it = match_rewrite_pair_list_.begin(); it != match_rewrite_pair_list_.end();) {
    //         bool matches = it->first.isMatching(code, body);
    //         if( matches ){
    //             code = static_cast<Http::Code>(it->second.status_);
    //             break;
    //         }
    //         it++;
    //     }
    // }


struct LocalReplyMatcher {
    uint32_t status_;
    std::string message_;
};

struct LocalReplyRewriter {
    uint32_t status_;
};

class SendLocalReplyConfig{
public:
    SendLocalReplyConfig (const envoy::config::filter::network::http_connection_manager::v2::HttpConnectionManager::SendLocalReplyConfig& config);

private:
    std::list<std::pair<LocalReplyMatcher, LocalReplyRewriter>> match_rewrite_pair_list_;
};

using SendLocalReplyConfigConstPtr = std::unique_ptr<const SendLocalReplyConfig>;

} // namespace Common
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
