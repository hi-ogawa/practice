def get_request(url):
    import urllib.request
    req = urllib.request.Request(url)
    req.add_header('User-agent', 'Mozilla/5.0')
    with urllib.request.urlopen(req) as f:
        return f.read().decode('utf-8')


def parse_codeforces(content):
    import re
    it = re.finditer('<pre>(.*?)</pre>', content, re.DOTALL)
    ls = ["\n".join(m.group(1).split('<br />')).strip() for m in it]
    return list(zip(ls[0::2], ls[1::2]))


def parse_atcoder(content):
    import re
    tests = []
    i = 1
    while re.search(f"Sample Input {i}", content):
        s1 = content.split(f"Sample Input {i}")[1]
        s2 = content.split(f"Sample Output {i}")[1]
        m1 = re.search('<pre>(.*?)</pre>', s1, re.DOTALL)
        m2 = re.search('<pre>(.*?)</pre>', s2, re.DOTALL)
        t1 = m1.group(1).strip()
        t2 = m2.group(1).strip()
        tests.append([t1, t2])
        i += 1
    return tests


def parse_hackerrank(content):
    import re
    ls = []
    if re.search('<code>', content):
        # Simple test format
        it = re.finditer('<code>(.*?)</code>', content, re.DOTALL)
        ls = [m.group(1).strip() for m in it]
    else:
        # Complex test format (all lines wrapped by <span>)
        it = re.finditer('<pre>(.*?)</pre>', content, re.DOTALL)
        for m in it:
            mit = re.finditer('<span(.*?)>(.*?)</span>', m.group(1), re.DOTALL)
            ls.append('\n'.join(mm.group(2) for mm in mit).strip())
    return list(zip(ls[0::2], ls[1::2]))


def get_tests(url):
    import re
    content = get_request(url)
    if re.search('codeforces\.com', url):
        tests = parse_codeforces(content)
    elif re.search('atcoder\.jp', url):
        tests = parse_atcoder(content)
    elif re.search('hackerrank\.com', url):
        tests = parse_hackerrank(content)
    else:
        raise RuntimeError('Unknown url')
    return tests


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
