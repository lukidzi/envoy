// #include "extensions/filters/network/http_connection_manager/local_reply.h"


// #include "envoy/config/filter/network/http_connection_manager/v2/http_connection_manager.pb.validate.h"

// namespace Envoy {
// namespace Extensions {
// namespace NetworkFilters {
// namespace HttpConnectionManager {

// SendLocalReplyConfig::SendLocalReplyConfig(const envoy::config::filter::network::http_connection_manager::v2::HttpConnectionManager::SendLocalReplyConfig& config){
//     if(config.config_size() > 0){
//       for(auto& match_rewrite_config : config.config()){
//             std::pair<LocalReplyMatcher, LocalReplyRewriter> pair = std::make_pair(
//                   LocalReplyMatcher {match_rewrite_config.match().status(), match_rewrite_config.match().body()},
//                   LocalReplyRewriter {match_rewrite_config.rewriter().status()});
//             match_rewrite_pair_list_.emplace_back(pair);  
//       }
//    }
// }

// } // namespace HttpConnectionManager
// } // namespace NetworkFilters
// } // namespace Extensions
// } // namespace Envoy

