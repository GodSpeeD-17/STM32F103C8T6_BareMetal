# !/bin/bash

ROOT_DIR=$1
MAIN_C=$2

# Track visited files to prevent infinite recursion
declare -A VISITED
DEPENDENT_SRCS=()

resolve_deps() {
    local file=$1
    [[ -n "${VISITED[$file]}" ]] && return
    VISITED["$file"]=1

    # If this is a header in Driver/Inc, add corresponding Src files
    if [[ $file == "$ROOT_DIR/BareMetal/Driver/"*"/Inc/"* ]]; then
        local driver_dir=$(dirname "$(dirname "$file")")
        local src_files=("$driver_dir/Src/"*.c)
        
        for src in "${src_files[@]}"; do
            if [[ -f "$src" ]]; then
                DEPENDENT_SRCS+=("$src")
            fi
        done
    fi

    # Process all includes in this file
    grep -oE '#include\s*["<][^">]+[">]' "$file" 2>/dev/null | while read -r include; do
        local header=$(echo "$include" | cut -d'"' -f2 | cut -d'<' -f2 | cut -d'>' -f1)
        
        # Search for header in project
        local found_header=$(find "$ROOT_DIR" -name "$header" -print -quit 2>/dev/null)
        
        if [[ -n "$found_header" && -z "${VISITED[$found_header]}" ]]; then
            resolve_deps "$found_header"
        fi
    done
}

### Main Execution ###

# Verify inputs
if [[ ! -f "$MAIN_C" ]]; then
    echo "Error: Main source file not found at $MAIN_C" >&2
    exit 1
fi

# Process main.c and its dependencies
resolve_deps "$MAIN_C"

# Output unique source files
printf "%s\n" "${DEPENDENT_SRCS[@]}" | sort -u