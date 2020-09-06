# WIP
#   hopefully something usable only with builtin library

def get_request(url):
    import urllib.request
    with urllib.request.urlopen(url) as f:
        return f.read().decode('utf-8')


def get_tests(url):
    import re
    content = get_request(url)
    it = re.finditer('<pre>(.*?)</pre>', content, re.DOTALL)
    ls = ["\n".join(m.group(1).split('<br />')).strip() for m in it]
    return list(zip(ls[0::2], ls[1::2]))


TEST_FORMAT = """\
%%%% begin
{}
%%%%
{}
%%%% end
"""

def main(url):
    print(f":: Downloading... [{url}]")
    tests = get_tests(url)
    print(f":: Download success")
    print()
    for inp, outp in tests:
        print(TEST_FORMAT.format(inp, outp))


def main_cli():
    import sys, argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("url", type=str)
    args = parser.parse_args()
    main(**args.__dict__)


if __name__ == "__main__":
    main_cli()
