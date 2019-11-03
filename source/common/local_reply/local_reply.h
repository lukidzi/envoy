#pragma once

#include <string>
#include <vector>

#include "envoy/http/codes.h"

#include "common/access_log/access_log_formatter.h"

namespace Envoy {
namespace LocalReply {

class ResponseRewriter {
public:
  ResponseRewriter(absl::optional<uint32_t> response_code);

  void rewrite(Http::Code& code);

private:
  absl::optional<uint32_t> response_code_;
};

using ResponseRewriterPtr = std::unique_ptr<ResponseRewriter>;

class ResponseMapper {
public:
  ResponseMapper(AccessLog::FilterPtr&& filter, ResponseRewriterPtr&& rewriter);

  bool match(const Http::HeaderMap* request_headers, const Http::HeaderMap* response_headers,
             const Http::HeaderMap* response_trailers, const StreamInfo::StreamInfo& stream_info);

  void rewrite(Http::Code& status_code);

private:
  AccessLog::FilterPtr filter_;
  ResponseRewriterPtr rewriter_;
};

using ResponseMapperPtr = std::unique_ptr<ResponseMapper>;

class LocalReply {
public:
  LocalReply(std::list<ResponseMapperPtr> mappers, AccessLog::FormatterPtr&& formatter,
             std::string content_type);

  /**
   * Run through defined in configuration filters and for first matched filter rewrite status code.
   * @param request_headers supplies the information about request headers required by filters
   * @param stream_info supplies the information about streams required by filters.
   * @param code status code which will be rewrited
   */
  void matchAndRewrite(const Http::HeaderMap* request_headers,
                       const Http::HeaderMap* response_headers,
                       const Http::HeaderMap* response_trailers,
                       const StreamInfo::StreamInfo& stream_info, Http::Code& code);

  std::string format(const Http::HeaderMap* request_headers,
                     const Http::HeaderMap* response_headers,
                     const Http::HeaderMap* response_trailers,
                     const StreamInfo::StreamInfo& stream_info, const absl::string_view& body);

  void insertContentHeaders(const absl::string_view& body, Http::HeaderMap* headers);

private:
  std::list<ResponseMapperPtr> mappers_;
  AccessLog::FormatterPtr formatter_;
  std::string content_type_;
};

using LocalReplyPtr = std::unique_ptr<LocalReply>;

} // namespace LocalReply
} // namespace Envoy
