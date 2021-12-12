#
# Download tests from online judges
#

def get_cookie(hostname):
    import subprocess
    command = f"python misc/cookie_chrome.py {hostname} --format=header"
    proc = subprocess.run(command.split(), check=True, capture_output=True)
    assert proc.returncode == 0
    return proc.stdout.strip()


def get_request(url, with_cookie=False):
    from urllib.request import Request, urlopen
    from urllib.parse import urlparse
    hostname = urlparse(url).hostname
    cookie = get_cookie(hostname) if with_cookie else ""
    user_agent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.75 Safari/537.36"
    req = Request(url, headers={"cookie": cookie, "user-agent": user_agent})
    with urlopen(req) as f:
        return f.read().decode()


def get_request_browserless(url):
    # Cf. https://docs.browserless.io/docs/faq.html#how-can-i-try-out-the-service
    import urllib.request, urllib.parse, json
    data = json.dumps(dict(url=url)).encode('utf-8')
    req = urllib.request.Request('https://chrome.browserless.io/content', data=data)
    req.add_header('Content-Type', 'application/json')
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


def parse_codechef(content):
    import re
    # TODO: there seem other patterns (e.g. without <code>)
    it = re.finditer('<pre(.*?)><code(.*?)>(.*?)</code></pre>', content, re.DOTALL)
    ls = [m.group(3).strip() for m in it]
    return list(zip(ls[0::2], ls[1::2]))


def parse_library_checker(content):
    import re
    content = content.split("Sample")[1]
    it = re.finditer('<pre>(.*?)</pre>', content, re.DOTALL)
    ls = [m.group(1).strip() for m in it]
    return list(zip(ls[0::2], ls[1::2]))


def parse_cses(content):
    import re
    it = re.finditer('<code>(.*?)</code>', content, re.DOTALL)
    ls = [''.join(m.group(1).split('<br />')).strip() for m in it]
    return list(zip(ls[0::2], ls[1::2]))


def get_tests(url):
    import re
    if re.search('codeforces\.com', url):
        content = get_request(url)
        tests = parse_codeforces(content)
    elif re.search('atcoder\.jp', url):
        content = get_request(url)
        tests = parse_atcoder(content)
    elif re.search('hackerrank\.com', url):
        content = get_request(url)
        tests = parse_hackerrank(content)
    elif re.search('codechef\.com', url):
        content = get_request_browserless(url)
        tests = parse_codechef(content)
    elif re.search('old\.yosupo\.jp', url):
        content = get_request(url)
        tests = parse_library_checker(content)
    elif re.search('cses\.fi', url):
        content = get_request(url)
        tests = parse_cses(content)
    else:
        raise RuntimeError('Unknown url')
    return tests


TEST_FORMAT = """
%%%% begin
{}
%%%%
{}
%%%% end
""".strip()


def main(url, quiet):
    if not quiet:
        print(f":: Downloading... [{url}]")
    tests = get_tests(url)
    if not quiet:
        print(f":: Download success")
    print("\n\n".join(TEST_FORMAT.format(x, y) for x, y in tests))


def main_cli():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("url", type=str)
    parser.add_argument("--quiet", action="store_true", default=False)
    main(**parser.parse_args().__dict__)


if __name__ == "__main__":
    main_cli()
