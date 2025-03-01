import subprocess
import shutil
import os
import sys

BUILD_DIR = "bin"  # Output directory for binaries
DLL_SRC_DIR = "BuildSystem"  # Source directory for DLL
EXE_SRC_DIR = "."  # Root directory for EXE

def get_shared_lib_extension():
    """Returns the correct shared library extension based on the OS."""
    if sys.platform.startswith("win"):
        return ".dll"
    elif sys.platform.startswith("darwin"):
        return ".dylib"
    else:
        return ".so"

def RunOdinCompiler(args):
    """Runs the Odin compiler with the given arguments and shows real-time output."""
    if not shutil.which("odin"):
        print("Error: Odin compiler not found. Ensure 'odin' is installed and in PATH.", file=sys.stderr)
        return -1

    try:
        process = subprocess.Popen(
            ["odin"] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding="utf-8"
        )

        # Print Odin output in real-time
        for line in iter(process.stdout.readline, ""):
            print(line, end="", flush=True)

        # Print errors in real-time
        for line in iter(process.stderr.readline, ""):
            print(line, end="", file=sys.stderr, flush=True)

        process.stdout.close()
        process.stderr.close()
        return_code = process.wait()

        if return_code != 0:
            print(f"Odin compilation failed with error code {return_code}", file=sys.stderr)

        return return_code

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return -1

def BuildDLL():
    """Builds the project as a shared library (DLL/so/dylib) from the BuildSystem directory."""
    if not os.path.exists(BUILD_DIR):
        os.makedirs(BUILD_DIR)  # Ensure output directory exists
    os.chdir("BuildSystem")
    output_file = os.path.join("../", BUILD_DIR, "DSL_BUILD_SYS" + get_shared_lib_extension())
    
    print(f"Building DLL from '{DLL_SRC_DIR}' -> {output_file}")

    build_args = ["build", ".", "-out:" + output_file, "-build-mode:dynamic"]
    
    exit_code = RunOdinCompiler(build_args)

    if exit_code == 0:
        print(f"DLL Build Successful: {output_file}")
        os.chdir("../")
    else:
        print("DLL Build Failed!", file=sys.stderr)
        os.chdir("../")
        sys.exit(exit_code)

def BuildEXE():
    """Builds the project as an executable from the root directory."""
    if not os.path.exists(BUILD_DIR):
        os.makedirs(BUILD_DIR)  # Ensure output directory exists

    exe_extension = ".exe" if sys.platform.startswith("win") else ""
    output_file = os.path.join(BUILD_DIR, "dieselc" + exe_extension)

    print(f"Building EXE from '{EXE_SRC_DIR}' -> {output_file}")  # FIXED: Removed Unicode character

    build_args = ["build", EXE_SRC_DIR, "-out:" + output_file]
    
    exit_code = RunOdinCompiler(build_args)

    if exit_code == 0:
        print(f"EXE Build Successful: {output_file}")
    else:
        print("EXE Build Failed!", file=sys.stderr)
        sys.exit(exit_code)

if __name__ == "__main__":
    BuildDLL()
    BuildEXE()
