def _version_reader_impl(repository_ctx):
    # 1. Point to your text file outside / inside the build space
    # (Using the label pointing to the root version.txt)
    version_file_path = repository_ctx.path(repository_ctx.attr.version_file)
    
    # 2. Read and strip whitespaces/newlines from the file
    version_string = repository_ctx.read(version_file_path).strip()
    
    # 3. Write a small .bzl file that exposes this string
    repository_ctx.file(
        "version.bzl",
        content = 'VERSION = "{}"\n'.format(version_string)
    )

# Define the repository rule
version_repo_rule = repository_rule(
    implementation = _version_reader_impl,
    attrs = {
        "version_file": attr.label(mandatory = True, allow_single_file = True),
    },
)

def _version_extension_impl(module_ctx):
    # Execute the rule to spin up an external repository (@project_version)
    version_repo_rule(
        name = "project_version",
        version_file = "//:VERSION.txt",
    )

# Define the module extension
version_ext = module_extension(
    implementation = _version_extension_impl,
)