import re

def align_macros(lines):
    pattern = re.compile(r'^\s*#define\s+(\w+)\s+(.*)$')
    matches = [pattern.match(line) for line in lines]
    max_macro_len = max((len(m.group(1)) for m in matches if m), default=0)

    aligned_lines = []
    for line in lines:
        match = pattern.match(line)
        if match:
            name, value = match.groups()
            padding = ' ' * (max_macro_len - len(name) + 1)
            aligned_lines.append(f"#define {name}{padding}{value}")
        else:
            aligned_lines.append(line)
    return aligned_lines

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python align_macros.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    with open(filename, 'r') as f:
        lines = f.readlines()

    aligned = align_macros(lines)

    with open(filename, 'w') as f:
        f.writelines(line + '\n' if not line.endswith('\n') else line for line in aligned)

    print(f"✅ Done aligning macros in: {filename}")

