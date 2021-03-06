# Borrowed from
# https://github.com/bazelbuild/rules_go/blob/master/proto/toolchain.bzl. This
# does some magic munging to remove workspace prefixes from output paths to
# convert path as understood by Bazel into paths as understood by protoc.
def _proto_path(proto):
    """
    The proto path is not really a file path
    It's the path to the proto that was seen when the descriptor file was generated.
    """
    path = proto.path
    root = proto.root.path
    ws = proto.owner.workspace_root
    if path.startswith(root):
        path = path[len(root):]
    if path.startswith("/"):
        path = path[1:]
    if path.startswith(ws):
        path = path[len(ws):]
    if path.startswith("/"):
        path = path[1:]
    return path

def api_proto_plugin_impl(target, ctx, output_group, mnemonic, output_suffixes):
    # Compute output files from the current proto_library node's dependencies.
    transitive_outputs = depset(transitive = [dep.output_groups[output_group] for dep in ctx.rule.attr.deps])
    proto_sources = target[ProtoInfo].direct_sources

    # If this proto_library doesn't actually name any sources, e.g. //api:api,
    # but just glues together other libs, we just need to follow the graph.
    if not proto_sources:
        return [OutputGroupInfo(**{output_group: transitive_outputs})]

    # Figure out the set of import paths. Ideally we would use descriptor sets
    # built by proto_library, which avoid having to do nasty path mangling, but
    # these don't include source_code_info, which we need for comment
    # extractions. See https://github.com/bazelbuild/bazel/issues/3971.
    import_paths = []
    for f in target[ProtoInfo].transitive_sources.to_list():
        if f.root.path:
            import_path = f.root.path + "/" + f.owner.workspace_root
        else:
            import_path = f.owner.workspace_root
        if import_path:
            import_paths += [import_path]

    # The outputs live in the ctx.label's package root. We add some additional
    # path information to match with protoc's notion of path relative locations.
    outputs = []
    for output_suffix in output_suffixes:
        outputs += [ctx.actions.declare_file(ctx.label.name + "/" + _proto_path(f) +
                                             output_suffix) for f in proto_sources]

    # Create the protoc command-line args.
    ctx_path = ctx.label.package + "/" + ctx.label.name
    output_path = outputs[0].root.path + "/" + outputs[0].owner.workspace_root + "/" + ctx_path
    args = ["-I./" + ctx.label.workspace_root]
    args += ["-I" + import_path for import_path in import_paths]
    args += ["--plugin=protoc-gen-api_proto_plugin=" + ctx.executable._api_proto_plugin.path, "--api_proto_plugin_out=" + output_path]
    args += [_proto_path(src) for src in target[ProtoInfo].direct_sources]
    ctx.actions.run(
        executable = ctx.executable._protoc,
        arguments = args,
        inputs = target[ProtoInfo].transitive_sources,
        tools = [ctx.executable._api_proto_plugin],
        outputs = outputs,
        mnemonic = mnemonic,
        use_default_shell_env = True,
    )

    transitive_outputs = depset(outputs, transitive = [transitive_outputs])
    return [OutputGroupInfo(**{output_group: transitive_outputs})]

def api_proto_plugin_aspect(tool_label, aspect_impl):
    return aspect(
        attr_aspects = ["deps"],
        attrs = {
            "_protoc": attr.label(
                default = Label("@com_google_protobuf//:protoc"),
                executable = True,
                cfg = "exec",
            ),
            "_api_proto_plugin": attr.label(
                default = Label(tool_label),
                executable = True,
                cfg = "exec",
            ),
        },
        implementation = aspect_impl,
    )
