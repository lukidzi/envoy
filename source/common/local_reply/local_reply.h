#pragma once

#include <string>
#include <vector>
#include "envoy/config/filter/network/http_connection_manager/v2/http_connection_manager.pb.validate.h"

#include "common/access_log/access_log_formatter.h"

namespace Envoy {
namespace LocalReply {

class ResponseRewriter {
  public:
    ResponseRewriter(absl::optional<uint32_t> response_code) : response_code_(response_code) {}
  
  private:
    absl::optional<uint32_t> response_code_;
};

using ResponseRewriterPtr = std::unique_ptr<ResponseRewriter>;

struct ResponseMapper {
  public:
   ResponseMapper() = default;
   ResponseMapper(AccessLog::FilterPtr&& filter, ResponseRewriterPtr&& rewriter) {
     filter_ = std::move(filter); 
     rewriter_ = std::move(rewriter);
   }

   bool match(const Http::HeaderMap* request_headers,
             const Http::HeaderMap* response_headers,
             const Http::HeaderMap* response_trailers,
             const StreamInfo::StreamInfo& stream_info){
        return filter_->evaluate(stream_info, *request_headers, *response_headers, *response_trailers );
   }
   
  private:
    AccessLog::FilterPtr filter_;
    ResponseRewriterPtr rewriter_;
};

using ResponseMapperPtr = std::unique_ptr<ResponseMapper>;

class LocalReply : Logger::Loggable<Logger::Id::http> {
public:
  LocalReply() = default;

  LocalReply(std::list<ResponseMapperPtr> mappers, AccessLog::FormatterPtr&& formatter) {
    mappers_ = std::move(mappers);
    formatter_ = std::move(formatter);
  } 

  void test( const Http::HeaderMap* request_headers,
             const Http::HeaderMap* response_headers,
             const Http::HeaderMap* response_trailers,
             const StreamInfo::StreamInfo& stream_info){
    for(auto& mapper: mappers_){
      // std::cout << "some test";
      ENVOY_LOG(info, "Testing some staff {}", mapper->match(request_headers, response_headers ,response_trailers,stream_info));
      // std::cout<< mapper->match(request_headers, response_headers ,response_trailers,stream_info);
    }
  }

private:
  std::list<ResponseMapperPtr> mappers_;
  AccessLog::FormatterPtr formatter_;
  
};

using LocalReplyPtr = std::unique_ptr<LocalReply>;

} // namespace LocalReply
} // namespace Envoy
