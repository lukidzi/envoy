licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "local_reply_lib",
    srcs = ["local_reply.cc"],
    hdrs = ["local_reply.h"],
    deps = [
        "//source/common/access_log:access_log_formatter_lib",
        "@envoy_api//envoy/config/filter/network/http_connection_manager/v2:pkg_cc_proto",
    ],
)
