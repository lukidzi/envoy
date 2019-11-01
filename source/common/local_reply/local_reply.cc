#include "common/local_reply/local_reply.h"

#include <string>
#include <vector>

#include "envoy/config/filter/network/http_connection_manager/v2/http_connection_manager.pb.validate.h"

#include "common/access_log/access_log_formatter.h"

namespace Envoy {
namespace LocalReply {

// std::unordered_map<std::string, std::string> convertJsonFormatToMap(ProtobufWkt::Struct json_format) {
//   std::unordered_map<std::string, std::string> output;
//   for (const auto& pair : json_format.fields()) {
//     if (pair.second.kind_case() != ProtobufWkt::Value::kStringValue) {
//       throw EnvoyException("Only string values are supported in the JSON access log format.");
//     }
//     output.emplace(pair.first, pair.second.string_value());
//   }
//   return output;
// }

// AccessLog::FormatterPtr createFormatter(const Protobuf::Message& config,
//                                               Server::Configuration::FactoryContext& context) {
//   const auto& local_reply_config = MessageUtil::downcastAndValidate<const envoy::config::filter::network::http_connection_manager::v2::LocalReplyConfig&>(
//           config, context.messageValidationVisitor());
//   AccessLog::FormatterPtr formatter;

//   if (local_reply_config.has_format()) {
//     if (local_reply_config.format().format_case() == envoy::type::StringOrJson::kStringFormat) {
//       formatter = std::make_unique<Envoy::AccessLog::FormatterImpl>(local_reply_config.format().string_format());
//     } else if (local_reply_config.format().format_case() == envoy::type::StringOrJson::kJsonFormat){
//       auto json_format_map = convertJsonFormatToMap(local_reply_config.format().json_format());
//       formatter = std::make_unique<AccessLog::JsonFormatterImpl>(json_format_map);
//     } else {
//       formatter = AccessLog::AccessLogFormatUtils::defaultAccessLogFormatter();
//     }
//   } else {
//     formatter = AccessLog::AccessLogFormatUtils::defaultAccessLogFormatter();
//   }

//   return formatter;
// }

  // ResponseMapper::ResponseMapper(AccessLog::FilterPtr&& filter, ResponseRewriter rewriter)
  // : filter_(std::move(filter)), rewriter_(rewriter){

  // };

  // LocalReply::LocalReply(const envoy::config::filter::network::http_connection_manager::v2::LocalReplyConfig& local_reply_config){
  //   if(local_reply_config.mapper().empty()){
  //     std::cout<< "Test value";
  //   } else {
  //     std::cout<< "Not empty";
  //   }
  // };
  
} // namespace LocalReply
} // namespace Envoy
