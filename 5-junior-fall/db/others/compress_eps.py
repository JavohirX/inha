"""Compress ImageMagick EPS files in-place using run-length encoding (compression 1)."""

import os
import re
import sys
import tempfile


def compress_eps_rle(src_path: str) -> tuple[bool, str]:
    with open(src_path, "rb") as f:
        data = f.read()

    page = data.find(b"%%Page:")
    if page < 0:
        return False, "no %%Page marker"

    m = re.search(
        rb"DisplayImage\r?\n(?:[^\r\n]+\r?\n){3}(\d+) (\d+)\r?\n(\d+)\r?\n(\d+)\r?\n",
        data[page:],
    )
    if not m:
        return False, "unrecognized format"

    cols, rows, comp = int(m.group(1)), int(m.group(2)), int(m.group(4))
    if comp != 0:
        return False, "already compressed"

    img_start = page + m.end()
    end_marker = data.rfind(b"\nend\n")
    if end_marker < 0:
        return False, "no end marker"

    hexdata = b"".join(
        line.strip()
        for line in data[img_start:end_marker].splitlines()
        if line.strip() and not line.strip().startswith(b"%")
    )
    pixels = [hexdata[i : i + 6] for i in range(0, len(hexdata), 6)]
    if len(pixels) != cols * rows:
        return False, f"pixel mismatch ({len(pixels)} vs {cols * rows})"

    out_hex = bytearray()
    i = 0
    while i < len(pixels):
        j = i + 1
        while j < len(pixels) and pixels[j] == pixels[i] and (j - i) < 256:
            j += 1
        run = j - i
        out_hex.extend(pixels[i])
        out_hex.extend(f"{run - 1:02X}".encode())
        i = j

    lines = []
    line = []
    for c in out_hex:
        line.append(chr(c))
        if len(line) >= 76:
            lines.append("".join(line))
            line = []
    if line:
        lines.append("".join(line))
    new_img = ("\n".join(lines) + "\n").encode("ascii")

    params_start = page + m.start()
    params_end = page + m.end()
    params_new = data[params_start:params_end][:-3] + b"1\n"
    new_data = data[:params_start] + params_new + new_img + data[end_marker:]

    orig_size = len(data)
    new_size = len(new_data)
    if new_size >= orig_size:
        return False, "compression would not shrink file"

    dir_name = os.path.dirname(src_path) or "."
    fd, tmp = tempfile.mkstemp(suffix=".eps", dir=dir_name)
    os.close(fd)
    try:
        with open(tmp, "wb") as f:
            f.write(new_data)
        os.replace(tmp, src_path)
    except Exception:
        os.remove(tmp)
        raise

    pct = 100 * new_size / orig_size
    return True, f"{orig_size:,} -> {new_size:,} bytes ({pct:.1f}%)"


def main(root: str) -> int:
    files = []
    for dirpath, _, filenames in os.walk(root):
        for name in filenames:
            if name.lower().endswith(".eps"):
                files.append(os.path.join(dirpath, name))

    if not files:
        print("No .eps files found.")
        return 1

    ok_count = skip_count = 0
    saved = 0

    for path in sorted(files):
        rel = os.path.relpath(path, root)
        try:
            ok, msg = compress_eps_rle(path)
        except Exception as exc:
            print(f"FAIL  {rel}: {exc}")
            continue

        if ok:
            before_s, rest = msg.split(" -> ", 1)
            after_s = rest.split(" ", 1)[0]
            before, after = int(before_s.replace(",", "")), int(after_s.replace(",", ""))
            saved += before - after
            ok_count += 1
            print(f"OK    {rel}: {msg}")
        else:
            skip_count += 1
            print(f"SKIP  {rel}: {msg}")

    print(f"\nDone: {ok_count} compressed, {skip_count} skipped, {saved / 1024 / 1024:.1f} MB saved")
    return 0


if __name__ == "__main__":
    target = sys.argv[1] if len(sys.argv) > 1 else os.path.dirname(os.path.abspath(__file__))
    raise SystemExit(main(target))